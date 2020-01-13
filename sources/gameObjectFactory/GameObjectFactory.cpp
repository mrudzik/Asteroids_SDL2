
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






void    GameObjectFactory::CreateObject(ObjectsEnum objType, int xPos, int yPos,
float xVec, float yVec, float speed, float rotationSpeed, float angle)
{
	if (objType == ObjectsEnum::BigAsteroidType)
	{
		BigAsteroid* tempObject =
			new BigAsteroid(_window, _bigAsteroidPic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle);
		tempObject->lockObj.SetLockData(_lockPic, GenerateUniqueID());
		_bigAsteroids.push_back(tempObject);
	}
	else if (objType == ObjectsEnum::SmallAsteroidType)
	{
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
		if (player->lockedID < 0)
			return; // Protection
		
		Torpedo* tempObject =
			new Torpedo(_window, _torpedoPic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle,
			player->lockedID);

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