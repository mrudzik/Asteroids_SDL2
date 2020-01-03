
#include "GameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory(GameSDL_Window* window, bool brownMotion)
	: spawnRadius((window->GetWidth() > window->GetHeight()) ? window->GetWidth() : window->GetHeight()),
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


	std::cout << "Creating Player" << std::endl;
	player = new Player(_window, _spaceShipPic, 0, 0, 0, 0, 0, 0, 0);
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

	std::cout << "Game Object Factory is destucted" << std::endl;
}

void 	GameObjectFactory::DeallocateAllObjects()
{
	std::cout << "Deallocating Objects" << std::endl;
    for (int i = 0; i < (int)_bigAsteroids.size(); i++)
    {// Deallocating Asteroids
		delete _bigAsteroids.at(i);
		_bigAsteroids.at(i) = NULL;
    }
	_bigAsteroids.clear();

	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{// Small Asteroids
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
}



void	GameObjectFactory::CalculateMovementAll()
{
	SDL_GetMouseState(&mousePosX, &mousePosY);
	player->CalculateAngle(mousePosX, mousePosY);
	player->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
	// std::cout << "Player Pos: X " << player->GetPosX()
		// << " Y " << player->GetPosY() << std::endl;
	player->InertiaDampeners();


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
	// for (int i = 0; i < (int)_collectables.size(); i++)
	{
		_collectables.at(i)->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
		if (_collectables.at(i)->DestroyTimer())
			DestroyObject(ObjectsEnum::CrystalWhiteType, i);
	}
}












void    GameObjectFactory::CreateObject(ObjectsEnum objType, int xPos, int yPos,
float xVec, float yVec, float speed, float rotationSpeed, float angle)
{
	if (objType == ObjectsEnum::BigAsteroidType)
	{
		BigAsteroid* tempObject =
			new BigAsteroid(_window, _bigAsteroidPic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle);
		_bigAsteroids.push_back(tempObject);
	}
	else if (objType == ObjectsEnum::SmallAsteroidType)
	{
		SmallAsteroid* tempObject =
			new SmallAsteroid(_window, _smallAsteroidPic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle);
		_smallAsteroids.push_back(tempObject);
	}
    else if (objType == ObjectsEnum::BulletType)
	{
		Bullet* tempObject =
			new Bullet(_window, _bulletPic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle);
		_bullets.push_back(tempObject);
	}
	else if (objType == ObjectsEnum::CrystalWhiteType)
	{
		Collectable* tempObject =
			new Collectable(_window, _crystalWhitePic, xPos, yPos,
			xVec, yVec, speed, rotationSpeed, angle);
		_collectables.push_back(tempObject);
	}
}

void    GameObjectFactory::DestroyObject(ObjectsEnum objType, int index)
{
	if (objType == ObjectsEnum::BigAsteroidType)
	{
		BigAsteroid* tempAsteroid = _bigAsteroids.at(index);
		// Erase that pointer from vector
		_bigAsteroids.erase(_bigAsteroids.begin() + index);
		// Deal with allocated data on that pointer
		delete tempAsteroid;
		tempAsteroid = NULL;
	}
	else if (objType == ObjectsEnum::SmallAsteroidType)
	{
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
	else if (objType == ObjectsEnum::CrystalWhiteType ||
		objType == ObjectsEnum::CrystalGreenType ||
		objType == ObjectsEnum::CrystalBlueType ||
		objType == ObjectsEnum::CrystalPurpleType)
	{
		Collectable* tempCollectable = _collectables.at(index);
		_collectables.erase(_collectables.begin() + index);
		delete tempCollectable;
		tempCollectable = NULL;
	}
    
}





int 	GameObjectFactory::GetAsteroidCount()
{
	return (int)(_bigAsteroids.size() + _smallAsteroids.size());
}
int 	GameObjectFactory::GetBulletCount()
{
	return (int)_bullets.size();
}

void 	GameObjectFactory::BulletReload(int const bulletLimit)
{
	if ((int)_bullets.size() < bulletLimit)
		return;
	DestroyObject(ObjectsEnum::BulletType, 0);
}

void 	GameObjectFactory::RestartBehaviour()
{
	DeallocateAllObjects();

	CreateObject(ObjectsEnum::BigAsteroidType, -110, 200, 1, -1, 1, -0.2f, 30);
	CreateObject(ObjectsEnum::BigAsteroidType, -200, 200, 0, 0, 0, -0.2f, 30);

}