#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include "point.h"
#include "entities.h"
#include "projectiles.h"
#include "mainfunctions.h"
#include "weapons.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;

SDL_Surface *screen = NULL;
SDL_Surface *map = NULL;
SDL_Surface *player = NULL;
SDL_Surface *bullet = NULL;
SDL_Surface *enemy = NULL;
SDL_Surface *scoreDisplay = NULL;
SDL_Surface *healthDisplay = NULL;
SDL_Color textColor = {255,255,255};

SDL_Event event;
TTF_Font *font = NULL;
Mix_Chunk *bulletSound = NULL;
SDL_Rect playerSlice[8];
SDL_Rect enemySlice[8];

Player playerObject;
Weapon primary;
Weapon secondary;
Weapon melee;

std::vector<BaseProjectile*> projectiles;
std::vector<SDL_Rect> obstacles;
std::vector<Enemy*> enemies;

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
	player=load_image("player.tga");
	enemy=load_image("enemy.tga");
	map=load_image("example_map.tga");
	font=TTF_OpenFont("tf2professor.ttf",30);
	bullet=load_image("bullet.tga",true);
	bulletSound=Mix_LoadWAV("bullet.wav");
	if((player->w)!=(player->h))
	{
		return false;
	}
	if((enemy->w)!=(enemy->h))
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
	if(((enemy->w)%6)!=0)
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
	
	int enemySize=(enemy->w)/3;
	
	enemySlice[0].x=enemySize;
	enemySlice[0].y=0;
	enemySlice[0].w=enemySize;
	enemySlice[0].h=enemySize;
	
	enemySlice[1].x=2*enemySize;
	enemySlice[1].y=0;
	enemySlice[1].w=enemySize;
	enemySlice[1].h=enemySize;
	
	enemySlice[2].x=2*enemySize;
	enemySlice[2].y=enemySize;
	enemySlice[2].w=enemySize;
	enemySlice[2].h=enemySize;
	
	enemySlice[3].x=2*enemySize;
	enemySlice[3].y=2*enemySize;
	enemySlice[3].w=enemySize;
	enemySlice[3].h=enemySize;
	
	enemySlice[4].x=enemySize;
	enemySlice[4].y=2*enemySize;
	enemySlice[4].w=enemySize;
	enemySlice[4].h=enemySize;
	
	enemySlice[5].x=0;
	enemySlice[5].y=2*enemySize;
	enemySlice[5].w=enemySize;
	enemySlice[5].h=enemySize;
	
	enemySlice[6].x=0;
	enemySlice[6].y=enemySize;
	enemySlice[6].w=enemySize;
	enemySlice[6].h=enemySize;
	
	enemySlice[7].x=0;
	enemySlice[7].y=0;
	enemySlice[7].w=enemySize;
	enemySlice[7].h=enemySize;
	
	//Origin,Size,Direction,MapSize,&obstacles,Speed,Health,Max Health,&enemies)
	playerObject.init(Point(playerSize/2,playerSize/2),playerSize,0,Point(map->w,map->h),&obstacles,8,100,100,&enemies);
	//Type,Projectile Type,Projectile Speed,ROF,DMG,&projectiles)
	primary.init(0,0,20,4,2,&projectiles);
	secondary.init(1,0,15,2,4,&projectiles);
	melee.init(2,0,10,1,6,&projectiles);

	SDL_Rect test;
	test.x=632;
	test.y=632;
	test.w=103;
	test.h=103;
	obstacles.push_back(test);
	test.x=1185;
	test.y=632;
	test.w=103;
	test.h=103;
	obstacles.push_back(test);
	test.x=1185;
	test.y=1185;
	test.w=103;
	test.h=103;
	obstacles.push_back(test);
	test.x=632;
	test.y=1185;
	test.w=103;
	test.h=103;
	obstacles.push_back(test);
	
	if(bulletSound==NULL)
	{
		return false;
	}
	
	return true;
}

void cleanup()
{
	SDL_FreeSurface(map);
	SDL_FreeSurface(player);
	
	for(std::vector<BaseProjectile*>::iterator it=projectiles.begin();it!=projectiles.end();)
	{
		delete *it;
		projectiles.erase(it);
	}
	
	for(std::vector<Enemy*>::iterator it=enemies.begin();it!=enemies.end();)
	{
		delete *it;
		enemies.erase(it);
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
	int currentWeapon=0;
	bool fireSound=false;
	Uint8 *keyStates=SDL_GetKeyState(NULL);
	
	Uint32 moveTimer=0;
	Uint32 fps=0;
	Uint32 changeWeapon=0;
	Uint32 spawnTimer=0;
	int spawnPlace=0;
	
	int score=0;
	int health;
	std::ostringstream temp;
	std::string temp2;
		
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
			
			if(event.type==SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_1:
						if(currentWeapon!=0)
						{
							changeWeapon=SDL_GetTicks();
						}
						currentWeapon=0;
						break;
						
					case SDLK_2:
						if(currentWeapon!=1)
						{
							changeWeapon=SDL_GetTicks();
						}
						currentWeapon=1;
						break;
						
					case SDLK_3:
						if(currentWeapon!=2)
						{
							changeWeapon=SDL_GetTicks();
						}
						currentWeapon=2;
						break;
				}
			}
		}
		if((SDL_GetTicks()-spawnTimer)>=5000-250*(score/10))
		{
			if(spawnPlace==0)
			{
				enemies.push_back(new Enemy(Point(960,245),Point(map->w,map->h),4,(enemy->w)/3,4,&obstacles,10,10,&enemies,2,&playerObject));
				spawnPlace++;
			}
			else if(spawnPlace==1)
			{
				enemies.push_back(new Enemy(Point(1675,960),Point(map->w,map->h),6,(enemy->w)/3,4,&obstacles,10,10,&enemies,2,&playerObject));
				spawnPlace++;
			}
			else if(spawnPlace==2)
			{
				enemies.push_back(new Enemy(Point(960,1675),Point(map->w,map->h),0,(enemy->w)/3,4,&obstacles,10,10,&enemies,2,&playerObject));
				spawnPlace++;
			}
			else
			{
				enemies.push_back(new Enemy(Point(245,960),Point(map->w,map->h),2,(enemy->w)/3,4,&obstacles,10,10,&enemies,2,&playerObject));
				spawnPlace=0;
			}
			spawnTimer=SDL_GetTicks();
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
		
		if(keyStates[SDLK_SPACE])
		{
			if(currentWeapon==0)
			{
				if(SDL_GetTicks()-changeWeapon>=500)
				{
					fireSound=primary.fire(playerObject,Point(map->w,map->h),bullet->w,&obstacles, &enemies);
				}
			}
			else if(currentWeapon==1)
			{
				if(SDL_GetTicks()-changeWeapon>=500)
				{
					fireSound=secondary.fire(playerObject,Point(map->w,map->h),bullet->w,&obstacles, &enemies);
				}
			}
			else if(currentWeapon==2)
			{
				if(SDL_GetTicks()-changeWeapon>=500)
				{
					fireSound=melee.fire(playerObject,Point(map->w,map->h),bullet->w,&obstacles, &enemies);
				}
			}
			if(fireSound==true)
			{
				if(Mix_PlayChannel(-1,bulletSound,0)==-1)
				{
					return 1;
				}
			}
		}
		SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00));
		if(moveDirection!=-1)
		{
			playerObject.move(moveDirection);
		}
		
		apply_surface(((SCREEN_WIDTH/2)-((playerObject.getPosition()).getX())),((SCREEN_HEIGHT/2)-((playerObject.getPosition()).getY())),map,screen);

		for(std::vector<BaseProjectile*>::iterator it=projectiles.begin();it!=projectiles.end();it++)
		{
			apply_surface((((SCREEN_WIDTH/2)-((playerObject.getPosition().getX())-((*(*it)).getPosition().getX())))-((*(*it)).getSize()/2)),(((SCREEN_HEIGHT/2)-((playerObject.getPosition().getY())-((*(*it)).getPosition().getY())))-((*(*it)).getSize()/2)),bullet,screen);
			
			if((*(*it)).hitScan()==true)
			{
				delete *it;
				projectiles.erase(it);
				it--;
			}
		}
		
		for(std::vector<Enemy*>::iterator it=enemies.begin();it!=enemies.end();it++)
		{
			if((*(*it)).getHealth()==0)
			{
				score++;
				if(score==100)
				{
					playerObject.heal(10);
				}
				delete *it;
				enemies.erase(it);
				it--;
			}
			else
			{
				(*(*it)).move();
				apply_surface((((SCREEN_WIDTH/2)-((playerObject.getPosition().getX())-((*(*it)).getPosition().getX())))-((*(*it)).getSize()/2)),(((SCREEN_HEIGHT/2)-((playerObject.getPosition().getY())-((*(*it)).getPosition().getY())))-((*(*it)).getSize()/2)),enemy,screen,&enemySlice[(*(*it)).getDirection()]);
			}
		}
		
		health=playerObject.getHealth();

		apply_surface((SCREEN_WIDTH/2)-(player->w/6),((SCREEN_HEIGHT/2)-(player->h/6)),player,screen,&playerSlice[playerObject.getDirection()]);
		
		temp.str("");
		temp<<health;
		temp2=temp.str();
		healthDisplay=TTF_RenderText_Solid(font,temp2.c_str(),textColor);
		temp.str("");
		temp<<score;
		temp2=temp.str();
		scoreDisplay=TTF_RenderText_Solid(font,temp2.c_str(),textColor);
		
		apply_surface(0,0,healthDisplay,screen);
		apply_surface(200,0,scoreDisplay,screen);

		if(SDL_Flip(screen)==-1)
		{
			return 1;
		}
		
		if(playerObject.getHealth()==0)
		{
			quit=true;
		}
		
		if((SDL_GetTicks()-fps)<(1000/FRAMES_PER_SECOND))
		{
			SDL_Delay((1000/FRAMES_PER_SECOND)-(SDL_GetTicks()-fps));
		}
	}
	
	cleanup();
	return 0;
}
