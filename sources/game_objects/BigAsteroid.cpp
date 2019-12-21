
#include "BigAsteroid.hpp"

BigAsteroid::BigAsteroid(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec, float speed, float rotation,
    float angle) : 
        AbstractGameObject(window, newAvatar, xPos, yPos, xVec, yVec,
        speed, rotation, angle)
{

}

BigAsteroid::~BigAsteroid()
{
}

void 	BigAsteroid::BounceRand()
{
	int random = rand() % 4;
	
	if (random == 0)
	{
		_rotationSpeed += 0.1f;
	}
	else if (random == 1)
	{
		_rotationSpeed += -0.1f;
	}
	else if (random == 2)
	{
		_rotationSpeed += -0.3f;
		_xVec -= random / 10;
		_yVec += random / 10;
	}
	else
	{
		_rotationSpeed += 0.2f;
		_xVec -= random / 10;
		_yVec += random / 10;
	}
	
	_rotationSpeed *= -1;
	_xVec *= -1;
	_yVec *= -1;
}