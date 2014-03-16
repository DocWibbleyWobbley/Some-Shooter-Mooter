#include "projectiles.h"
#include "entities.h"
#include "point.h"

bool Bullet::hitScan() {
	if((origin_.getX()+(size_/2))>=map_.getX()) {
		hit_=true;
	}
	else if((origin_.getX()-(size_/2))<=0) {
		hit_=true;
	}
	else if((origin_.getY()+(size_/2))>=map_.getY()) {
		hit_=true;
	}
	else if((origin_.getY()-(size_/2))<=0) {
		hit_=true;
	}
	else {
		switch(direction_) {
			case 0:
				origin_.setY(origin_.getY()-4);
				break;
			case 1:
				origin_.setX(origin_.getX()+2);
				origin_.setY(origin_.getY()-2);
				break;
			case 2:
				origin_.setX(origin_.getX()+4);
				break;
			case 3:
				origin_.setX(origin_.getX()+2);
				origin_.setY(origin_.getY()+2);
				break;
			case 4:
				origin_.setY(origin_.getY()+4);
				break;
			case 5:
				origin_.setX(origin_.getX()-2);
				origin_.setY(origin_.getY()+2);
				break;
			case 6:
				origin_.setX(origin_.getX()-4);
				break;
			case 7:
				origin_.setX(origin_.getX()-2);
				origin_.setY(origin_.getY()-2);
				break;
		}
	}
	return hit_;
}

Point Bullet::getPosition() const {
	return origin_;
}

int Bullet::getSize() const {
	return size_;
}
