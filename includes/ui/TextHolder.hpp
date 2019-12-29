
#ifndef TEXT_HOLDER_HPP
#define TEXT_HOLDER_HPP

#include "GameSDL_Window.hpp"


class TextHolder
{// The main purpose of this class is optimization
// There is no need to calculate how same text looks every frame
// It's better when we just have it saved and only render it

private:
	GameSDL_Window* _window;

	// Texture with needed Text
	SDL_Texture*	_fontTexture;
	// Needed text position
	SDL_Rect		_fontRect;

public:
	TextHolder(GameSDL_Window* window,
		const char* str, TTF_Font* font, SDL_Color color,
		int posX, int posY);
	~TextHolder();

	void RenderText();
};





#endif