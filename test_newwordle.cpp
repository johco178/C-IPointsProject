// Wordle test

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "newwordle.h"


// Wordle test


// Simple test framework
#define TEST(name) static void test_##name(void)
#define RUN_TEST(name) do { \
    printf("Running %s...\n", #name); \
    test_##name(); \
    printf("%s passed!\n", #name); \
} while (0)

static const char wordle_mock_dictionary[3][MAX_wordle_WORD_LENGTH] = { "apple", "green", "slack" };
static const int wordle_mock_dictionary_size = 3;
extern bool has_letter_been_guessed[26];
extern char guessone[6];
extern char guesstwo[6];
extern char guessthree[6];
extern char guessfour[6];
extern char guessfive[6];
extern char guesssix[6];
extern char clueone[6];
extern char cluetwo[6];
extern char cluethree[6];
extern char cluefour[6];
extern char cluefive[6];
extern char cluesix[6];

void setup() {
    // Reset global variables
    memset(has_letter_been_guessed, 0, sizeof(has_letter_been_guessed)); // Set to false

    // Initialize guess arrays
    for (int i = 0; i < 6; i++) {
        guessone[i] = '_';    // Initialize to '_'
        guesstwo[i] = '_';
        guessthree[i] = '_';
        guessfour[i] = '_';
        guessfive[i] = '_';
        guesssix[i] = '_';

        clueone[i] = '_';     // Initialize clue arrays
        cluetwo[i] = '_';
        cluethree[i] = '_';
        cluefour[i] = '_';
        cluefive[i] = '_';
        cluesix[i] = '_';
    }
}



TEST(globalVariablesInitialization) {
    setup();
    assert(wordle_mock_dictionary_size == 3);


    for (int i = 0; i < 26; i++) {
        assert(has_letter_been_guessed[i] == false);
    }
    for (int i = 0; i < 6; i++) {
        assert(guessone[i] == '_');
        assert(guesstwo[i] == '_');
        assert(guessthree[i] == '_');
        assert(guessfour[i] == '_');
        assert(guessfive[i] == '_');
        assert(guesssix[i] == '_');
        assert(clueone[i] == '_');
        assert(cluetwo[i] == '_');
        assert(cluethree[i] == '_');
        assert(cluefour[i] == '_');
        assert(cluefive[i] == '_');
        assert(cluesix[i] == '_');
    }
}

// Test for updating global variables after a guess
TEST(globalVariablesAfterGuess) {
    memset(has_letter_been_guessed, 0, sizeof(has_letter_been_guessed));
    memset(guessone, 0, sizeof(guessone));
    memset(guesstwo, 0, sizeof(guesstwo));

    const char* guess = "apple";
    updateLettersGuessed(guess);
    updateclue(1, processGuess("apple", guess), guess);

    // Check if the guesses have been updated
    assert(strcmp(guessone, "apple") == 0);
    assert(strcmp(clueone, "GGGGG") == 0);  // Assuming "apple" is the correct answer

    // Check letter states after the guess
    assert(has_letter_been_guessed['a' - 'a'] == true);
    assert(has_letter_been_guessed['p' - 'a'] == true);
    assert(has_letter_been_guessed['l' - 'a'] == true);
    assert(has_letter_been_guessed['e' - 'a'] == true);
    assert(has_letter_been_guessed['b' - 'a'] == false);
}


TEST(conatainsonlychar) {

    assert(conatainsonlychar("al-ha") == false);
    assert(conatainsonlychar("alpha") == true);

}
TEST(toLowerCase) {

    const char* guess = "HELLO";
    char* lower = toLowerCase(guess);
    assert(strcmp(lower, "hello") == 0);

    const char* alreadylower = "hello";
    char* newlower = toLowerCase(alreadylower);
    assert(strcmp(newlower, "hello") == 0);
}
TEST(processGuess) {
    const char* answer = "apple";
    const char* guess = "anvil";
    assert(strcmp(processGuess(answer, guess), "G___Y") == 0);

    const char* sec_guess = "piper";
    assert(strcmp(processGuess(answer, sec_guess), "Y_GY_") == 0);

    const char* third_guess = "apple";
    assert(strcmp(processGuess(answer, third_guess), "GGGGG") == 0);
}

TEST(correctlength) {
    assert(correctlength("hello") == true);
    assert(correctlength("hell") == false);
    assert(correctlength("helloo") == false);

    

}
TEST(validWord) {
    set_wordle_mock_dictionary(wordle_mock_dictionary, wordle_mock_dictionary_size);
    assert(validWord("aaple") == false);
    assert(validWord("apple") == true);



}

TEST(get_word) {
    set_wordle_mock_dictionary(wordle_mock_dictionary, wordle_mock_dictionary_size);
    assert(strcmp(get_word(0), "apple") == 0);
    assert(strcmp(get_word(4), "green") == 0);
    assert(strcmp(get_word(2), "slack") == 0);

}
// Test for updateLettersGuessed
TEST(updateLettersGuessed) {
    // Reset the has_letter_been_guessed array before each test
    memset(has_letter_been_guessed, 0, sizeof(has_letter_been_guessed));

    // Example guess with some letters
    const char* guess = "maple";
    updateLettersGuessed(guess);


    assert(has_letter_been_guessed['m' - 'a'] == true);
    assert(has_letter_been_guessed['a' - 'a'] == true);
    assert(has_letter_been_guessed['p' - 'a'] == true);
    assert(has_letter_been_guessed['l' - 'a'] == true);
    assert(has_letter_been_guessed['e' - 'a'] == true);


    assert(has_letter_been_guessed['b' - 'a'] == false);
    assert(has_letter_been_guessed['c' - 'a'] == false);
    assert(has_letter_been_guessed['f' - 'a'] == false);

}




// Test for lettersNotGuessed
TEST(lettersNotGuessed) {

    memset(has_letter_been_guessed, 0, sizeof(has_letter_been_guessed));

   
    

    // Example guess with some letters
    const char* guess = "maple";
    updateLettersGuessed(guess);

    // Get the letters not guessed
    char* notGuessed = lettersNotGuessed();

    // Expected result after guessing "maple": 'b', 'c', 'd', 'f', ..., 'z' should be present
    assert(strchr(notGuessed, 'b') != NULL);
    assert(strchr(notGuessed, 'c') != NULL);
    assert(strchr(notGuessed, 'd') != NULL);
    assert(strchr(notGuessed, 'f') != NULL);
    // Check specific letters that were guessed
    assert(strchr(notGuessed, 'm') == NULL);
    assert(strchr(notGuessed, 'a') == NULL);
    assert(strchr(notGuessed, 'p') == NULL);
    assert(strchr(notGuessed, 'l') == NULL);
    assert(strchr(notGuessed, 'e') == NULL);

    free(notGuessed); // Free memory allocated by lettersNotGuessed
}

TEST(updateclue) {
    memset(clueone, 0, sizeof(clueone));
    memset(guessone, 0, sizeof(guessone));
    memset(cluetwo, 0, sizeof(cluetwo));
    memset(guesstwo, 0, sizeof(guesstwo));
    memset(cluethree, 0, sizeof(cluethree));
    memset(guessthree, 0, sizeof(guessthree));
    memset(cluefour, 0, sizeof(cluefour));
    memset(guessfour, 0, sizeof(guessfour));

    memset(cluefive, 0, sizeof(cluefive));
    memset(guessfive, 0, sizeof(guessfive));
    memset(cluesix, 0, sizeof(cluesix));
    memset(guesssix, 0, sizeof(guesssix));


    int turn = 1;
    const char* answer = "grave";
    const char* guess = "maple";
    char* clue = processGuess(answer, guess);


    updateclue(turn, clue, guess);
    assert(strcmp(clueone, "_Y__G") == 0);
    assert(strcmp(guessone, "maple") == 0);

    turn = 2;
    guess = "stale";
    clue = processGuess(answer, guess);

    updateclue(turn, clue, guess);
    assert(strcmp(clueone, "_Y__G") == 0);
    assert(strcmp(guessone, "maple") == 0);
    assert(strcmp(cluetwo, "__G_G") == 0);
    assert(strcmp(guesstwo, "stale") == 0);

    turn = 3;
    guess = "crane";
    clue = processGuess(answer, guess);

    updateclue(turn, clue, guess);
    assert(strcmp(clueone, "_Y__G") == 0);
    assert(strcmp(guessone, "maple") == 0);
    assert(strcmp(cluetwo, "__G_G") == 0);
    assert(strcmp(guesstwo, "stale") == 0);
    assert(strcmp(cluethree, "_GG_G") == 0);
    assert(strcmp(guessthree, "crane") == 0);


    turn = 4;
    guess = "nudge";
    clue = processGuess(answer, guess);
    updateclue(turn, clue, guess);



    assert(strcmp(clueone, "_Y__G") == 0);
    assert(strcmp(guessone, "maple") == 0);
    assert(strcmp(cluetwo, "__G_G") == 0);
    assert(strcmp(guesstwo, "stale") == 0);
    assert(strcmp(cluethree, "_GG_G") == 0);
    assert(strcmp(guessthree, "crane") == 0);
    assert(strcmp(cluefour, "___YG") == 0);
    assert(strcmp(guessfour, "nudge") == 0);
    
    turn = 5;
    guess = "brave";
    clue = processGuess(answer, guess);
    updateclue(turn, clue, guess);
    assert(strcmp(clueone, "_Y__G") == 0);
    assert(strcmp(guessone, "maple") == 0);
    assert(strcmp(cluetwo, "__G_G") == 0);
    assert(strcmp(guesstwo, "stale") == 0);
    assert(strcmp(cluethree, "_GG_G") == 0);
    assert(strcmp(guessthree, "crane") == 0);
    assert(strcmp(cluefour, "___YG") == 0);
    assert(strcmp(guessfour, "nudge") == 0);
    assert(strcmp(cluefive, "_GGGG") == 0);
    assert(strcmp(guessfive, "brave") == 0);

    turn = 6;
    guess = "grave";
    clue = processGuess(answer, guess);
    updateclue(turn, clue, guess);
    assert(strcmp(clueone, "_Y__G") == 0);
    assert(strcmp(guessone, "maple") == 0);
    assert(strcmp(cluetwo, "__G_G") == 0);
    assert(strcmp(guesstwo, "stale") == 0);
    assert(strcmp(cluethree, "_GG_G") == 0);
    assert(strcmp(guessthree, "crane") == 0);
    assert(strcmp(cluefour, "___YG") == 0);
    assert(strcmp(guessfour, "nudge") == 0);
    assert(strcmp(cluefive, "_GGGG") == 0);
    assert(strcmp(guessfive, "brave") == 0);
    assert(strcmp(cluesix, "GGGGG") == 0);
    assert(strcmp(guesssix, "grave") == 0);





}

int runwordletests() {
    printf("Running Wordle unit tests...\n");

    RUN_TEST(conatainsonlychar);
    RUN_TEST(toLowerCase);
    RUN_TEST(processGuess);
    RUN_TEST(correctlength);
    RUN_TEST(validWord);
    RUN_TEST(get_word);
    RUN_TEST(updateLettersGuessed);
    RUN_TEST(lettersNotGuessed);
    RUN_TEST(updateclue);

    RUN_TEST(globalVariablesInitialization);
    RUN_TEST(globalVariablesAfterGuess);



    printf("All tests passed!\n");
    return 0;
}


