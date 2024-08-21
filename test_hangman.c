// gcc -DUNIT_TESTING hangman.c hangman_tests.c -o hangman_tests
// . / hangman_tests

// hangman_tests.c

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hangman.h"

// Since some functions are static in hangman.c, we'll need to declare them here for testing
// Note: In a real-world scenario, you might want to consider making these functions non-static
// or use more advanced techniques to test static functions
static char* select_word(int desired_length);
static int is_word_guessed(const int* guessed, int length);
static void to_uppercase(char* str);

// Test framework
#define TEST(name) void test_##name(void)
#define RUN_TEST(name) printf("Running %s...\n", #name); test_##name(); printf("%s passed!\n", #name)

// Mock dictionary for testing
static char mock_dictionary[3][MAX_WORD_LENGTH] = { "APPLE", "BANANA", "CHERRY" };
static int mock_dictionary_size = 3;

// Tests
TEST(select_word) {
    // Mock the dictionary
    memcpy(dictionary, mock_dictionary, sizeof(mock_dictionary));
    dictionary_size = mock_dictionary_size;

    // Test random word selection
    char* word = select_word(0);
    assert(word != NULL);
    assert(strcmp(word, "APPLE") == 0 || strcmp(word, "BANANA") == 0 || strcmp(word, "CHERRY") == 0);

    // Test specific length selection
    word = select_word(5);
    assert(strcmp(word, "APPLE") == 0);

    word = select_word(6);
    assert(strcmp(word, "BANANA") == 0 || strcmp(word, "CHERRY") == 0);

    // Test invalid length
    word = select_word(10);
    assert(word != NULL); // Should return a random word
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

int main() {
    printf("Running Hangman unit tests...\n");

    RUN_TEST(select_word);
    RUN_TEST(is_word_guessed);
    RUN_TEST(to_uppercase);

    printf("All tests passed!\n");
    return 0;
}