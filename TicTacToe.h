/*!
    @file TicTacToe.h
    @brief Header file for TicTacToe class
    @author Curtis Mellsop
 */
#include <iostream>
using namespace std;


const int ROWS = 3;
const int COLS = 3;
extern char board[ROWS][COLS];

/*!
    @brief Initialises the 2D array board to empty character values
*/
void initBoard();

/*!
    @brief Displays the TicTacToe board in the terminal
*/
void displayBoard();

/*!
    @brief Checks for a winner
    @return True if winner identified, False if not
*/
bool checkWin();

/*!
    @brief Checks for a draw
    @return True if no moves available and no winner, false otherwise
*/
bool checkDraw();

/*!
    @brief Asks the player where they'd like to make their move and adds the move to board
    @param player Which person is playing (player 1 or player 2)
*/
void move(char player);

/*!
    @brief Function to run the game
*/
void playTicTacToe();