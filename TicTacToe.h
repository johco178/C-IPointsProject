#include <iostream>
using namespace std;

const int ROWS = 3;
const int COLS = 3;
extern char board[ROWS][COLS];

void initBoard();
void displayBoard();
bool checkWin();
bool checkDraw();
void move(char player);
void playTicTacToe();