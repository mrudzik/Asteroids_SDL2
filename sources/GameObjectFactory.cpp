
#include "GameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory(GameSDL_Window* window,
	bool brownMotion, float abilProb) :
		_abilityProb(abilProb),
		spawnRadius((window->GetWidth() > window->GetHeight())
			? window->GetWidth() : window->GetHeight()),
		brownianMotion(brownMotion)
{
    std::cout << "Game Object Factory Creation" << std::endl;
    _window = window;
	_background = new BackGroundControl(_window);

    _bigAsteroidPic = new PicTexture();
    _bigAsteroidPic->LoadFromFile("resourses/big_asteroid.png", *_window);
    _smallAsteroidPic = new PicTexture();
    _smallAsteroidPic->LoadFromFile("resourses/small_asteroid.png", *_window);
    _spaceShipPic = new PicTexture();
    _spaceShipPic->LoadFromFile("resourses/spaceship.png", *_window);
    _bulletPic = new PicTexture();
    _bulletPic->LoadFromFile("resourses/bullet.png", *_window);
	// Crystal sprites
	_crystalWhitePic = new PicTexture();
	_crystalWhitePic->LoadFromFile("resourses/crystals/crystal_white_small.png", *_window);
	_crystalGreenPic = new PicTexture();
	_crystalGreenPic->LoadFromFile("resourses/crystals/crystal_green_small.png", *_window);
	_crystalBluePic = new PicTexture();
	_crystalBluePic->LoadFromFile("resourses/crystals/crystal_blue_small.png", *_window);
	_crystalPurplePic = new PicTexture();
	_crystalPurplePic->LoadFromFile("resourses/crystals/crystal_purple_small.png", *_window);
	// Ability pics
	_shieldAbilPic = new PicTexture();
	_shieldAbilPic->LoadFromFile("resourses/ShieldBattery.png", *_window);
	_torpedoAbilPic = new PicTexture();
	_torpedoAbilPic->LoadFromFile("resourses/torpedos/Torpedo2_small_Ammo.png", *_window);

	
	// Shield pics
	_shieldPic = new PicTexture();
	_shieldPic->LoadFromFile("resourses/ShieldCircle.png", *_window);
	// Torpedo pics
	_torpedoPic = new PicTexture();
	_torpedoPic->LoadFromFile("resourses/torpedos/Torpedo2_small.png", *_window);
	// Locking pics
	_lockPic = new PicTexture();
	_lockPic->LoadFromFile("resourses/torpedos/target.png", *_window);


	// Creating Player
	std::cout << "Creating Player" << std::endl;
	player = new Player(_window, _spaceShipPic, 0, 0, 0, 0, 0, -1.0f, 0,
		_shieldPic);

}

GameObjectFactory::~GameObjectFactory()
{// Deallocate all Objects

	delete player;
	delete _background;

	DeallocateAllObjects();

	// Deallocate all saved Pictures
    delete _bigAsteroidPic;
    delete _smallAsteroidPic;
    delete _spaceShipPic;
    delete _bulletPic;

	delete _crystalWhitePic;
	delete _crystalGreenPic;
	delete _crystalBluePic;
	delete _crystalPurplePic;

	delete _shieldAbilPic;
	delete _torpedoAbilPic;

	delete _shieldPic;
	delete _torpedoPic;
	delete _lockPic;
	
	std::cout << "Game Object Factory is destucted" << std::endl;
}

void 	GameObjectFactory::DeallocateAllObjects()
{
	std::cout << "Deallocating Objects" << std::endl;
    for (int i = 0; i < (int)_bigAsteroids.size(); i++)
    {// Deallocating Asteroids
		// _bigAsteroids.at(i).reset();
		delete _bigAsteroids.at(i);
		_bigAsteroids.at(i) = NULL;
    }
	_bigAsteroids.clear();

	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{// Small Asteroids
		// _smallAsteroids.at(i).reset();
		delete _smallAsteroids.at(i);
		_smallAsteroids.at(i) = NULL;
	}
	_smallAsteroids.clear();

	for (int i = 0; i < (int)_bullets.size(); i++)
	{// Bullets
		delete _bullets.at(i);
		_bullets.at(i) = NULL;
	}
	_bullets.clear();

	for (int i = 0; i < (int)_collectables.size(); i++)
	{// Collectables
		delete _collectables.at(i);
		_collectables.at(i) = NULL;
	}
	_collectables.clear();

	for (int i = 0; i < (int)_torpedos.size(); i++)
    {// Deallocating Torpedos
		delete _torpedos.at(i);
		_torpedos.at(i) = NULL;
    }
	_torpedos.clear();
}













void	GameObjectFactory::CalculateMovementAll()
{
	SDL_GetMouseState(&mousePosX, &mousePosY);
	mouseWorldPosX = (mousePosX - _window->GetWidthHalf()) * -1
		+ player->GetPosX();
	mouseWorldPosY = (mousePosY - _window->GetHeightHalf()) * -1
		+ player->GetPosY();



	player->CalculateAngle(mousePosX, mousePosY);
	player->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
	player->InertiaDampeners();
	player->CalculateShield();


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


void    GameObjectFactory::CreateObject(ObjectsEnum objType, int xPos, int yPos,
float xVec, float yVec, float speed, float rotationSpeed, float angle)
{
	if (objType == ObjectsEnum::BigAsteroidType)
	{
		// std::shared_ptr<BigAsteroid> tempObject =
		// 	std::make_shared<BigAsteroid>(_window, _bigAsteroidPic,
		// 	xPos, yPos, xVec, yVec,
		// 	speed, rotationSpeed, angle);
		BigAsteroid* tempObject =
			new BigAsteroid(_window, _bigAsteroidPic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle);
		tempObject->lockObj.SetLockData(_lockPic, GenerateUniqueID());
		_bigAsteroids.push_back(tempObject);
	}
	else if (objType == ObjectsEnum::SmallAsteroidType)
	{
		// std::shared_ptr<SmallAsteroid> tempObject =
		// 	std::make_shared<SmallAsteroid>(_window, _smallAsteroidPic,
		// 	xPos, yPos, xVec, yVec,
		// 	speed, rotationSpeed, angle);
		SmallAsteroid* tempObject =
			new SmallAsteroid(_window, _smallAsteroidPic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle);
		tempObject->lockObj.SetLockData(_lockPic, GenerateUniqueID());
		_smallAsteroids.push_back(tempObject);
	}
    else if (objType == ObjectsEnum::BulletType)
	{
		Bullet* tempObject =
			new Bullet(_window, _bulletPic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle);
		_bullets.push_back(tempObject);
	}
	else if (objType == ObjectsEnum::TorpedoType)
	{
		if (player->lockedObject == NULL)
			return; // Protection
		
		Torpedo* tempObject =
			new Torpedo(_window, _torpedoPic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle,
			player->lockedObject->lockObj.GetID());

		_torpedos.push_back(tempObject);
	}
	else if (objType == ObjectsEnum::CrystalWhiteType ||
		objType == ObjectsEnum::CrystalGreenType ||
		objType == ObjectsEnum::CrystalBlueType ||
		objType == ObjectsEnum::CrystalPurpleType ||
		objType == ObjectsEnum::ShieldBatteryType ||
		objType == ObjectsEnum::TorpedoAmmoType)
	{
		PicTexture* tempPic = NULL;

		if (objType == ObjectsEnum::CrystalWhiteType)
			tempPic = _crystalWhitePic;
		else if (objType == ObjectsEnum::CrystalGreenType)
			tempPic = _crystalGreenPic;
		else if (objType == ObjectsEnum::CrystalBlueType)
			tempPic = _crystalBluePic;
		else if (objType == ObjectsEnum::CrystalPurpleType)
			tempPic = _crystalPurplePic;
		else if (objType == ObjectsEnum::ShieldBatteryType)
			tempPic = _shieldAbilPic;
		else if (objType == ObjectsEnum::TorpedoAmmoType)
			tempPic = _torpedoAbilPic;
		else 
		{ // Little Protection
			std::cout << "Tried to create object with wrong Enum" << std::endl;
			return;
		}

		Collectable* tempObject =
			new Collectable(_window, tempPic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle);
		tempObject->type = objType; // Important for scoring
		_collectables.push_back(tempObject);
	}
}

void    GameObjectFactory::DestroyObject(ObjectsEnum objType, int index)
{
	if (objType == ObjectsEnum::BigAsteroidType)
	{
		// _bigAsteroids.at(index).reset();	
		BigAsteroid* tempAsteroid = _bigAsteroids.at(index);
		// Erase that pointer from vector
		_bigAsteroids.erase(_bigAsteroids.begin() + index);
		// Deal with allocated data on that pointer
		delete tempAsteroid;
		tempAsteroid = NULL;
	}
	else if (objType == ObjectsEnum::SmallAsteroidType)
	{
		// _smallAsteroids.at(index).reset();
		SmallAsteroid* tempAsteroid = _smallAsteroids.at(index);
		// Erase that pointer from vector
		_smallAsteroids.erase(_smallAsteroids.begin() + index);
		// Deal with allocated data on that pointer
		delete tempAsteroid;
		tempAsteroid = NULL;
	}
	else if (objType == ObjectsEnum::BulletType)
	{
		Bullet* tempBullet = _bullets.at(index);
		// Erase that pointer from vector
		_bullets.erase(_bullets.begin() + index);
		// Deal with allocated data on that pointer
		delete tempBullet;
		tempBullet = NULL;
	}
	else if (objType == ObjectsEnum::TorpedoType)
	{
		Torpedo* tempObj = _torpedos.at(index);

		Asteroid* tempAst = GetAsteroidByID(tempObj->GetTargetID());
		if (tempAst != NULL) // Release lock
			tempAst->lockObj.SetLock(false);

		_torpedos.erase(_torpedos.begin() + index);
		delete tempObj;
		tempObj = NULL;
	}
	else if (objType == ObjectsEnum::CrystalWhiteType ||
		objType == ObjectsEnum::CrystalGreenType ||
		objType == ObjectsEnum::CrystalBlueType ||
		objType == ObjectsEnum::CrystalPurpleType ||
		objType == ObjectsEnum::ShieldBatteryType ||
		objType == ObjectsEnum::TorpedoAmmoType)
	{
		Collectable* tempCollectable = _collectables.at(index);
		_collectables.erase(_collectables.begin() + index);
		delete tempCollectable;
		tempCollectable = NULL;
	}
    
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

Asteroid* GameObjectFactory::GetAsteroidByID(int targetID)
{
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






void 	GameObjectFactory::BulletReload(int const bulletLimit)
{
	if ((int)_bullets.size() < bulletLimit)
		return;
	DestroyObject(ObjectsEnum::BulletType, 0);
}

void 	GameObjectFactory::RestartBehaviour(RestartScenarioEnum scenario)
{
	DeallocateAllObjects();

	if (scenario == RestartScenarioEnum::Start)
	{
		SDL_RenderClear(_window->GetRender());
		_window->DrawText(
			"Loading...",
			_window->GetWidthHalf() - 50, _window->GetHeightHalf(),
			_window->GetColor(ColorEnum::Green));

		SDL_RenderPresent(_window->GetRender());
		SDL_Delay(500);
	}
	else if (scenario == RestartScenarioEnum::Death)
	{
		_window->DrawText(
			" You Died"
			"\n Now wait for Respawn"
			"\n And try again",
			_window->GetWidthHalf() - 100, _window->GetHeightHalf() - 100,
			_window->GetColor(ColorEnum::Red));
		SDL_RenderPresent(_window->GetRender());
		SDL_Delay(2000);
	}

	CreateObject(ObjectsEnum::BigAsteroidType, -110, 200, 1, -1, 1, -0.2f, 30);
	CreateObject(ObjectsEnum::BigAsteroidType, -200, 200, 0, 0, 0, -0.2f, 30);

}