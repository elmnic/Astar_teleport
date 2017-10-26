#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <array>
#include <iostream>
#include <time.h>
#include <chrono>
#include "StateStruct.h"

class Map
{
public:

	enum direction { up, down, left, right};
	enum tileID { empty, agent, wall, teleport, goal, expensive, bestPath};
	static void printMap(std::vector<std::vector<int>> map);

	static Map* instance();
	~Map();

	void update(sf::RenderWindow &window);
	void render(sf::RenderWindow &window);

	StateStruct::State move(direction dir, StateStruct::State currentState);
	
	void initialize(int fieldSize);
	void shuffleMap();
	void locateSpace(int & iRow, int & iCol, StateStruct::State state);
	void restart();

	int getHeight() { return mMap[0].size(); }
	int getWidth() { return mMap.size(); }

	sf::Vector2i getGoal();
	int getWeight(sf::Vector2i position);
	int getID(sf::Vector2i position) { return mMap[position.y][position.x]; }
	sf::Vector2i findOtherTeleport(sf::Vector2i fromPos);


	StateStruct::State getGoalState();
	StateStruct::State getCurrentState();

	void updateCurrentState(StateStruct::State newState);

private:
	Map();

	bool mShuffling = false;

	// 0: empty, 1: agent, 2: wall, 3: teleport, 4: goal, 5: expensive path, 6: best path outline
	std::vector<std::vector<int>> mMap = {
	{ 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0 },
	{ 0, 0, 0, 0, 2, 0, 2, 5, 5, 5, 0, 0, 5, 5, 3, 0, 0, 0, 0, 5 },
	{ 0, 0, 0, 2, 0, 0, 2, 5, 5, 5, 0, 0, 5, 5, 0, 0, 0, 0, 5, 5 },
	{ 0, 5, 5, 2, 0, 0, 2, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 0, 0, 0, 2, 0, 0, 2, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 5, 0, 2, 0, 0, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5 },
	{ 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 5, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 },
	{ 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0 },
	{ 0, 0, 0, 2, 0, 0, 2, 5, 5, 5, 0, 0, 0, 2, 0, 0, 2, 5, 5, 5 },
	{ 0, 0, 0, 2, 0, 0, 2, 5, 0, 0, 0, 0, 0, 2, 0, 0, 2, 5, 5, 5 },
	{ 0, 0, 2, 2, 2, 2, 2, 0, 0, 5, 2, 2, 2, 2, 0, 0, 2, 5, 5, 5 },
	{ 0, 0, 3, 2, 0, 0, 2, 0, 5, 5, 0, 0, 0, 2, 0, 0, 2, 5, 5, 5 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};

	StateStruct::State mCurrentState;
	StateStruct::State mStartState;

};

