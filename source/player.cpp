#include "entities.h"

void Player::checkDirection(int dir, int *xVel, int *yVel) const
{
	int x=origin_.getX();
	int y=origin_.getY();
	switch(dir)
	{
		case 0:
			*xVel=0;
			*yVel=-speed_;
			if((y+*yVel)<(size_/2))
			{
				*yVel=(size_/2)-y;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x)&&(y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
				{
					*yVel=((*it).y+(*it).h+(size_/2))-y;
				}
			}
			break;
		case 1:
			*xVel=speed_/2;
			*yVel=-speed_/2;
			if((y+*yVel)<(size_/2))
			{
				*yVel=(size_/2)-y;
			}
			if((x+*xVel)>(map_.getX()-(size_/2)))
			{
				*xVel=(map_.getX()-(size_/2))-x;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x)&&(y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
				{
					if(y-(size_/2)!=(*it).y+(*it).h)
					{
						if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x))
						{
							*xVel=((*it).x-(size_/2))-x;
						}
					}
					else if(x+(size_/2)!=(*it).x)
					{
						if((y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
						{
							*yVel=((*it).y+(*it).h+(size_/2))-y;
						}
					}
				}
			}
			break;
		case 2:
			*xVel=speed_;
			*yVel=0;
			if((x+*xVel)>(map_.getX()-(size_/2)))
			{
				*xVel=(map_.getX()-(size_/2))-x;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x)&&(y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
				{
					*xVel=((*it).x-(size_/2))-x;
				}
			}
			break;
		case 3:
			*xVel=speed_/2;
			*yVel=speed_/2;
			if((y+*yVel)>(map_.getY()-(size_/2)))
			{
				*yVel=(map_.getY()-(size_/2))-y;
			}
			if((x+*xVel)>(map_.getX()-(size_/2)))
			{
				*xVel=(map_.getX()-(size_/2))-x;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x)&&(y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
				{
					if(y+(size_/2)!=(*it).y)
					{
						if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x))
						{
							*xVel=((*it).x-(size_/2))-x;
						}
					}
					else if(x+(size_/2)!=(*it).x)
					{
						if((y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
						{
							*yVel=((*it).y-(size_/2))-y;
						}
					}
				}
			}
			break;
		case 4:
			*xVel=0;
			*yVel=speed_;
			if((y+*yVel)>(map_.getY()-(size_/2)))
			{
				*yVel=(map_.getY()-(size_/2))-y;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x)&&(y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
				{
					*yVel=((*it).y-(size_/2))-y;
				}
			}
			break;
		case 5:
			*xVel=-speed_/2;
			*yVel=speed_/2;
			if((x+*xVel)<(size_/2))
			{
				*xVel=(size_/2)-x;
			}
			if((y+*yVel)>(map_.getY()-(size_/2)))
			{
				*yVel=(map_.getY()-(size_/2))-y;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x)&&(y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
				{
					if(y+(size_/2)!=(*it).y)
					{
						if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x))
						{
							*xVel=((*it).x+(*it).w+(size_/2))-x;
						}
					}
					else if(x-(size_/2)!=(*it).x+(*it).w)
					{
						if((y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
						{
							*yVel=((*it).y-(size_/2))-y;
						}
					}
				}
			}
			break;
		case 6:
			*xVel=-speed_;
			*yVel=0;
			if((x+*xVel)<(size_/2))
			{
				*xVel=(size_/2)-x;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x)&&(y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
				{
					*xVel=((*it).x+(*it).w+(size_/2))-x;
				}
			}
			break;
		case 7:
			*xVel=-speed_/2;
			*yVel=-speed_/2;
			if((x+*xVel)<(size_/2))
			{
				*xVel=(size_/2)-x;
			}
			if((y+*yVel)<(size_/2))
			{
				*yVel=(size_/2)-y;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x)&&(y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
				{
					if(y-(size_/2)!=(*it).y+(*it).h)
					{
						if((x+*xVel-(size_/2)<(*it).x+(*it).w)&&(x+*xVel+(size_/2)>(*it).x))
						{
							*xVel=((*it).x+(*it).w+(size_/2))-x;
						}
					}
					else if(x-(size_/2)!=(*it).x+(*it).w)
					{
						if((y+*yVel-(size_/2)<(*it).y+(*it).h)&&(y+*yVel+(size_/2)>(*it).y))
						{
							*yVel=((*it).y+(*it).h+(size_/2))-y;
						}
					}
				}
			}
			break;
	}
}
Point Player::getPosition() const
{
	return origin_;
}

void Player::movePlayer(int dir)
{
	int xVel;
	int yVel;
	direction_=dir;
	checkDirection(direction_,&xVel,&yVel);
	origin_.setX(origin_.getX()+xVel);
	origin_.setY(origin_.getY()+yVel);
}
	
int Player::getDirection() const
{
	return direction_;
}

void Player::init(Point origin, int size, int dir, Point map, std::vector<SDL_Rect> *obstacles, int speed)
{
	origin_.setX(origin.getX());
	origin_.setY(origin.getY());
	size_=size;
	direction_=dir;
	map_.setX(map.getX());
	map_.setY(map.getY());
	obstacles_=obstacles;
	speed_=speed;
}
