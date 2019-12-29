
#include "Informer.hpp"

Informer::Informer(GameSDL_Window* window)
	: _window(window)
{
	text1 = new TextHolder(_window, "Hello there from Informer",
		_window->font_ArialRegular, _window->GetColor(ColorEnum::White),
		100, 100);
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