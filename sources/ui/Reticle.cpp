
#include "Reticle.hpp"

Reticle::Reticle(GameSDL_Window* window, int size, float rotateSpeed)
	: _size(size), _sizeHalf(size / 2)
{
	_window = window;
	_rotatingSpeed = rotateSpeed;

	_picture = new PicTexture;
	_picture->LoadFromFile("resourses/reticle.png", *_window);

}

Reticle::~Reticle()
{
	delete _picture;
	_picture = NULL;
}

void	Reticle::Render(int xPos, int yPos)
{
	_angle += _rotatingSpeed;
	_picture->RenderPicResized(*_window,
		xPos - _sizeHalf, yPos - _sizeHalf,
			NULL, _angle, NULL, SDL_FLIP_NONE, _size, _size);
}