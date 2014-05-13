#ifndef ITEMS_H_
#define ITEMS_H_

class Item {
public:
	int type_;
	int pDamage_;
	int sDamage_;
	int mDamage_;
	int eDamage_;
	int health_;
	int pSpeed_;
	int eSpeed_;
	int cost_;

	Item(int type = 0, int pDamage = 0, int sDamage = 0, int mDamage = 0, int eDamage = 0, int health = 0, int pSpeed = 0, int eSpeed = 0, int cost = 0)
	: type_(type),
	  pDamage_(pDamage),
	  sDamage_(sDamage),
	  mDamage_(mDamage),
	  eDamage_(eDamage),
	  health_(health),
	  pSpeed_(pSpeed),
	  eSpeed_(eSpeed),
	  cost_(cost)
	{}
	
	void reset()
	{
		pDamage_=0;
		sDamage_=0;
		mDamage_=0;
		eDamage_=0;
		health_=0;
		pSpeed_=0;
		eSpeed_=0;
	}
};

Item* loadItem(int itemIndex);
#endif
