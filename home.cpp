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
    hangman_initialize();
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
        printf("\nWelcome to the Game Hub!\n");
        printf("1. Play Hangman\n");
        printf("2. Play Wordle\n");
        printf("3. Secret Number\n");
        printf("4. Tic-Tac-Toe\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            hangman_play();
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