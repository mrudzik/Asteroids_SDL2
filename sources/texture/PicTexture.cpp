#include "PicTexture.hpp"

PicTexture::PicTexture()
{
//Initialization
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

PicTexture::~PicTexture()
{
	FreeTexture();
}

SDL_Texture* 	PicTexture::GetTexture(void)
{
	return (this->mTexture);
}

int     PicTexture::GetWidth(void)
{
	return (this->mWidth);
}

int     PicTexture::GetHeight(void)
{
	return (this->mHeight);
}





void    PicTexture::FreeTexture(void)
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

bool    PicTexture::LoadFromFile(std::string path, GameSDL_Window &wind)
{
	FreeTexture();
	//Final Texture
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path << std::endl;
		std::cout << "SDL Error " << SDL_GetError() << std::endl;
	}
	else
	{   //Color key image
		//SDL_MapRGB -> sets transparent pixel with something
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		//Create Texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(wind.GetRender(), loadedSurface);
		if ( newTexture == NULL)
		{
			std::cout << "Unable to create texture from " << path << std::endl;
			std::cout << "SDL Error " << SDL_GetError() << std::endl;
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		// Get rid of temp surface
		SDL_FreeSurface (loadedSurface);
	}
	this->mTexture = newTexture;
	return (this->mTexture != NULL);
}

void 	PicTexture::RenderPic(GameSDL_Window &wind, int x, int y,
SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopyEx(wind.GetRender(), mTexture, clip, &renderQuad,
        angle, center, flip);
}



