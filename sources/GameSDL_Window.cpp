
#include<GameSDL_Window.hpp>

GameSDL_Window::GameSDL_Window(std::string str, int sizeX, int sizeY,
int win_pos_x, int win_pos_y, int mapX, int mapY):
	_wind_W(sizeX), _wind_W_half(sizeX / 2),
	_wind_H(sizeY), _wind_H_half(sizeY / 2),
	mapSizeX(mapX), mapSizeY(mapY)
{
	std::cout << "SDL Initializing everything" << std::endl;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	std::cout << "Window Start" << std::endl;
	if ((window = SDL_CreateWindow(str.c_str(),
	win_pos_x, win_pos_y, _wind_W, _wind_H, SDL_WINDOW_FOREIGN)))
	{
		std::cout << "Window Created" << std::endl;
		if ((renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_PRESENTVSYNC)))
		{
			std::cout << "Renderer Created" << std::endl;
			std::cout << "Loading Fonts" << std::endl;
			font_ArialRegular = TTF_OpenFont("resourses/fonts/ArialRegular.ttf", 12);
		}
	}
	SDL_ShowCursor(SDL_DISABLE); // This should hide cursor
	std::cout << "Window Initialized" << std::endl;
	return;
}


GameSDL_Window::~GameSDL_Window()
{
	std::cout << "Cleaning Fonts" << std::endl;
	TTF_CloseFont(font_ArialRegular);

	TTF_Quit();

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

SDL_Color 	GameSDL_Window::GetColor(ColorEnum colorName)
{
	SDL_Color tempColor;
	// Basic Black
	tempColor.r = 0;
	tempColor.g = 0;
	tempColor.b = 0;

	switch (colorName)
	{
	case ColorEnum::Red:
		tempColor.r = 255;
		return tempColor;

	case ColorEnum::Green:
		tempColor.g = 255;
		return tempColor;

	case ColorEnum::Blue:
		tempColor.b = 255;
		return tempColor;

	case ColorEnum::White:
		tempColor.r = 255; tempColor.g = 255; tempColor.b = 255;
		return tempColor;

	case ColorEnum::Black:
		return tempColor;
	
	case ColorEnum::Yellow:
		tempColor.r = 255; tempColor.g = 215; tempColor.b = 54;
		return tempColor;

	case ColorEnum::Cyan:
		tempColor.r = 50; tempColor.g = 190; tempColor.b = 245;
		return tempColor;

	default:
		break;
	}

	return tempColor;
}


void 	GameSDL_Window::DrawText(const char* text, int x, int y, SDL_Color color)
{
	SDL_Surface	*fontSurface;
	SDL_Texture	*fontTexture;
	SDL_Rect	fontRect;
	// Texture Width and Height
	int tW, tH;
	
	// Render Text to Surface
	fontSurface = TTF_RenderText_Blended_Wrapped(font_ArialRegular, text, color, _wind_W);
	// Converting that Surface to Texture
	fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	// Query the attributes of a texture
	SDL_QueryTexture(fontTexture, NULL, NULL, &tW, &tH);
	fontRect.x = x;
	fontRect.y = y;
	fontRect.w = tW;
	fontRect.h = tH;
	SDL_RenderCopy(renderer, fontTexture, NULL, &fontRect);
	// Clearing
	SDL_DestroyTexture(fontTexture);
	SDL_FreeSurface(fontSurface);

}


