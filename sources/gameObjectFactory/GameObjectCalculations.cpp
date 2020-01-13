#include "GameObjectFactory.hpp"



void	GameObjectFactory::CalculateMovementAll()
{
	// Finding mouse positions
	SDL_GetMouseState(&mousePosX, &mousePosY);
	mouseWorldPosX = (mousePosX - _window->GetWidthHalf()) * -1
		+ player->GetPosX();
	mouseWorldPosY = (mousePosY - _window->GetHeightHalf()) * -1
		+ player->GetPosY();

	// Calculating player
	player->CalculateAngle(mousePosX, mousePosY);
	player->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
	player->InertiaDampeners();
	player->CalculateShield();

	// Calculating All objects
	for (int i = 0; i < (int)_bigAsteroids.size(); i++)
	{// Asteroids Movement
		_bigAsteroids.at(i)->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
	}
	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{// Small Asteroids
		_smallAsteroids.at(i)->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
	}
	for (int i = 0; i < (int)_bullets.size(); i++)
	{
		_bullets.at(i)->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
	}
	for (int i = (int)_collectables.size() - 1; i > -1; i--)
	{
		_collectables.at(i)->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
		if (_collectables.at(i)->DestroyTimer())
			DestroyObject(ObjectsEnum::CrystalWhiteType, i);
	}
	for (int i = (int)_torpedos.size() - 1; i > -1; i--)
	{
		if (!_torpedos.at(i)->AimTarget(
			GetAsteroidByID(_torpedos.at(i)->GetTargetID()),
			_window->mapSizeX, _window->mapSizeY))
		{
			DestroyObject(ObjectsEnum::TorpedoType, i);
			continue;
		}
		_torpedos.at(i)->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
	}

}




// ID Stuff
int 	GameObjectFactory::GenerateUniqueID()
{
	bool idReady = false;
	int result;

	while (!idReady)
	{
		result = rand();
		idReady = true;
		// Just In case
		// Checking all asteroids if they have same id
		for (int i = 0; i < (int)_bigAsteroids.size(); i++)
		{
			if (result == _bigAsteroids.at(i)->lockObj.GetID())
			{
				idReady = false;
				break;
			}
		}
		if (!idReady)
			continue;
		for (int i = 0; i < (int)_smallAsteroids.size(); i++)
		{
			if (result == _smallAsteroids.at(i)->lockObj.GetID())
			{
				idReady = false;
				break;
			}
		}
	}

	return result;
}




Asteroid* GameObjectFactory::GetAsteroidByID(int targetID)
{
	if (targetID < 0)
		return NULL; // Protection
	if (GetAsteroidCount() <= 0)
		return NULL; // Protection
	
	for (int i = 0; i < (int)_bigAsteroids.size(); i++)
	{	// Big Asteroids
		if (_bigAsteroids.at(i)->lockObj.GetID() == targetID)
			return _bigAsteroids.at(i);
	}
	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{	// Small Asteroids
		if (_smallAsteroids.at(i)->lockObj.GetID() == targetID)
			return _smallAsteroids.at(i);
	}
	return NULL;
}

Asteroid* GameObjectFactory::GetClosestAsteroid(int posX, int posY)
{
	Asteroid* tempResult = NULL;
	if (GetAsteroidCount() <= 0)
		return tempResult;
	
	float closestDist = -1;
	// Check for closest dist
	for (int i = 0; i < (int)_bigAsteroids.size(); i++)
	{	// Big Asteroids
		BigAsteroid* tempTarget = _bigAsteroids.at(i);

		if (tempTarget->lockObj.IsLocked())
			continue;

		float dist = ((posX - tempTarget->GetPosX()) * (posX - tempTarget->GetPosX()))
			+ ((posY - tempTarget->GetPosY()) * (posY - tempTarget->GetPosY()));
		if (tempResult == NULL || closestDist > dist)
		{
			closestDist = dist;
			tempResult = tempTarget;
		}
	}
	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{	// Small Asteroids
		SmallAsteroid* tempTarget = _smallAsteroids.at(i);
		if (tempTarget->lockObj.IsLocked())
			continue;
		
		float dist = ((posX - tempTarget->GetPosX()) * (posX - tempTarget->GetPosX()))
			+ ((posY - tempTarget->GetPosY()) * (posY - tempTarget->GetPosY()));
		if (tempResult == NULL || closestDist > dist)
		{
			closestDist = dist;
			tempResult = tempTarget;
		}
	}
	return tempResult;
}












int 	GameObjectFactory::GetAsteroidCount()
{
	return (int)(_bigAsteroids.size() + _smallAsteroids.size());
}
int 	GameObjectFactory::GetBulletCount()
{
	return (int)_bullets.size();
}
int 	GameObjectFactory::GetCollectableCount()
{
	return (int)_collectables.size();
}
int 	GameObjectFactory::GetTorpedoCount()
{
	return (int)_torpedos.size();
}
