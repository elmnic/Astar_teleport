#include "Agent.h"



Agent::Agent(): mPosition(9, 0)
{
	mMap = new Map();
	mSolver = new Solver();
	mPath = mSolver->solve(mPosition, mMap->getGoal());
	for each (Node* node in mPath)
	{
		std::cout << "X: " << node->getState().x << " Y: " << node->getState().y << " Weight: " << mMap->getWeight(node->getState()) << std::endl;
	}
}


Agent::~Agent()
{
}

int Agent::move(Agent::direction dir)
{
	switch (dir)
	{
	case Agent::up:
		if (mPosition.y > 0)
			mPosition.y--;
		if (mMap->getID(mPosition) == Map::tileID::teleport)
			mPosition = mMap->findOtherTeleport(mPosition);
		return mMap->getWeight(mPosition);
		break;
	case Agent::down:
		if (mPosition.y < mMap->getHeight() - 1)
			mPosition.y++;
		if (mMap->getID(mPosition) == Map::tileID::teleport)
			mPosition = mMap->findOtherTeleport(mPosition);
		return mMap->getWeight(mPosition);
		break;
	case Agent::left:
		if (mPosition.x > 0)
			mPosition.x--;
		if (mMap->getID(mPosition) == Map::tileID::teleport)
			mPosition = mMap->findOtherTeleport(mPosition);
		return mMap->getWeight(mPosition);
		break;
	case Agent::right:
		if (mPosition.x < mMap->getWidth() - 1)
			mPosition.x++;
		if (mMap->getID(mPosition) == Map::tileID::teleport)
			mPosition = mMap->findOtherTeleport(mPosition);
		return mMap->getWeight(mPosition);
		break;
	default:
		break;
	}
}
