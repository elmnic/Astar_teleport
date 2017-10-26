#include "Node.h"



Node::Node(StateStruct::State state, Node* parent, int cost) :
	mState(state),
	mParent(parent),
	pathCost(cost)
{
	mMap = Map::instance();
	heuristicCost = heuristic();
	totalCost = pathCost + heuristicCost;
}


Node::~Node()
{
	//clear();
}

void Node::expandChildren()
{
	// Iterate through the four possible directions
	for (int i = 0; i < 4; i++)
	{
		// Create new state by making a move in a valid direction
		StateStruct::State newState = mState;
		int weight = 0;
		switch (static_cast<Map::direction>(i))
		{
		case Map::direction::up:
			if (mState.y > 0)
				newState.y--;
			break;
		case Map::direction::down:
			if (mState.y < mMap->getHeight() - 1)
				newState.y++;
			break;
		case Map::direction::left:
			if (mState.x > 0)
				newState.x--;
			break;
		case Map::direction::right:
			if (mState.x < mMap->getWidth() - 1)
				newState.x++;
			break;
		default:
			break;
		}

		if (mMap->getID(newState) == Map::tileID::wall)
			continue; // Skip this node if position is wall

		if (mMap->getID(newState) == Map::tileID::teleport)
			newState = mMap->findOtherTeleport(newState);
		weight = mMap->getWeight(newState);

		//StateStruct::State newState = map.move(static_cast<Map::direction>(i), mState);

		// If parent exists and newState is the same as the parent's state, then skip
		if (mParent != NULL)
		{
			if (StateStruct::compare(newState, mParent->getState()))
			{
				continue;
			}
		}

		// If the move is valid, add it to the child nodes
		mChildren.push_back(new Node(newState, this, pathCost + weight));
	}

}

// Calculates the pythagorean distance
float Node::heuristic()
{
	sf::Vector2i goalPos = mMap->getGoal();
	return std::sqrtf(std::powf(goalPos.x - mState.x, 2) + std::powf(goalPos.y - mState.y, 2));

	//int fieldSize = mState.size() * mState.size();

	//// Search for targetValue and calc manhattan distance from target position
	//int targetValue = 1;
	//bool foundTarget = false;
	//int totalCost = 0;

	//// Manhattan distance
	//while (targetValue < fieldSize)
	//{
	//	int targetPosX = (targetValue - 1) / (int)mState.size();
	//	int targetPosY = (targetValue - 1) % (int)mState.size();
	//	int actualPosX;
	//	int actualPosY;
	//	for (int i = 0; i < mState.size(); i++)
	//	{
	//		for (int j = 0; j < mState.size(); j++)
	//		{
	//			if (mState[i][j] == targetValue)
	//			{
	//				actualPosX = i;
	//				actualPosY = j;
	//				int manhDis = std::abs(targetPosX - actualPosX) + std::abs(targetPosY - actualPosY);
	//				totalCost += manhDis;
	//				//std::cout << "Calculated cost for value " << targetValue << ": " << manhDis << std::endl << std::endl;
	//				targetValue++;
	//				foundTarget = true;
	//				break;
	//			}
	//		}
	//		if (foundTarget)
	//			break;
	//	}
	//	foundTarget = false;
	//}

	//return totalCost;
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


