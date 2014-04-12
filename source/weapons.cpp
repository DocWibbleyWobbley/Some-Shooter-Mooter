#include "weapons.h"

void Weapon::init(int type, int pType, int pSpeed, int rof, int dmg, std::vector<BaseProjectile*> *projectiles) {
	type_ = type;
	projectileType_ = pType;
	projectileSpeed_ = pSpeed;
	rof_ = rof;
	damage_ = dmg;
	projectiles_ = projectiles;
}

bool Weapon::fire(Player player, Point map, int size, std::vector<SDL_Rect> *obstacles) {
	if((SDL_GetTicks()-rofTimer_)>=(1000/rof_))
	{
		rofTimer_=SDL_GetTicks();
		(*projectiles_).push_back(new BaseProjectile(player, damage_, map, size, projectileType_, obstacles, projectileSpeed_));
		return true;
	}
	return false;
}
