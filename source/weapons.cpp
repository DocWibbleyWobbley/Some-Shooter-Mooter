#include "weapons.h"

void Weapon::init(int type, int pType, int pSpeed, int rof, int dmg, std::vector<BaseProjectile*> *projectiles, std::vector<Item*> *backpack) {
	type_ = type;
	projectileType_ = pType;
	projectileSpeed_ = pSpeed;
	rof_ = rof;
	damage_ = dmg;
	projectiles_ = projectiles;
	backpack_ = backpack;
}

bool Weapon::fire(Player player, Point map, int size, std::vector<SDL_Rect> *obstacles, std::vector<Enemy*> *enemies) {
	if((SDL_GetTicks()-rofTimer_)>=(1000/rof_))
	{
		int tmpdmg=damage_;
		for(std::vector<Item*>::iterator it=(*backpack_).begin();it!=(*backpack_).end();it++)
		{
			switch(type_)
			{
				case 0: tmpdmg+=(*(*it)).pDamage_;
				case 1: tmpdmg+=(*(*it)).sDamage_;
				case 2: tmpdmg+=(*(*it)).mDamage_;
			}
		}
		rofTimer_=SDL_GetTicks();
		(*projectiles_).push_back(new BaseProjectile(player, tmpdmg, map, size, projectileType_, obstacles, projectileSpeed_, enemies));
		return true;
	}
	return false;
}
