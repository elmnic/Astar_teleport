#pragma once

#include <vector>
#include <SFML\System.hpp>
#include "Map.h"
#include "Solver.h"

class Agent
{
public:
	static Agent* instance();
	enum direction { up, down, left, right };
	~Agent();

	void update(sf::RenderWindow &window);
	void render(sf::RenderWindow &window);

	// Returns the cost of the tile to move into
	void move(direction dir);
	sf::Vector2i getPosition() { return mPosition; }

private:
	Agent();

	void findPath(sf::Vector2i target);

	sf::Vector2i mPosition;
	Map* mMap;
	Solver* mSolver;

	std::vector<Node*> mPath;
};

