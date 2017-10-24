#pragma once

#include <vector>
#include <SFML\System.hpp>
#include "Map.h"
#include "Solver.h"

class Agent
{
public:

	enum direction { up, down, left, right };
	Agent();
	~Agent();

	// Returns the cost of the tile to move into
	int move(direction dir);

	sf::Vector2i getPosition() { return mPosition; }

private:
	sf::Vector2i mPosition;
	Map* mMap;
	Solver* mSolver;

	std::vector<Node*> mPath;
};

