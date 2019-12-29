#ifndef UI_CONTROL_HPP
#define UI_CONTROL_HPP

#include "Reticle.hpp"
#include "Informer.hpp"
#include "FPS_Timer.hpp"


class UI_Control
{
private:
	GameSDL_Window* _window;

	Informer 	_informer;
	Reticle 	_mouseReticle;
	FPS_Timer	_fpsTimer;

	std::stringstream	_strBuilder;

public:
	UI_Control(GameSDL_Window* window);
	~UI_Control();

	void 	RenderAll(int const mousePosX, int const mousePosY,
		int const curBullets, int const limBullets);
	
	void 	RenderBulletStatus(int const curBullets, int const limBullets);
	
};




#endif