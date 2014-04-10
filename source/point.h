#ifndef POINT_H_
#define POINT_H_

class Point
{
	int x_;
	int y_;
	
public:
	Point(int x=0, int y=0)
	:	x_(x),
		y_(y)
	{}
	
	int getY() const;
	int getX() const;
	void setX(int x);
	void setY(int y);
};

#endif
