#include <iostream>
#include "Point.h"

using namespace std;



//first constructor
Point::Point() : x(1), y(1) // default constructor
{}

Point::Point(unsigned int newX, unsigned int newY) : x(newX), y(newY)
{}

Point::Point(const Point& other) // copy constructor
{
	this->x = other.x;
	this->y = other.y;
}

// this function change x coordinate  and y coordinate togther  
void Point::setXY(const unsigned int x, const unsigned int y)
{
	this->x = x;
	this->y = y;
}

// this function print a char ch to the screen acoording to x coordinate and y coordinate of the point 
void Point::draw(const char ch)
{
	gotoxy(this->x, this->y);
	cout << ch;
	cout.flush();
}