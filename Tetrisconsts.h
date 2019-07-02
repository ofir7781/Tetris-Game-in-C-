#ifndef _TETRISCONSTS_H
#define _TETRISCONSTS_H

// list of all the const variables in our program.

const int ROWSFORMENU = 9;
const int ROWS = 16 + ROWSFORMENU;
const int COLS = 12;

const int LINE_SIZE = 4;
const int PYRAMID_SIZE = 4;
const int LEFT_SNAKE_SIZE = 4;
const int INVERSE_L_SIZE = 4;
const int CUBE_SIZE = 4;
const int BOMB_SIZE = 1;
const int JOKER_SIZE = 1;

const char BLOCK_APPEARANCE = '#';
const char BOMB_APPEARANCE = '@';

const int MIN_SPEED = 50;
const int MAX_SPEED = 2000;
const int CHANGE_SPEED = 100;
const int DROP_RATE = 50;
const int INITIAL_GAME_SPEED = 450;

const int JOKER_SCORE = 50;
const int BOMBED_DECREASE_SCORE = 50;
const int ONE_LINE_SCORE = 100;
const int TWO_LINE_SCORE = 300;
const int THREE_LINE_SCORE = 500;
const int FOUR_LINE_SCORE = 800;


#endif // !_TETRISCONSTS_H
