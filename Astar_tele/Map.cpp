#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}

void Map::initialize(int fieldSize)
{
	mStartState.clear();

	mStartState.resize(fieldSize, std::vector<int>(fieldSize, 0));

	int blankTile = fieldSize * fieldSize;
	int fieldValue = 0;

	/* Fill the matrix with 1, 2, 3, ... depending on fieldSize
							3, 4, 5, ...
							6, 7, 0, ...
	*/

	for (int i = 0; i < fieldSize; i++)
	{
		for (int j = 0; j < fieldSize; j++)
		{
			if (blankTile != (i + 1) * (j + 1))
				mStartState[i][j] = ++fieldValue;
		}
	}
	mCurrentState = mStartState;
}

void Map::restart()
{
	initialize(mCurrentState.size());
}

StateStruct::State Map::getGoalState()
{
	return mStartState;
}

StateStruct::State Map::getCurrentState()
{
	return mCurrentState;
}
void Map::updateCurrentState(StateStruct::State newState)
{
	if (newState != StateStruct::State(NULL))
		mCurrentState = newState;
}

void Map::printMap(StateStruct::State map)
{
	for (int row = 0; row < map.size(); row++)
	{
		for (int col = 0; col < map[0].size(); col++)
		{
			std::cout << map[row][col] << " ";
		}
		std::cout << std::endl;
	}
}

void Map::shuffleMap()
{
	mShuffling = true;
	int seed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() / 100;
	srand(seed);
	StateStruct::State state;
	for (int i = 0; i < 1000; i++)
	{
		int randomVal = rand();
		switch (randomVal % 4)
		{
		case 0:
			updateCurrentState(move(Map::up, mCurrentState));
			break;
		case 1:
			updateCurrentState(move(Map::down, mCurrentState));
			break;
		case 2:
			updateCurrentState(move(Map::left, mCurrentState));
			break;
		case 3:
			updateCurrentState(move(Map::right, mCurrentState));
			break;
		default:
			break;
		}
	}

	mShuffling = false;
}

StateStruct::State Map::move(direction dir, StateStruct::State currentState)
{

	StateStruct::State returnState;
	returnState = currentState;

	int spaceRow = 0, spaceCol = 0;
	locateSpace(spaceRow, spaceCol, currentState);

	int tileRow = spaceRow;
	int tileCol = spaceCol;

	// Determine which tile is to be moved
	switch (dir)
	{
	case Map::up:
		tileRow = tileRow + 1;
		break;
	case Map::down:
		tileRow = tileRow - 1;
		break;
	case Map::left:
		tileCol = tileCol + 1;
		break;
	case Map::right:
		tileCol = tileCol - 1;
		break;
	default:
		break;
	}

	// If tile is on the map
	if (tileCol >= 0 && tileCol < currentState.size() &&
		tileRow >= 0 && tileRow < currentState.size())
	{

		// Move the tile into the empty block
		returnState[spaceRow][spaceCol] = returnState[tileRow][tileCol];
		returnState[tileRow][tileCol] = 0;
		return returnState;
	}

	// Else return NULL State
	return StateStruct::State(NULL);


	//if (!mShuffling)
	//	correctPercentage();

}

void Map::locateSpace(int & iRow, int & iCol, StateStruct::State state)
{

	for (int row = 0; row < state.size(); row++)
	{
		for (int col = 0; col < state[0].size(); col++)
		{
			if (state[row][col] == 0)
			{
				iRow = row;
				iCol = col;
			}
		}
	}

	//std::cout << "Space is at: " << iRow << ", " << iCol << std::endl;

}
