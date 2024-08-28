#ifndef SECRETNUMBER_H
#define SECRETNUMBER_H
#include <stdbool.h>


 //Generates a random secret number between the lower and upper bounds
int getSecretNumber(int lowerBound, int upperBound);

// Checks if the input for the difficulty level is valid
bool validDifficulty(char difficulty);

//Gets the difficulty level from the user input
char getDifficulty();

// Checks if the input for a guess is valid
bool validGuess(int guess, int lowerBound, int upperBound, int check);

// Takes the user's input as a guess and checks if it is valid
int getGuess(int lowerBound, int upperBound);

// Plays the game 
void play(char difficulty);

//Checks if the input is valid for playAgain
bool validPlayAgain(char playAgain);

// Asks the user if they want to play again
bool playAgain();

/**
 * Starts the game by calling getDifficulty to get the difficulty level
 * and calling play to play the game
 */
void secretNumberStart();

#endif // SECRETNUMBER_H