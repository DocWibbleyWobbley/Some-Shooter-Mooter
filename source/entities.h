#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "point.h"

#include "SDL/SDL.h"
#include <vector>

class Player {
protected:
	Point origin_;
	Point map_;
	int direction_;
	int size_;
	int speed_;
	std::vector<SDL_Rect> *obstacles_;

private:
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
	
	Player(Point origin, Point map, int dir, int size, int speed, std::vector<SDL_Rect> *obstacles)
	:	origin_(origin.getX(),origin.getY()),
		map_(map.getX(),map.getY()),
		direction_(dir),
		size_(size),
		speed_(speed),
		obstacles_(obstacles)
	{}
	
	Point getPosition() const;
	int getDirection() const;
	void move(int dir);
	void init(Point origin, int size, int dir, Point map, std::vector<SDL_Rect> *obstacles, int speed);
};

class Enemy::public Player {
	Player player_;
	int findPlayer(int *xVel, int *yVel);
public:
	Enemy(Point origin, Point map, int dir, int size, int speed, std::vector<SDL_Rect> *obstacles, Player player)
	: Player(origin, map, dir, size, speed, obstacles),
	  player_(player)
	{}
	void move();
};
#endif
