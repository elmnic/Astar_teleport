#pragma once

#include <SFML\Graphics.hpp>

class Hunter;

class BaseState
{
public:
	virtual ~BaseState() {}

	virtual void enter(Hunter*) = 0;

	virtual void execute(Hunter*) = 0;

	virtual void render(Hunter*, sf::RenderWindow&) = 0;

	virtual void exit(Hunter*) = 0;
};

