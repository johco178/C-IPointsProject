// test_hangman.c
#include <assert.h>
#include "hangman.h"

void test_is_word_guessed() {
    int guessed1[] = { 1, 1, 1, 1 };
    assert(is_word_guessed(guessed1, 4) == 1);

    int guessed2[] = { 1, 1, 0, 1 };
    assert(is_word_guessed(guessed2, 4) == 0);
}

void test_to_uppercase() {
    char word[] = "Hello";
    to_uppercase(word);
    assert(strcmp(word, "HELLO") == 0);
}

int main() {
    test_is_word_guessed();
    test_to_uppercase();
    printf("All tests passed!\n");
    return 0;
}

// test with:
// gcc test_hangman.c hangman.c -o test_hangman
// . / test_hangman