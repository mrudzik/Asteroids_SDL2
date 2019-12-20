
#ifndef SMALLASTEROID_HPP
#define SMALLASTEROID_HPP

#include "AbstractGameObject.hpp"

class SmallAsteroid : public AbstractGameObject
{

private:

    /* data */
public:

    SmallAsteroid(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec, float speed,
	float rotation, float angle);
    ~SmallAsteroid();

};





#endif