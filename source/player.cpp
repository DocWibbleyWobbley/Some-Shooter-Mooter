#include "point.h"
#include "entities.h"

int Player::checkDirection(int dir) const {
	int x=origin_.getX();
	int y=origin_.getY();
	switch(dir) {
		case 0:
			if(y==(size_/2)) {
				return 12;
			}
			else if(y==(size_/2)+1) {
				return 8;
			}
			else return 0;
			break;
		case 1:
			if((y==(size_/2))&&(x!=(map_.getX()-(size_/2)))) {
				return 9;
			}
			else if((y==(size_/2))&&(x==(map_.getX()-(size_/2)))) {
				return 13;
			}
			else if((y!=(size_/2))&&(x==(map_.getX()-(size_/2)))) {
				return 8;
			}
			else return 1;
			break;
		case 2:
			if(x==(map_.getX()-(size_/2))) {
				return 14;
			}
			else if(x==(map_.getX()-((size_/2)+1))) {
				return 9;
			}
			else {
				return 2;
			}
			break;
		case 3:
			if((y==(map_.getY()-(size_/2)))&&(x!=(map_.getX()-(size_/2)))) {
				return 9;
			}
			else if((y==(map_.getY()-(size_/2)))&&(x==(map_.getX()-(size_/2)))) {
				return 15;
			}
			else if((y!=(map_.getY()-(size_/2)))&&(x==(map_.getX()-(size_/2)))) {
				return 10;
			}
			else return 3;
			break;
		case 4:
			if(y==(map_.getY()-(size_/2))) {
				return 16;
			}
			else if(y==(map_.getX()-((size_/2)+1))) {
				return 10;
			}
			else return 4;
			break;
		case 5:
			if((y==(map_.getY()-(size_/2)))&&(x!=(size_/2))) {
				return 11;
			}
			else if((y==(map_.getY()-(size_/2)))&&(x==(size_/2))) {
				return 17;
			}
			else if((y!=(map_.getY()-(size_/2)))&&(x==(size_/2))) {
				return 10;
			}
			else return 5;
			break;
		case 6:
			if(x==(size_/2)) {
				return 18;
			}
			else if(x==((size_/2)+1)) {
				return 11;
			}
			else {
				return 6;
			}
			break;
		case 7:
			if((y==(size_/2))&&(x!=(size_/2))) {
				return 11;
			}
			else if((y==(size_/2))&&(x==(size_/2))) {
				return 19;
			}
			else if((y!=(size_/2))&&(x==(size_/2))) {
				return 8;
			}
			else return 7;
			break;
	}
}

Point Player::getPosition() const {
	return origin_;
}

void Player::movePlayer(int dir) {
	direction_=checkDirection(dir);
	switch(direction_) {
		case 0:
			origin_.setY(origin_.getY()-2);
			break;
		case 1:
			origin_.setX(origin_.getX()+1);
			origin_.setY(origin_.getY()-1);
			break;
		case 2:
			origin_.setX(origin_.getX()+2);
			break;
		case 3:
			origin_.setX(origin_.getX()+1);
			origin_.setY(origin_.getY()+1);
			break;
		case 4:
			origin_.setY(origin_.getY()+2);
			break;
		case 5:
			origin_.setX(origin_.getX()-1);
			origin_.setY(origin_.getY()+1);
			break;
		case 6:
			origin_.setX(origin_.getX()-2);
			break;
		case 7:
			origin_.setX(origin_.getX()-1);
			origin_.setY(origin_.getY()-1);
			break;
		case 8:
			direction_=0;
			origin_.setY(origin_.getY()-1);
			break;
		case 9:
			direction_=2;
			origin_.setX(origin_.getX()+1);
			break;
		case 10:
			direction_=4;
			origin_.setY(origin_.getY()+1);
			break;
		case 11:
			direction_=6;
			origin_.setX(origin_.getX()-1);
			break;
		case 12:
			direction_=0;
			break;
		case 13:
			direction_=1;
			break;
		case 14:
			direction_=2;
			break;
		case 15:
			direction_=3;
			break;
		case 16:
			direction_=4;
			break;
		case 17:
			direction_=5;
			break;
		case 18:
			direction_=6;
			break;
		case 19:
			direction_=7;
			break;
	}
}
	
int Player::getDirection() const {
	return direction_;
}

void Player::init(Point origin, int size, int dir, Point map) {
	origin_.setX(origin.getX());
	origin_.setY(origin.getY());
	size_=size;
	direction_=dir;
	map_.setX(map.getX());
	map_.setY(map.getY());
}
