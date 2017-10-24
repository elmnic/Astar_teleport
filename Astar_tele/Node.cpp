#include "Node.h"



Node::Node(StateStruct::State state, Node* parent, int cost) :
	mState(state),
	mParent(parent),
	pathCost(cost)
{
	heuristicCost = heuristic();
	totalCost = pathCost + heuristicCost;
}


Node::~Node()
{
	clear();
}

void Node::expandChildren()
{
	Map map;
	// Iterate through the four possible directions
	for (int i = 0; i < 4; i++)
	{

		// Create new state by making a move in a direction
		//std::cout << "Move to be made: " << static_cast<Map::direction>(i) << std::endl;
		StateStruct::State newState = map.move(static_cast<Map::direction>(i), mState);

		// If parent exists and newState is the same as the parent's state, then skip
		if (mParent != NULL)
		{
			if (StateStruct::compare(newState, mParent->getState()))
			{
				//std::cout << "New state is parent. Skip" << std::endl;
				continue;
			}
		}
		
		//std::cout << "New State: \n";
		//Map::printMap(newState);

		// If the move is valid, add it to the child nodes
		if (newState != StateStruct::State(NULL))
		{
			//std::cout << "Added child to neighbours" << std::endl;
			mChildren.push_back(new Node(newState, this, pathCost + 1));
			//std::cout << "Child cost: " << mChildren.back()->pathCost + mChildren.back()->heuristicCost << std::endl;
		}
	}

}

// Calculates the cumulative manhattan distance for all values on the board
int Node::heuristic()
{
	int fieldSize = mState.size() * mState.size();

	// Search for targetValue and calc manhattan distance from target position
	int targetValue = 1;
	bool foundTarget = false;
	int totalCost = 0;

	// Manhattan distance
	while (targetValue < fieldSize)
	{
		int targetPosX = (targetValue - 1) / (int)mState.size();
		int targetPosY = (targetValue - 1) % (int)mState.size();
		int actualPosX;
		int actualPosY;
		for (int i = 0; i < mState.size(); i++)
		{
			for (int j = 0; j < mState.size(); j++)
			{
				if (mState[i][j] == targetValue)
				{
					actualPosX = i;
					actualPosY = j;
					int manhDis = std::abs(targetPosX - actualPosX) + std::abs(targetPosY - actualPosY);
					totalCost += manhDis;
					//std::cout << "Calculated cost for value " << targetValue << ": " << manhDis << std::endl << std::endl;
					targetValue++;
					foundTarget = true;
					break;
				}
			}
			if (foundTarget)
				break;
		}
		foundTarget = false;
	}

	return totalCost;
}

void Node::reconstructPath(std::vector<Node*>& cameFrom)
{
	// Add the parent's state as long as there exist a parent. 
	if (mParent != NULL) {
		mParent->reconstructPath(cameFrom);
	}

	// If parent doesn't exist, add this. Will be the final element in the vector
	cameFrom.push_back(this);
}

void Node::clear()
{
	mChildren.clear();
}


