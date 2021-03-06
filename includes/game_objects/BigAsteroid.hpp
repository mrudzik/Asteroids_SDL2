
#ifndef BIGASTEROID_HPP
#define BIGASTEROID_HPP

#include "Asteroid.hpp"

class BigAsteroid final :
    public Asteroid
{

private:

    /* data */
public:

    BigAsteroid(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec, float speed,
	float rotation, float angle);
    ~BigAsteroid();


};





#endif