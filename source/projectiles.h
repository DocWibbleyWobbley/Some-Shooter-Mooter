#ifndef PROJECTILES_H_
#define PROJECTILES_H_

#include "point.h"
#include "entities.h"

class BaseProjectile {
	int direction_;
	Point origin_;
	Point map_;
	bool hit_;
	int damage_;
	int size_;
	int type_;
	std::vector<SDL_Rect> *obstacles_;
	int speed_;
	
public:
	BaseProjectile()
	: direction_(0),
	  origin_(0,0),
	  map_(640,480),
	  hit_(false),
	  damage_(0),
	  size_(0),
	  type_(0),
	  obstacles_(NULL),
	  speed_(4)
	{}
	
	BaseProjectile(Player p, int dmg = 0, Point map, int size, int type, std::vector<SDL_Rect> *obstacles, int speed)
	: direction_(p.getDirection()),
	  origin_(p.getPosition()),
	  map_(map),
	  hit_(false),
	  damage_(dmg),
	  size_(size),
	  type_(type),
	  obstacles_(obstacles),
	  speed_(speed)
	{}
	
	bool hitScan();
	Point getPosition() const;
	int getSize() const;
	int getType() const;
};
#endif
