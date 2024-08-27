#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

/**
 * Generates a random secret number between the lower and upper bounds
 * 
 * @param lowerBound The lower bound of the range for the secret number
 * @param upperBound The upper bound of the range for the secret number
 * @return The randomly generated secret number
 */
int getSecretNumber(int lowerBound, int upperBound) {
    srand(time(0)); // Seed the random number generator
    return rand() % (upperBound - lowerBound + 1) + lowerBound;// returns a random number between the lower and upper bounds
}

/**
 * Gets the difficulty level from the user input
 * 
 * @return The difficulty level chosen by the user as a char
 */
char getDifficulty() {
    char difficulty;
    printf("Choose difficulty level (e: easy, m: medium, h: hard): ");
    scanf(" %c", &difficulty); //assign the value of scanning a character from the user input
    difficulty = tolower(difficulty);//converts the input to lowercase incase of valid uppercase input

    while (difficulty != 'e' && difficulty != 'm' && difficulty != 'h') {
        printf("That is not a valid input. Please choose 'e' for easy, 'm' for medium, or 'h' for hard.\n");
        scanf(" %c", &difficulty); //assign the value of scanning a character from the user input
        difficulty = tolower(difficulty);//converts the input to lowercase incase of valid uppercase input
    }
    return difficulty;//returns the difficulty level
}

/**
 * Takes the user's input as a guess and checks if it is valid
 * 
 * @param lowerBound The lower bound of the range for the secret number
 * @param upperBound The upper bound of the range for the secret number
 * @return The user's guess as an integer
 */
int getGuess(int lowerBound, int upperBound) {
    int guess, check;
    printf("Enter a guess between %d and %d : ", lowerBound, upperBound);
    check = scanf("%d", &guess); //assign the value of scanning a number from the user input

    if (check == 0 || guess < lowerBound || guess > upperBound)//if check is 0 input is not a number, also checks if guess is wihtin the bounds
    {
        printf("That is not a valid input. Please enter a number between %d and %d.\n", lowerBound, upperBound);
        while (getchar() != '\n'); //Copilot suggested this line and the code loops endlessly without it
        return getGuess(lowerBound, upperBound);//recursion to get a valid input
    }
    return guess;//returns the guess if it is valid
}

/**
 * PLays the game by taking the difficulty level in
 * calling getSecretNumber to get a secret number
 * calling getGuess to get the user's guess
 * checking if the guess is correct and if not looping until it is or the user runs out of attempts
 * 
 * @param difficulty The difficulty level chosen by the user as a char
 * @return 0
 */
void play(char difficulty){
    int lowerBound, upperBound, maxAttempts, attempts = 0, secretNumber, guess, attemptsLeft, check;
    
    //Sets the lower and upper bounds and max attempts based on the difficulty level
    if (difficulty == 'e'){
        lowerBound = 1; 
        upperBound = 10;
        maxAttempts = 10;
    } else if (difficulty == 'm'){
        lowerBound = 1; 
        upperBound = 50;
        maxAttempts = 20;
    } else if (difficulty == 'h'){
        lowerBound = 1; 
        upperBound = 100;
        maxAttempts = 10;
    }
    //Gets a secret number
    secretNumber = getSecretNumber(lowerBound, upperBound);

    printf("The secret number is between %d and %d.\n", lowerBound, upperBound);
    printf("You have %d attempts to guess the number.\n", maxAttempts);
    //attemptsLeft set to max attempts and is decremented each time the user guesses a valid guess
    attemptsLeft = maxAttempts;
    
        do {
        //Gets the user's guess
        guess = getGuess(lowerBound, upperBound);
        
        //Increments the number of attempts and decrements the number of attempts left
        attempts++;
        attemptsLeft--;

        //Checks if the guess is correct and if not tells the user if they guessed too high or too low
        if (guess > secretNumber) {
            printf("You guessed too high! Try again.\n");
        } else if (guess < secretNumber) {
            printf("You guessed too low! Try again.\n");

        } else {
            printf("Huzzah! You guessed the secret number %d in %d attempts.\n", guess,  attempts);
            break;
        }
        
        //If the user runs out of attempts, the game ends and the secret number is revealed
        if (attempts >= maxAttempts) {
            printf("Sorry, you've reached the maximum number of attempts. The number was %d.\n", secretNumber);
            break;
        }

        //Tells the user how many attempts they have left
        printf("You have %d attempts left.\n \n", attemptsLeft);

    } while (guess != secretNumber);//loops until the user guesses the correct number or runs out of attempts
}

/**
 * Asks the user if they want to play again
 * 
 * @return true if the user wants to play again, false if they do not
 */
bool playAgain() {
    char playAgain;
    printf("\nWould you like to play The Secret Number game again? \nPlease enter 'y' to play again or 'n' to exit to the game menu: ");
    scanf(" %c", &playAgain); //assign the value of scanning a character from the user input
    playAgain = tolower(playAgain); //converts the input to lowercase incase of valid uppercase input
    while (true)
    {
        if (playAgain == 'y') { //if the user wants to play again 
        return true;
    } 
    else if (playAgain == 'n') //if the user wants to exit to the game menu
    {
        return false;
    }
    else {//if the user input is invalid 
        printf("That is not a valid input. Please choose 'y' to play again or 'n' to return to the menu.\n");
            scanf(" %c", &playAgain);
            playAgain = tolower(playAgain);
    }
    }
}

/**
 * Starts the game by calling getDifficulty to get the difficulty level
 * and calling play to play the game
 */
void secretNumberStart() {
    int secretNumber, guess, attempts = 0, maxAttempts;
    int lowerBound, upperBound;
    char difficulty;

    //Gets the difficulty level from the user input
    printf("Welcome to the Secret Number Game!\n");
    difficulty = getDifficulty();

    //Plays the game
    play(difficulty);

    //Asks the user if they want to play again, loops until they don't
    while (playAgain()) {
        printf("Choose difficulty level (e: easy, m: medium, h: hard): ");
        scanf(" %c", &difficulty);//assign the value of scanning a character from the user input
        difficulty = tolower(difficulty);//converts the input to lowercase incase of valid uppercase input
        play(difficulty);//plays the game with specified difficulty
    }

}