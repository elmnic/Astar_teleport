#include "Game.h"


Game::Game() :
	mWindow()
{
	mAgent = Agent::instance();
	mHunter = Hunter::instance();
	mSolver = Solver::instance();
	mMap = Map::instance();
}

Game::~Game()
{
	clear();
}

void Game::clear() 
{
	mSolver->clear();
	//delete mSolver;
}

void Game::run()
{
	mWindow.create(sf::VideoMode(sf::VideoMode::getDesktopMode().height / 2, sf::VideoMode::getDesktopMode().height / 2), "A*",sf::Style::Close);
	mWindow.setVerticalSyncEnabled(true);

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
			case sf::Event::KeyPressed: // Move agent
				if (event.key.code == sf::Keyboard::W)
					mAgent->move(Agent::direction::up);
				if (event.key.code == sf::Keyboard::S)
					mAgent->move(Agent::direction::down);
				if (event.key.code == sf::Keyboard::A)
					mAgent->move(Agent::direction::left);
				if (event.key.code == sf::Keyboard::D)
					mAgent->move(Agent::direction::right);
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::O)
					mRenderOpen = !mRenderOpen;
				if (event.key.code == sf::Keyboard::P)
					mRenderClosed = !mRenderClosed;
			}
		}
		update();
		render();
	}
}

void Game::update()
{
	mAgent->update(mWindow);
	mMap->update(mWindow);
	mHunter->update(mWindow, mAgent->getPosition());
}

void Game::render()
{
	mWindow.clear();

	mMap->render(mWindow);
	mSolver->render(mWindow, mRenderClosed, mRenderOpen, sf::Vector2f(mMap->getWidth(), mMap->getHeight()));
	mAgent->render(mWindow);
	mHunter->render(mWindow);

	mWindow.display();
}