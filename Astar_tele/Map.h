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
	Map();
	~Map();

	void initialize(int fieldSize);
	static void printMap(StateStruct::State map);
	void shuffleMap();
	StateStruct::State move(direction dir, StateStruct::State currentState);
	void locateSpace(int & iRow, int & iCol, StateStruct::State state);
	void restart();

	StateStruct::State getGoalState();
	StateStruct::State getCurrentState();

	void updateCurrentState(StateStruct::State newState);


private:

	bool mShuffling = false;

	// Default arrays
	StateStruct::State mField3x3 = {{{ 1, 2, 3 },
						{ 4, 5, 6 },
						{ 7, 8, 0 }}};

	StateStruct::State mField4x4 = {{{ 1,  2,  3,  4  },
						{ 5,  6,  7,  8  },
						{ 9,  10, 11, 12 },
						{ 13, 14, 15, 0  }}};

	StateStruct::State mCurrentState;
	StateStruct::State mStartState;

};

