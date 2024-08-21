#include <stdio.h>
#include <stdlib.h>



void HomeScreen() {
	int choice;
	printf("What game do you want to play?");
	printf("Type in a number for the game you want to play.");
	printf("[1] Hangman \t[2] Code Breaker \t[3] Wordle \t[4] TicTacToe");

	if (scanf("%d", &choice) != 1) {
		printf("Invalid input please enter a number in the range");
		void HomeScreen();
	}

	if (choice == 1) {

	}




}
