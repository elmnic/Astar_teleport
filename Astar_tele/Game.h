#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "Solver.h"
#include "Agent.h"


class Game
{
public:
	Game();
	~Game();

	// Starting point
	void run();

private:
	
	
	void render();
	void clear();
	
	sf::RenderWindow mWindow;

	Agent* mAgent;
};

