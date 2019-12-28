#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "AbstractGameObject.hpp"

class Player final: public AbstractGameObject
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
	
	void CalculateAngle(int mousePosX, int mousePosY);
	void MoveX(float xVec);
	void MoveY(float yVec);
	void InertiaDampeners();

	void RestartBehaviour();

	void RenderOnWindow(int xPlayer, int yPlayer);

};





#endif