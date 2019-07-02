#ifndef BOMB_H
#define BOMB_H

#include"Shape.h"


class Bomb : public Shape
{
public:
	Bomb(); //constructor 
	Bomb(const Bomb& other) :Shape(other) {} // copy constructor
	~Bomb() {} // destructor

    // this function decide where to place the tetris shape points according to the initial place of the board.
	virtual void updateShapeValues(vector<Point>& shape) override;
	virtual bool rotateShape(const char rotateAxis, const char horizontal, const int**const matOfGame) override;
	virtual bool checkIfGameOver(const int**const matOfGame) const override;
	virtual bool checkIfShapeRotate()const override; // checks if we can rotate our current shape.

};


#endif // !BOMB_H
