#ifndef _TETRIS_GAME
#define _TETRIS_GAME

#include "Gotoxy.h"
#include "Point.h"
#include <stdlib.h>
#include"Shape.h"
#include "Tetrisconsts.h"
#include <vector>

class TetrisGame
{
private: //Attributes:	
	int score = 0; // we will initialize the score as 0 because this is our starting point in the game
	int numOfBlock = 0; // we will initialize the number of blocks as 0 because this is our starting point in the game
	int** matOfGame;

public: //methods:
	TetrisGame(); // constructor
	TetrisGame(const TetrisGame& other); // copy constructor
	~TetrisGame(); // destructor

	//get functions
	int** getMatOfGame()const { return matOfGame; }
	int getNumOfBlocks()const { return numOfBlock; }
	int getScore()const { return score; }

	// main function that runs the game.
	void run();

	// this functions responsible to print all the things we need for the game on the screen
	void showMenu()const;
	void showGameDetails()const;
	void printBoard()const;
	

	void updateMatOfGameLimit();
	bool checkIfGameOver(const Shape& form) const;

	void updateArrayOfMat(const Shape& form);

	// this functions responsible for the score update and change the board if we have complete lines
	int checkForCompleteLines();
	void makeCompleteLinesZero(const vector<int>& whichLinesAreCompleted);
	void dropShapesAfterCompleteLines(const vector<int>& whichLinesAreCompleted);
	void updateScore(Shape& form, const int completeLineCounter, const int dropdistance, int& countBombedBlocks);

    // this functions responsible for all the differnt kind of moves in the game.
	bool move(Shape& form, int& speed);
	bool moveShapeDown(Shape& form , int& countBombedBlocks);
	bool moveShapeLeftOrRight(Shape& form, const char pressedKey, int& countBombedBlocks);
	int dropShapeDown(Shape& form, int& countBombedBlocks);
	bool rotateShape(Shape& form, const char rotateAxis, const char horizontal);


	void welcomeScreen()const;
	void printGameOver()const;

};


#endif // !_TETRIS_GAME
