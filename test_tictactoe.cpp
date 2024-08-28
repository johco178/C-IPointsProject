#include "test_tictactoe.h"
#include <iostream>

int runttttests(){
    test_initBoard();
    test_checkWin();
    test_checkDraw();
    return 0;
}

void test_initBoard(){
    bool pass = true;
    initBoard();
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            if(board[i][j] != ' '){
                pass = false;
            }
        }
    }
    std::cout << "Initiate board function: " << (pass ? "PASSED" : "FAILED") << std::endl;
}

void test_checkWin(){
    // Check winning row
    initBoard();
    board[0][0] = 'X';
    board[0][1] = 'X';
    board[0][2] = 'X';
    std::cout << "Check Win function, row test: " << (checkWin() ? "PASSED" : "FAILED") << std::endl;

    // Check winning column
    initBoard();
    board[0][0] = 'O';
    board[1][0] = 'O';
    board[2][0] = 'O';
    std::cout << "Check Win function, column test: " << (checkWin() ? "PASSED" : "FAILED") << std::endl;

    // Check winning diagonal
    initBoard();
    board[0][0] = 'X';
    board[1][1] = 'X';
    board[2][2] = 'X';
    std::cout << "Check Win function, diagonal test: " << (checkWin() ? "PASSED" : "FAILED") << std::endl;

    // Check non-winning state
    initBoard();
    board[0][0] = 'X';
    board[0][1] = '0';
    board[0][2] = 'X';
    std::cout << "Check Win function, non-winning state: " << (!checkWin() ? "PASSED" : "FAILED") << std::endl;


}

void test_checkDraw(){
    initBoard();
    char drawState[ROWS][COLS] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'O', 'X', 'O'}
    };
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            board[i][j] = drawState[i][j];
        }
    }
    std::cout << "Check Draw function: " << (checkDraw() ? "PASSED" : "FAILED") << std::endl;

}