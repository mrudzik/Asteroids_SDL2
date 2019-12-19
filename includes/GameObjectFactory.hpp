
#ifndef GAMEOBJECTFACTORY_HPP
#define GAMEOBJECTFACTORY_HPP

#include <iostream>
#include <vector>
#include "GameSDL_Window.hpp"
#include "AbstractGameObject.hpp"

enum ObjectsEnum
{
	BigAsteroid,
	SmallAsteroid,
	Bullet
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

    // Allocated Asteroids
    std::vector<AbstractGameObject*>    _asteroids;


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