#ifndef PYRAMID_H
#define PYRAMID_H

#include"Shape.h"


class  Pyramid : public Shape
{
private:  //Attributes:
	//char appearance; // how do you look

public:
	Pyramid();//constructor
	Pyramid(const Pyramid& other) :Shape(other) {} // copy constructor
	~Pyramid() {} // destructor

    // this function decide where to place the tetris shape points according to the initial place of the board.
	virtual void updateShapeValues(vector<Point>& shape) override;
	virtual bool rotateShape(const char rotateAxis, const char horizontal, const int**const matOfGame)override;
	virtual bool checkIfGameOver(const int**const matOfGame)const override;
	virtual bool checkIfShapeRotate()const override; // checks if we can rotate our current shape.

};


#endif // !PYRAMID_H
