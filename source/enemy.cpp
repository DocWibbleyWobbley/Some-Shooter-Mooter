#include "entities.h"

int Enemy::findPlayer(int *xVel, int *yVel)
{
	int x=origin_.getX();
	int y=origin_.getY();
	int xDiff=(*player_).getPosition().getX()-x;
	int yDiff=(*player_).getPosition().getY()-y;
	int dir;
	int xDist;
	int yDist;
	
	if(xDiff<0)
	{
		xDist=-xDiff;
	}
	else
	{
		xDist=xDiff;
	}
	
	if(yDiff<0)
	{
		yDist=-yDiff;
	}
	else
	{
		yDist=yDiff;
	}
	
	if(xDiff==0)
	{
		if(yDiff<0)
		{
			dir=0;
		}
		else
		{
			dir=4;
		}
	}
	else if(yDiff==0)
	{
		if(xDiff<0)
		{
			dir=6;
		}
		else
		{
			dir=2;
		}
	}
	else if((xDiff<0)&&(yDiff<0))
	{
		if(xDist<=tolerance_)
		{
			dir=0;
		}
		else if(yDist<=tolerance_)
		{
			dir=6;
		}
		else
		{
			dir=7;
		}
	}
	else if((xDiff>0)&&(yDiff<0))
	{
		if(xDist<=tolerance_)
		{
			dir=0;
		}
		else if(yDist<=tolerance_)
		{
			dir=2;
		}
		else
		{
			dir=1;
		}
	}
	else if((xDiff<0)&&(yDiff>0))
	{
		if(xDist<=tolerance_)
		{
			dir=4;
		}
		else if(yDist<=tolerance_)
		{
			dir=6;
		}
		else
		{
			dir=5;
		}
	}
	else
	{
		if(xDist<=tolerance_)
		{
			dir=4;
		}
		else if(yDist<=tolerance_)
		{
			dir=2;
		}
		else
		{
			dir=3;
		}
	}

	if((xDist<=tolerance_)&&(yDist<=tolerance_))
	{
		if((SDL_GetTicks()-hitTimer_)>=1000)
		{
			(*player_).hurt(damage_);
			hitTimer_=SDL_GetTicks();
		}
		*xVel=0;
		*yVel=0;
	}
	else
	{
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
			
			for(std::vector<Enemy*>::iterator it=(*enemies_).begin();it!=(*enemies_).end();it++)
			{
				if((*(*it)).getPosition()==origin_)
				{
					continue;
				}
				
				if((x+*xVel-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+*xVel+(size_/2)>(*(*it)).getPosition().getX()-(*(*it)).getSize()/2)&&(y+*yVel-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+*yVel+(size_/2)>(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
				{
					*yVel=((*(*it)).getPosition().getY()+(*(*it)).getSize()/2+(size_/2))-y;
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
					if((y-(size_/2)<(*it).y+(*it).h)&&(y+size_/2>(*it).y))
					{
						*xVel=((*it).x-(size_/2))-x;
					}
					else if((x+(size_/2)>(*it).x)&&(x-size_/2<(*it).x+(*it).w))
					{
						*yVel=((*it).y+(*it).h+(size_/2))-y;
					}
				}
			}
			
			for(std::vector<Enemy*>::iterator it=(*enemies_).begin();it!=(*enemies_).end();it++)
			{
				if((*(*it)).getPosition()==origin_)
				{
					continue;
				}
				
				if((x+*xVel-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+*xVel+(size_/2)>(*(*it)).getPosition().getX()-(*(*it)).getSize()/2)&&(y+*yVel-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+*yVel+(size_/2)>(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
				{
					if((y-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+(size_/2)<(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
					{
						*xVel=((*(*it)).getPosition().getX()-(size_/2))-x;
					}
					else if((x-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+(size_/2)<(*(*it)).getPosition().getX()-(*(*it)).getSize()/2))
					{
						*yVel=((*(*it)).getPosition().getY()+(*(*it)).getSize()/2+(size_/2))-y;
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
			
			for(std::vector<Enemy*>::iterator it=(*enemies_).begin();it!=(*enemies_).end();it++)
			{
				if((*(*it)).getPosition()==origin_)
				{
					continue;
				}
				
				if((x+*xVel-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+*xVel+(size_/2)>(*(*it)).getPosition().getX()-(*(*it)).getSize()/2)&&(y+*yVel-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+*yVel+(size_/2)>(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
				{
					*xVel=((*(*it)).getPosition().getX()-(*(*it)).getSize()/2-(size_/2))-x;
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
					if((y-(size_/2)<(*it).y+(*it).h)&&(y+size_/2>(*it).y))
					{
						*xVel=((*it).x-(size_/2))-x;
					}
					else if((x+(size_/2)>(*it).x)&&(x-size_/2<(*it).x+(*it).w))
					{
						*yVel=((*it).y-(size_/2))-y;
					}
				}
			}
			
			for(std::vector<Enemy*>::iterator it=(*enemies_).begin();it!=(*enemies_).end();it++)
			{
				if((*(*it)).getPosition()==origin_)
				{
					continue;
				}
				
				if((x+*xVel-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+*xVel+(size_/2)>(*(*it)).getPosition().getX()-(*(*it)).getSize()/2)&&(y+*yVel-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+*yVel+(size_/2)>(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
				{
					if((y-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+(size_/2)<(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
					{
						*xVel=((*(*it)).getPosition().getX()-(*(*it)).getSize()/2-(size_/2))-x;
					}
					else if((x-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+(size_/2)<(*(*it)).getPosition().getX()-(*(*it)).getSize()/2))
					{
						*yVel=((*(*it)).getPosition().getY()-(*(*it)).getSize()/2-(size_/2))-y;
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
			
			for(std::vector<Enemy*>::iterator it=(*enemies_).begin();it!=(*enemies_).end();it++)
			{
				if((*(*it)).getPosition()==origin_)
				{
					continue;
				}
				
				if((x+*xVel-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+*xVel+(size_/2)>(*(*it)).getPosition().getX()-(*(*it)).getSize()/2)&&(y+*yVel-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+*yVel+(size_/2)>(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
				{
					*yVel=((*(*it)).getPosition().getY()-(*(*it)).getSize()/2-(size_/2))-y;
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
					if((y-(size_/2)<(*it).y+(*it).h)&&(y+size_/2>(*it).y))
					{
						*xVel=((*it).x+(*it).w+(size_/2))-x;
					}
					
					if((x+(size_/2)>(*it).x)&&(x-size_/2<(*it).x+(*it).w))
					{
						*yVel=((*it).y-(size_/2))-y;
					}
				}
			}
			
			for(std::vector<Enemy*>::iterator it=(*enemies_).begin();it!=(*enemies_).end();it++)
			{
				if((*(*it)).getPosition()==origin_)
				{
					continue;
				}
				
				if((x+*xVel-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+*xVel+(size_/2)>(*(*it)).getPosition().getX()-(*(*it)).getSize()/2)&&(y+*yVel-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+*yVel+(size_/2)>(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
				{
					if((y-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+(size_/2)<(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
					{
						*xVel=((*(*it)).getPosition().getX()+(*(*it)).getSize()/2+(size_/2))-x;
					}
					else if((x-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+(size_/2)<(*(*it)).getPosition().getX()-(*(*it)).getSize()/2))
					{
						*yVel=((*(*it)).getPosition().getY()-(*(*it)).getSize()/2-(size_/2))-y;
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
			
			for(std::vector<Enemy*>::iterator it=(*enemies_).begin();it!=(*enemies_).end();it++)
			{
				if((*(*it)).getPosition()==origin_)
				{
					continue;
				}
				
				if((x+*xVel-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+*xVel+(size_/2)>(*(*it)).getPosition().getX()-(*(*it)).getSize()/2)&&(y+*yVel-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+*yVel+(size_/2)>(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
				{
					*xVel=((*(*it)).getPosition().getX()+(*(*it)).getSize()/2+(size_/2))-x;
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
					if((y-(size_/2)<(*it).y+(*it).h)&&(y+size_/2>(*it).y))
					{
						*xVel=((*it).x+(*it).w+(size_/2))-x;
					}
					
					if((x+(size_/2)>(*it).x)&&(x-size_/2<(*it).x+(*it).w))
					{
						*yVel=((*it).y+(*it).h+(size_/2))-y;
					}
				}
			}
			
			for(std::vector<Enemy*>::iterator it=(*enemies_).begin();it!=(*enemies_).end();it++)
			{
				if((*(*it)).getPosition()==origin_)
				{
					continue;
				}
				
				if((x+*xVel-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+*xVel+(size_/2)>(*(*it)).getPosition().getX()-(*(*it)).getSize()/2)&&(y+*yVel-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+*yVel+(size_/2)>(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
				{
					if((y-(size_/2)<(*(*it)).getPosition().getY()+(*(*it)).getSize()/2)&&(y+(size_/2)<(*(*it)).getPosition().getY()-(*(*it)).getSize()/2))
					{
						*xVel=((*(*it)).getPosition().getX()+(*(*it)).getSize()/2+(size_/2))-x;
					}
					else if((x-(size_/2)<(*(*it)).getPosition().getX()+(*(*it)).getSize()/2)&&(x+(size_/2)<(*(*it)).getPosition().getX()-(*(*it)).getSize()/2))
					{
						*yVel=((*(*it)).getPosition().getY()+(*(*it)).getSize()/2+(size_/2))-y;
					}
				}
			}
			break;
	}
	}
	return dir;
}

void Enemy::move() {
	int xVel;
	int yVel;
	direction_ = findPlayer(&xVel, &yVel);
	origin_.setX(origin_.getX() + xVel);	
	origin_.setY(origin_.getY() + yVel);
}
