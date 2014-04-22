#include "point.h"

int Point::getY() const
{
	return y_;
}
int Point::getX() const
{
	return x_;
}
void Point::setX(int x)
{
	x_=x;
}
void Point::setY(int y)
{
	y_=y;
}

bool Point::operator==(const Point p) const
{
	if((x_==p.getX())&&(y_==p.getY()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
