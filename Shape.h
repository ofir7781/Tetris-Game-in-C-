#ifndef _SHAPE_H
#define _SHAPE_H

#include "Gotoxy.h"
#include "Point.h"
#include <stdlib.h>
#include "Tetrisconsts.h"
#include <vector>


enum shapeofsymbol { CUBE = '#', LINE = '$', JOKER = '&', BOMB = '@' };//
enum value { LEFT = 'f', RIGHT = 'h', UP = 't', DOWN = 'g',START = '1',PAUSE = '2', FASTER = '3', SLOWER = '4', EXIT = '9', STOPJOKER = 's'};
//To use with arrow keys(untested) :
//enum value { LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, START = '1', PAUSE = '2', FASTER = '3', SLOWER = '4', EXIT = '9', STOPJOKER = 's' };

class Shape
{

protected: //Attributes:
	vector<Point> shape; //stl: vector of points in order to know where excactly is every shape.
	int size;
	char appearance; // how do you look

	Shape() {}; //constructor
	Shape(const Shape& other); //copy constructor

public: //methods:


	virtual ~Shape() {}; //destructor

	int getSize()const { return this->size; }
	char getAppearance()const { return this->appearance; }
	vector<Point> getShape()const {return this->shape;}
	void setShape(const vector<Point>& other) { shape = other; }

	//abstract functions:

	// this function decide where to place the tetris shape points according to the initial place of the board.
	virtual void updateShapeValues(vector<Point>& shape) = 0; // abstract
	virtual bool rotateShape(const char rotateAxis, const char horizontal, const int**const matOfGame) = 0;// abstract
	virtual bool checkIfGameOver(const int**const matOfGame) const = 0; // abstract
	virtual bool checkIfShapeRotate()const = 0; // abstract
};


#endif  //_SHAPE_H

