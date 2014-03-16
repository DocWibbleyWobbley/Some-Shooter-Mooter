#include "mainfunctions.h"

SDL_Surface *load_image(std::string filename, bool alpha)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage!=NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		if(optimizedImage!=NULL)
		{
			if(alpha==false)
			{
        		optimizedImage = SDL_DisplayFormat(loadedImage);
			}
			else
			{
				optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
			}
		}
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
    
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface(source,clip,destination,&offset);
}
