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
	
	void 	RestartBehaviour();
	void 	RenderOnWindow(int xPlayer, int yPlayer);

	// Score
	int 	GetScore();
	// Retrieving stuff stuff ;P
	void 	RetrieveCollectable(ObjectsEnum type);

	// Shield Stuff
	bool 	IsShielded();
	int 	GetShieldCap();
	int 	GetShieldEn();
	void 	RechargeShield(int fuelCount);
	void 	SetShieldActive(bool state);
	void 	CalculateShield();
	// Torpedo Stuff
	int 	GetTorpedoCap();
	int 	GetTorpedoCount();
	void 	RechargeTorpedo(int count);

	// Moving stuff
	void 	MoveX(float xVec);
	void 	MoveY(float yVec);
	void 	InertiaDampeners();
	void 	CalculateAngle(int mousePosX, int mousePosY);

	

	
};





#endif