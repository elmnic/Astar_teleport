#pragma once

#include <vector>

using namespace std;;

struct StateStruct
{
	typedef vector<vector<int>> State;

	// Assumes s0 and s1 are equal size
	// Returns true if states are equal
	static bool compare(State const &s0, State const &s1) {
		for (int i = 0; i < s0.size(); i++)
		{
			for (int j = 0; j < s0.size(); j++)
			{
				if (s0[i][j] != s1[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
};

