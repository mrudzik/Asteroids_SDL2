
#include "UI_Control.hpp"

UI_Control::UI_Control(GameSDL_Window* window)
	: _window(window), _informer(window),
	_mouseReticle(window, 100, 1)
{

}

UI_Control::~UI_Control()
{
}



void UI_Control::RenderPlayerStatus(int const mousePosX, int const mousePosY,
	int const playerPosX, int const playerPosY)
{
	_strBuilder.str("");
	_strBuilder
		<< "\n " << _fpsTimer.TextFrames()
		<< "\n\n Player World Position"
		<< "\n X:" << playerPosX << " Y:" << playerPosY
		<< "\n\n Mouse Screen Position"
		<< "\n X:" << mousePosX << " Y:" << mousePosY;

	_window->DrawText(_strBuilder.str().c_str(),
		5, 100, _window->GetColor(ColorEnum::Green));
}

void UI_Control::RenderObjectsStatus(int const curBullets, int const limBullets,
	int const curAsteroids, int const limAsteroids)
{
	_strBuilder.str("");
	_strBuilder 
		<< "Objects"
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
	if (data.showHelp)
		_informer.RenderText(InfoEnum::HelpText);
	if (data.showCheatHelp)
		_informer.RenderText(InfoEnum::CheatText);
	if (data.showObjectsStatus)
		RenderObjectsStatus(data.bullets, data.limBullets,
			data.asteroids, data.limAsteroids);
	if (data.showPlayerStatus)
		RenderPlayerStatus(data.mousePosX, data.mousePosY,
			data.playerPosX, data.playerPosY);
}

