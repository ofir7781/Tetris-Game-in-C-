using namespace std;

#include <iostream>
#include "Gotoxy.h"
#include "Point.h"
#include <stdlib.h>
#include <string.h>
#include "Shape.h"
#include <Windows.h>
#include <conio.h>
#include "TetrisGame.h"
#include "Tetrisconsts.h"


Shape::Shape(const Shape& other) //we wont use this copy constructor for now. but we might use it in the future.
{
	this->size = other.getSize();
	this->appearance = other.getAppearance();
	shape = other.getShape();
}
