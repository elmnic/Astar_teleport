#pragma once
#include "BaseState.h"

class Hunter;

class Patrol : public BaseState
{
public:
	static Patrol* instance();
	virtual void enter(Hunter* Hunter);
	virtual void execute(Hunter* Hunter);
	virtual void render(Hunter*, sf::RenderWindow& window);
	virtual void exit(Hunter* Hunter);
private:
	Patrol() {}
	Patrol(const Patrol&);
	Patrol& operator=(const Patrol&);

	// Variables for patrol state
	float mPatrolSpeed = 500.0f;
	float mPatrolSight = 5;
};


class Hunt : public BaseState
{
public:
	static Hunt* instance();
	virtual void enter(Hunter* Hunter);
	virtual void execute(Hunter* Hunter);
	virtual void render(Hunter*, sf::RenderWindow& window);
	virtual void exit(Hunter* Hunter);
private:
	Hunt() {}
	Hunt(const Hunt&);
	Hunt& operator=(const Hunt&);

	// Variables for hunt state
	float mHuntSpeed = 250.0f;
	float mHuntSight = 10;
};
