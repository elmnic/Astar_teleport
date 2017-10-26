#include "Solver.h"


Solver* Solver::instance()
{
	static Solver solver;
	return &solver;
}

Solver::Solver()
{
}

Solver::~Solver()
{
	clear();
}

void Solver::render(sf::RenderWindow & window, bool closed, bool open, sf::Vector2f mapSize)
{
	float sizeX = window.getSize().x / mapSize.x;
	float sizeY = window.getSize().y / mapSize.y;
	int radiDiv = 4;


	sf::CircleShape circle((sizeX + sizeY) / 2 / radiDiv);

	// Draw closedList
	if (closed)
	{
		for (auto it : closedList)
		{
			sf::Vector2i state = it->getState();
			sf::Vector2f pos = sf::Vector2f(state.x * sizeX + sizeX / 2, state.y * sizeY + sizeY / 2);
			circle.setOrigin(circle.getRadius(), circle.getRadius());
			circle.setPosition(pos);
			circle.setFillColor(sf::Color(190, 0, 0));
			window.draw(circle);
		}
	}
	// Draw openList
	if(open)
	{
		for (auto it : openSet)
		{
			sf::Vector2i state = it->getState();
			sf::Vector2f pos = sf::Vector2f(state.x * sizeX + sizeX / 2, state.y * sizeY + sizeY / 2);
			circle.setOrigin(circle.getRadius(), circle.getRadius());
			circle.setPosition(pos);
			circle.setFillColor(sf::Color(53, 74, 92));
			window.draw(circle);
		}
	}
	// Draw optimal path
	for (auto it : cameFrom)
	{
		sf::Vector2i state = it->getState();
		sf::Vector2f pos = sf::Vector2f(state.x * sizeX + sizeX / 2, state.y * sizeY + sizeY / 2);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(pos);
		circle.setFillColor(sf::Color(0, 55, 27));
		window.draw(circle);
	}

}


std::vector<Node*> Solver::solve(StateStruct::State start, StateStruct::State goal)
{
	// Clear lists
	for (auto it : openSet)
		delete it;
	openSet.clear();
	while (!openList.empty())
		openList.pop();

	for (auto it : closedList)
		delete it;
	closedList.clear();
	cameFrom.clear();

	// Push start node
	openList.push(new Node(start, NULL, 0));

	// A set is used to search for the occurence of a node in the openList
	openSet.insert(openList.top());

	// Add start node to cameFrom vector
	int iterations = 0;
	while (!openList.empty()) 
	{
		iterations++;
		
		Node *current = openList.top();
		if (current->getState() == goal) 
		{
			std::cout << "Found solution after " << iterations << " iterations" << std::endl;
			current->reconstructPath(cameFrom);
			std::cout << "Number of steps: " << cameFrom.size() - 1 << std::endl;
			return cameFrom;
		}

		// Create child nodes
		current->expandChildren();

		openSet.erase(current);
		openList.pop();
		closedList.push_back(current);

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

