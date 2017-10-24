#include "Solver.h"



Solver::Solver()
{
}

Solver::~Solver()
{
	clear();
}


std::vector<Node*> Solver::solve(StateStruct::State start, StateStruct::State goal)
{

	// Push start node
	openList.push(new Node(start, NULL, 0));

	// A set is used to search for the occurence of a node in the openList
	openSet.insert(openList.top());

	closedList.clear();
	cameFrom.clear();

	// Add start node to cameFrom vector
	int iterations = 0;
	while (!openList.empty()) 
	{
		iterations++;
		if (iterations % 1000 == 0)
			std::cout << iterations << " iterations..." << std::endl;

		Node *current = openList.top();
		if (current->getState() == goal) 
		{
			std::cout << "Found solution after " << iterations << " iterations" << std::endl;
			current->reconstructPath(cameFrom);
			return cameFrom;
		}

		// Create child nodes
		current->expandChildren();

		openSet.erase(current);
		openList.pop();
		closedList.push_back(current);

		//std::cout << "Nr of children: " << current->getChildren().size() << std::endl;

		for each (Node* child in current->getChildren())
		{
			// If child already expanded, skip to next child
			bool isInClosed = false;
			for (int i = 0; i < closedList.size(); i++)
			{
				if (StateStruct::compare(closedList[i]->getState(), child->getState()))
					isInClosed = true;
			}
			if (isInClosed)
				continue;
			
			// If child not yet opened, add to openList
			bool foundInstance = false;
			std::set<unsigned long>::iterator it;
			for (auto it = openSet.begin(); it != openSet.end(); it++)
			{
				Node *temp = *it;
				if (StateStruct::compare(temp->getState(), child->getState()))
				{
					foundInstance = true;
				}
			}

			if (!foundInstance)
			{
				//std::cout << "Added to openList" << std::endl;
				openSet.insert(child);
				openList.push(child);
			}

			// If childs path cost is lower, then that path is better
			if (current->pathCost >= child->pathCost)
				continue;
		}
	}

	return std::vector<Node*>();
}

std::vector<Node*> Solver::reconstructPath(Node * finalChild)
{
	std::vector<Node*> pathBackwards;
	pathBackwards.push_back(finalChild);



	return std::vector<Node*>();
}

void Solver::clear()
{

	while (!openList.empty())
	{
		delete openList.top();
		openList.pop();
	}

	for (auto i = closedList.begin(); i != closedList.end(); )
	{
		delete *i;
		i = closedList.erase(i);
	}

	openSet.clear();
	cameFrom.clear();
}

bool Solver::isGoal(StateStruct::State state, StateStruct::State goal)
{

	return false;
}

