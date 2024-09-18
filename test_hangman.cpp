// hangman_tests.c

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hangman.h"

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

TEST(print_hangman) {
    // Redirect stdout to a string stream for testing
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    print_hangman(0);
    assert(buffer.str().find("  +---+") != std::string::npos);

    buffer.str("");
    print_hangman(6);
    assert(buffer.str().find(" /|\\") != std::string::npos);

    // Restore stdout
    std::cout.rdbuf(old);
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