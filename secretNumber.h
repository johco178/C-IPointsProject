#ifndef SECRETNUMBER_H
#define SECRETNUMBER_H
#include <stdbool.h>

/*!
    @file
    @brief This file contains the function declarations for the Secret Number game.
    
*/

//Gets a random number between lowerBound and upperBound (based off difficulty)
int getSecretNumber(int lowerBound, int upperBound);

//Gets the difficulty level from the user input
char getDifficulty();

//Takes the user's input as a guess and checks if it is valid
int getGuess(int lowerBound, int upperBound);

//PLays the game by calling for the guess and checkin gif it is correct
int play(char difficulty);

//Asks the user if they want to play again
bool playAgain();

//Starts the game
void secretNumberStart();


#endif // SECRETNUMBER_H