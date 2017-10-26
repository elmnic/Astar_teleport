#include "Hunter.h"


Hunter* Hunter::instance()
{
	static Hunter instance;
	return &instance;
}

Hunter::Hunter() :
	mPosition(0, 0),
	mTargetPosition(0, 0),
	mPatrolPosition(0, 0),
	mTargetPreviousPosition(-1, -1),
	mSizeXY(0, 0),
	mClock()
{
	mCurrentState = Patrol::instance();
	
	mMap = Map::instance();
	mSolver = Solver::instance();

	// The four corners of the map
	mPatrol.push_back(sf::Vector2i(0, 0));
	mPatrol.push_back(sf::Vector2i(mMap->getWidth() - 1, 0));
	mPatrol.push_back(sf::Vector2i(mMap->getWidth() - 1, mMap->getHeight() - 1));
	mPatrol.push_back(sf::Vector2i(0, mMap->getHeight() - 1));

	mPatrolPosition = mPatrol[0];
}


Hunter::~Hunter()
{
}

void Hunter::update(sf::RenderWindow & window, sf::Vector2i targetPos)
{
	mTargetPosition = targetPos;
	if (mCurrentState)
		mCurrentState->execute(this);
}

void Hunter::render(sf::RenderWindow & window)
{
	if (mCurrentState)
		mCurrentState->render(this, window);

	float sizeX = window.getSize().x / mMap->getWidth();
	float sizeY = window.getSize().y / mMap->getHeight();
	mSizeXY = sf::Vector2f(sizeX, sizeY);
	sf::Vector2f pos = sf::Vector2f(mPosition.x * sizeX + sizeX / 2, mPosition.y * sizeY + sizeY / 2);

	sf::CircleShape circle(sizeX / 3);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(pos);
	circle.setFillColor(sf::Color(12, 157, 57));
	window.draw(circle);

}

void Hunter::changeState(BaseState * newState)
{
	if (mCurrentState && newState)
	{
		mCurrentState->exit(this);

		mCurrentState = newState;

		mCurrentState->enter(this);
	}
}


void Hunter::findPath(sf::Vector2i target)
{
	mTargetPreviousPosition = mTargetPosition;
	mPath = mSolver->solve(mPosition, target);
	mPathIterator = 0;
}

void Hunter::move(float delay)
{
	if (mClock.getElapsedTime().asMilliseconds() > delay)
	{
		if (!mPath.empty())
		{
			mPosition = mPath[mPathIterator]->getState();

			if (mPathIterator < mPath.size() - 1)
				mPathIterator++;

			mClock.restart();
		}
	}

}

bool Hunter::spottedTarget(sf::Vector2i target, float threshold)
{
	float distance = std::sqrtf(  std::powf(target.x - mPosition.x, 2)
								+ std::powf(target.y - mPosition.y, 2));
	return distance < threshold;
}

bool Hunter::reachedTarget(sf::Vector2i target)
{
	return mPosition == target;
}

bool Hunter::lostTarget(sf::Vector2i target, float threshold)
{
	float distance = std::sqrtf(  std::powf(target.x - mPosition.x, 2)
								+ std::powf(target.y - mPosition.y, 2));
	return distance > threshold;
}

void Hunter::nextPatrol()
{
	mCurrentPatrol++;
	if (mCurrentPatrol >= 4)
		mCurrentPatrol = 0;
	mPatrolPosition = mPatrol[mCurrentPatrol];
}
