#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#ifndef MAINFUNCTIONS_H_
#define MAINFUNCTIONS_H_

SDL_Surface *load_image(std::string filename, bool alpha=false);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

#endif
