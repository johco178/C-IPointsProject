// home.c
/*!
    @file home.cpp
	@brief Main file for the Game Hub
*/
#include <stdio.h>
#include "secretNumber.h"
#include "hangman.h"
#include "newwordle.h"
#include "TicTacToe.h"
#include "startmusic.h"
// Include headers for other games as you add them

/*!
    @brief Function to initialize all games
*/
void initialize_games(void) {
    hangmanInitialize();
    wordle_initialize();
    // Initialize other games as you add them
}

/*!
	@brief Function to display the homescreen and allow the user to choose a game to play
*/
int homescreen(void) {
    int choice;


    initialize_games();
    startmusic();

    while (1) {
        printf("\nWelcome to the Game Hub!\n\n");
        printf("1. HANGMAN\n\n");
        printf("    +---+\n    |   |\n    O   |\n   /|\\  |\n   / \\  |\n        |\n  =========\n\n");

        printf("2. WORDLE\n\n");
        printf("   S _ _ _ _\n");
        printf("   S _ E A _\n");
        printf("   S T E A _\n");
        printf("   S T E A M\n\n");

        printf("3. SECRET NUMBER\n\n");

        printf("4. TICTACTOE\n\n");
        printf("   X | O | O\n");
        printf("   ---------\n");
        printf("   O | X | O\n");
        printf("   ---------\n");
        printf("   X | O | X\n\n");

        printf("0. Exit\n\n");
        printf("Which would you like to play? ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            hangmanPlay();
            break;
        case 2:
            playWordle();
            break;
        case 3:
            secretNumberStart();
            break;
        case 4:
            runGame();
            break;
        case 0:
            printf("Thank you for playing. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// to test:
// gcc home.cpp hangman.cpp secretNumber.cpp -o gamehub