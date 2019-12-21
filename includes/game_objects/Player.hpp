#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "AbstractGameObject.hpp"

class Player : public AbstractGameObject
{

private:

    /* data */
	float _slowingSpeed;
	int _screenPosX;
	int _screenPosY;

public:

    Player(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec, float speed,
	float rotation, float angle);
    ~Player();

	int GetPosX();
	int GetPosY();
	float GetAngle();
	
	
	void CalculateAngle();
	void MoveX(float xVec);
	void MoveY(float yVec);
	void InertiaDampeners();


};





#endif