#ifndef _POINT_H
#define _POINT_H

#include "Gotoxy.h"
#include <stdlib.h>
#include <iostream>

using namespace std;


class  Point
{
private: //Attributes:
	unsigned int x;
	unsigned int y;

public: //methods:
	Point();
	Point(unsigned int newX, unsigned int newY);
	Point(const Point& other);
	unsigned int getX() const { return x; }
	unsigned int getY() const { return y; }
	void setXY(const unsigned int x, const unsigned int y);
	void draw(const char ch);
};


#endif // _POINT_H


