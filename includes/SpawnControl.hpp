#ifndef SPAWN_CONTROL_HPP
#define SPAWN_CONTROL_HPP

#include "GameObjectFactory.hpp"

class SpawnControl
{
private:
	GameObjectFactory*	_objectFactory;

	const int 	_asteroidSpawnLimit;
	const int 	_asteroidSpawnChance; // value between 0 and 100
public:

	SpawnControl(GameObjectFactory* objFact,
		int asteroidLimit);
	~SpawnControl();

	bool	NeedToSpawnAsteroid();
	void 	SpawnRandomAsteroid();

};

#endif