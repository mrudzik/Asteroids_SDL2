
#include<GameSDL_Window.hpp>

GameSDL_Window::GameSDL_Window(std::string str, int sizeX, int sizeY,
int win_pos_x, int win_pos_y): _wind_W(sizeX), _wind_H(sizeY)
{
	std::cout << "Window Start" << std::endl;
	if ((window = SDL_CreateWindow(str.c_str(),
	win_pos_x, win_pos_y, _wind_W, _wind_H, SDL_WINDOW_FOREIGN)))
	{
		std::cout << "Window Created" << std::endl;
		if ((renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_PRESENTVSYNC)))
		{
			std::cout << "Renderer Created" << std::endl;
			// if ((texture = SDL_CreateTexture(renderer,
			// SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, _wind_W, _wind_H)))
			// {
			// 	std::cout << "Texture Created" << std::endl;
			// 	// font_ttf = TTF_OpenFont("ARIAL.TTF", 15);
			// 	key_state = SDL_GetKeyboardState(NULL);
			// }
			SDL_Delay( 2000 );
		}
	}
	std::cout << "Window Initialized" << std::endl;
	return;
}


GameSDL_Window::~GameSDL_Window()
{
		if (texture != NULL)
			SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

