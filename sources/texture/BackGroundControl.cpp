
#include "BackGroundControl.hpp"

BackGroundControl::BackGroundControl(GameSDL_Window* window)
{
	_window = window;
	_backGroundTexture = new PicTexture();
	_backGroundTexture->LoadFromFile("resourses/background.png", *_window);
}

BackGroundControl::~BackGroundControl()
{
	delete _backGroundTexture;
	_backGroundTexture = NULL;
}


void BackGroundControl::RenderSpecific(int posX, int posY)
{
	_backGroundTexture->RenderPicResized(*_window,
		posX - _window->mapSizeX, posY - _window->mapSizeY,
		NULL, 0, NULL, SDL_FLIP_NONE,
		_window->mapSizeX, _window->mapSizeY);
}
