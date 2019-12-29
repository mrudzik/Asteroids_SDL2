
#include "UI_Control.hpp"

UI_Control::UI_Control(GameSDL_Window* window)
	: _window(window), _informer(window),
	_mouseReticle(window, 100, 1)
{

}

UI_Control::~UI_Control()
{
}



void UI_Control::RenderBulletStatus(int const curBullets, int const limBullets)
{
	_strBuilder.str("");
	_strBuilder << "Bullets in Space: " << curBullets << "/" << limBullets;

	_window->DrawText(_strBuilder.str().c_str(),
		_window->GetWidthHalf() + 20, _window->GetHeightHalf() - 20,
		_window->GetColor(ColorEnum::Green));
}

void UI_Control::RenderAll(int const mousePosX, int const mousePosY,
	int const curBullets, int const limBullets)
{
	// Mouse Reticle Rendering
	_mouseReticle.Render(mousePosX, mousePosY);
	// This will draw some information
	_informer.RenderText(InfoEnum::MakersSign);
	// FPS Counter and Drawer
	_window->DrawText(_fpsTimer.TextFrames().c_str(),
		10, 100, _window->GetColor(ColorEnum::White));
	RenderBulletStatus(curBullets, limBullets);
}

