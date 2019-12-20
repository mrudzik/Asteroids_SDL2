
#ifndef BULLET_HPP
#define BULLET_HPP

#include "AbstractGameObject.hpp"

class Bullet : public AbstractGameObject
{

private:

    /* data */
public:

    Bullet(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec, float speed,
	float rotation, float angle);
    ~Bullet();

};





#endif