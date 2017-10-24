#include "Map.h"


Map::Map()
{
	//printMap(mMap);
}


Map::~Map()
{
}

void Map::initialize(int fieldSize)
{
	//srand(NULL);
	//mStartState.clear();

	//mStartState.resize(fieldSize, std::vector<int>(fieldSize, 0));

	//int blankTile = fieldSize * fieldSize;
	//int fieldValue = 0;


	//// Randomize map
	//for (int i = 0; i < fieldSize; i++)
	//{
	//	for (int j = 0; j < fieldSize; j++)
	//	{
	//		mStartState[i][j] = rand() % 3 + 1;
	//	}
	//}

	//mCurrentState = mStartState;
}

void Map::restart()
{
	//initialize(mCurrentState.size());
}

sf::Vector2i Map::getGoal()
{
	sf::Vector2i goalPos;
	for (int i = 0; i < getWidth(); i++)
	{
		for (int j = 0; j < getHeight(); j++)
		{
			if (mMap[j][i] == tileID::goal)
			{
				goalPos = sf::Vector2i(i, j);
				break;
			}
		}
	}
	return goalPos;
}

int Map::getWeight(sf::Vector2i position)
{
	int tileID = mMap[position.y][position.x];
	switch (tileID)
	{
	case 0: // Empty
		return 5;
		break;
	case 1: // Agent
		return 0;
		break;
	case 2: // Wall
		return 100;
		break;
	case 3: // Teleport
		return 7;
		break;
	case 4: // Goal
		return 5;
		break;
	case 5: // Expensive path
		return 10;
		break;
	case 6: // Path outline
		return 0;
		break;
	default:
		return 0;
		break;
	}
}

sf::Vector2i Map::findOtherTeleport(sf::Vector2i fromPos)
{
	sf::Vector2i otherPos;

	for (int i = 0; i < getWidth(); i++)
	{
		for (int j = 0; j < getHeight(); j++)
		{
			if (mMap[j][i] == tileID::teleport && (i != fromPos.x || j != fromPos.y))
			{
				otherPos = sf::Vector2i(i, j);
				std::cout << "X: " << i << " Y: " << j << std::endl;
				break;
			}
		}
	}

	return otherPos;
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
	/*if (newState != StateStruct::State(NULL))
		mCurrentState = newState;*/
}

void Map::printMap(std::vector<std::vector<int>> map)
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

	// Determine which tile is to be moved
	//switch (dir)
	//{
	//case Map::up:
	//	tileRow = tileRow + 1;
	//	break;
	//case Map::down:
	//	tileRow = tileRow - 1;
	//	break;
	//case Map::left:
	//	tileCol = tileCol + 1;
	//	break;
	//case Map::right:
	//	tileCol = tileCol - 1;
	//	break;
	//default:
	//	break;
	//}

	//// If tile is on the map
	//if (tileCol >= 0 && tileCol < currentState.size() &&
	//	tileRow >= 0 && tileRow < currentState.size())
	//{

	//	// Move the tile into the empty block
	//	returnState[spaceRow][spaceCol] = returnState[tileRow][tileCol];
	//	returnState[tileRow][tileCol] = 0;
	//	return returnState;
	//}

	// Else return NULL State
	return StateStruct::State();
}

void Map::locateSpace(int & iRow, int & iCol, StateStruct::State state)
{

	/*for (int row = 0; row < state.size(); row++)
	{
		for (int col = 0; col < state[0].size(); col++)
		{
			if (state[row][col] == 0)
			{
				iRow = row;
				iCol = col;
			}
		}
	}*/

	//std::cout << "Space is at: " << iRow << ", " << iCol << std::endl;

}
