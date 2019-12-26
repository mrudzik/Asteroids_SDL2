
#ifndef BACK_GROUND_CONTROL_HPP
#define BACK_GROUND_CONTROL_HPP

#include "PicTexture.hpp"

class BackGroundControl
{

private:
	GameSDL_Window*	_window;
	PicTexture* 	_backGroundTexture;

public:

	BackGroundControl(GameSDL_Window* window);
	~BackGroundControl();

	void RenderSpecific(int posX, int posY);
	// void RenderAll(int playerPosX, int playerPosY);
};





#endif