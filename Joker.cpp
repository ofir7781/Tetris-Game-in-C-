#include <iostream>
#include "Joker.h"

using namespace std;


Joker::Joker() : Shape()
{
	// create the new shape according to the inherit class 
	this->size = JOKER_SIZE;
	this->appearance = BLOCK_APPEARANCE;
	updateShapeValues(this->shape);
}

// this function decide where to place the tetris shape points according to the initial place of the board.
void Joker::updateShapeValues(vector<Point>& shape)
{
	Point one;
	one.setXY(5, 0 + (ROWSFORMENU - 1));
	shape.push_back(one);
}

// this function responsible to rotate the shape. if the shape is not rotateble, do nothing.
bool Joker::rotateShape(const char rotateAxis, const char horizontal, const int**const matOfGame)
{
	return 0;
}

//checks if game is over because of the current shape that got in the game.
bool Joker::checkIfGameOver(const int**const matOfGame)const
{
	int col;

	for (col = 5; col < 5 + size; col++)
	{
		if (matOfGame[ROWSFORMENU][col] == 1)
			return true;
	}
	return false;
}

// checks if we can rotate our current shape.
bool Joker::checkIfShapeRotate()const
{
	return false;
}