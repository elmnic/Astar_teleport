#pragma once

#include "Node.h"
#include "StateStruct.h"
#include <algorithm>
#include <set>

class OrderByCost
{
public:
	bool operator()(Node const *n1, Node const *n2)
	{
		return n1->totalCost > n2->totalCost;
	}
};

class Solver
{
public:

	Solver();
	~Solver();

	std::vector<Node*> solve(StateStruct::State start, StateStruct::State goal);
	std::vector<Node*> reconstructPath(Node* finalChild);

	void clear();

private:
	bool isGoal(StateStruct:: State state, StateStruct::State goal);

	// Queue not yet expanded child nodes
	std::priority_queue<Node*, std::vector<Node*>, OrderByCost> openList;
	std::vector<Node*> closedList;

	std::set<Node*> openSet;

	// Contains the solution
	std::vector<Node*> cameFrom;
};

