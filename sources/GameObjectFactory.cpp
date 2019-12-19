
#include "GameObjectFactory.hpp"



GameObjectFactory::GameObjectFactory(GameSDL_Window* window)
{
    std::cout << "Game Object Factory Creation" << std::endl;
    _window = window;

    _bigAsteroidPic = new PicTexture();
    _bigAsteroidPic->LoadFromFile("resourses/big_asteroid.png", *_window);

    _smallAsteroidPic = new PicTexture();
    _smallAsteroidPic->LoadFromFile("resourses/small_asteroid.png", *_window);

    _spaceShipPic = new PicTexture();
    _spaceShipPic->LoadFromFile("resourses/spaceship.png", *_window);

    _bulletPic = new PicTexture();
    _bulletPic->LoadFromFile("resourses/bullet.png", *_window);
}

GameObjectFactory::~GameObjectFactory()
{
    
    // Deallocate all Objects
	std::cout << "Deallocating Asteroids" << std::endl;
    for (int i = 0; i < (int)_asteroids.size(); i++)
    {// Deallocating Asteroids
		delete _asteroids.at(i);
        // DestroyAsteroid(i);
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
	for (int i = 0; i < (int)_asteroids.size(); i++)
	{// Asteroids Movement
		_asteroids.at(i)->CalculateMovement();
	}

}

void 	GameObjectFactory::CalculateIntersectionsAll()
{
	// Clear all Objects from calculated flag

	for (int i = 0; i < (int)_asteroids.size(); i++)
	{// Asteroids
		_asteroids.at(i)->IntersectCalculated = false;
	}
}


void	GameObjectFactory::RenderAll(int playerX, int playerY)
{
	for (int i = 0; i < (int)_asteroids.size(); i++)
	{// Asteroids Rendering
		_asteroids.at(i)->RenderOnWindow(playerX, playerY);
	}

}









void    GameObjectFactory::CreateObject(ObjectsEnum objType, int xPos, int yPos,
float xVec, float yVec, float speed, float rotationSpeed, float angle)
{
    AbstractGameObject* tempObject;

	if (objType == ObjectsEnum::BigAsteroid)
	{
		tempObject = new AbstractGameObject(_window, _bigAsteroidPic, xPos, yPos,
		xVec, yVec, speed, rotationSpeed, angle);
		_asteroids.push_back(tempObject);
	}
    
}

void    GameObjectFactory::DestroyObject(ObjectsEnum objType, int index)
{
	if (objType == ObjectsEnum::BigAsteroid)
	{
		AbstractGameObject* tempAsteroid = _asteroids.at(index);
		// Erase that pointer from vector
		_asteroids.erase(_asteroids.begin() + index);
		// Deal with allocated data on that pointer
		delete tempAsteroid;
	}
    
}

