
#include "Informer.hpp"

Informer::Informer(GameSDL_Window* window)
	: _window(window)
{
	text1 = new TextHolder(_window, " Asteroids. Powered by SDL2 on C++\n Created by Max Rudzik",
		_window->font_ArialRegular, _window->GetColor(ColorEnum::White),
		5, 5);
}

Informer::~Informer()
{
	delete text1;
}


void Informer::RenderText(InfoEnum name)
{
	if (name == InfoEnum::MakersSign)
	{
		text1->RenderText();
	}
}