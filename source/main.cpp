#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include "point.h"
#include "entities.h"
#include "projectiles.h"
#include "mainfunctions.h"

#include <vector>
#include <string>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;

SDL_Surface *screen = NULL;
SDL_Surface *map = NULL;
SDL_Surface *player = NULL;
SDL_Surface *bullet = NULL;
SDL_Event event;
TTF_Font *font = NULL;
Mix_Chunk *bulletSound = NULL;
SDL_Rect playerSlice[8];

Player playerObject;
std::vector<BaseProjectile*> bulletObjects;
std::vector<SDL_Rect> obstacles;

bool init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
	{
		return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
    
	if(screen == NULL)
	{
		return false;
	}
	if(TTF_Init()==-1)
	{
		return false;
	}
	if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1)
	{
		return false;
	}

	SDL_WM_SetCaption("Some Shooter Mooter", NULL);

	return true;
}

bool load_files()
{
	player=load_image("player.tga",true);
	map=load_image("example_map.tga");
	font=TTF_OpenFont("tf2professor.ttf",30);
	bullet=load_image("bullet.tga",true);
	bulletSound=Mix_LoadWAV("bullet.wav");
	if((player->w)!=(player->h))
	{
		return false;
	}
	if((bullet->w)!=(bullet->h))
	{
		return false;
	}
	if(((bullet->w)%2)!=0)
	{
		return false;
	}
	if(((player->w)%6)!=0)
	{
		return false;
	}
	if(map==NULL)
	{
		return false;
	}
	if(player==NULL)
	{
		return false;
	}
	if(font==NULL)
	{
		return false;
	}
	if(bullet==NULL)
	{
		return false;
	}
	
	int playerSize=(player->w)/3;
	
	playerSlice[0].x=playerSize;
	playerSlice[0].y=0;
	playerSlice[0].w=playerSize;
	playerSlice[0].h=playerSize;
	
	playerSlice[1].x=2*playerSize;
	playerSlice[1].y=0;
	playerSlice[1].w=playerSize;
	playerSlice[1].h=playerSize;
	
	playerSlice[2].x=2*playerSize;
	playerSlice[2].y=playerSize;
	playerSlice[2].w=playerSize;
	playerSlice[2].h=playerSize;
	
	playerSlice[3].x=2*playerSize;
	playerSlice[3].y=2*playerSize;
	playerSlice[3].w=playerSize;
	playerSlice[3].h=playerSize;
	
	playerSlice[4].x=playerSize;
	playerSlice[4].y=2*playerSize;
	playerSlice[4].w=playerSize;
	playerSlice[4].h=playerSize;
	
	playerSlice[5].x=0;
	playerSlice[5].y=2*playerSize;
	playerSlice[5].w=playerSize;
	playerSlice[5].h=playerSize;
	
	playerSlice[6].x=0;
	playerSlice[6].y=playerSize;
	playerSlice[6].w=playerSize;
	playerSlice[6].h=playerSize;
	
	playerSlice[7].x=0;
	playerSlice[7].y=0;
	playerSlice[7].w=playerSize;
	playerSlice[7].h=playerSize;
	
	Point temp((playerSize/2),(playerSize/2));
	Point temp2(map->w,map->h);
	
	playerObject.init(temp,playerSize,0,temp2,&obstacles,2);

	if(bulletSound==NULL)
	{
		return false;
	}
	
	/*SDL_Rect test;
	test.x=100;
	test.y=100;
	test.w=500;
	test.h=100;
	obstacles.push_back(test);
	test.x=100;
	test.y=100;
	test.w=100;
	test.h=500;
	obstacles.push_back(test);*/
	
	return true;
}

void cleanup()
{
	SDL_FreeSurface(map);
	SDL_FreeSurface(player);
	
	for(std::vector<BaseProjectile*>::iterator it=bulletObjects.begin();it!=bulletObjects.end();)
	{
		delete *it;
		bulletObjects.erase(it);
	}
	Mix_FreeChunk(bulletSound);
	TTF_CloseFont(font);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	bool quit=false;
	int moveDirection;
	Uint8 *keyStates=SDL_GetKeyState(NULL);
	
	Uint32 moveTimer = 0;
	Uint32 fps = 0;
	Uint32 shootTimer = 0;
		
	if(init()==false)
	{
		return 1;
	}
	if(load_files()==false)
	{
		return 1;
	}
	
	while(quit==false)
	{
		fps=SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				quit=true;
			}
		}
		
		if((SDL_GetTicks()-moveTimer)>=50)
		{
			if(keyStates[SDLK_w]&&(!keyStates[SDLK_a])&&(!keyStates[SDLK_s])&&(!keyStates[SDLK_d]))
			{
				moveTimer=SDL_GetTicks();
				moveDirection=0;
			}
			else if(keyStates[SDLK_w]&&(!keyStates[SDLK_a])&&(!keyStates[SDLK_s])&&(keyStates[SDLK_d]))
			{
				moveTimer=SDL_GetTicks();
				moveDirection=1;
			}
			else if(!keyStates[SDLK_w]&&(!keyStates[SDLK_a])&&(!keyStates[SDLK_s])&&(keyStates[SDLK_d]))
			{
				moveTimer=SDL_GetTicks();
				moveDirection=2;
			}
			else if(!keyStates[SDLK_w]&&(!keyStates[SDLK_a])&&(keyStates[SDLK_s])&&(keyStates[SDLK_d]))
			{
				moveTimer=SDL_GetTicks();
				moveDirection=3;
			}
			else if(!keyStates[SDLK_w]&&(!keyStates[SDLK_a])&&(keyStates[SDLK_s])&&(!keyStates[SDLK_d]))
			{
				moveTimer=SDL_GetTicks();
				moveDirection=4;
			}
			else if(!keyStates[SDLK_w]&&(keyStates[SDLK_a])&&(keyStates[SDLK_s])&&(!keyStates[SDLK_d]))
			{
				moveTimer=SDL_GetTicks();
				moveDirection=5;
			}
			else if(!keyStates[SDLK_w]&&(keyStates[SDLK_a])&&(!keyStates[SDLK_s])&&(!keyStates[SDLK_d]))
			{
				moveTimer=SDL_GetTicks();
				moveDirection=6;
			}
			else if(keyStates[SDLK_w]&&(keyStates[SDLK_a])&&(!keyStates[SDLK_s])&&(!keyStates[SDLK_d]))
			{
				moveTimer=SDL_GetTicks();
				moveDirection=7;
			}
			else
			{
				moveDirection=-1;
			}
		}
		if(keyStates[SDLK_ESCAPE])
		{
			quit=true;
		}
		if(SDL_GetTicks()-shootTimer>=250)
		{
			if(keyStates[SDLK_SPACE])
			{
				shootTimer=SDL_GetTicks();
				Point temp(map->w,map->h);
				bulletObjects.push_back(new BaseProjectile(playerObject,0,temp,bullet->w,0,&obstacles,4));
				if(Mix_PlayChannel(-1,bulletSound,0)==-1)
				{
					return 1;
				}
			}
		}
			
		SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00));
		if(moveDirection!=-1)
		{
			playerObject.movePlayer(moveDirection);
		}
		
		apply_surface(((SCREEN_WIDTH/2)-((playerObject.getPosition()).getX())),((SCREEN_HEIGHT/2)-((playerObject.getPosition()).getY())),map,screen);
		
		for(std::vector<BaseProjectile*>::iterator it=bulletObjects.begin();it!=bulletObjects.end();it++)
		{
			apply_surface((((SCREEN_WIDTH/2)-((playerObject.getPosition().getX())-((*(*it)).getPosition().getX())))-((*(*it)).getSize()/2)),(((SCREEN_HEIGHT/2)-((playerObject.getPosition().getY())-((*(*it)).getPosition().getY())))-((*(*it)).getSize()/2)),bullet,screen);
			if((*(*it)).hitScan()==true)
			{
				delete *it;
				bulletObjects.erase(it);
				it--;
			}
		}
		
		apply_surface((SCREEN_WIDTH/2)-(player->w/6),((SCREEN_HEIGHT/2)-(player->h/6)),player,screen,&playerSlice[playerObject.getDirection()]);

		if(SDL_Flip(screen)==-1)
		{
			return 1;
		}
		if((SDL_GetTicks()-fps)<(1000/FRAMES_PER_SECOND))
		{
			SDL_Delay((1000/FRAMES_PER_SECOND)-(SDL_GetTicks()-fps));
		}
	}
	
	cleanup();
	return 0;
}
