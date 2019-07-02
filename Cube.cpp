#include <iostream>
#include "Cube.h"

using namespace std;


Cube::Cube() : Shape()
{
	// create the new shape according to the inherit class 
	this->size = CUBE_SIZE;
	this->appearance = BLOCK_APPEARANCE;
	updateShapeValues(this->shape);
}

// this function decide where to place the tetris shape points according to the initial place of the board.
void Cube::updateShapeValues(vector<Point>& shape)
{
	Point one, two, three, four;

	one.setXY(5, 0 + (ROWSFORMENU - 1));
	two.setXY(6, 0 + (ROWSFORMENU - 1));
	three.setXY(5, 1 + (ROWSFORMENU - 1));
	four.setXY(6, 1 + (ROWSFORMENU - 1));

	// put the Point class in the vector of point
	shape.push_back(one);
	shape.push_back(two);
	shape.push_back(three);
	shape.push_back(four);
}

// this function responsible to rotate the shape. if the shape is not rotateble, do nothing.
bool Cube::rotateShape(const char rotateAxis, const char horizontal, const int**const matOfGame)
{
	return 0;
}


//checks if game is over because of the current shape that got in the game.
bool Cube::checkIfGameOver(const int**const matOfGame) const
{
	int col;

	for (col = 5; col < 5 + (size / 2); col++) // we do size/2 because it is a cube and we need to check only horizontal length
	{
		if (matOfGame[ROWSFORMENU][col] == 1)
			return true;
	}
	return false;
}

// checks if we can rotate our current shape.
bool Cube::checkIfShapeRotate()const
{
	return false;
}