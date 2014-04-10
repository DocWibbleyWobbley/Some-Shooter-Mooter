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
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x)&&(y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
				{
					yVel=((*it).y+(*it).h+(size_/2))-y;
				}
			}
			if(yVel==0)
			{
				hit_=true;
			}
			else
			{
				origin_.setX(x+xVel);
				origin_.setY(y+yVel);
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
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x)&&(y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
				{
					if(y-(size_/2)!=(*it).y+(*it).h)
					{
						if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x))
						{
							xVel=((*it).x-(size_/2))-x;
						}
					}
					else if(x+(size_/2)!=(*it).x)
					{
						if((y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
						{
							yVel=((*it).y+(*it).h+(size_/2))-y;
						}
					}
				}
			}
			if((yVel==0)||(xVel==0))
			{
				hit_=true;
			}
			else
			{
				origin_.setX(x+xVel);
				origin_.setY(y+yVel);
			}
			break;
		case 2:
			xVel=speed_;
			yVel=0;
			if((x+xVel)>(map_.getX()-(size_/2)))
			{
				xVel=(map_.getX()-(size_/2))-x;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x)&&(y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
				{
					xVel=((*it).x-(size_/2))-x;
				}
			}
			if(xVel==0)
			{
				hit_=true;
			}
			else
			{
				origin_.setX(x+xVel);
				origin_.setY(y+yVel);
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
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x)&&(y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
				{
					if(y+(size_/2)!=(*it).y)
					{
						if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x))
						{
							xVel=((*it).x-(size_/2))-x;
						}
					}
					else if(x+(size_/2)!=(*it).x)
					{
						if((y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
						{
							yVel=((*it).y-(size_/2))-y;
						}
					}
				}
			}
			if((yVel==0)||(xVel==0))
			{
				hit_=true;
			}
			else
			{
				origin_.setX(x+xVel);
				origin_.setY(y+yVel);
			}
			break;
		case 4:
			xVel=0;
			yVel=speed_;
			if((y+yVel)>(map_.getY()-(size_/2)))
			{
				yVel=(map_.getY()-(size_/2))-y;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x)&&(y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
				{
					yVel=((*it).y-(size_/2))-y;
				}
			}
			if(yVel==0)
			{
				hit_=true;
			}
			else
			{
				origin_.setX(x+xVel);
				origin_.setY(y+yVel);
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
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x)&&(y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
				{
					if(y+(size_/2)!=(*it).y)
					{
						if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x))
						{
							xVel=((*it).x+(*it).w+(size_/2))-x;
						}
					}
					else if(x-(size_/2)!=(*it).x+(*it).w)
					{
						if((y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
						{
							yVel=((*it).y-(size_/2))-y;
						}
					}
				}
			}
			if((yVel==0)||(xVel==0))
			{
				hit_=true;
			}
			else
			{
				origin_.setX(x+xVel);
				origin_.setY(y+yVel);
			}
			break;
		case 6:
			xVel=-speed_;
			yVel=0;
			if((x+xVel)<(size_/2))
			{
				xVel=(size_/2)-x;
			}
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x)&&(y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
				{
					xVel=((*it).x+(*it).w+(size_/2))-x;
				}
			}
			if(xVel==0)
			{
				hit_=true;
			}
			else
			{
				origin_.setX(x+xVel);
				origin_.setY(y+yVel);
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
			for(std::vector<SDL_Rect>::iterator it=(*obstacles_).begin();it!=(*obstacles_).end();it++)
			{
				if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x)&&(y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
				{
					if(y-(size_/2)!=(*it).y+(*it).h)
					{
						if((x+xVel-(size_/2)<(*it).x+(*it).w)&&(x+xVel+(size_/2)>(*it).x))
						{
							xVel=((*it).x+(*it).w+(size_/2))-x;
						}
					}
					else if(x-(size_/2)!=(*it).x+(*it).w)
					{
						if((y+yVel-(size_/2)<(*it).y+(*it).h)&&(y+yVel+(size_/2)>(*it).y))
						{
							yVel=((*it).y+(*it).h+(size_/2))-y;
						}
					}
				}
			}
			if((yVel==0)||(xVel==0))
			{
				hit_=true;
			}
			else
			{
				origin_.setX(x+xVel);
				origin_.setY(y+yVel);
			}
			break;
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
