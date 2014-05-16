#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "point.h"
#include "items.h"

#include "SDL/SDL.h"
#include <vector>

class Enemy;

class Player {
protected:
	Point origin_;
	Point map_;
	int direction_;
	int size_;
	int speed_;
	std::vector<SDL_Rect> *obstacles_;
	int health_;
	int maxHealth_;
	std::vector<Enemy*> *enemies_;
	std::vector<Item*> *backpack_;
	int money_;

private:
	void checkDirection(int dir, int *xVel, int *yVel) const;

public:	
	Player()
	:	origin_(1,1),
		map_(640,480),
		direction_(0),
		size_(2),
		speed_(0),
		obstacles_(NULL),
		health_(100),
		maxHealth_(100),
		enemies_(NULL),
		backpack_(NULL),
		money_(0)
	{}
	
	Player(Point origin, Point map, int dir, int size, int speed, std::vector<SDL_Rect> *obstacles, int health, int maxHealth, std::vector<Enemy*> *enemies, std::vector<Item*> *backpack, int money = 0)
	:	origin_(origin.getX(),origin.getY()),
		map_(map.getX(),map.getY()),
		direction_(dir),
		size_(size),
		speed_(speed),
		obstacles_(obstacles),
		health_(health),
		maxHealth_(maxHealth),
		enemies_(enemies),
		backpack_(backpack),
		money_(money)
	{}
	
	Point getPosition() const;
	int getDirection() const;
	void move(int dir);
	void init(Point origin, int size, int dir, Point map, std::vector<SDL_Rect> *obstacles, int speed, int health, int maxHealth, std::vector<Enemy*> *enemies, std::vector<Item*> *backpack, int money = 0);
	void hurt(int val);
	void heal(int val);
	int getHealth();
	int getSize();
	int getMoney();
	void transaction(int money);
	int getMaxHealth();
	void modifyMaxHealth(int modifier);
};

class Enemy: public Player {
	Player *player_;
	int findPlayer(int *xVel, int *yVel);
	Uint32 hitTimer_;
	int damage_;
	int tolerance_;
public:
	Enemy(Point origin, Point map, int dir, int size, int speed, std::vector<SDL_Rect> *obstacles, int health, int maxHealth, std::vector<Enemy*> *enemies, std::vector<Item*> *backpack, int damage, Player *player, int money = 3)
	: Player(origin, map, dir, size, speed, obstacles, health, maxHealth, enemies, backpack, money),
	  player_(player),
	  hitTimer_(0),
	  damage_(damage),
	  tolerance_(0)
	{
		tolerance_=(size_+(*player_).getSize())*5/8;
	}
	
	void move();
};
#endif
