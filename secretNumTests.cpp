#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "secretNumber.h" // Include the header file

// Function to run all tests
void runTests();

// Test functions
void test_getSecretNumber();
void test_validDifficulty();
void test_getDifficulty();
void test_validGuess();
void test_validPlayAgain();
void test_playAgain();
void test_playAgain_withMockInput();
void test_play_withMockInput();
void test_getGuess_withMockInput();

// Function to Print test results
void printTestResult(const char* testName, bool result);

int secNumTests() {
    runTests();
    return 0;
}

int main() {
    secNumTests();
    return 0;
}

void runTests() {
    test_getSecretNumber();
    test_validDifficulty();
    test_getDifficulty();
    test_validGuess();
    test_validPlayAgain();
    test_playAgain();
    test_getGuess_withMockInput();
}

void test_getSecretNumber() {
    int lowerBound = 1;
    int upperBound = 10;
    int secretNumber = getSecretNumber(lowerBound, upperBound);
    bool result = (secretNumber >= lowerBound && secretNumber <= upperBound);
    printTestResult("test_getSecretNumber", result);
}

void test_validDifficulty() {
    bool result = validDifficulty('e') && validDifficulty('m') && validDifficulty('h') && !validDifficulty('x');
    printTestResult("test_validDifficulty", result);
}

void test_getDifficulty(){
    bool result = getDifficulty('E') == 'e' && getDifficulty('m') == 'm';
    printTestResult("test_getDifficulty", result);
}

void test_validGuess() {
    bool result = validGuess(5, 1, 10, 1) && !validGuess(15, 1, 10, 1);
    printTestResult("test_validGuess", result);
}

void test_validPlayAgain() {
    bool result = validPlayAgain('y') && validPlayAgain('n') && !validPlayAgain('x') && validPlayAgain('Y') && validPlayAgain('N');
    printTestResult("test_validPlayAgain", result);
}

void test_playAgain(){
    bool result = playAgain('y') == true && playAgain('n') == false;
    printTestResult("test_playAgain", result);
}

void test_getGuess_withMockInput() {
    const int mockGuesses[] = {5, 7}; 
    int mockGuessCount = sizeof(mockGuesses) / sizeof(mockGuesses[0]);

    int guess = getGuess(1, 10, mockGuesses, mockGuessCount);

    bool result = (guess == 5);
    printTestResult("test_getGuess_withMockInput", result);
}

void printTestResult(const char* testName, bool result) {
    if (result) {
        printf("%s: PASSED\n", testName);
    } else {
        printf("%s: FAILED\n", testName);
    }
}