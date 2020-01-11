
#ifndef GAMEOBJECTFACTORY_HPP
#define GAMEOBJECTFACTORY_HPP

#include <iostream>
#include <vector>
#include <memory>

#include "GameSDL_Window.hpp"
#include "BackGroundControl.hpp"

#include "AbstractGameObject.hpp"
#include "BigAsteroid.hpp"
#include "SmallAsteroid.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Collectable.hpp"
#include "Torpedo.hpp"

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

	PicTexture* 	_crystalWhitePic;
	PicTexture* 	_crystalGreenPic;
	PicTexture* 	_crystalBluePic;
	PicTexture*		_crystalPurplePic;

	PicTexture* 	_shieldAbilPic;
	PicTexture* 	_torpedoAbilPic;


	PicTexture* 	_shieldPic;
	PicTexture* 	_torpedoPic;
	PicTexture*		_lockPic;

    // Allocated Objects
	// TODO make them all unique ptr
    std::vector<BigAsteroid*>		_bigAsteroids;
	std::vector<SmallAsteroid*>		_smallAsteroids;
	std::vector<Bullet*>			_bullets;
	std::vector<Collectable*>		_collectables;
	std::vector<Torpedo*> 			_torpedos;

	float const _abilityProb;

	bool _zoneToRender[9];
public:
	Player*	player;
	int const 	spawnRadius;
	int mousePosX;
	int mousePosY;
	int mouseWorldPosX;
	int mouseWorldPosY;

	bool const brownianMotion;

    GameObjectFactory(GameSDL_Window* window,
		bool brownMotion, float abilProb);
    ~GameObjectFactory();

	void CalculateMovementAll();
	int GenerateUniqueID();
    void CreateObject(ObjectsEnum objType, int xPos, int yPos,
		float xVec, float yVec, float speed, float rotationSpeed, float angle);
    void DestroyObject(ObjectsEnum objType, int index);
	void DeallocateAllObjects();
	

	Asteroid* GetClosestAsteroid(int posX, int posY);
	Asteroid* GetAsteroidByID(int targetID);

	int GetAsteroidCount();
	int GetBulletCount();
	int GetCollectableCount();
	int GetTorpedoCount();

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
	void TorpedoIntersections();
	void AsteroidsIntersections();
	bool PlayerIntersections();
	void BigAsteroidSplit(AbstractGameObject* tempBullet, BigAsteroid* tempTarget);
	void CreateResource(int posX, int posY);

};




#endif