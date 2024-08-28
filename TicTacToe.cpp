#include "TicTacToe.h"

char board[ROWS][COLS];

void initBoard(){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            board[i][j] = ' ';
        }
    }
}

void displayBoard(){
    cout << "\n" << endl;
    cout << "\t  1   2   3" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << "\t" << char('A' + i) << " ";
        for (int j = 0; j < COLS; j++) {
            cout << board[i][j];
            if (j < COLS - 1) cout << " | ";
        }
        cout << endl;
        if (i < ROWS - 1) cout << "\t  ---------" << endl;
    }
    cout << "\n" << endl;
}

bool checkWin(){
    // Check rows
    for(int i = 0; i < ROWS; i++){
        if((board[i][0] == board[i][1] && board[i][1] == board[i][2]) && board[i][0] != ' '){
            return true;
        }
    }

    // Check columns
    for(int i = 0; i < COLS; i++){
        if((board[0][i] == board[1][i] && board[1][i] == board[2][i]) && board[0][i] != ' '){
            return true;
        }
    }

    // Check diagonals
    if(board[1][1] != ' ' && ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[0][2] == board[1][1] && board[1][1] == board[2][0]))){
        return true;
    }
    return false;
}

bool checkDraw(){
    for(int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            if (board[i][j] == ' '){
                return false;
            }
        }
    }
    return true;
}

void move(char player){
    string input;
    char charRow;
    int col;
    int row;
    int p = (player == 'X') ? 1 : 2;
    while(true){
        cout << "Player " << p << ", please enter your move (format example: A2): ";
        cin >> input;
        charRow = toupper(input[0]);
        row = charRow - 'A';
        col = input[1] - '1';
        if(row > (ROWS - 1) || row < 0 || col > (COLS - 1) || col < 0){
            cout << "Invalid row or column" << endl;
            continue;
        }
        if(board[row][col] != ' '){
            cout << "Positiom already has a value" << endl;
            continue;
        }
        board[row][col] = player;
        break;
    }    
}

int playTicTacToe(){
    char currentPlayer = 'X';
    initBoard();

    cout << "Welcome to Tic-Tac-Toe" << endl;
    cout << "To play, enter the coordinates of where you want to put your piece:" << endl;

    while (true) {
        displayBoard();
        move(currentPlayer);

        if (checkWin()) {
            displayBoard();
            cout << "Player " << ((currentPlayer == 'X') ? 1 : 2) << " wins!" << endl;
            break;
        } else if (checkDraw()) {
            displayBoard();
            cout << "It's a draw!" << endl;
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    return 0;
}