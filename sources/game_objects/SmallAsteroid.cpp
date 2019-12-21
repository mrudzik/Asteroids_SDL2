
#include "SmallAsteroid.hpp"


SmallAsteroid::SmallAsteroid(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec, float speed, float rotation,
    float angle) : 
        AbstractGameObject(window, newAvatar, xPos, yPos, xVec, yVec,
        speed, rotation, angle)
{

}

SmallAsteroid::~SmallAsteroid()
{
}

void 	SmallAsteroid::BounceRand()
{
	int random = rand() % 4;
	float randDir = random / 10;

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
		_xVec -= randDir;
		_yVec += randDir;
	}
	else
	{
		_rotationSpeed += 0.2f;
		_xVec += randDir;
		_yVec -= randDir;
	}
	
	_rotationSpeed *= -1;
	_xVec *= -1;
	_yVec *= -1;
}