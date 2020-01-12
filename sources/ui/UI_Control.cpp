
#include "UI_Control.hpp"

UI_Control::UI_Control(GameSDL_Window* window)
	: _window(window), _informer(window),
	_mouseReticle(window, 100, 1)
{

}

UI_Control::~UI_Control()
{
}



void UI_Control::RenderPlayerStatus(
	int const screenX, int const screenY,
	int const mousePosX, int const mousePosY,
	int const mousePosX_world, int const mousePosY_world,
	int const playerPosX, int const playerPosY)
{
	_strBuilder.str("");
	_strBuilder
		<< "\n " << _fpsTimer.TextFrames()
		<< "\n Player World Position"
		<< "\n X:" << playerPosX << " Y:" << playerPosY
		<< "\n Mouse World Position"
		<< "\n X:" << mousePosX_world << " Y:" << mousePosY_world
		<< "\n Mouse Screen Position"
		<< "\n X:" << mousePosX << " Y:" << mousePosY;

	_window->DrawText(_strBuilder.str().c_str(),
		screenX, screenY,
		_window->GetColor(ColorEnum::Yellow));
}

void UI_Control::RenderObjectsStatus(
	int const screenX, int const screenY,
	int const curBullets, int const limBullets,
	int const curAsteroids, int const limAsteroids,
	int const curCollectables,
	int const curTorpedos)
{
	_strBuilder.str("");
	_strBuilder 
		<< "Objects"
		<< "\nCollectables : " << curCollectables
		<< "\nBullets : " << curBullets << " / " << limBullets
		<< "\nTorpedos: " << curTorpedos
		<< "\nAsteroids : " << curAsteroids << " / " << limAsteroids;

	_window->DrawText(_strBuilder.str().c_str(),
		screenX, screenY,
		_window->GetColor(ColorEnum::Yellow));
}

void UI_Control::RenderCurrentCheats(
	int const screenX, int const screenY,
	bool const infShield, bool const infTorpedo,
	bool const showObjects, bool const showPlayerInfo)
{
	if (!infShield && !infTorpedo && !showObjects && !showPlayerInfo)
		return;

	_strBuilder.str("");
	_strBuilder << "Current cheats";
	if (infShield)
		_strBuilder << "\n - Infinite Shield";
	if (infTorpedo)
		_strBuilder << "\n - Infinite Torpedos";
	if (showObjects)
		_strBuilder << "\n - Objects info";
	if (showPlayerInfo)
		_strBuilder << "\n - Player info";
	
	_window->DrawText(_strBuilder.str().c_str(),
		screenX, screenY,
		_window->GetColor(ColorEnum::Yellow));
}

void UI_Control::RenderPlayerUI(
	int const screenX, int const screenY,
	int const score)
{
	_strBuilder.str("");
	_strBuilder
		<< "Score : " << score;
	
	_window->DrawText(_strBuilder.str().c_str(),
		screenX, screenY,
		_window->GetColor(ColorEnum::White)); // TODO Change to yellow and digital font
}

std::string CoolBar(int const maxPoint, int const curPoint, std::string symb)
{
	std::string result = "";
	for (int i = 0; i < maxPoint; i++)
	{
		if (i < curPoint)
			result += symb;
		else
			result += " ";
	}
	return result;
}

void UI_Control::RenderShieldUI(
	int const screenX, int const screenY,
	int const shieldCap, int const shieldEn,
	bool const isShielded)
{
	_strBuilder.str("");
	_strBuilder // Shield : 54 / 100
		<< "Shield  " //<< shieldEn << " / " << shieldCap
		// [///////.....]
		<< "[" << CoolBar(40, 40 * ((float)shieldEn / (float)shieldCap), "/") << "]";
	
	SDL_Color tempColor = _window->GetColor(ColorEnum::White);
	if (isShielded)
	{
		float tempNum = (float)shieldEn / (float)shieldCap;
		if (tempNum < 0.3f)
			tempColor = _window->GetColor(ColorEnum::Red);
		else if (tempNum < 0.6f)
			tempColor = _window->GetColor(ColorEnum::Yellow);
		else
			tempColor = _window->GetColor(ColorEnum::Cyan);
	}
	_window->DrawText(_strBuilder.str().c_str(),
		screenX, screenY,
		tempColor);

}

void UI_Control::RenderTorpedoUI(
	int const screenX, int const screenY,
	int const torpCap, int const torpCount,
	bool const isLocking)
{
	_strBuilder.str("");
	SDL_Color tempColor = _window->GetColor(ColorEnum::White);

	if (isLocking)
	{
		_strBuilder << "Locking";
		if (torpCount < 2)
			tempColor = _window->GetColor(ColorEnum::Red);
		else if (torpCount < torpCap / 2)
			tempColor = _window->GetColor(ColorEnum::Yellow);
		else
			tempColor = _window->GetColor(ColorEnum::Green);
	}
	
	_strBuilder
		<< "\nTorpedos  " << torpCount << " / " << torpCap
		// [00000   ]
		<< "\n > " << CoolBar(torpCap, torpCount, "0");
	
	
	_window->DrawText(_strBuilder.str().c_str(),
		screenX, screenY,
		tempColor);
}

void UI_Control::RenderAutoShootUI(
	int const screenX, int const screenY,
	bool const isLocking)
{
	_strBuilder.str("");
	SDL_Color tempColor = _window->GetColor(ColorEnum::White);
	if (isLocking)
	{
		tempColor = _window->GetColor(ColorEnum::Green);
		_strBuilder << "Locking";
	}
	_strBuilder
		<< "\nAuto Aiming Shot";
	
	_window->DrawText(_strBuilder.str().c_str(),
		screenX, screenY,
		tempColor);
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
	// Cheat Info

	RenderCurrentCheats(
		_window->GetWidth() - 120, 10,
		data.infShield, data.infTorpedo,
		data.showObjectsStatus, data.showPlayerStatus);
	if (data.showObjectsStatus)
		RenderObjectsStatus(
			5, 250,
			data.bullets, data.limBullets,
			data.asteroids, data.limAsteroids,
			data.collectables,
			data.torpedos);
	if (data.showPlayerStatus)
		RenderPlayerStatus(
			5, 100,
			data.mousePosX, data.mousePosY,
			data.mousePosX_world, data.mousePosY_world,
			data.playerPosX, data.playerPosY);

	RenderPlayerUI(
		_window->GetWidthHalf() + 20, _window->GetHeightHalf() - 20,
		data.playerScore);
	RenderShieldUI(
		_window->GetWidthHalf() + 20, _window->GetHeightHalf(),
		data.shieldCapacity, data.shieldEnergy,
		data.isShielded);

	if (data.currentAbility == AbilityType::TorpedoAbil)
		RenderTorpedoUI(
			_window->GetWidthHalf() + 20, _window->GetHeightHalf() + 15,
			data.torpedoCapacity, data.torpedoCount, data.isLocking);
	else if (data.currentAbility == AbilityType::AimshootAbil)
		RenderAutoShootUI(
			_window->GetWidthHalf() + 20, _window->GetHeightHalf() + 15,
			data.isLocking);
}

