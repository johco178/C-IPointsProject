// home.c

#include <stdio.h>
#include "secretNumber.h"
#include "hangman.h"
// Include headers for other games as you add them

void initialize_games(void) {
    hangman_initialize();
    // Initialize other games as you add them
}

int main(void) {
    int choice;

    initialize_games();

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
            printf("Game 2 is not implemented yet.\n");
            break;
        case 3:
            secretNumberStart();
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

// gcc home.c hangman.c -o gamehub