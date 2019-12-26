
#include "GameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory(GameSDL_Window* window)
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

	std::cout << "Creating Player" << std::endl;
	player = new Player(_window, _spaceShipPic, 0, 0, 0, 0, 0, 0, 0);
}

GameObjectFactory::~GameObjectFactory()
{// Deallocate all Objects
	
	delete player;
	delete _background;

	std::cout << "Deallocating Asteroids" << std::endl;
    for (int i = 0; i < (int)_bigAsteroids.size(); i++)
    {// Deallocating Asteroids
		delete _bigAsteroids.at(i);
		_bigAsteroids.at(i) = NULL;
    }
	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{// Small Asteroids
		delete _smallAsteroids.at(i);
		_smallAsteroids.at(i) = NULL;
	}
	for (int i = 0; i < (int)_bullets.size(); i++)
	{// Small Asteroids
		delete _bullets.at(i);
		_bullets.at(i) = NULL;
	}

	// Deallocate all saved Pictures
    delete _bigAsteroidPic;
    delete _smallAsteroidPic;
    delete _spaceShipPic;
    delete _bulletPic;

	std::cout << "Game Object Factory is destucted" << std::endl;
}


void	GameObjectFactory::CalculateMovementAll()
{
	player->CalculateAngle();
	player->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
	std::cout << "Player Pos: X " << player->GetPosX()
		<< " Y " << player->GetPosY() << std::endl;
	player->InertiaDampeners();


	for (int i = 0; i < (int)_bigAsteroids.size(); i++)
	{// Asteroids Movement
		_bigAsteroids.at(i)->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
		std::cout << "Asteroid Pos: X " << _bigAsteroids.at(i)->GetPosX()
		<< " Y " << _bigAsteroids.at(i)->GetPosY() << std::endl;
	}
	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{// Small Asteroids
		_smallAsteroids.at(i)->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
	}
	for (int i = 0; i < (int)_bullets.size(); i++)
	{
		_bullets.at(i)->CalculateMovement(_window->mapSizeX, _window->mapSizeY);
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
	


    
}

