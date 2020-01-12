
#include "Informer.hpp"

Informer::Informer(GameSDL_Window* window)
	: _window(window)
{
	text1 = new TextHolder(_window,
		" Asteroids. Powered by SDL2 on C++"
		"\n Created by Max Rudzik"
		"\n F1 for Game Info"
		"\n F2 for Cheat Info"
		,
		_window->font_ArialRegular, _window->GetColor(ColorEnum::White),
		5, 5);
	text2 = new TextHolder(_window,
		" How to play"
		"\n - W,A,S,D or Arrows - to move spaceship"
		"\n - Use Mouse - for Aiming"
		"\n - Left Mouse Button - to shoot"
		"\n - 1,2,3 - to select special ability"
		"\n - Hold Shift - for locking nearest to reticle asteroid"
		"\n - Right Mouse Button - to use selected special ability"
		"\n\n Tips:"
		"\n - Dodge Asteroids to avoid ship destruction"
		"\n - Shoot Asteroids to destroy danger"
		"\n - Collect Minerals and Space Junk"
		"\n\n Special Abilities Description"
		"\n   1. Phase Shield - once activated, grants protection from asteroids"
		"\n for limited time (few seconds)"
		"\n   2. Homing Missile - [requires locking] once locked and activated,"
		"\n follows locked asteroid and then explodes"
		"\n   3. Aimbot Shoot - [requires locking] once locked and activated,"
		"\n shoots aimed bullet to locked asteroid, on intercepting trajectory"
		,
		_window->font_ArialRegular, _window->GetColor(ColorEnum::White),
		300, 50);
	text3 = new TextHolder(_window,
		" Cheat Help"
		"\n    Keypad 1 - Show Player Status"
		"\n    Keypad 2 - Show Objects Status"
		"\n    Keypad 8 - Infinite Torpedos"
		"\n    Keypad 9 - Infinite Shield"
		,
		_window->font_ArialRegular, _window->GetColor(ColorEnum::White),
		300, 50);
}

Informer::~Informer()
{
	delete text1;
	delete text2;
	delete text3;

}


void Informer::RenderText(InfoEnum name)
{
	if (name == InfoEnum::MakersSign)
	{
		text1->RenderText();
	}
	if (name == InfoEnum::HelpText)
	{
		text2->RenderText();
	}
	if (name == InfoEnum::CheatText)
	{
		text3->RenderText();
	}
}