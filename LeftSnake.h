#ifndef LEFT_SNAKE_H
#define LEFT_SNAKE_H

#include"Shape.h"


class  LeftSnake : public Shape
{
public:
	LeftSnake();//constructor
	LeftSnake(const LeftSnake& other) :Shape(other) {} // copy constructor
	~LeftSnake() {} // destructor

	// this function decide where to place the tetris shape points according to the initial place of the board.
	virtual void updateShapeValues(vector<Point>& shape) override;
	virtual bool rotateShape(const char rotateAxis, const char horizontal, const int**const matOfGame)override;
	virtual bool checkIfGameOver(const int**const matOfGame)const override;
	virtual bool checkIfShapeRotate()const override; // checks if we can rotate our current shape.
};


#endif // !LEFT_SNAKE_H
