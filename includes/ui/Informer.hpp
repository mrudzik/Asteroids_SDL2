
#ifndef INFORMER_HPP
#define INFORMER_HPP

#include "GameSDL_Window.hpp"
#include "TextHolder.hpp"

enum InfoEnum
{
	MakersSign
};

class Informer
{// This class must be used to hold structs with messages
// And print them whenever and wherever need
// without rendering same message every frame

private:
	GameSDL_Window* _window;

	TextHolder* text1;



public:
	Informer(GameSDL_Window* window);
	~Informer();

	void RenderText(InfoEnum name);
};






#endif