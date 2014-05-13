#include "items.h"

Item* loadItem(int itemIndex) {
	switch(itemIndex) {
	// Type, PrimaryDamage, SecondaryDamage, MeleeDamage, EnemyDamage,
	// Health, PlayerSpeed, EnemySpeed, Cost
		//Passives
		case 0: return new Item(0,0,0,0,0,10,0,0,20); break;
		case 1: return new Item(0,0,0,0,0,50,-2,0,100); break;
		case 2: return new Item(0,5,0,0,0,0,0,0,30); break;
		case 3: return new Item(0,0,5,0,0,0,0,0,30); break;
		case 4: return new Item(0,0,0,5,0,0,0,0,30); break;
		case 5: return new Item(0,10,0,0,5,0,0,0,50); break;
		case 6: return new Item(0,0,10,0,5,0,0,0,50); break;
		case 7: return new Item(0,0,0,10,5,0,0,0,50); break;
		case 8: return new Item(0,2,2,2,4,0,0,0,10); break;
		case 9: return new Item(0,6,6,6,0,0,0,6,66); break;
		case 10: return new Item(0,0,0,0,0,0,2,0,10); break;
		case 11: return new Item(0,0,0,0,0,0,-2,-2,20); break;
		//Healz
		case 12: return new Item(1,0,0,0,0,10,0,0,33); break;
		case 13: return new Item(1,0,0,0,0,25,0,0,66); break;
		case 14: return new Item(1,0,0,0,0,50,0,0,90); break;
	}
}
