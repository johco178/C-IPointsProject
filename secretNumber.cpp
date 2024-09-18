#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>


/*!
    @brief Generates a random secret number between the lower and upper bounds
    @param lowerBound The lower bound of the range for the secret number
    @param upperBound The upper bound of the range for the secret number
    @return The randomly generated secret number
*/
int getSecretNumber(int lowerBound, int upperBound) {
    srand(time(0)); // Seed the random number generator
    return rand() % (upperBound - lowerBound + 1) + lowerBound;// returns a random number between the lower and upper bounds
}

/*!
    @brief Checks if the input for the difficulty level is valid
    @param difficulty The difficulty level taken from the input as a char
    @return true if the input is valid, false if it is not
*/
bool validDifficulty(char difficulty) {
    bool isValid = false;
    if (difficulty == 'e' || difficulty == 'm' || difficulty == 'h')
    {
        isValid = true;
    }
    
    return isValid;//returns the difficulty level
}

/*!
    @brief Gets the difficulty level from the user input
    @return The difficulty level chosen by the user as a char
*/
char getDifficulty(char difficulty) {
    bool valid;
    if(difficulty != ' '){
        printf("Choose difficulty level (e: easy, m: medium, h: hard): ");
        scanf(" %c", &difficulty); //assign the value of scanning a character from the user input
    }
    difficulty = tolower(difficulty);//converts the input to lowercase incase of valid uppercase input
    valid = validDifficulty(difficulty);
    while (!valid)//checks if the input is valid
    {
       printf("That is not a valid input. Please choose 'e' for easy, 'm' for medium, or 'h' for hard.\n");
       scanf(" %c", &difficulty);
       difficulty = tolower(difficulty);
       valid = validDifficulty(difficulty);
    }

    return difficulty;//returns the difficulty level
}

/*!
    @brief Checks if the input for a guess is valid
    @param guess The guess as an integer
    @param lowerBound The lower bound of the range for the secret number
    @param upperBound The upper bound of the range for the secret number
    @param check The number of scanf to determine if it is a number or not
    @return true if the input is valid, false if it is not
*/
bool validGuess(int guess, int lowerBound, int upperBound, int check) {
    bool isValid = true;
    if (check == 0 || guess < lowerBound || guess > upperBound)//checks if it is a num and within the bounds
    {
        isValid = false;
    }
    return isValid;
}


/*!
    @brief Gets the guess from input and checks if it is valid
    @param lowerBound The lower bound of the range for the secret number
    @param upperBound The upper bound of the range for the secret number
    @return The guess as an integer
*/
int getGuess(int lowerBound, int upperBound) {
    int guess, check;
    bool isValid;
    printf("Enter a guess between %d and %d : ", lowerBound, upperBound);
    check = scanf("%d", &guess); //assign the value of scanning a number from the user input
    isValid = validGuess(guess, lowerBound, upperBound, check);

    while (!isValid)
    {
        while (getchar() != '\n'){} 
        printf("That is not a valid input.\nPlease enter a number between %d and %d:\n", lowerBound, upperBound);
        check = scanf("%d", &guess);
        isValid = validGuess(guess, lowerBound, upperBound, check);
    }
    
    return guess;//returns the guess if it is valid
}


/*!
    @brief Plays the game
    @param difficulty The difficulty level taken from input as a char
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

/*!
    @brief Checks if the input for play again is valid
    @param playAgain The input for play again as a char
    @return true if the input is valid, false if it is not
*/
bool validPlayAgain(char playAgain) {
    bool isValid = false;
    if (playAgain == 'y' || playAgain == 'n')
    {
        isValid = true;
    }
    return isValid;
}

/*!
    @brief Asks the user if they want to play again
    @return true if the user wants to play again, false if they do not
*/
bool playAgain() {
    char playAgain;
    bool isValid;
    printf("\nWould you like to play The Secret Number game again? \nPlease enter 'y' to play again or 'n' to exit to the game menu: ");
    scanf(" %c", &playAgain); //assign the value of scanning a character from the user input
    playAgain = tolower(playAgain); //converts the input to lowercase incase of valid uppercase input
    isValid = validPlayAgain(playAgain);//checks if the input is valid

    while (!isValid)
    {
        printf("That is not a valid input. Please choose 'y' to play again or 'n' to return to the menu.\n");
        scanf(" %c", &playAgain);
        playAgain = tolower(playAgain);
        isValid = validPlayAgain(playAgain);
    }

    if (playAgain == 'y') { //if the user wants to play again 
        return true;
    } 
    else //if the user wants to exit to the game menu
    {
        return false;
    }
}


/*!
    @brief Starts the game
*/
void secretNumberStart() {
//int main() {
    
    int secretNumber, guess, attempts = 0, maxAttempts;
    int lowerBound, upperBound;
    char difficulty;

    //Gets the difficulty level from the user input
    printf("Welcome to the Secret Number Game!\n");
    difficulty = getDifficulty(' ');

    //Plays the game
    play(difficulty);

    //Asks the user if they want to play again, loops until they don't
    while (playAgain()) {
        printf("Choose difficulty level (e: easy, m: medium, h: hard): ");
        scanf(" %c", &difficulty);//assign the value of scanning a character from the user input
        difficulty = tolower(difficulty);//converts the input to lowercase incase of valid uppercase input
        play(difficulty);//plays the game with specified difficulty
    }
    //return 0;
}