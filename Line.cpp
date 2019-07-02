#include <iostream>
#include "Line.h"

using namespace std;


Line::Line(): Shape()
{
	// create the new shape according to the inherit class 
	this->size = LINE_SIZE;
	this->appearance = BLOCK_APPEARANCE;
	updateShapeValues(this->shape);
}

// this function decide where to place the tetris shape points according to the initial place of the board.
void Line::updateShapeValues(vector<Point>& shape)
{
	Point one, two, three, four;

	one.setXY(3, 0 + (ROWSFORMENU - 1));
	two.setXY(4, 0 + (ROWSFORMENU - 1));
	three.setXY(5, 0 + (ROWSFORMENU - 1));
	four.setXY(6, 0 + (ROWSFORMENU - 1));

	// put the Point class in the vector of point
	shape.push_back(one);
	shape.push_back(two);
	shape.push_back(three);
	shape.push_back(four);
}

// this function responsible to rotate the shape. if the shape is not rotateble, do nothing.
bool Line::rotateShape(const char rotateAxis, const char horizontal, const int**const matOfGame)
{
	int i, x, y;
	bool canMove = true;

	if (rotateAxis == 'R' && horizontal == 'T')
	{

		x = shape[2].getX();
		y = shape[2].getY();

		if (matOfGame[y + 1][x] == 1 || matOfGame[y + 2][x] == 1) // no need to check blocks that are above the shape
			canMove = false;

		if(canMove)
		{
			for (i = 0; i < size; i++)
				shape[i].draw(' ');

			shape[0].setXY(x, y - 1);
			shape[1].setXY(x, y);
			shape[2].setXY(x, y + 1);
			shape[3].setXY(x, y + 2);

			for (i = 0; i < size; i++)
			{
				shape[i].draw(appearance);
			}
		}

	}
	else if (rotateAxis == 'L' && horizontal == 'T')
	{
		x = shape[1].getX();
		y = shape[1].getY();

		if (matOfGame[y + 1][x] == 1) // no need to check blocks that are above the shape
			canMove = false;

		if (canMove)
		{ 
		for (i = 0; i < size; i++)
			shape[i].draw(' ');

		shape[0].setXY(x, y - 2);
		shape[1].setXY(x, y - 1);
		shape[2].setXY(x, y);
		shape[3].setXY(x, y + 1);

		for (i = 0; i < size; i++)
		{
			shape[i].draw(appearance);
		}
		}
	}
	else if (rotateAxis == 'R' && horizontal == 'F')
	{
		x = shape[1].getX();
		y = shape[1].getY();
		if (matOfGame[y][x + 1] == 1 || matOfGame[y][x - 1] == 1 || matOfGame[y][x - 2] == 1) // no need to check x,y because x,y is the axis of the rotate.
		{
			canMove = false;
		}
		if (canMove)
		{
			for (i = 0; i < size; i++)
				shape[i].draw(' ');

			shape[0].setXY(x - 2, y);
			shape[1].setXY(x - 1, y);
			shape[2].setXY(x, y);
			shape[3].setXY(x + 1, y);

			for (i = 0; i < size; i++)
			{
				shape[i].draw(appearance);
			}
		}
		
	}
	else if (rotateAxis == 'L' && horizontal == 'F')
	{
		x = shape[2].getX();
		y = shape[2].getY();


		if (matOfGame[y][x - 1] == 1 || matOfGame[y][x + 1] == 1 || matOfGame[y][x + 2] == 1) // no need to check x,y because x,y is the axis of the rotate.
		{
			canMove = false;
		}
		if (canMove)
		{
			for (i = 0; i < size; i++)
				shape[i].draw(' ');

			shape[0].setXY(x - 1, y);
			shape[1].setXY(x, y);
			shape[2].setXY(x + 1, y);
			shape[3].setXY(x + 2, y);

			for (i = 0; i < size; i++)
			{
				shape[i].draw(appearance);
			}
		}
		
	}

	return canMove;
}

//checks if game is over because of the current shape that got in the game.
bool Line::checkIfGameOver(const int**const matOfGame)const
{
	int col;

	for (col = 4; col < 4 + size; col++)
	{
		if (matOfGame[ROWSFORMENU][col] == 1)
			return true;
	}
	return false;
}

// checks if we can rotate our current shape.
bool Line::checkIfShapeRotate()const
{
	return true;
}