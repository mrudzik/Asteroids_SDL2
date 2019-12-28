
#ifndef GAMEOBJECTFACTORY_HPP
#define GAMEOBJECTFACTORY_HPP

#include <iostream>
#include <vector>

#include "GameSDL_Window.hpp"
#include "BackGroundControl.hpp"

#include "AbstractGameObject.hpp"
#include "BigAsteroid.hpp"
#include "SmallAsteroid.hpp"
#include "Bullet.hpp"
#include "Player.hpp"

enum ObjectsEnum
{
	BigAsteroidType,
	SmallAsteroidType,
	BulletType,
	PlayerType
};

class GameObjectFactory
{
private:
    GameSDL_Window*  	_window;
	BackGroundControl* 	_background;

    // Allocated and Saved Pictures
    PicTexture*     _bigAsteroidPic;
    PicTexture*     _smallAsteroidPic;
    PicTexture*     _spaceShipPic;
    PicTexture*     _bulletPic;

    // Allocated Objects
    std::vector<BigAsteroid*>		_bigAsteroids;
	std::vector<SmallAsteroid*>		_smallAsteroids;
	std::vector<Bullet*>			_bullets;

	bool _zoneToRender[9];
public:
	Player*	player;
	int const 	spawnRadius;
	int mousePosX;
	int mousePosY;

	bool const brownianMotion;

    GameObjectFactory(GameSDL_Window* window, bool brownMotion);
    ~GameObjectFactory();

	void CalculateMovementAll();
    void CreateObject(ObjectsEnum objType, int xPos, int yPos,
		float xVec, float yVec, float speed, float rotationSpeed, float angle);
    void DestroyObject(ObjectsEnum objType, int index);
	void DeallocateAllObjects();
	
	int GetAsteroidCount();
	void BulletReload(int const bulletLimit);
	void RestartBehaviour();


	// In GameObjectsRender.cpp
	void RenderAll();
	void CheckWarpZones(int playerX, int playerY);
	void RenderBackground(int xDif, int yDif);
	void RenderObjects(int playerX, int playerY);
	void RenderSpecific(int posX, int posY);

	// In GameObjectsIntersections.cpp
	void CalculateIntersectionsAll();
	void BulletIntersections();
	void AsteroidsIntersections();
	bool PlayerIntersections();
	void BigAsteroidSplit(Bullet* tempBullet, BigAsteroid* tempTarget);


};




#endif