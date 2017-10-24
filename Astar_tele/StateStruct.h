#pragma once

#include <vector>
#include <SFML\System.hpp>

using namespace std;;

struct StateStruct
{
	//typedef vector<vector<int>> State;
	typedef sf::Vector2i State;

	// Assumes s0 and s1 are equal size
	// Returns true if states are equal
	static bool compare(State const &s0, State const &s1) {
		
		return s0 == s1;
	}
};

