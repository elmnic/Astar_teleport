#pragma once

#include "BaseState.h"
#include "HunterStates.h"
#include "Map.h"
#include "Solver.h"

class Hunter
{
public:
	static Hunter* instance();
	~Hunter();

	void update(sf::RenderWindow &window, sf::Vector2i targetPos);
	void render(sf::RenderWindow &window);

	void changeState(BaseState* newState);

	void findPath(sf::Vector2i target);
	void move(float delay);
	bool spottedTarget(sf::Vector2i target, float threshold);
	bool reachedTarget(sf::Vector2i target);
	bool lostTarget(sf::Vector2i target, float threshold);

	void nextPatrol();
	
	int mCurrentPatrol = 0;
	std::vector<sf::Vector2i> mPatrol;

	// Two different targets depending on state
	sf::Vector2i mPosition;
	sf::Vector2i mTargetPosition;
	sf::Vector2i mTargetPreviousPosition;
	sf::Vector2i mPatrolPosition;

	sf::Vector2f mSizeXY;
private:
	Hunter();
	BaseState* mCurrentState;

	sf::Clock mClock;


	Map*	mMap;
	Solver* mSolver;

	std::vector<Node*> mPath;

	int mPathIterator = 0;
};

