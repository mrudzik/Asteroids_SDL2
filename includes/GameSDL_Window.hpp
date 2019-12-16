
#ifndef GAMESDL_WINDOW_HPP
#define GAMESDL_WINDOW_HPP


// class GameSDL_Window
// {
// private:
// 	// Private fields here
// public:
// 	// Constructor/Destructor
// 	GameSDL_Window();
// 	~GameSDL_Window();
// };

# include <iostream>

# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "SDL_net.h"

#define 	W 	1200
#define 	H 	1200

class GameSDL_Window
{

private:

	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	TTF_Font			*font_ttf;
	
	int 				_wind_W;
	int 				_wind_H;
	int 				_img_buff[H][W];


	GameSDL_Window(void){
		return;
	}

public:
	const Uint8			*key_state;
	
	int 			getWidth(void);
	int 			getHeight(void);

	void 			draw_text(const char* text, int x, int y);
	void 	 		draw_window(void);

	SDL_Renderer*	get_render(void);

	
	

	GameSDL_Window(std::string str, int win_pos_x, int win_pos_y);

	~GameSDL_Window();

};

#endif
