#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "point.h"

#include "SDL/SDL.h"
#include <vector>

class Player {
	Point origin_;
	Point map_;
	int direction_;
	int size_;
	int speed_;
	std::vector<SDL_Rect> *obstacles_;
	
	void checkDirection(int dir, int *xVel, int *yVel) const;
	
public:
	
	Player()
	:	origin_(1,1),
		map_(640,480),
		direction_(0),
		size_(2),
		speed_(0),
		obstacles_(NULL)
	{}
	
	Point getPosition() const;
	int getDirection() const;
	void movePlayer(int dir);
	void init(Point origin, int size, int dir, Point map, std::vector<SDL_Rect> *obstacles, int speed);
};

#endif
