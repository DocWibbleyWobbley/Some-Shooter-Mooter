#ifndef PROJECTILES_H_
#define PROJECTILES_H_
#include "point.h"
#include "entities.h"

class Bullet {
	int direction_;
	Point origin_;
	Point map_;
	bool hit_;
	int damage_;
	int size_;
	
public:
	Bullet()
	: direction_(0),
	  origin_(0,0),
	  map_(640,480),
	  hit_(false),
	  damage_(0),
	  size_(0)
	{}
	
	Bullet(Player p, int dmg = 0, Point map, int size)
	: direction_(p.getDirection()),
	  origin_(p.getPosition()),
	  map_(map),
	  hit_(false),
	  damage_(dmg),
	  size_(size)
	{}
	
	bool hitScan();
	Point getPosition() const;
	int getSize() const;
};
#endif
