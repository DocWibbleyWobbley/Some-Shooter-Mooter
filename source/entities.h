#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "point.h"

class Player {
	Point origin_;
	Point map_;
	int direction_;
	int size_;
	
	int checkDirection(int dir) const;
	
public:
	
	Player()
	:	origin_(5,5),
		map_(640,480),
		direction_(0),
		size_(10)
	{}
	
	Point getPosition() const;
	int getDirection() const;
	void movePlayer(int dir);
	void init(Point origin, int size, int dir, Point map);
};

#endif
