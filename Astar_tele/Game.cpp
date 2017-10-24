#include "Game.h"

Solver* solver;

Game::Game() :
	mWindow()
{
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
	mWindow.create(sf::VideoMode(400, 400), "8/15", sf::Style::Close);
	mWindow.setVerticalSyncEnabled(true);

	Map map;
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

				if (event.key.code > 26 && event.key.code < 36)
					map.initialize(event.key.code - 26);

				if (event.key.code == sf::Keyboard::R)
					map.restart();
				if (event.key.code == sf::Keyboard::T)
					map.shuffleMap();

				if (event.key.code == sf::Keyboard::W)
					map.updateCurrentState(map.move(Map::up, map.getCurrentState()));
				if (event.key.code == sf::Keyboard::S)
					map.updateCurrentState(map.move(Map::down, map.getCurrentState()));
				if (event.key.code == sf::Keyboard::A)
					map.updateCurrentState(map.move(Map::left, map.getCurrentState()));
				if (event.key.code == sf::Keyboard::D)
					map.updateCurrentState(map.move(Map::right, map.getCurrentState()));
				
				if (event.key.code == sf::Keyboard::Space)
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
				}
				

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