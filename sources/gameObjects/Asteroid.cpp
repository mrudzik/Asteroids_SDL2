#include "Asteroid.hpp"

Asteroid::Asteroid(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec,
	float speed, float rotation, float angle) : 
        AbstractGameObject(window, newAvatar, xPos, yPos, xVec, yVec,
        speed, rotation, angle)
{
}

Asteroid::~Asteroid()
{
}