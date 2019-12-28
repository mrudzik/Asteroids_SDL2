
#include<GameSDL_Window.hpp>

GameSDL_Window::GameSDL_Window(std::string str, int sizeX, int sizeY,
int win_pos_x, int win_pos_y, int mapX, int mapY):
	_wind_W(sizeX), _wind_W_half(sizeX / 2),
	_wind_H(sizeY), _wind_H_half(sizeY / 2),
	mapSizeX(mapX), mapSizeY(mapY)
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
	SDL_ShowCursor(SDL_DISABLE); // This should hide cursor
	std::cout << "Window Initialized" << std::endl;
	return;
}


GameSDL_Window::~GameSDL_Window()
{
	std::cout << "Destructing Window" << std::endl;
	if (texture != NULL)
	{
		std::cout << "Destoying Texture" << std::endl;
		SDL_DestroyTexture(texture);
	}
	if (renderer != NULL)
	{
		std::cout << "Destoying Renderer" << std::endl;
		SDL_DestroyRenderer(renderer);
	}
	if (window != NULL)
	{
		std::cout << "Destoying Window" << std::endl;		
		SDL_DestroyWindow(window);
	}
	std::cout << "Destructing Window Complete" << std::endl;

}



int 			GameSDL_Window::GetHeight()
{
	return _wind_H;
}

int 			GameSDL_Window::GetHeightHalf()
{
	return _wind_H_half;
}

int 			GameSDL_Window::GetWidth()
{
	return _wind_W;
}

int 			GameSDL_Window::GetWidthHalf()
{
	return _wind_W_half;
}


SDL_Renderer*	GameSDL_Window::GetRender()
{
	return renderer;
}


// void 			GameSDL_Window::draw_text(const char* text, int x, int y)
// {
// 	SDL_Surface			*font_surf;
// 	SDL_Texture			*font_textr;
// 	SDL_Rect			font_rect;
// 	SDL_Color 			color;
	
// 	int	tw;
// 	int	th;

// 	color.r = 255;
// 	color.g = 255;
// 	color.b = 255;

// 	font_surf = TTF_RenderText_Solid(font_ttf, text, color);
// 	font_textr = SDL_CreateTextureFromSurface(renderer, font_surf);
// 	SDL_QueryTexture(font_textr, NULL, NULL, &tw, &th);
// 	font_rect.x = x;
// 	font_rect.y = y;
// 	font_rect.w = tw;
// 	font_rect.h = th;
// 	SDL_RenderCopy(renderer, font_textr, NULL, &font_rect);
// 	SDL_DestroyTexture(font_textr);
// 	SDL_FreeSurface(font_surf);
// }

// void 	 		GameSDL_Window::DrawWindow(void)
// {
// 	SDL_RenderClear(renderer);
// 	// SDL_UpdateTexture(texture, NULL, _img_buff, _wind_W << 2);
// 	SDL_RenderCopy(renderer, texture, NULL, NULL);
	
// 	// int x;
// 	// int y;

// 	// y = 0;
// 	// while (y < _wind_H)
// 	// {
// 	// 	x = 0;
// 	// 	while (x < _wind_W)
// 	// 	{
// 	// 		_img_buff[y][x] = 0x333333;
// 	// 		x++;
// 	// 	}
// 	// 	y++;
// 	// }
// }

