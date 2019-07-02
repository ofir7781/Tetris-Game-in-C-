using namespace std;

#include <iostream>
#include "TetrisGame.h"
#include "Shape.h"
#include "cube.h"
#include "Joker.h"
#include "Line.h"
#include "Bomb.h"
#include "LeftSnake.h"
#include "Pyramid.h"
#include "InverseL.h"
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "Tetrisconsts.h"
#include <vector>
#include <typeinfo>
#include <string>



TetrisGame::TetrisGame() // constructor
{
	// the constructor creates an array that follows where is every block in the game and update the
	// board after every new shape.
	int row, col;
	this->matOfGame = new int*[ROWS];

	for (row = 0; row < ROWS; row++)
	{
		this->matOfGame[row] = new int[COLS];
	}

	for (row = 0; row < ROWS; row++)
	{
		for (col = 0; col < COLS; col++)
		{
			this->matOfGame[row][col] = 0;
		}
	}
	
}

TetrisGame::~TetrisGame() // destructor
{
	// free the dynamic array mat of game.
	int i;
	for (i = 0; i < ROWS; i++)
	{
		delete[]matOfGame[i];
	}
	delete[]matOfGame;

}

TetrisGame::TetrisGame(const TetrisGame& other) //we wont use this copy constructor for now. but we might use it in the future.
{
	int row, col, i;
	int** tmpMatOfGame;

	tmpMatOfGame = other.getMatOfGame();

	this->numOfBlock = other.getNumOfBlocks();
	this->score = other.getScore();

	for (i = 0; i < ROWS; i++) // delete the old array of arrays 
	{
		delete[]matOfGame[i];
	}
	delete[]matOfGame;

	this->matOfGame = new int*[ROWS]; // create new dynamic array of arrays

	for (row = 0; row < ROWS; row++)
	{
		this->matOfGame[row] = new int[COLS];
	}

	for(row = 0; row < ROWS; row++) // copy the values from the array of arrays of other
	{
		for (col = 0; col < COLS; col++)
		{
			this->matOfGame[row][col] = tmpMatOfGame[row][col];
		}
	}

}

// the main function that runs the game
void TetrisGame::run()
{
	// Start - to make Cursor disappear:
	HANDLE hOut; 
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10; 
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
	// End - to make Cursor disappear.
	

	int num;
	bool isGameOver = false;
	int speed = INITIAL_GAME_SPEED;
	char startGame = 0;

	gotoxy(0, 0);
    welcomeScreen();
	Sleep(3000);
	system("cls");
	showMenu();

	while (!isGameOver) // as long as isGameOver is false keep runnig the game.
	{
		showGameDetails();

		while (startGame != START)
		{
			if (_kbhit())
			{
				startGame = _getch();
			}
		}
		
		printBoard();

		num = rand() % 100; //we will get a number between 0 to 99 and according to the number we will create the shape.

		if (num >= 0 && num < 16)
		{
			Shape* form = new Cube; 
			isGameOver = move((*form), speed);
			delete form;
		}
		else if (num >= 16 && num < 32)
		{
			
			Shape* form = new Line; 
			isGameOver = move((*form), speed);
			delete form;
		}
		else if (num >= 32 && num < 48)
		{
			Shape* form = new LeftSnake; 
			isGameOver = move((*form), speed);
			delete form;
		}
		else if (num >= 48 && num < 64)
		{
			Shape* form = new Pyramid;
			isGameOver = move((*form), speed);
			delete form;
		}
		else if (num >= 64 && num < 80)
		{
			Shape* form = new InverseL;
			isGameOver = move((*form), speed);
			delete form;
		}
		else if (num >= 80 && num < 90)
		{
			Shape* form = new Joker; 
			isGameOver = move((*form), speed);
			delete form;
		}
		else if (num >= 90 && num < 99)
		{
			Shape* form = new Bomb;
			isGameOver = move((*form), speed);
			delete form;
		}
		
		this->numOfBlock++; //update number of blocks every time we finish using a shape.
	}

}


// this is our main function tha responsible for all the differnt kind of moves in the game.
bool TetrisGame::move(Shape& form, int& speed)
{
	int size = form.getSize();
	vector<Point> shape;
	shape = form.getShape();
	bool isContinue = true; // the shape can still move
	char rotateAxis = 'R'; // we will use this char in order to know which block to use as axis for the rotate - R for Light, L for Left
	char horizontal = 'T'; // Is the line horizontal? True or False.
	bool isGameOver = checkIfGameOver(form); // check if game is over before we start moving
	int completeLineCounter, dropdistance, countBombedBlocks;
	countBombedBlocks = 0;
	dropdistance = 0;

	if (isGameOver == true)
	{
		printGameOver();
	}


	while (isContinue && !(isGameOver)) // if game is not over yet and shape can move, enter the loop.
	{
		char pressedKey = 0;
		if (_kbhit()) // checks if there is anything in the buffer
		{
			pressedKey = _getch(); // take the head of the buffer

		/*  To use with arrow keys(untested) : 
			if (pressedKey == -32)
			{
				pressedKey = _getch();
			}
		*/		

			switch (pressedKey)
			{
			case PAUSE:
			{
				pressedKey = 0;
				gotoxy(17, 15);
				cout << "Pause:";
				gotoxy(17, 17);
				cout << "Press 2 to Resume";
				gotoxy(17, 18);
				cout << "Press 9 to Exit";
				while (pressedKey != PAUSE && pressedKey != EXIT)
				{


					if (_kbhit())
					{
						pressedKey = _getch();

						if (pressedKey == EXIT)
						{
							printGameOver();
							return true;
						}
					}
				}
				gotoxy(17, 15);
				cout <<"                  " << endl;
				gotoxy(17, 17);
				cout <<"                             "<< endl;
				gotoxy(17, 18);
				cout <<"                         ";
			}
			case SLOWER:
			{
				if(speed < MAX_SPEED)
				speed = speed + CHANGE_SPEED;
				break;
			}
			case FASTER:
			{
				if (speed > MIN_SPEED)
				speed = speed - CHANGE_SPEED;
				break;
			}
			case EXIT:
			{		
				printGameOver();
				return true;
				break;
			}
			case UP:
			{

				int minY;
				bool rotatingShape, isRotated;
				rotatingShape = form.checkIfShapeRotate(); // this function check if we can rotate the current shape. 
				shape = form.getShape();
				minY = shape[0].getY();
				for (int i = 1; i < size; i++)
				{
					if (minY > shape[i].getY())
						minY = shape[i].getY();
				}

				if (rotatingShape && minY > ROWSFORMENU) // to avoid the shape exception from board limit.
				{

					isRotated = rotateShape(form, rotateAxis, horizontal);
					
					if (isRotated)
					{
						if (horizontal == 'T')
							horizontal = 'F';
						else
							horizontal = 'T';

						if (rotateAxis == 'R' && horizontal == 'T')
							rotateAxis = 'L';
						else if (rotateAxis == 'L' && horizontal == 'T')
							rotateAxis = 'R';
					}

				
				}
					break;
			}
			case LEFT:
			{
				isContinue = moveShapeLeftOrRight(form, pressedKey, countBombedBlocks);
				break;
			}
			case RIGHT:
			{
				isContinue = moveShapeLeftOrRight(form, pressedKey, countBombedBlocks);
				break;
			}
			case DOWN:
			{
				dropdistance=dropShapeDown(form, countBombedBlocks);
				isContinue = false;
				break;
			} 
			case STOPJOKER:
			{
				if (typeid(form).name() == typeid(Joker).name()) // Shape is a Joker/// if not working do strcmp
					isContinue = false;
				break;
			}
			default:
				break;
			}
		}
		if (isContinue) //is the shape can still move
		{
			Sleep(speed); // update the speed
			isContinue = moveShapeDown(form, countBombedBlocks);
		}
	}

	if (isGameOver == false)
	{
		updateArrayOfMat(form);// UPDATE ARRAY
		completeLineCounter = checkForCompleteLines();
		updateScore(form, completeLineCounter, dropdistance, countBombedBlocks);
	}

	form.setShape(shape);
	return isGameOver; // false unless it is game over
}

bool TetrisGame::moveShapeLeftOrRight(Shape& form, const char pressedKey, int& countBombedBlocks)
{
	bool canMove = true;
	int i, j, x, y, rowLim, colLimLeft,colLimRight, size;
	vector<Point> shape;
	size = form.getSize();
	rowLim = ROWS - 1;
	colLimLeft = 0;
	colLimRight = COLS - 1;

	shape = form.getShape();
	
			for (i = 0; i < size; i = i++)
			{
				x = shape[i].getX();
				y = shape[i].getY();
				if (typeid(form) != typeid(Joker)) // Joker can move onto other blocks
				{
					if (pressedKey == LEFT)
					{
						if (this->matOfGame[y][x - 1] == 1)
						{
							canMove = false;
						}
					}
					else // if the direction is RIGHT
					{
						if (this->matOfGame[y][x + 1] == 1)
						{
							canMove = false;
						}
					}
				}
				else  // Is a Joker
				{
					if (pressedKey == LEFT)
					{
						if (x - 1 <= colLimLeft)
						{
							canMove = false;
						}
					}
					else // if the direction is RIGHT
					{
						if (x + 1 >= colLimRight)
						{
							canMove = false;
						}
					}

				}

				
			}

			if (!canMove && typeid(form) == typeid(Bomb)) // A bomb hit a block from below
			{

				x = shape[0].getX();
				y = shape[0].getY();
				for (i = -1; i < 2; i++) // in order to cheack 3x3 blocks around the bomb
				{
					for (j = -1; j < 2; j++) 
					{
						gotoxy(x + i, y + j);
						if (this->matOfGame[y + j][x + i] == 1)
						{
							if ((y + j) < rowLim && (x + i) < colLimRight && (x + i) > colLimLeft)
							{
								countBombedBlocks++;
								cout << " ";
							}
						}
						gotoxy(x, y); // erase the place of bomb.
						cout << " ";
					}
				}
				return false; // so bomb will not continue to move

			}
			else if (canMove)
			{
				for (i = 0; i < size; i++)
				{
					x = shape[i].getX();
					y = shape[i].getY();
					if (typeid(form) != typeid(Joker))   // if the shape is NOT a joker  
						shape[i].draw(' ');
					else if (this->matOfGame[y][x] == 0) // Joker does not encounter a block
					{
						shape[i].draw(' ');
					}

					if (pressedKey == LEFT)
					{
						shape[i].setXY(x - 1, y);
					}
					else // if the direction is RIGHT
					{
						shape[i].setXY(x + 1, y);
					}
					
				}
				for (i = 0; i < size; i++)
				{
					shape[i].draw(form.getAppearance()); //draw the shape to the screen
				}
			}
			form.setShape(shape);
			return true; 
	}

int TetrisGame::dropShapeDown(Shape& form , int& countBombedBlocks)
{

	bool canMove = true;
	vector<Point> shape;
	int i, j, x, y, dropDistance, rowLim, colLimLeft, colLimRight, size;
	unsigned initialY, endY;
	char appearance = form.getAppearance();
	size = form.getSize();
	shape = form.getShape();
	rowLim = ROWS - 1;
	colLimLeft = 0;
	colLimRight = COLS - 1;

	dropDistance = 0;
	initialY = shape[0].getY(); // bigest Y-coordinate of the shape that was now dropped
	endY = 0; // The Y-coordinate after the drop

	if(typeid(form) != typeid(Joker) && typeid(form) != typeid(Bomb))
		for(i = 1; i < size; i++)
		{
			if (initialY < shape[i].getY())
				initialY = shape[i].getY(); // finding bigest Y-coordinate
		}

	while (canMove)
	{

		if (typeid(form) == typeid(Joker))  // if the shape is a joker
		{
			y = shape[0].getY();
			if (y + 2 == ROWS) // cheak the bottom line of board
				canMove = false;
		}
		else 
		{
			for (i = 0; i < size; i++)
			{
				x = shape[i].getX();
				y = shape[i].getY();
				if (this->matOfGame[y + 1][x] == 1)
					canMove = false;
			}

		}
		
		if (!canMove && typeid(form) == typeid(Bomb)) // A bomb hit a block from below
		{

			x = shape[0].getX();
			y = shape[0].getY();
			for (i = -1; i < 2; i++) // in order to cheack 3x3 blocks around the bomb
			{
				for (j = -1; j < 2; j++)
				{
					gotoxy(x + i, y + j);

					if (this->matOfGame[y + j][x + i] == 1)
					{

						if ((y + j) < rowLim && (x + i) < colLimRight && (x + i) > colLimLeft)
						{
							countBombedBlocks++;
							cout << " ";
						}
					}
					gotoxy(x, y); // erase the place of bomb.
					cout << " ";
				}
			}
		}
		else if (canMove) //otherwish, if can still keep moving
		{
			for (i = 0; i < size; i++)
			{
				x = shape[i].getX();
				y = shape[i].getY();
				if (typeid(form) != typeid(Joker))   // if the shape is NOT a joker  
					shape[i].draw(' ');
				else if (this->matOfGame[y][x] == 0) // Joker does not encounter a block
				{
					shape[i].draw(' ');
				}
					
				shape[i].setXY(x, y + 1);
			}

			for (i = 0; i < size; i++)
			{
				if (typeid(form) != typeid(Joker))   // if the shape is NOT a joker  
					shape[i].draw(appearance);
				else if (this->matOfGame[y+1][x] == 0) // Joker does not encounter a block
				{
					shape[i].draw(appearance);
				}

			}
			Sleep(DROP_RATE);
		}
	
	}
	
	if (typeid(form) != typeid(Joker) && typeid(form) != typeid(Bomb))
		for (i = 1; i < form.getSize(); i++)
		{
			if (endY < shape[i].getY())
				endY = shape[i].getY();
		}
	else // Is a BOMB or a JOKER
		endY = shape[0].getY();

	dropDistance = endY - initialY;

	form.setShape(shape);
	return dropDistance;

}

bool  TetrisGame::moveShapeDown(Shape& form, int& countBombedBlocks)
{
	bool canMove = true;
	vector<Point> shape;
	int i, j, x, y, rowLim, colLimLeft, colLimRight, size;
	size = form.getSize();
	char appearance = form.getAppearance();
	shape = form.getShape();
	rowLim = ROWS - 1;
	colLimLeft = 0;
	colLimRight = COLS - 1;



	if (typeid(form) == typeid(Joker))  // if the shape is a joker
	{
		y = shape[0].getY();
		if (y + 2 == ROWS) // cheak the bottom line of board
			canMove = false;
	}
	else
	{
		for (i = 0; i < size; i++)
		{
			x = shape[i].getX();
			y = shape[i].getY();
			if (this->matOfGame[y + 1][x] == 1)
				canMove = false;
		}
	}

	if (!canMove && typeid(form) == typeid(Bomb)) // A bomb hit a block from below
	{

		x = shape[0].getX();
		y = shape[0].getY();
		for (i = -1; i < 2; i++) // in order to cheack 3x3 blocks around the bomb
		{
			for (j = -1; j < 2; j++)
			{
				gotoxy(x + i, y + j);
				if (this->matOfGame[y + j][x + i] == 1)
				{
					if ((y + j) < rowLim && (x + i) < colLimRight && (x + i) > colLimLeft)
					{
					countBombedBlocks++;
					cout << " ";
					}
				}
				gotoxy(x, y); // erase the place of bomb.
				cout << " ";
			}

		}
	}
	else if (canMove) 
	{
		for (i = 0; i < size; i++)
		{
			x = shape[i].getX();
			y = shape[i].getY();
			if (typeid(form) != typeid(Joker))   // if the shape is NOT a joker  
				shape[i].draw(' ');
			else if (this->matOfGame[y][x] == 0) // Joker does not encounter a block
			{
				shape[i].draw(' ');
			}

			shape[i].setXY(x, y + 1);
		}

		for (i = 0; i < size; i++)
		{
			if (typeid(form) != typeid(Joker))   // if the shape is NOT a joker  
				shape[i].draw(appearance);
			else if (this->matOfGame[y + 1][x] == 0) // Joker does not encounter a block
			{
				shape[i].draw(appearance);
			}

		}
	}
	
	form.setShape(shape);
	return canMove;
}

// this function rotate the LINE shape according to the game you gave us.
bool TetrisGame::rotateShape(Shape& form, const char rotateAxis, const char horizontal)
{
	return form.rotateShape(rotateAxis, horizontal, (const int**) this->matOfGame);
}

// this function is responsible for the score in the game
void TetrisGame::updateScore(Shape& form, const int completeLineCounter, const int dropdistance, int& countBombedBlocks)
{
	int size;
	size = form.getSize();
	 this->score = this->score + (2 * dropdistance); // update the score after we drop a shape

	 if (completeLineCounter > 0) // if we have complete lines, update the score according to the number of them.
	 {
		 if (typeid(form) == typeid(Joker))// special case for a complete line using the JOKER
			 this->score = this->score + JOKER_SCORE;
		 else if (typeid(form) != typeid(Bomb))
		 {
			 switch (completeLineCounter)
			 {
			 case 1:
			 {
				 this->score = this->score + ONE_LINE_SCORE;
				 break;
			 }
			 case 2:
			 {
				 this->score = this->score + TWO_LINE_SCORE;
				 break;
			 }
			 case 3:
			 {
				 this->score = this->score + THREE_LINE_SCORE;
				 break;
			 }
			 case 4:
			 {
				 this->score = this->score + FOUR_LINE_SCORE;
				 break;
			 }
			 }
		 } 
	}

	 if(typeid(form) == typeid(Bomb)) // if we destroy blocks using bomb
	 {
		 this->score = this->score - (countBombedBlocks * BOMBED_DECREASE_SCORE);
		 if (this->score < 0)
			 this->score = 0;

		 gotoxy(6, 6);
		 cout << "          ";
	 }
}

// this function check if game is over by checkig every shape and if there is a place for him in the top of the board.
bool TetrisGame::checkIfGameOver(const Shape& form)const
{
	return form.checkIfGameOver((const int**) this->matOfGame);
}

// this function show us the game menu in the begining of every game.
void TetrisGame::showMenu() const
{
	gotoxy(0, 0);
	cout << "THE TETRIS GAME MENU: " << endl;
	cout << "press 1 to start game                         t-Rotate" << endl;
	cout << "press 2 to pause/continue game          f-Left g-Drop h-Right" << endl;
	cout << "press 3 to make game run faster              s-Stop Joker" << endl;
	cout << "press 4 to make game run slower" << endl;
	cout << "press 9 to exit game" << endl;
}

void TetrisGame::showGameDetails()const
{
	gotoxy(0, 6); 
	cout << "Score: " << this->score;
	cout << endl;
	cout << "Number of blocks in game: " << this->numOfBlock;
}


// this function prints the board to the screen 
void TetrisGame::printBoard()const
{
int i;

   
   for (i = 0 + ROWSFORMENU; i < (ROWS - 1); i++) // matOfGame always start from 0,0
      {
           gotoxy(0, i);
		   matOfGame[i][0] = 1;
           cout << "|";
           gotoxy((COLS - 1), i);
		   matOfGame[i][COLS - 1] = 1;
           cout << "|";
      }


    gotoxy(0, (ROWS - 1));
    cout << "%%%%%%%%%%%%";

	for(i = 0; i < COLS; i++)
		matOfGame[ROWS - 1][i] = 1;


} 

// this function update the edges of the matrix of game as 1 in order the have limits for our board.
void  TetrisGame::updateMatOfGameLimit() 
{
	int row, col;

	for (row = 0; row < ROWS; row++)
	{
		for (col = 0; col < COLS; col++)
		{
			if (row == (ROWS - 1))
			{
				this->matOfGame[row][col] = 1;
			}
			else if ((col == 0) || (col == (COLS - 1)))
			{
				this->matOfGame[row][col] = 1;
			}

		}
	}


}

// update the matrix of game after every shape 
void TetrisGame::updateArrayOfMat(const Shape& form)
{
	vector<Point> shape;
	int i, j, x, y, size;
	shape = form.getShape();
	size = form.getSize();
	if (typeid(form) == typeid(Bomb)) // is a bomb
	{
		x = shape[0].getX();
		y = shape[0].getY();
		for (i = -1; i < 2; i++)
		{
			for (j = -1; j < 2; j++)
			{
				this->matOfGame[y + j][x + i] = 0;
			}

		}
	}
	else // not a bomb
	{
		for (i = 0; i < size; i++)
		{
			x = shape[i].getX();
			y = shape[i].getY();
			this->matOfGame[y][x] = 1;
		}
	}
}

//this function look for complete lines(a line of only 1) after every shape drop and change the board according to the number of complete lines
int TetrisGame::checkForCompleteLines()
{
	int row, col, z ;
	bool completeLine = true;
	vector<int> whichLinesAreCompleted; // the highest number of complete lines that we can have is 4.

	row = ROWS - 2;
	while (whichLinesAreCompleted.size() == 0 && row > ROWSFORMENU)
	{
		col = 1;
		completeLine = true;
		while (col <= COLS - 2)
	    {
			if (this->matOfGame[row][col] == 0) // if there is an empty spot in the row. this is not a complete line
				completeLine = false;
			col++;
		}
		if (completeLine == true) // if there is a complete line
		{
			whichLinesAreCompleted.push_back(row);
			

			for (z = 1; z < 4; z++) // Vertical Line is 4 blocks and it the longest shape, therefore maximum 4 rows can be completed at once.
			{
				col = 1;
				while (completeLine && col <= COLS - 2)
				{
					if (this->matOfGame[row - z][col] == 0)
						completeLine = false;
					col++;
				}
				if (completeLine == true)
				{
					whichLinesAreCompleted.push_back(row - z);
				}
				completeLine = true;
			}
		}
		row--;
	}

	if (whichLinesAreCompleted.size() > 0) // if there are complete lines we need to take off
	{
		makeCompleteLinesZero(whichLinesAreCompleted);
		dropShapesAfterCompleteLines(whichLinesAreCompleted);
	}
	return whichLinesAreCompleted.size();
}

//this function update the matrix of game as 0 insted of 1 and erase the symbol from the screen 
void TetrisGame::makeCompleteLinesZero(const vector<int>& whichLinesAreCompleted)
{
	int col;

		for (int rowToMakeZero : whichLinesAreCompleted)
		{
			for (col = 1; col <= COLS - 2; col++)
			{
				this->matOfGame[rowToMakeZero][col] = 0;
				gotoxy(col, rowToMakeZero);
				cout << " ";
			}

		}
}

// this function drop all the blocks after the complete lines disappear
void TetrisGame::dropShapesAfterCompleteLines(const vector<int>& whichLinesAreCompleted)
{
	int row, col, lastline;
	lastline = 1;
	vector<int>::const_iterator itr = whichLinesAreCompleted.begin();
	vector<int>::const_iterator itrEnd = whichLinesAreCompleted.end();
	while(lastline)
	{
		--itrEnd;
		if (itrEnd == itr)
		{
			lastline = 0;
		}
		gotoxy(26, 0);
		cout << lastline;
		row = *itrEnd;
		while (row > ROWSFORMENU) // this while loop goes from the first complete line until the top of board
		{
			for (col = 1; col <= COLS - 2; col++)
			{

				if (this->matOfGame[row - 1][col] == 1) // if there is a symbol, drop him down
				{
					gotoxy(col, row - 1);
					cout << " ";
					gotoxy(col, row);
					cout << BLOCK_APPEARANCE;
					this->matOfGame[row][col] = 1;
					this->matOfGame[row - 1][col] = 0;
				}

			}
			row--;
		}
	}
}





void TetrisGame::welcomeScreen() const
{
	cout << "*******************************************************************************" << endl;
	cout << "*         ___ .  . .___    ___ .___ ___ __  _ _ .__   .__. .__..  ..___       *" << endl;
	cout << "*          |  |__| |___     |  |___  |  |_|  |  |_    | __ |__||\\/||___       *" << endl;
	cout << "*          |  |  | |___     |  |___  |  |\\  _|_ ._|   |__] |  ||  ||___       *" << endl;
	cout << "*                                                                             *" << endl;
	cout << "*                                                                     __      *" << endl;
	cout << "*                       By Ofir Cohen and Ran Barak                  |__|     *" << endl;
	cout << "*                                                              ______|__|     *" << endl;
	cout << "*     __                                                      |__|_|_|__|     *" << endl;
	cout << "*    |__|                                                     |__|            *" << endl;
	cout << "*    |__|                                                     |__|            *" << endl;
	cout << "*    |__|                                                                     *" << endl;
	cout << "*    |__|                                                                     *" << endl;
	cout << "*                                                                             *" << endl;
	cout << "*                                                              ___            *" << endl;
	cout << "*           __ __                                             |   |           *" << endl;
	cout << "*          |__|__|                                     _______|___|_______    *" << endl;
	cout << "*          |__|__|                                     |   |  |   |  |   |    *" << endl;
	cout << "*                                                      |___|__|___|__|___|    *" << endl;
	cout << "*                                                                             *" << endl;
	cout << "*******************************************************************************" << endl;


}


void TetrisGame::printGameOver() const
{

	system("cls");
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "+                                                                              +" << endl;
	cout << "+     _______ _______ _______ _______      _______ ___ ___ _______ ______      +" << endl;
	cout << "+    |     __|   _   |   |   |    ___|    |       |   |   |    ___|   __ \\     +" << endl;
	cout << "+    |    |  |       |       |    ___|    |   -   |   |   |    ___|      <     +" << endl;
	cout << "+    |_______|___|___|__|_|__|_______|    |_______|\\_____/|_______|___|__|     +" << endl;
	cout << "+                                                                              +" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Final Score:  " << this->score << "  " << endl;
}