
#ifndef GAMEOBJECTFACTORY_HPP
#define GAMEOBJECTFACTORY_HPP

#include <iostream>
#include <vector>

#include "GameSDL_Window.hpp"
#include "AbstractGameObject.hpp"
#include "BigAsteroid.hpp"
#include "SmallAsteroid.hpp"

enum ObjectsEnum
{
	BigAsteroidType,
	SmallAsteroidType,
	BulletType
};

class GameObjectFactory
{
private:
    GameSDL_Window*  _window;

    // Allocated and Saved Pictures
    PicTexture*     _bigAsteroidPic;
    PicTexture*     _smallAsteroidPic;
    PicTexture*     _spaceShipPic;
    PicTexture*     _bulletPic;

    // Allocated Objects
    std::vector<BigAsteroid*>		_bigAsteroids;
	std::vector<SmallAsteroid*>		_smallAsteroids;


public:

    GameObjectFactory(GameSDL_Window* window);
    ~GameObjectFactory();

	void CalculateMovementAll();
	void CalculateIntersectionsAll();
	void RenderAll(int playerX, int playerY);

    void CreateObject(ObjectsEnum objType, int xPos, int yPos,
		float xVec, float yVec, float speed, float rotationSpeed, float angle);
    void DestroyObject(ObjectsEnum objType, int index);

};




#endif