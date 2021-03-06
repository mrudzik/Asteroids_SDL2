#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "AbstractGameObject.hpp"
#include "LockableObject.hpp"

class Asteroid :
	public AbstractGameObject
{
private:
	
	/* data */
public:
	LockableObject lockObj;

	Asteroid(GameSDL_Window* window, PicTexture* newAvatar,
    	int xPos, int yPos, float xVec, float yVec,
		float speed, float rotation, float angle);
	~Asteroid();
};




#endif