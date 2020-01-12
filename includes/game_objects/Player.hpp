#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "AbstractGameObject.hpp"
#include "Asteroid.hpp"

enum AbilityType
{
	TorpedoAbil,
	AimshootAbil
};

class Player final: public AbstractGameObject
{

private:
	// Shield Stuff
	PicTexture* _shieldPic;
	bool	_isShielded;
	int		_shieldCapacity;
	int		_shieldEnergy;
	int 	_shieldUsage;
	float	_shieldAngle;

	// Torpedo Stuff
	int 	_torpedoCapacity;
	int 	_torpedoCount;

	// Moving and Showing
	float _slowingSpeed;
	int _screenPosX;
	int _screenPosY;

	int _score;
	
public:

	AbilityType 	selectedAbility = AbilityType::TorpedoAbil;
	int 			lockedID;

    Player(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec, float speed,
	float rotation, float angle,
	PicTexture* shieldPic);
    ~Player();
	
	int 	GetScore();
	bool 	IsShielded();
	int 	GetShieldCap();
	int 	GetShieldEn();
	void 	RechargeShield(int fuelCount);
	int 	GetTorpedoCap();
	int 	GetTorpedoCount();
	void 	RechargeTorpedo(int count);

	void CalculateAngle(int mousePosX, int mousePosY);
	void MoveX(float xVec);
	void MoveY(float yVec);
	void InertiaDampeners();

	void RestartBehaviour();

	void RenderOnWindow(int xPlayer, int yPlayer);

	void RetrieveCollectable(ObjectsEnum type);
	void SetShieldActive(bool state);
	void CalculateShield();
};





#endif