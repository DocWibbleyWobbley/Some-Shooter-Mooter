#include "entities.h"

int Enemy::findPlayer(int *xVel, int *yVel) {
//Nedko svurshi si rabotata
//pip	
}

void Enemy::move() {
	int xVel;
	int yVel;
	direction_ = findPlayer(&xVel, &yVel);
	origin_.setX(origin_.getX() + xVel);	
	origin_.setY(origin_.getY() + yVel);
}
