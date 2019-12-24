
#include "BackGroundControl.hpp"

BackGroundControl::BackGroundControl(GameSDL_Window* window)
{
	_window = window;
	_backGroundTexture = new PicTexture();
	_backGroundTexture->LoadFromFile("resourses/backgroundDebug.png", *_window);
}

BackGroundControl::~BackGroundControl()
{
	delete _backGroundTexture;
	_backGroundTexture = NULL;
}


void BackGroundControl::RenderAll(int playerPosX, int playerPosY)
{
	_backGroundTexture->RenderPic(*_window, playerPosX, playerPosY, NULL, 0, NULL, SDL_FLIP_NONE);
}