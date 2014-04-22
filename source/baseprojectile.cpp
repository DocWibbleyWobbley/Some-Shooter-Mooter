#include "projectiles.h"

bool BaseProjectile::hitScan() {
	int x=origin_.getX();
	int y=origin_.getY();
	int xVel;
	int yVel;
	switch(direction_)
	{
		case 0:
			xVel=0;
			yVel=-speed_;
			if((y+yVel)<(size_/2))
			{
				yVel=(size_/2)-y;
			}
			if(yVel==0)
			{
				hit_=true;
			}
			break;
		case 1:
			xVel=speed_/2;
			yVel=-speed_/2;
			if((y+yVel)<(size_/2))
			{
				yVel=(size_/2)-y;
			}
			if((x+xVel)>(map_.getX()-(size_/2)))
			{
				xVel=(map_.getX()-(size_/2))-x;
			}
			if((xVel==0)||(yVel==0))
			{
				hit_=true;
			}
			break;
		case 2:
			xVel=speed_;
			yVel=0;
			if((x+xVel)>(map_.getX()-(size_/2)))
			{
				xVel=(map_.getX()-(size_/2))-x;
			}
			if(xVel==0)
			{
				hit_=true;
			}
			break;
		case 3:
			xVel=speed_/2;
			yVel=speed_/2;
			if((y+yVel)>(map_.getY()-(size_/2)))
			{
				yVel=(map_.getY()-(size_/2))-y;
			}
			if((x+xVel)>(map_.getX()-(size_/2)))
			{
				xVel=(map_.getX()-(size_/2))-x;
			}
			if((xVel==0)||(yVel==0))
			{
				hit_=true;
			}
			break;
		case 4:
			xVel=0;
			yVel=speed_;
			if((y+yVel)>(map_.getY()-(size_/2)))
			{
				yVel=(map_.getY()-(size_/2))-y;
			}
			if(yVel==0)
			{
				hit_=true;
			}
			break;
		case 5:
			xVel=-speed_/2;
			yVel=speed_/2;
			if((x+xVel)<(size_/2))
			{
				xVel=(size_/2)-x;
			}
			if((y+yVel)>(map_.getY()-(size_/2)))
			{
				yVel=(map_.getY()-(size_/2))-y;
			}
			if((xVel==0)||(yVel==0))
			{
				hit_=true;
			}
			break;
		case 6:
			xVel=-speed_;
			yVel=0;
			if((x+xVel)<(size_/2))
			{
				xVel=(size_/2)-x;
			}
			if(xVel==0)
			{
				hit_=true;
			}
			break;
		case 7:
			xVel=-speed_/2;
			yVel=-speed_/2;
			if((x+xVel)<(size_/2))
			{
				xVel=(size_/2)-x;
			}
			if((y+yVel)<(size_/2))
			{
				yVel=(size_/2)-y;
			}
			if((xVel==0)||(yVel==0))
			{
				hit_=true;
			}
			break;
	}
	
	for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
	{
		if(hit_==true) break;
		if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x)&&(y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
		{
			hit_=true;
		}
	}
	
	for(std::vector<Enemy*>::iterator it=(*enemies_).begin();it!=(*enemies_).end();it++)
	{
		if(hit_==true) break;
		if((x+xVel-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+xVel+(size_/2)>(*(*it)).getPosition().getX()-(*(*it)).getSize()/2)&&(y+yVel-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+yVel+(size_/2)>(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
		{
			(*(*it)).hurt(damage_);
			hit_=true;
		}
	}
	
	if(hit_!=true)
	{
		origin_.setX(x+xVel);
		origin_.setY(y+yVel);
	}
	
	return hit_;
}

Point BaseProjectile::getPosition() const {
	return origin_;
}

int BaseProjectile::getSize() const {
	return size_;
}

int	BaseProjectile::getType() const {
	return type_;
}
