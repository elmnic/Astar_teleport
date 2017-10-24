#include "Game.h"

Solver* solver;

Game::Game() :
	mWindow()
{
	mAgent = new Agent();
	solver = new Solver();
}

Game::~Game()
{
	clear();
}

void Game::clear() 
{
	solver->clear();
	delete solver;
}

void Game::run()
{
	mWindow.create(sf::VideoMode(600, 600), "A*", sf::Style::Close);
	mWindow.setVerticalSyncEnabled(true);

	//Map map;
	//map.initialize(4);

	StateStruct::State state;

	// Main loop
	while (mWindow.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		// Events
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				mWindow.close();
				break;
			case sf::Event::KeyPressed:

				/*if (event.key.code > 26 && event.key.code < 36)
					map.initialize(event.key.code - 26);*/

				/*if (event.key.code == sf::Keyboard::R)
					map.restart();
				if (event.key.code == sf::Keyboard::T)
					map.shuffleMap();*/

				if (event.key.code == sf::Keyboard::W)
					mAgent->move(Agent::direction::up);
				if (event.key.code == sf::Keyboard::S)
					mAgent->move(Agent::direction::down);
				if (event.key.code == sf::Keyboard::A)
					mAgent->move(Agent::direction::left);
				if (event.key.code == sf::Keyboard::D)
					mAgent->move(Agent::direction::right);
				
				/*if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "Solving..." << std::endl;
					std::vector<Node*> cameFrom;
					solver->clear();
					cameFrom = solver->solve(map.getCurrentState(), map.getGoalState());
					std::cout << "Solution requires: " << cameFrom.size() - 1 << " steps\n\n";
					for each (Node* node in cameFrom)
					{
						map.printMap(node->getState());
						std::cout << std::endl;
					}
				}
				else
				{
					map.printMap(map.getCurrentState());
				}*/
				

			case sf::Event::MouseButtonPressed:

				break;
			}

		}

		render();

	}
}

void Game::render()
{
	mWindow.clear();

	mWindow.display();
}