#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "Solver.h"
#include "Agent.h"
#include "Hunter.h"


class Game
{
public:
	Game();
	~Game();

	// Starting point
	void run();

private:
	
	void update();
	void render();
	void clear();
	
	sf::RenderWindow mWindow;

	Agent* mAgent;
	Hunter* mHunter;
	Solver* mSolver;
	Map* mMap;

	bool mRenderClosed = false;
	bool mRenderOpen = false;
};

