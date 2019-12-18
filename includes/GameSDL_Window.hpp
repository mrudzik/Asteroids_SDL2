
#ifndef GAMESDL_WINDOW_HPP
#define GAMESDL_WINDOW_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

// # include "SDL_image.h"
// # include "SDL_mixer.h"
// # include "SDL_ttf.h"
// # include "SDL_net.h"

class GameSDL_Window
{

private:

	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	// TTF_Font			*font_ttf;
	
	int 				_wind_W;
	int 				_wind_H;

	GameSDL_Window(void){
		return;
	}

public:
	
	int 			GetWidth(void);
	int 			GetHeight(void);
	SDL_Renderer*	GetRender(void);

	// void 			DrawText(const char* text, int x, int y);
	// void 	 		DrawWindow(void);

	GameSDL_Window(std::string str, int sizeX, int sizeY,
	int win_pos_x, int win_pos_y);
	~GameSDL_Window();

};

#endif
