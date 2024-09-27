/*!
    @file test_hangman.cpp
	@brief Hangman Testing
    @author Nick Garner
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hangman.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <functional>
#include <cstdio>

// Simple test framework
#define TEST(name) static void test_##name(void)
#define RUN_TEST(name) do { \
    printf("Running %s...\n", #name); \
    test_##name(); \
    printf("%s passed!\n", #name); \
} while (0)

// Mock dictionary for testing
static const char mock_dictionary[3][MAX_WORD_LENGTH] = { "APPLE", "BANANA", "CHERRY" };
static const int mock_dictionary_size = 3;

/*!
    @brief Test for word selection function
*/
TEST(select_word) {
    set_mock_dictionary(mock_dictionary, mock_dictionary_size);

    char* word = select_word(0);
    assert(word != NULL);
    assert(strcmp(word, "APPLE") == 0 || strcmp(word, "BANANA") == 0 || strcmp(word, "CHERRY") == 0);

    word = select_word(5);
    assert(strcmp(word, "APPLE") == 0);

    word = select_word(6);
    assert(strcmp(word, "BANANA") == 0 || strcmp(word, "CHERRY") == 0);

    word = select_word(10);
    assert(word != NULL);
}

/*!
    @brief Test to check correct guess
*/
TEST(is_word_guessed) {
    int guessed1[] = { 1, 1, 1, 1, 1 };
    assert(is_word_guessed(guessed1, 5) == 1);

    int guessed2[] = { 1, 1, 0, 1, 1 };
    assert(is_word_guessed(guessed2, 5) == 0);

    int guessed3[] = { 0, 0, 0, 0, 0 };
    assert(is_word_guessed(guessed3, 5) == 0);
}

/*!
    @brief Test for convertion to uppercase method
*/
TEST(to_uppercase) {
    char word[] = "Hello, World!";
    to_uppercase(word);
    assert(strcmp(word, "HELLO, WORLD!") == 0);

    char already_upper[] = "UPPERCASE";
    to_uppercase(already_upper);
    assert(strcmp(already_upper, "UPPERCASE") == 0);

    char empty[] = "";
    to_uppercase(empty);
    assert(strcmp(empty, "") == 0);
}

/*!
    @brief Test for letter checking method
*/
TEST(is_letter_in_word) {
    assert(is_letter_in_word('A', "APPLE") == true);
    assert(is_letter_in_word('Z', "APPLE") == false);
    assert(is_letter_in_word('E', "HELLO") == true);
    assert(is_letter_in_word('X', "") == false);
}

/*!
    @brief Test for dictionary loading method
*/
TEST(load_dictionary) {
    const char* temp_filename = "temp_dictionary.txt";
    FILE* temp_file;
    int result;
    char test_dictionary[MAX_DICTIONARY_SIZE][MAX_WORD_LENGTH];

    // Test 1: Loading a non-existent file
    result = load_dictionary("non_existent_file.txt", test_dictionary, MAX_DICTIONARY_SIZE);
    assert(result <= 0);

    // Test 2: Loading a valid file with various word lengths
    temp_file = fopen(temp_filename, "w");
    assert(temp_file != NULL);
    fprintf(temp_file, "apple\nBANANA\nCherry\ndate\nEGGPLANT\n");
    fclose(temp_file);

    result = load_dictionary(temp_filename, test_dictionary, MAX_DICTIONARY_SIZE);
    assert(result == 5);
    assert(strcmp(test_dictionary[0], "APPLE") == 0);
    assert(strcmp(test_dictionary[1], "BANANA") == 0);
    assert(strcmp(test_dictionary[2], "CHERRY") == 0);
    assert(strcmp(test_dictionary[3], "DATE") == 0);
    assert(strcmp(test_dictionary[4], "EGGPLANT") == 0);

    // Test 3: Loading a file with a word at MAX_WORD_LENGTH
    temp_file = fopen(temp_filename, "w");
    assert(temp_file != NULL);
    for (int i = 0; i < MAX_WORD_LENGTH - 1; i++) {
        fprintf(temp_file, "a");
    }
    fprintf(temp_file, "\n");
    fclose(temp_file);

    result = load_dictionary(temp_filename, test_dictionary, MAX_DICTIONARY_SIZE);
    assert(result >= 1);
    assert(strlen(test_dictionary[0]) == MAX_WORD_LENGTH - 1);

    // Test 4: Loading a file with more words than MAX_DICTIONARY_SIZE
    temp_file = fopen(temp_filename, "w");
    assert(temp_file != NULL);
    for (int i = 0; i < MAX_DICTIONARY_SIZE + 10; i++) {
        fprintf(temp_file, "word%d\n", i);
    }
    fclose(temp_file);

    result = load_dictionary(temp_filename, test_dictionary, MAX_DICTIONARY_SIZE);
    assert(result == MAX_DICTIONARY_SIZE);

    // Test 5: Loading an empty file
    temp_file = fopen(temp_filename, "w");
    assert(temp_file != NULL);
    fclose(temp_file);

    result = load_dictionary(temp_filename, test_dictionary, MAX_DICTIONARY_SIZE);
    assert(result == 0);

    // Clean up
    remove(temp_filename);
}

/*!
    @brief Test for main play function
*/
void test_hangman_play() {
    // Mock dictionary
    const char mock_dict[][MAX_WORD_LENGTH] = {
        "APPLE",
        "BANANA",
        "CHERRY",
        "ORANGE"
    };
    int mock_dict_size = sizeof(mock_dict) / sizeof(mock_dict[0]);

    // Set the mock dictionary
    set_mock_dictionary(mock_dict, mock_dict_size);

    // Redirect stdin and stdout to test input and output
    FILE* stdin_backup = stdin;
    FILE* stdout_backup = stdout;
    FILE* temp_input = fopen("temp_input.txt", "w");
    FILE* temp_output = fopen("temp_output.txt", "w");
    *stdin = *temp_input;
    *stdout = *temp_output;

    // Test case 1: Play the game and guess the word correctly
    fprintf(temp_input, "5\n");  // Enter desired word length
    fprintf(temp_input, "A\n");  // Guess 'A'
    fprintf(temp_input, "P\n");  // Guess 'P'
    fprintf(temp_input, "L\n");  // Guess 'L'
    fprintf(temp_input, "E\n");  // Guess 'E'
    fprintf(temp_input, "Y\n");  // Guess 'Y'
    fprintf(temp_input, "2\n");  // Choose to play again

    hangman_play();

    // Verify the output
    rewind(temp_output);
    char output[100];
    fgets(output, sizeof(output), temp_output);
    assert(strcmp(output, "Welcome to Hangman!\n\nWord: _ _ _ _ _ \nTries left: 7\n  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n\nGuess a letter: \n") == 0);

    // Test case 2: Play the game and fail to guess the word within the maximum tries
    fprintf(temp_input, "6\n");  // Enter desired word length
    fprintf(temp_input, "A\n");  // Guess 'A'
    fprintf(temp_input, "B\n");  // Guess 'B'
    fprintf(temp_input, "C\n");  // Guess 'C'
    fprintf(temp_input, "D\n");  // Guess 'D'
    fprintf(temp_input, "F\n");  // Guess 'F'
    fprintf(temp_input, "G\n");  // Guess 'G'
    fprintf(temp_input, "2\n");  // Choose to play again

    hangman_play();

    // Verify the output
    rewind(temp_output);
    fgets(output, sizeof(output), temp_output);
    assert(strcmp(output, "Welcome to Hangman!\n\nWord: _ _ _ _ _ _ \nTries left: 7\n  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n\nGuess a letter: \n") == 0);

    // Clean up
    fclose(temp_input);
    fclose(temp_output);
    remove("temp_input.txt");
    remove("temp_output.txt");
    *stdin = *stdin_backup;
    *stdout = *stdout_backup;
}

void hangmanTests() {
    printf("Running Hangman unit tests...\n");

    RUN_TEST(load_dictionary);
    RUN_TEST(select_word);
    RUN_TEST(is_word_guessed);
    RUN_TEST(to_uppercase);
    RUN_TEST(is_letter_in_word);
    //RUN_TEST(hangman_play);


    printf("All tests passed!\n");
}
// compile and run with:
// gcc hangman.cpp test_hangman.cpp -o test_hangman.cpp -DUNIT_TESTING
// ./test_hangman