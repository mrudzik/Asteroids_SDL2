#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "AbstractGameObject.hpp"
#include "Asteroid.hpp"

class Player final: public AbstractGameObject
{

private:
	PicTexture* _shieldPic;
	bool _isShielded;
	float _shieldAngle;
	
	float _slowingSpeed;
	int _screenPosX;
	int _screenPosY;

	int _score;

public:

	Asteroid* lockedObject;

    Player(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec, float speed,
	float rotation, float angle,
	PicTexture* shieldPic);
    ~Player();
	
	int 	GetScore();
	bool 	IsShielded();

	void CalculateAngle(int mousePosX, int mousePosY);
	void MoveX(float xVec);
	void MoveY(float yVec);
	void InertiaDampeners();

	void RestartBehaviour();

	void RenderOnWindow(int xPlayer, int yPlayer);

	void RetrieveCollectable(ObjectsEnum type);
	void SetShieldActive(bool state);
};





#endif