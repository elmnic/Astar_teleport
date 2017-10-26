#include "HunterStates.h"
#include "Hunter.h"



Patrol* Patrol::instance()
{
	static Patrol instance;
	return &instance;
}

void Patrol::enter(Hunter* hunter)
{
	std::cout << "Patrolling\n";
	hunter->findPath(hunter->mPatrolPosition);
}

void Patrol::execute(Hunter* hunter)
{
	// Find path to next checkpoint
	if (hunter->reachedTarget(hunter->mPatrolPosition))
	{
		hunter->nextPatrol();
		hunter->findPath(hunter->mPatrolPosition);
	}
	// Move toward checkpoint
	else
	{
		hunter->move(mPatrolSpeed);
	}

	// Initiate hunt
	if (hunter->spottedTarget(hunter->mTargetPosition, mPatrolSight))
	{
		hunter->changeState(Hunt::instance());
	}
}

void Patrol::render(Hunter* hunter, sf::RenderWindow& window)
{
	sf::Vector2f pos = sf::Vector2f(hunter->mPosition.x * hunter->mSizeXY.x + hunter->mSizeXY.x / 2,
									hunter->mPosition.y * hunter->mSizeXY.y + hunter->mSizeXY.y / 2);
	sf::CircleShape circle(hunter->mSizeXY.x * mPatrolSight);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(pos);
	circle.setFillColor(sf::Color(255, 255, 0, 90));
	window.draw(circle);
}

void Patrol::exit(Hunter* hunter)
{

}




Hunt* Hunt::instance()
{
	static Hunt instance;
	return &instance;
}

void Hunt::enter(Hunter* hunter)
{
	std::cout << "Hunting\n";
	hunter->findPath(hunter->mTargetPosition);
}

void Hunt::execute(Hunter* hunter)
{
	hunter->move(mHuntSpeed);
	// Find path as long as target is in sight
	if (!hunter->lostTarget(hunter->mTargetPosition, mHuntSight) &&
		 hunter->mTargetPosition != hunter->mTargetPreviousPosition) // Only search if target moved
	{
		hunter->findPath(hunter->mTargetPosition);
	}
	
	// If hunter reached last seen location, start patrolling
	if (hunter->reachedTarget(hunter->mTargetPreviousPosition))
	{
		hunter->changeState(Patrol::instance());
	}
}

void Hunt::render(Hunter* hunter, sf::RenderWindow& window)
{
	sf::Vector2f pos = sf::Vector2f(hunter->mPosition.x * hunter->mSizeXY.x + hunter->mSizeXY.x / 2,
									hunter->mPosition.y * hunter->mSizeXY.y + hunter->mSizeXY.y / 2);
	sf::CircleShape circle(hunter->mSizeXY.x * mHuntSight);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(pos);
	circle.setFillColor(sf::Color(255, 0, 0, 90));
	window.draw(circle);
}

void Hunt::exit(Hunter* hunter)
{

}
