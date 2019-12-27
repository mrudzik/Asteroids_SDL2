
#include "SpawnControl.hpp"


SpawnControl::SpawnControl(GameObjectFactory* objFact, int asteroidLimit)
: _asteroidSpawnLimit(asteroidLimit), _asteroidSpawnChance(30)
{
	_objectFactory = objFact;
}

SpawnControl::~SpawnControl()
{

}


void 	SpawnControl::SpawnRandomAsteroid()
{
	

	int posX = _objectFactory->player->GetPosX();
	int posY = _objectFactory->player->GetPosY();
	int len = _objectFactory->spawnRadius;

	int sector = rand() % 4;
	int angle = 5 + (rand() % 81);

	float newPosX = cos(angle * M_PI / 180.0f);
	float newPosY = sin(angle * M_PI / 180.0f);

	switch (sector)	// 3 | 0
	{				//-------
	case 1:			// 2 | 1
		newPosY *= -1;
		break;
	case 2:
		newPosX *= -1;
		newPosY *= -1;
		break;
	case 3:
		newPosX *= -1;
		break;
	default:
		break;
	}
	
	float relatPosX = newPosX * len + posX;
	float relatPosY = newPosY * len + posY;
	// Result can be any number from 	-1 to 1
	// float dispersion = ((1 + rand() % 100) / 100) * ((rand() % 3) - 1);

	float vecX = rand() % 3;
	if (vecX == 0)
		vecX = -1;
	float vecY = rand() % 3;
	if (vecY == 0)
		vecY = -1;

	int random = rand() % 2;
	if (random == 0)
		_objectFactory->CreateObject(ObjectsEnum::BigAsteroidType,
			relatPosX + rand() % 50, relatPosY + rand() % 50,
			vecX * 5, vecY * 5, // Moving Vectors
			(5 + rand() % 19) / 10, (1 + rand() % 40) / 10, rand() % 360);
	else
		_objectFactory->CreateObject(ObjectsEnum::SmallAsteroidType,
			relatPosX + rand() % 50, relatPosY + rand() % 50,
			vecX * 5, vecY * 5, // Moving Vectors 
			(5 + rand() % 19) / 10, (1 + rand() % 19) / 10, rand() % 360);
	// std::cout << "Spawn: Angle " << angle << " xPos " <<
	// newPosX << " yPos " << newPosY << std::endl;
}

bool	SpawnControl::NeedToSpawnAsteroid()
{
	if (_asteroidSpawnLimit <= _objectFactory->GetAsteroidCount())
		return false; // If have lots of asteroids already
	if (rand() % 100 < _asteroidSpawnChance)
		return false; // Prevents from spawning immediatly all asteroids
	return true;
}
