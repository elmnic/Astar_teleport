#pragma once
#include <vector>
#include <queue>
#include <stdlib.h>
#include <iostream>
#include "StateStruct.h"
#include "Map.h"

class Node
{
public:
	
	Node(StateStruct::State state, Node* parent, int cost);
	~Node();

	void expandChildren();
	float heuristic();

	float pathCost;
	float heuristicCost;

	// totalCost = pathCost + heuristicCost
	float totalCost;

	void reconstructPath(std::vector<Node*> &cameFrom);

	void clear();

	const StateStruct::State& getState() { return mState; };
	std::vector<Node*> getChildren() { return mChildren; };

private:
	StateStruct::State mState; // Its position
	Node* mParent;
	std::vector<Node*> mChildren;

	Map* mMap;

};



