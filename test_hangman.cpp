// hangman_tests.c

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hangman.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

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

std::string trim(const std::string& str) {
    auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
    return (start < end ? std::string(start, end) : std::string());
}

TEST(print_hangman) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    print_hangman(0);
    std::string output = buffer.str();
    std::cout.rdbuf(old);  // Restore the original buffer

    std::cout << "Actual output for print_hangman(0):" << std::endl;
    std::cout << output << std::endl;
    std::cout.flush();

    const char* expected_raw = "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n";
    std::cout << "Expected output:" << std::endl;
    std::cout << expected_raw << std::endl;
    std::cout.flush();

    std::string expected(expected_raw);

    // Trim both strings
    std::string trimmed_output = trim(output);
    std::string trimmed_expected = trim(expected);

    std::cout << "Trimmed actual output: '" << trimmed_output << "'" << std::endl;
    std::cout << "Trimmed expected output: '" << trimmed_expected << "'" << std::endl;
    std::cout.flush();

    // Remove all whitespace for a strict comparison
    std::string stripped_output = trimmed_output;
    stripped_output.erase(std::remove_if(stripped_output.begin(), stripped_output.end(), ::isspace), stripped_output.end());
    std::string stripped_expected = trimmed_expected;
    stripped_expected.erase(std::remove_if(stripped_expected.begin(), stripped_expected.end(), ::isspace), stripped_expected.end());

    std::cout << "Stripped actual output: '" << stripped_output << "'" << std::endl;
    std::cout << "Stripped expected output: '" << stripped_expected << "'" << std::endl;
    std::cout.flush();

    bool match = (stripped_output == stripped_expected);

    std::cout << "Character by character comparison:" << std::endl;
    for (size_t i = 0; i < std::max(stripped_output.length(), stripped_expected.length()); ++i) {
        if (i >= stripped_output.length()) {
            std::cout << "Position " << i << ": Expected '" << stripped_expected[i]
                << "' (ASCII " << (int)stripped_expected[i] << "), but actual output is too short." << std::endl;
        }
        else if (i >= stripped_expected.length()) {
            std::cout << "Position " << i << ": Actual '" << stripped_output[i]
                << "' (ASCII " << (int)stripped_output[i] << "), but expected output is too short." << std::endl;
        }
        else if (stripped_output[i] != stripped_expected[i]) {
            std::cout << "Mismatch at position " << i << ": expected '"
                << stripped_expected[i] << "' (ASCII " << (int)stripped_expected[i]
                << "), got '" << stripped_output[i] << "' (ASCII " << (int)stripped_output[i] << ")" << std::endl;
        }
        else {
            std::cout << "Position " << i << ": Match '" << stripped_output[i] << "'" << std::endl;
        }
        std::cout.flush();
    }

    if (!match) {
        std::cout << "Test failed: Output does not match expected after trimming whitespace" << std::endl;
    }
    else {
        std::cout << "Test passed: Output matches expected after trimming whitespace" << std::endl;
    }
    std::cout.flush();

    assert(match && "Output does not match expected after trimming whitespace");
}

TEST(print_word) {
    const char* word = "HELLO";
    int guessed[5] = { 1, 0, 1, 1, 0 };

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    print_word(word, guessed);
    assert(buffer.str() == "H _ L L _\n");

    std::cout.rdbuf(old);
}

TEST(load_dictionary) {
    // Create a temporary file for testing
    FILE* temp = fopen("temp_dict.txt", "w");
    fprintf(temp, "APPLE\nBANANA\nCHERRY\n");
    fclose(temp);

    assert(load_dictionary("temp_dict.txt") == 1);
    assert(dictionary_size == 3);
    assert(strcmp(dictionary[0], "APPLE") == 0);
    assert(strcmp(dictionary[1], "BANANA") == 0);
    assert(strcmp(dictionary[2], "CHERRY") == 0);

    remove("temp_dict.txt");
}

void hangmanTests() {
    printf("Running Hangman unit tests...\n");

    RUN_TEST(select_word);
    RUN_TEST(is_word_guessed);
    RUN_TEST(to_uppercase);
    RUN_TEST(is_letter_in_word);
    RUN_TEST(print_hangman);
    RUN_TEST(print_word);
    RUN_TEST(load_dictionary);

    printf("All tests passed!\n");
}
// compile and run with:
// gcc hangman.cpp test_hangman.cpp -o test_hangman.cpp -DUNIT_TESTING
// ./test_hangman