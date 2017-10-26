#include "Agent.h"


Agent* Agent::instance()
{
	static Agent instance;
	return &instance;
}

Agent::Agent(): mPosition()
{
	mMap = Map::instance();
	mSolver = Solver::instance();
	mPosition = sf::Vector2i(mMap->getWidth() - 1, 0);
	findPath(mMap->getGoal());
}


Agent::~Agent()
{
}

void Agent::update(sf::RenderWindow & window)
{
}

void Agent::render(sf::RenderWindow & window)
{
	float sizeX = window.getSize().x / mMap->getWidth();
	float sizeY = window.getSize().y / mMap->getHeight();
	sf::Vector2f pos = sf::Vector2f(mPosition.x * sizeX + sizeX / 2, mPosition.y * sizeY + sizeY / 2);

	sf::CircleShape circle(sizeX / 3);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(pos);
	circle.setFillColor(sf::Color::Black);
	window.draw(circle);
}

void Agent::move(Agent::direction dir)
{
	int returnWeight = 0;
	sf::Vector2i previousPosition = mPosition;
	switch (dir)
	{
	case Agent::up:
		if (mPosition.y > 0)
			mPosition.y--;
		break;
	case Agent::down:
		if (mPosition.y < mMap->getHeight() - 1)
			mPosition.y++;
		break;
	case Agent::left:
		if (mPosition.x > 0)
			mPosition.x--;
		break;
	case Agent::right:
		if (mPosition.x < mMap->getWidth() - 1)
			mPosition.x++;
		break;
	default:
		break;
	}

	if (mMap->getID(mPosition) == Map::tileID::wall)
		mPosition = previousPosition;

	if (mMap->getID(mPosition) == Map::tileID::teleport)
		mPosition = mMap->findOtherTeleport(mPosition);

	// A* to goal
	findPath(mMap->getGoal());
}

void Agent::findPath(sf::Vector2i target)
{
	//mPath = mSolver->solve(mPosition, target);
}
