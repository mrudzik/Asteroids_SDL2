#ifndef PICTEXTURE_HPP
#define PICTEXTURE_HPP

#include "GameSDL_Window.hpp"

class 	PicTexture
{

private:

	SDL_Texture* 	mTexture;

	int				mWidth;
	int 			mHeight;

public:

SDL_Texture* 	GetTexture(void);
int 			GetWidth(void);
int 			GetHeight(void);

void	FreeTexture(void);
bool	LoadFromFile(std::string path, GameSDL_Window &wind);
void	RenderPic(GameSDL_Window &wind, int x, int y, SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

	PicTexture();
	~PicTexture();
};


#endif