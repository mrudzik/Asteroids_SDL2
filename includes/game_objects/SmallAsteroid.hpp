
#ifndef SMALLASTEROID_HPP
#define SMALLASTEROID_HPP

#include "Asteroid.hpp"

class SmallAsteroid final:
    public Asteroid
{
private:

public:

    SmallAsteroid(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec, float speed,
	float rotation, float angle);
    ~SmallAsteroid();

	// void BounceFrom();
};





#endif