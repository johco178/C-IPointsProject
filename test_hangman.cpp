// hangman_tests.c

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

TEST(is_word_guessed) {
    int guessed1[] = { 1, 1, 1, 1, 1 };
    assert(is_word_guessed(guessed1, 5) == 1);

    int guessed2[] = { 1, 1, 0, 1, 1 };
    assert(is_word_guessed(guessed2, 5) == 0);

    int guessed3[] = { 0, 0, 0, 0, 0 };
    assert(is_word_guessed(guessed3, 5) == 0);
}

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

TEST(is_letter_in_word) {
    assert(is_letter_in_word('A', "APPLE") == true);
    assert(is_letter_in_word('Z', "APPLE") == false);
    assert(is_letter_in_word('E', "HELLO") == true);
    assert(is_letter_in_word('X', "") == false);
}

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

const char* mock_select_word(int desired_length) {
    return "APPLE";
}

TEST(hangman_play) {
    // Redirect cout to our stringstream
    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    // Prepare input
    std::stringstream input;
    input << "5\n" << "A\n" << "P\n" << "L\n" << "E\n" << "2\n";
    std::streambuf* old_cin = std::cin.rdbuf(input.rdbuf());

    // Replace select_word with our mock version
    auto old_select_word = select_word;
    select_word = mock_select_word;

    // Call the function
    hangman_play();

    // Restore cout and cin
    std::cout.rdbuf(old_cout);
    std::cin.rdbuf(old_cin);

    // Restore original select_word
    select_word = old_select_word;

    // Get the output as a string
    std::string output_str = output.str();

    // Perform assertions
    assert(output_str.find("Enter desired word length") != std::string::npos);
    assert(output_str.find("Welcome to Hangman!") != std::string::npos);
    assert(output_str.find("_ _ _ _ _") != std::string::npos);
    assert(output_str.find("A _ _ _ _") != std::string::npos);
    assert(output_str.find("A P P _ _") != std::string::npos);
    assert(output_str.find("A P P L _") != std::string::npos);
    assert(output_str.find("A P P L E") != std::string::npos);
    assert(output_str.find("Congratulations! You've guessed the word: APPLE") != std::string::npos);
    assert(output_str.find("Do you want to play again?") != std::string::npos);
    assert(output_str.find("Thanks for playing Hangman!") != std::string::npos);

    std::cout << "hangman_play test passed!" << std::endl;
}

void hangmanTests() {
    printf("Running Hangman unit tests...\n");

    RUN_TEST(load_dictionary);
    RUN_TEST(select_word);
    RUN_TEST(is_word_guessed);
    RUN_TEST(to_uppercase);
    RUN_TEST(is_letter_in_word);
    RUN_TEST(hangman_play);


    printf("All tests passed!\n");
}
// compile and run with:
// gcc hangman.cpp test_hangman.cpp -o test_hangman.cpp -DUNIT_TESTING
// ./test_hangman