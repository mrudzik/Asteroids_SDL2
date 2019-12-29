
#ifndef GAMESDL_WINDOW_HPP
#define GAMESDL_WINDOW_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

// # include "SDL_image.h"
// # include "SDL_mixer.h"
// # include "SDL_ttf.h"
// # include "SDL_net.h"

#define RENDER_TRESHOLD 50

enum ColorEnum
{// Just Collection of often used collors
	White, Black, // Basic Colors
	Red, Green, Blue // Standart Colors

};

class GameSDL_Window
{

private:

	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;


	

	int 				_wind_W;
	int 				_wind_W_half;
	int 				_wind_H;
	int 				_wind_H_half;

public:
	TTF_Font			*font_ArialRegular;

	const int 	mapSizeX;
	const int 	mapSizeY;

	int 			GetWidth();
	int 			GetWidthHalf();
	int 			GetHeight();
	int 			GetHeightHalf();
	SDL_Renderer*	GetRender();


	SDL_Color 	GetColor(ColorEnum colorName);
	void 	DrawText(const char* text, int x, int y, SDL_Color color);


	GameSDL_Window(std::string str, int sizeX, int sizeY,
	int win_pos_x, int win_pos_y, int mapX, int mapY);
	~GameSDL_Window();

};

#endif
