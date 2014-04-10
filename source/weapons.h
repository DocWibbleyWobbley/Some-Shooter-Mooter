#ifndef WEAPONS_H_
#define WEAPONS_H_

#include "point.h"
#include "projectiles.h"
#include "entities.h"

#include <vector>

class Weapon {
	int type_;
	int projectileType_;
	int projectileSpeed_;
	int rof_;
	int damage_;
	std::vector<BaseProjectile*> *projectiles_;
	
public:
	Weapon()
	: type_(0),
	  projectileType_(0),
	  projectileSpeed_(10),
	  rof_(4),
	  damage_(0),
	  projectiles_(NULL)
	{}
	
	void init(int type, int pType, int pSpeed, int rof, int dmg, std::vector<BaseProjectile*> *projectiles);
	void fire(Player player, Point map, int size, std::vector<SDL_Rect> *obstacles);
	int getRof();
}

#endif
