
#ifndef RETICLE_HPP
#define RETICLE_HPP

#include "PicTexture.hpp"

class Reticle
{
private:
	GameSDL_Window* _window;
	PicTexture* 	_picture;
	
	const int _size;
	const int _sizeHalf;
	float _angle = 0;
	float _rotatingSpeed = 0;

public:
	Reticle(GameSDL_Window* window, int size, float rotateSpeed);
	~Reticle();

	void Render(int xPos, int yPos);
};




#endif