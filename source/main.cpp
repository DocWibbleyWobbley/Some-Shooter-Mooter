#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include "point.h"
#include "entities.h"
#include "projectiles.h"
#include "mainfunctions.h"
#include "weapons.h"
#include "items.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;
const int HUD_SIZE = 100;

SDL_Surface *screen = NULL;
SDL_Surface *map = NULL;
SDL_Surface *player = NULL;
SDL_Surface *bullet = NULL;
SDL_Surface *enemy = NULL;
SDL_Surface *hudSurface = NULL;
SDL_Surface *menuSurface = NULL;
SDL_Surface *optionSurface = NULL;
SDL_Surface *highlightOptionSurface = NULL;
SDL_Surface *text = NULL;
SDL_Surface *pistols = NULL;
SDL_Surface *rpg = NULL;
SDL_Surface *bfg = NULL;
SDL_Surface *laser = NULL;
SDL_Surface *highlightWeapon = NULL;
SDL_Surface *weapon1 = NULL;
SDL_Surface *weapon2 = NULL;
SDL_Surface *weapon3 = NULL;
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
int weapons[4]={0,0,0,0};
int score=0;
bool game=false;

std::vector<BaseProjectile*> projectiles;
std::vector<SDL_Rect> obstacles;
std::vector<Enemy*> enemies;
std::vector<Item*> backpack;

std::stringstream stream;
std::string txtString;

bool market[15];

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
	enemy=load_image("enemy.tga",true);
	map=load_image("example_map.tga");
	font=TTF_OpenFont("tf2professor.ttf",30);
	pistols=load_image("pistols.tga");
	rpg=load_image("rpg.tga");
	bfg=load_image("bfg.tga");
	laser=load_image("laser.tga");
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
	if(pistols==NULL)
	{
		return false;
	}
	if(rpg==NULL)
	{
		return false;
	}
	if(bfg==NULL)
	{
		return false;
	}
	if(laser==NULL)
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
	
	hudSurface=SDL_CreateRGBSurface(SDL_HWSURFACE,SCREEN_WIDTH,HUD_SIZE,32,0,0,0,0);
	menuSurface=SDL_CreateRGBSurface(SDL_HWSURFACE,SCREEN_WIDTH,SCREEN_HEIGHT,32,0,0,0,0);
	optionSurface=SDL_CreateRGBSurface(SDL_HWSURFACE,SCREEN_WIDTH/4,SCREEN_HEIGHT/16,32,0,0,0,0);
	highlightOptionSurface=SDL_CreateRGBSurface(SDL_HWSURFACE,(SCREEN_WIDTH/4)+(SCREEN_WIDTH/32),(SCREEN_HEIGHT/16)+(SCREEN_WIDTH/32),32,0,0,0,0);
	highlightWeapon=SDL_CreateRGBSurface(SDL_HWSURFACE,80,80,32,0,0,0,0);
	
	for(int i=0;i<11;i++)
	{
		market[i]=false;
	}
	
	//Origin,Size,Direction,MapSize,&obstacles,Speed,Health,Max Health,&enemies,&backpack,Money
	playerObject.init(Point(map->w/2,map->h/2),playerSize,0,Point(map->w,map->h),&obstacles,8,100,100,&enemies,&backpack);

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
	test.x=0;
	test.y=0;
	test.w=1920;
	test.h=182;
	obstacles.push_back(test);
	test.x=0;
	test.y=0;
	test.w=182;
	test.h=1920;
	obstacles.push_back(test);
	test.x=0;
	test.y=1738;
	test.w=1920;
	test.h=182;
	obstacles.push_back(test);
	test.x=1738;
	test.y=0;
	test.w=182;
	test.h=1920;
	obstacles.push_back(test);
	
	if(bulletSound==NULL)
	{
		return false;
	}
	
	return true;
}

void renderHUD(int score,int currentWeapon)
{
	SDL_FillRect(hudSurface,NULL,SDL_MapRGB(screen->format,0x40,0x40,0x40));
	
	stream.str("");
	stream<<"Health: "<<playerObject.getHealth();
	txtString=stream.str();
	text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
	apply_surface(SCREEN_WIDTH/8-text->w/2,HUD_SIZE/3-text->h/2,text,hudSurface);
	
	stream.str("");
	stream<<"Max Health: "<<playerObject.getMaxHealth();
	txtString=stream.str();
	text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
	apply_surface(SCREEN_WIDTH/8-text->w/2,HUD_SIZE/3*2-text->h/2,text,hudSurface);
	
	stream.str("");
	stream<<"Money: "<<playerObject.getMoney();
	txtString=stream.str();
	text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
	apply_surface(SCREEN_WIDTH/8*7-text->w/2,HUD_SIZE/3-text->h/2,text,hudSurface);
	
	stream.str("");
	stream<<"Kills: "<<score;
	txtString=stream.str();
	text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
	apply_surface(SCREEN_WIDTH/8*7-text->w/2,HUD_SIZE/3*2-text->h/2,text,hudSurface);
	
	switch(currentWeapon)
	{
		case 0: apply_surface(SCREEN_WIDTH/8*3-highlightWeapon->w/2,HUD_SIZE/2-highlightWeapon->h/2,highlightWeapon,hudSurface); break;
		case 1: apply_surface(SCREEN_WIDTH/8*4-highlightWeapon->w/2,HUD_SIZE/2-highlightWeapon->h/2,highlightWeapon,hudSurface); break;
		case 2: apply_surface(SCREEN_WIDTH/8*5-highlightWeapon->w/2,HUD_SIZE/2-highlightWeapon->h/2,highlightWeapon,hudSurface); break;
	}
	
	apply_surface(SCREEN_WIDTH/8*3-weapon1->w/2,HUD_SIZE/2-weapon1->h/2,weapon1,hudSurface);
	apply_surface(SCREEN_WIDTH/8*4-weapon2->w/2,HUD_SIZE/2-weapon2->h/2,weapon2,hudSurface);
	apply_surface(SCREEN_WIDTH/8*5-weapon3->w/2,HUD_SIZE/2-weapon3->h/2,weapon3,hudSurface);
	apply_surface(0,0,hudSurface,screen);
}

void shop(bool* quit, bool *pause)
{
	bool shop=true;
	int option=0;
	Item* temp=loadItem(0);
	Item tmp(0);
	
	while(shop)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				shop=false;
				*pause=false;
				*quit=true;
			}
			
			if(event.type==SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{		
					case SDLK_UP:
						if(option==0)
						{
							option=14;
						}
						else
						{
							option--;
						}
						break;
						
					case SDLK_DOWN:
						if(option==14)
						{
							option=0;
						}
						else
						{
							option++;
						}
						break;
						
					case SDLK_ESCAPE:
						shop=false;
						break;
					
					case SDLK_RETURN:
						if((market[option]==false)&&(playerObject.getMoney()>=(*temp).cost_))
						{
							if(option>11)
							{
								Item *thing = loadItem(option);
								playerObject.heal((*thing).health_);
								delete thing;
							}
							else
							{
								Item *thing = loadItem(option);
								if((*thing).health_!=0)
								{
									playerObject.modifyMaxHealth((*thing).health_);
								}
								backpack.push_back(loadItem(option));
								market[option]=true;
							}
							playerObject.transaction(-((*temp).cost_));
						}
						break;
				}
				delete temp;
				temp=loadItem(option);
			}
			
			SDL_FillRect(menuSurface,NULL,SDL_MapRGB(screen->format,0x00,0x00,0x00));
			
			tmp.reset();
			for(std::vector<Item*>::iterator it=backpack.begin();it!=backpack.end();it++)
			{
				tmp.pDamage_+=(*(*it)).pDamage_;
				tmp.sDamage_+=(*(*it)).sDamage_;
				tmp.mDamage_+=(*(*it)).mDamage_;
				tmp.eDamage_+=(*(*it)).eDamage_;
				tmp.health_+=(*(*it)).health_;
				tmp.pSpeed_+=(*(*it)).pSpeed_;
				tmp.eSpeed_+=(*(*it)).eSpeed_;
			}
			
			txtString="SHOP";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface((SCREEN_WIDTH/2)-(text->w)/2,(SCREEN_HEIGHT/16)-(text->h)/2,text,menuSurface);
			
			stream.str("");
			stream<<"You have: "<<playerObject.getMoney();
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*7-text->w,SCREEN_HEIGHT/16+text->h,text,menuSurface);
			
			stream.str("");
			stream<<"Cost: "<<(*temp).cost_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8,SCREEN_HEIGHT/16+text->h,text,menuSurface);
			
			stream.str("");
			stream<<"Item No."<<option+1;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/16+text->h,text,menuSurface);
			
			stream.str("");
			stream<<"Weapon 1 Damage Modifier";
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/16*2+text->h,text,menuSurface);
			
			stream.str("");
			stream<<"Weapon 2 Damage Modifier";
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/16*3+text->h,text,menuSurface);
			
			stream.str("");
			stream<<"Weapon 3 Damage Modifier";
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/16*4+text->h,text,menuSurface);
			
			stream.str("");
			stream<<"Enemy Damage Modifier";
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/16*5+text->h,text,menuSurface);
			
			stream.str("");
			stream<<"Max Health/Heal Modifier";
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/16*6+text->h,text,menuSurface);
			
			stream.str("");
			stream<<"Player Speed Modifier";
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/16*7+text->h,text,menuSurface);
			
			stream.str("");
			stream<<"Enemy Speed Modifier";
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/16*8+text->h,text,menuSurface);
			
			stream.str("");
			stream<<"HEAL";
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/16*9+text->h,text,menuSurface);
			
			stream.str("");
			stream<<(*temp).pDamage_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8,SCREEN_HEIGHT/16*2+text->h,text,menuSurface);
			
			stream.str("");
			stream<<tmp.pDamage_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*7-text->w,SCREEN_HEIGHT/16*2+text->h,text,menuSurface);
			
			stream.str("");
			stream<<(*temp).sDamage_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8,SCREEN_HEIGHT/16*3+text->h,text,menuSurface);
			
			stream.str("");
			stream<<tmp.sDamage_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*7-text->w,SCREEN_HEIGHT/16*3+text->h,text,menuSurface);
			
			stream.str("");
			stream<<(*temp).mDamage_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8,SCREEN_HEIGHT/16*4+text->h,text,menuSurface);
			
			stream.str("");
			stream<<tmp.mDamage_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*7-text->w,SCREEN_HEIGHT/16*4+text->h,text,menuSurface);
			
			stream.str("");
			stream<<(*temp).eDamage_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8,SCREEN_HEIGHT/16*5+text->h,text,menuSurface);
			
			stream.str("");
			stream<<tmp.eDamage_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*7-text->w,SCREEN_HEIGHT/16*5+text->h,text,menuSurface);
			
			stream.str("");
			stream<<(*temp).health_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8,SCREEN_HEIGHT/16*6+text->h,text,menuSurface);
			
			stream.str("");
			stream<<tmp.health_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*7-text->w,SCREEN_HEIGHT/16*6+text->h,text,menuSurface);
			
			stream.str("");
			stream<<(*temp).pSpeed_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8,SCREEN_HEIGHT/16*7+text->h,text,menuSurface);
			
			stream.str("");
			stream<<tmp.pSpeed_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*7-text->w,SCREEN_HEIGHT/16*7+text->h,text,menuSurface);
			
			stream.str("");
			stream<<(*temp).eSpeed_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8,SCREEN_HEIGHT/16*8+text->h,text,menuSurface);
			
			stream.str("");
			stream<<tmp.eSpeed_;
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*7-text->w,SCREEN_HEIGHT/16*8+text->h,text,menuSurface);
			
			stream.str("");
			if(option>11)
			{
				stream<<"YES";
			}
			else
			{
				stream<<"NO";
			}
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8,SCREEN_HEIGHT/16*9+text->h,text,menuSurface);
			
			stream.str("");
			stream<<playerObject.getHealth();
			txtString=stream.str();
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*7-text->w,SCREEN_HEIGHT/16*9+text->h,text,menuSurface);
			
			if(market[option])
			{
				stream.str("");
				stream<<"ALREADY BOUGHT";
				txtString=stream.str();
				text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
				apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/16*11+text->h,text,menuSurface);
			}
			
			apply_surface(0,0,menuSurface,screen);
			SDL_Flip(screen);
		}
	}
}

void mapChoose(bool *quit)
{
	bool menu=true;
	int option=0;
	
	while(menu)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				menu=false;
				*quit=true;
			}
			
			if(event.type==SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{		
					case SDLK_LEFT:
						if(option==0)
						{
							option=3;
						}
						else
						{
							option--;
						}
						break;
						
					case SDLK_RIGHT:
						if(option==3)
						{
							option=0;
						}
						else
						{
							option++;
						}
						break;
					
					case SDLK_RETURN:
						if(weapons[0]+weapons[1]+weapons[2]+weapons[3]==3)
						{
							menu=false;
						}
						break;
					
					case SDLK_SPACE:
						if(weapons[option]==0)
						{
							weapons[option]=1;
						}
						else
						{
							weapons[option]=0;
						}
						break;
				}
			}
			
			SDL_FillRect(menuSurface,NULL,SDL_MapRGB(screen->format,0x00,0x00,0x00));
			SDL_FillRect(highlightWeapon,NULL,SDL_MapRGB(screen->format,0x00,0xFF,0x00));
			
			if(weapons[0]==1)
			{
				apply_surface(SCREEN_WIDTH/8-highlightWeapon->w/2,SCREEN_HEIGHT/2-highlightWeapon->h/2,highlightWeapon,menuSurface);
			}
			
			if(weapons[1]==1)
			{
				apply_surface(SCREEN_WIDTH/8*3-highlightWeapon->w/2,SCREEN_HEIGHT/2-highlightWeapon->h/2,highlightWeapon,menuSurface);
			}
			
			if(weapons[2]==1)
			{
				apply_surface(SCREEN_WIDTH/8*5-highlightWeapon->w/2,SCREEN_HEIGHT/2-highlightWeapon->h/2,highlightWeapon,menuSurface);
			}
			
			if(weapons[3]==1)
			{
				apply_surface(SCREEN_WIDTH/8*7-highlightWeapon->w/2,SCREEN_HEIGHT/2-highlightWeapon->h/2,highlightWeapon,menuSurface);
			}
			
			SDL_FillRect(highlightWeapon,NULL,SDL_MapRGB(screen->format,0xFF,0xFF,0x00));
			switch(option)
			{
				case 0: apply_surface(SCREEN_WIDTH/8-highlightWeapon->w/2,SCREEN_HEIGHT/2-highlightWeapon->h/2,highlightWeapon,menuSurface); break;
				case 1: apply_surface(SCREEN_WIDTH/8*3-highlightWeapon->w/2,SCREEN_HEIGHT/2-highlightWeapon->h/2,highlightWeapon,menuSurface); break;
				case 2: apply_surface(SCREEN_WIDTH/8*5-highlightWeapon->w/2,SCREEN_HEIGHT/2-highlightWeapon->h/2,highlightWeapon,menuSurface); break;
				case 3: apply_surface(SCREEN_WIDTH/8*7-highlightWeapon->w/2,SCREEN_HEIGHT/2-highlightWeapon->h/2,highlightWeapon,menuSurface); break;
			}
			
			apply_surface(SCREEN_WIDTH/8-pistols->w/2,SCREEN_HEIGHT/2-pistols->h/2,pistols,menuSurface);
			apply_surface(SCREEN_WIDTH/8*3-rpg->w/2,SCREEN_HEIGHT/2-rpg->h/2,rpg,menuSurface);
			apply_surface(SCREEN_WIDTH/8*5-bfg->w/2,SCREEN_HEIGHT/2-bfg->h/2,bfg,menuSurface);
			apply_surface(SCREEN_WIDTH/8*7-laser->w/2,SCREEN_HEIGHT/2-laser->h/2,laser,menuSurface);
			
			txtString="Dual Pistols";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8-text->w/2,SCREEN_HEIGHT/2+pistols->h/2+text->h/2,text,menuSurface);
			
			txtString="Rocket Launcher";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*3-text->w/2,SCREEN_HEIGHT/2+rpg->h/2+text->h/2,text,menuSurface);
			
			txtString="Big Fucking Gun";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*5-text->w/2,SCREEN_HEIGHT/2+bfg->h/2+text->h/2,text,menuSurface);
			
			txtString="Laser Rifle";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface(SCREEN_WIDTH/8*7-text->w/2,SCREEN_HEIGHT/2+laser->h/2+text->h/2,text,menuSurface);
			
			txtString="CHOOSE YOUR 3 WEAPONS";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface((SCREEN_WIDTH/2)-(text->w)/2,(SCREEN_HEIGHT/16)-(text->h)/2,text,menuSurface);
			
			apply_surface(0,0,menuSurface,screen);
			SDL_Flip(screen);
		}
	}
	
	int count=0;
	for(int i=0;i<4;i++)
	{
		if(weapons[i]==1)
		{
			if(count==0)
			{
				if(i==0)
				{
					primary.init(0,0,20,4,3,&projectiles,&backpack);
					weapon1=pistols;
				}
				else
				{
					primary.init(1,0,10,1,8,&projectiles,&backpack);
					weapon1=rpg;
				}
				count++;
			}
			else if(count==1)
			{
				if(i==1)
				{
					secondary.init(1,0,10,1,8,&projectiles,&backpack);
					weapon2=rpg;
				}
				else
				{
					secondary.init(2,0,15,2,10,&projectiles,&backpack);
					weapon2=bfg;
				}
				count++;
			}
			else
			{
				if(i==2)
				{
					melee.init(2,0,15,2,10,&projectiles,&backpack);
					weapon3=bfg;
				}
				else
				{
					melee.init(3,0,30,2,5,&projectiles,&backpack);
					weapon3=laser;
				}
				count++;
			}
		}
	}
}

void menu(bool* quit)
{
	bool menu=true;
	int option=0;
	
	while(menu)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				menu=false;
				*quit=true;
			}
			
			if(event.type==SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{		
					case SDLK_UP:
						if(option==0)
						{
							option=1;
						}
						else
						{
							option--;
						}
						break;
						
					case SDLK_DOWN:
						if(option==1)
						{
							option=0;
						}
						else
						{
							option++;
						}
						break;
					
					case SDLK_RETURN:
						if(option==0)
						{
							menu=false;
						}
						else
						{
							menu=false;
							*quit=true;
						}
						break;
				}
			}
			
			SDL_FillRect(menuSurface,NULL,SDL_MapRGB(screen->format,0x00,0x00,0x00));
			SDL_FillRect(optionSurface,NULL,SDL_MapRGB(screen->format,0x00,0x00,0x00));
			SDL_FillRect(highlightOptionSurface,NULL,SDL_MapRGB(screen->format,0xFF,0xFF,0x00));
			
			if(option==0)
			{
				apply_surface((SCREEN_WIDTH/2)-(highlightOptionSurface->w)/2,(SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/16)-(highlightOptionSurface->h)/2,highlightOptionSurface,menuSurface);
			}
			else
			{
				apply_surface((SCREEN_WIDTH/2)-(highlightOptionSurface->w)/2,(SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/16)-(highlightOptionSurface->h)/2,highlightOptionSurface,menuSurface);
			}
			
			apply_surface((SCREEN_WIDTH/2)-(optionSurface->w)/2,(SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/16)-(optionSurface->h)/2,optionSurface,menuSurface);
			apply_surface((SCREEN_WIDTH/2)-(optionSurface->w)/2,(SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/16)-(optionSurface->h)/2,optionSurface,menuSurface);
			
			txtString="SOME SHOOTER MOOTER - THE GAME";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface((SCREEN_WIDTH/2)-(text->w)/2,(SCREEN_HEIGHT/16)-(text->h)/2,text,menuSurface);
			
			txtString="START";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface((SCREEN_WIDTH/2)-(text->w)/2,(SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/16)-(text->h)/2,text,menuSurface);
			
			txtString="QUIT";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface((SCREEN_WIDTH/2)-(text->w)/2,(SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/16)-(text->h)/2,text,menuSurface);
			
			apply_surface(0,0,menuSurface,screen);
			SDL_Flip(screen);
		}
	}
}

void pause(bool* quit)
{
	bool pause=true;
	int option=0;
	
	while(pause)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				pause=false;
				*quit=true;
			}
			
			if(event.type==SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						pause=false;
						break;
						
					case SDLK_UP:
						if(option==0)
						{
							option=2;
						}
						else
						{
							option--;
						}
						break;
						
					case SDLK_DOWN:
						if(option==2)
						{
							option=0;
						}
						else
						{
							option++;
						}
						break;
					
					case SDLK_RETURN:
						if(option==0)
						{
							pause=false;
						}
						else if(option==1)
						{
							shop(quit,&pause);
						}
						else
						{
							pause=false;
							*quit=true;
						}
						break;
				}
			}
			SDL_FillRect(menuSurface,NULL,SDL_MapRGB(screen->format,0x00,0x00,0x00));
			SDL_FillRect(optionSurface,NULL,SDL_MapRGB(screen->format,0x00,0x00,0x00));
			SDL_FillRect(highlightOptionSurface,NULL,SDL_MapRGB(screen->format,0xFF,0xFF,0x00));
			
			if(option==0)
			{
				apply_surface((SCREEN_WIDTH/2)-(highlightOptionSurface->w)/2,(SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/16)-(SCREEN_HEIGHT/32)-(highlightOptionSurface->h)/2,highlightOptionSurface,menuSurface);
			}
			else if(option==1)
			{
				apply_surface((SCREEN_WIDTH/2)-(highlightOptionSurface->w)/2,(SCREEN_HEIGHT/2)-(highlightOptionSurface->h)/2,highlightOptionSurface,menuSurface);
			}
			else
			{
				apply_surface((SCREEN_WIDTH/2)-(highlightOptionSurface->w)/2,(SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/16)+(SCREEN_HEIGHT/32)-(highlightOptionSurface->h)/2,highlightOptionSurface,menuSurface);
			}
			
			apply_surface((SCREEN_WIDTH/2)-(optionSurface->w)/2,(SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/16)-(SCREEN_HEIGHT/32)-(optionSurface->h)/2,optionSurface,menuSurface);
			apply_surface((SCREEN_WIDTH/2)-(optionSurface->w)/2,(SCREEN_HEIGHT/2)-(optionSurface->h)/2,optionSurface,menuSurface);
			apply_surface((SCREEN_WIDTH/2)-(optionSurface->w)/2,(SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/16)+(SCREEN_HEIGHT/32)-(optionSurface->h)/2,optionSurface,menuSurface);
			
			txtString="PAUSE";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface((SCREEN_WIDTH/2)-(text->w)/2,(SCREEN_HEIGHT/16)-(text->h)/2,text,menuSurface);
			
			txtString="RESUME";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface((SCREEN_WIDTH/2)-(text->w)/2,(SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/16)-(SCREEN_HEIGHT/32)-(text->h)/2,text,menuSurface);
			
			txtString="SHOP";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface((SCREEN_WIDTH/2)-(text->w)/2,(SCREEN_HEIGHT/2)-(text->h)/2,text,menuSurface);
			
			txtString="QUIT";
			text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
			apply_surface((SCREEN_WIDTH/2)-(text->w)/2,(SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/16)+(SCREEN_HEIGHT/32)-(text->h)/2,text,menuSurface);
			
			apply_surface(0,0,menuSurface,screen);
			SDL_Flip(screen);
		}
	}
}

void gameOver()
{
	bool quit=false;
	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				quit=true;
			}
			
			if(event.type==SDL_KEYDOWN)
			{
				quit=true;
			}
		}
		SDL_FillRect(menuSurface,NULL,SDL_MapRGB(screen->format,0x00,0x00,0x00));
		
		txtString="THE GAME OVER";
		text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
		apply_surface((SCREEN_WIDTH/2)-(text->w)/2,(SCREEN_HEIGHT/16)-(text->h)/2,text,menuSurface);
		
		stream.str("");
		stream<<"Your Score: "<<score;
		txtString=stream.str();
		text=TTF_RenderText_Solid(font,txtString.c_str(),textColor);
		apply_surface(SCREEN_WIDTH/2-text->w/2,SCREEN_HEIGHT/2-text->h/2,text,menuSurface);
		
		apply_surface(0,0,menuSurface,screen);
		SDL_Flip(screen);
	}
}

void cleanup()
{
	SDL_FreeSurface(map);
	SDL_FreeSurface(player);
	SDL_FreeSurface(bullet);
	SDL_FreeSurface(enemy);
	SDL_FreeSurface(hudSurface);
	SDL_FreeSurface(menuSurface);
	SDL_FreeSurface(highlightOptionSurface);
	SDL_FreeSurface(text);
	SDL_FreeSurface(pistols);
	SDL_FreeSurface(rpg);
	SDL_FreeSurface(bfg);
	SDL_FreeSurface(laser);
	SDL_FreeSurface(highlightWeapon);
	
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
	game=true;
	int moveDirection;
	int currentWeapon=0;
	bool fireSound=false;
	Uint8 *keyStates=SDL_GetKeyState(NULL);
	
	Uint32 moveTimer=0;
	Uint32 fps=0;
	Uint32 changeWeapon=0;
	Uint32 spawnTimer=0;
	int spawnPlace=0;
	int health;
		
	if(init()==false)
	{
		return 1;
	}
	if(load_files()==false)
	{
		return 1;
	}
	
	menu(&quit);
	if(!quit)
	{
		mapChoose(&quit);
	}
	while(!quit)
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
					case SDLK_q:
						if(currentWeapon==0)
						{
							currentWeapon=2;
						}
						else
						{
							currentWeapon--;
						}
						changeWeapon=SDL_GetTicks();
						break;
						
					case SDLK_e:
						if(currentWeapon==2)
						{
							currentWeapon=0;
						}
						else
						{
							currentWeapon++;
						}
						changeWeapon=SDL_GetTicks();
						break;
						
					case SDLK_ESCAPE:
						pause(&quit);
						break;
				}
			}
		}
		
		if((SDL_GetTicks()-spawnTimer)>=5000-250*(score/10))
		{
			if(spawnPlace==0)
			{
				enemies.push_back(new Enemy(Point(960,245),Point(map->w,map->h),4,(enemy->w)/3,6,&obstacles,10,10,&enemies,&backpack,2,&playerObject));
				spawnPlace++;
			}
			else if(spawnPlace==1)
			{
				enemies.push_back(new Enemy(Point(1675,960),Point(map->w,map->h),6,(enemy->w)/3,6,&obstacles,10,10,&enemies,&backpack,2,&playerObject));
				spawnPlace++;
			}
			else if(spawnPlace==2)
			{
				enemies.push_back(new Enemy(Point(960,1675),Point(map->w,map->h),0,(enemy->w)/3,6,&obstacles,10,10,&enemies,&backpack,2,&playerObject));
				spawnPlace++;
			}
			else
			{
				enemies.push_back(new Enemy(Point(245,960),Point(map->w,map->h),2,(enemy->w)/3,6,&obstacles,10,10,&enemies,&backpack,2,&playerObject));
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
		
		if(keyStates[SDLK_SPACE])
		{
			if(currentWeapon==0)
			{
				if(SDL_GetTicks()-changeWeapon>=500)
				{
					fireSound=primary.fire(playerObject,Point(map->w,map->h),bullet->w,&obstacles,&enemies);
				}
			}
			else if(currentWeapon==1)
			{
				if(SDL_GetTicks()-changeWeapon>=500)
				{
					fireSound=secondary.fire(playerObject,Point(map->w,map->h),bullet->w,&obstacles,&enemies);
				}
			}
			else if(currentWeapon==2)
			{
				if(SDL_GetTicks()-changeWeapon>=500)
				{
					fireSound=melee.fire(playerObject,Point(map->w,map->h),bullet->w,&obstacles,&enemies);
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
		
		apply_surface(((SCREEN_WIDTH/2)-((playerObject.getPosition()).getX())),(((SCREEN_HEIGHT+HUD_SIZE)/2)-((playerObject.getPosition()).getY())),map,screen);

		for(std::vector<BaseProjectile*>::iterator it=projectiles.begin();it!=projectiles.end();it++)
		{
			apply_surface((((SCREEN_WIDTH/2)-((playerObject.getPosition().getX())-((*(*it)).getPosition().getX())))-((*(*it)).getSize()/2)),((((SCREEN_HEIGHT+HUD_SIZE)/2)-((playerObject.getPosition().getY())-((*(*it)).getPosition().getY())))-((*(*it)).getSize()/2)),bullet,screen);
			
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
				playerObject.transaction((*(*it)).getMoney());
				if(score%100==0)
				{
					playerObject.heal(50);
				}
				delete *it;
				enemies.erase(it);
				it--;
			}
			else
			{
				(*(*it)).move();
				apply_surface((((SCREEN_WIDTH/2)-((playerObject.getPosition().getX())-((*(*it)).getPosition().getX())))-((*(*it)).getSize()/2)),((((SCREEN_HEIGHT+HUD_SIZE)/2)-((playerObject.getPosition().getY())-((*(*it)).getPosition().getY())))-((*(*it)).getSize()/2)),enemy,screen,&enemySlice[(*(*it)).getDirection()]);
			}
		}
		
		health=playerObject.getHealth();
		if(health==0)
		{
			quit=true;
		}
		
		apply_surface((SCREEN_WIDTH/2)-(player->w/6),(((SCREEN_HEIGHT+HUD_SIZE)/2)-(player->h/6)),player,screen,&playerSlice[playerObject.getDirection()]);
		
		renderHUD(score,currentWeapon);

		if(SDL_Flip(screen)==-1)
		{
			return 1;
		}
		
		if((SDL_GetTicks()-fps)<(1000/FRAMES_PER_SECOND))
		{
			SDL_Delay((1000/FRAMES_PER_SECOND)-(SDL_GetTicks()-fps));
		}
	}
	if(game)
	{
		gameOver();
	}
	cleanup();
	return 0;
}
