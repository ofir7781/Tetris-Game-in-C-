#include <iostream>
#include "Bomb.h"

using namespace std;

Bomb::Bomb() : Shape() 
{
	// create the new shape according to the inherit class 
	this->size = BOMB_SIZE;
	this->appearance = BOMB_APPEARANCE;
	updateShapeValues(this->shape);
}

// this function decide where to place the tetris shape points according to the initial place of the board.
void Bomb::updateShapeValues(vector<Point>& shape)
{
	Point one;
	one.setXY(5, 0 + (ROWSFORMENU - 1));
	shape.push_back(one);
}

// this function responsible to rotate the shape. if the shape is not rotateble, do nothing.
bool Bomb::rotateShape(const char rotateAxis, const char horizontal, const int**const matOfGame)
{
	return 0;
}

//checks if game is over because of the current shape that got in the game.
bool Bomb::checkIfGameOver(const int**const matOfGame) const
{
	return false; // bomb cannot lose the game.
}

// checks if we can rotate our current shape.
bool Bomb::checkIfShapeRotate()const
{
	return false;
}