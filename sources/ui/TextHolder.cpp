
#include "TextHolder.hpp"


TextHolder::TextHolder(GameSDL_Window* window,
	const char* str, TTF_Font* font, SDL_Color color,
	int posX, int posY)
: _window(window)
{
	// Temporary surface
	SDL_Surface	*fontSurface;
	// Texture Width and Height
	int tW, tH;
	
	// Render Text to Surface
	fontSurface = TTF_RenderText_Solid(font, str, color);
	// Converting that Surface to Texture
	_fontTexture = SDL_CreateTextureFromSurface(_window->GetRender(), fontSurface);
	// Query the attributes of a texture
	SDL_QueryTexture(_fontTexture, NULL, NULL, &tW, &tH);
	_fontRect.x = posX;
	_fontRect.y = posY;
	_fontRect.w = tW;
	_fontRect.h = tH;
	// Clearing Temp stuff
	SDL_FreeSurface(fontSurface);
}

TextHolder::~TextHolder()
{
	SDL_DestroyTexture(_fontTexture);
}

void TextHolder::RenderText()
{
	SDL_RenderCopy(_window->GetRender(), _fontTexture, NULL, &_fontRect);
}