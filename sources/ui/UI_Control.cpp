
#include "UI_Control.hpp"

UI_Control::UI_Control(GameSDL_Window* window)
	: _window(window), _informer(window),
	_mouseReticle(window, 100, 1)
{

}

UI_Control::~UI_Control()
{
}



void UI_Control::RenderObjectsStatus(int const curBullets, int const limBullets,
	int const curAsteroids, int const limAsteroids)
{
	_strBuilder.str("");
	_strBuilder << "Objects"
		<< "\nBullets : " << curBullets << " / " << limBullets
		<< "\nAsteroids : " << curAsteroids << " / " << limAsteroids;

	_window->DrawText(_strBuilder.str().c_str(),
		_window->GetWidthHalf() + 20, _window->GetHeightHalf() - 20,
		_window->GetColor(ColorEnum::Green));
}

void UI_Control::RenderAll(s_UIData const data)
{
	// Mouse Reticle Rendering
	_mouseReticle.Render(data.mousePosX, data.mousePosY);
	// This will draw some information
	_informer.RenderText(InfoEnum::MakersSign);
	// FPS Counter and Drawer
	_window->DrawText(_fpsTimer.TextFrames().c_str(),
		10, 100, _window->GetColor(ColorEnum::White));


	RenderObjectsStatus(data.bullets, data.limBullets,
		data.asteroids, data.limAsteroids);
}

