
#include<GameSDL_Window.hpp>

GameSDL_Window::GameSDL_Window(std::string str, int sizeX, int sizeY,
int win_pos_x, int win_pos_y): _wind_W(sizeX), _wind_H(sizeY)
{
	std::cout << "SDL Initializing everything" << std::endl;
	SDL_Init(SDL_INIT_EVERYTHING);


	std::cout << "Window Start" << std::endl;
	if ((window = SDL_CreateWindow(str.c_str(),
	win_pos_x, win_pos_y, _wind_W, _wind_H, SDL_WINDOW_FOREIGN)))
	{
		std::cout << "Window Created" << std::endl;
		if ((renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_PRESENTVSYNC)))
		{
			std::cout << "Renderer Created" << std::endl;
			// SDL_Delay( 2000 );
		}
	}
	std::cout << "Window Initialized" << std::endl;
	return;
}


GameSDL_Window::~GameSDL_Window()
{
	std::cout << "Shutting down" << std::endl;
	if (texture != NULL)
		SDL_DestroyTexture(texture);
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);
	if (window != NULL)
		SDL_DestroyWindow(window);
}

