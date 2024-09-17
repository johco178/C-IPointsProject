// Wordle test

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "newwordle.h"


// Simple test framework
#define TEST(name) static void test_##name(void)
#define RUN_TEST(name) do { \
    printf("Running %s...\n", #name); \
    test_##name(); \
    printf("%s passed!\n", #name); \
} while (0)

static const char wordle_mock_dictionary[3][MAX_wordle_WORD_LENGTH] = { "apple", "green", "slack" };
static const int wordle_mock_dictionary_size = 3;
extern char test_letters_left_to_guess[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
extern bool test_has_letter_been_guessed[26] = { false };

#define has_letter_been_guessed test_has_letter_been_guessed

// Wordle test

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "newwordle.h"


// Simple test framework
#define TEST(name) static void test_##name(void)
#define RUN_TEST(name) do { \
    printf("Running %s...\n", #name); \
    test_##name(); \
    printf("%s passed!\n", #name); \
} while (0)

static const char wordle_mock_dictionary[3][MAX_wordle_WORD_LENGTH] = { "apple", "green", "slack" };
static const int wordle_mock_dictionary_size = 3;
extern bool test_has_letter_been_guessed[26];


// Function to reset the test arrays
static void resetTestArrays() {
    memset(test_has_letter_been_guessed, 0, sizeof(test_has_letter_been_guessed));

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


TEST(updateLettersGuessed) {
    // Reset the test arrays before each test
    resetTestArrays();

    // Example guess with some letters
    const char* guess = "maple";
    updateLettersGuessed(guess);

    // Expected result: 'm', 'a', 'p', 'l', 'e' should be set to true
    assert(test_has_letter_been_guessed['m' - 'a'] == true);
    assert(test_has_letter_been_guessed['a' - 'a'] == true);
    assert(test_has_letter_been_guessed['p' - 'a'] == true);
    assert(test_has_letter_been_guessed['l' - 'a'] == true);
    assert(test_has_letter_been_guessed['e' - 'a'] == true);

    // Letters not guessed yet (e.g., 'b', 'c', 'd', etc., should be false)
    assert(test_has_letter_been_guessed['b' - 'a'] == false);
    assert(test_has_letter_been_guessed['c' - 'a'] == false);
    assert(test_has_letter_been_guessed['f' - 'a'] == false);
    // Add more assertions as needed
}

// Test for lettersNotGuessed
TEST(lettersNotGuessed) {
    // Reset the test arrays before each test
    resetTestArrays();

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

    printf("All tests passed!\n");
    return 0;
}


