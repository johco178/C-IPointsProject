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


TEST(conatainsonlychar) {

    assert(conatainsonlychar("al-ha") == false);
    assert(conatainsonlychar("alpha") == true);

}
TEST(toLowerCase) {

    const char* guess = "HELLO";
    char* lower = toLowerCase(guess);
    assert(strcmp(lower, "hello") == 0);

    const char* alreadylower = "hello";
    char* lower = toLowerCase(alreadylower);
    assert(strcmp(lower, "hello") == 0);
}
TEST(processGuess) {
    const char* answer = "apple";
    const char* guess = "anvil";
    assert(strcmp(processGuess(answer, guess), "G___Y") == 0);

    const char* guess = "piper";
    assert(strcmp(processGuess(answer, guess), "Y_GY_") == 0);

    const char* guess = "apple";
    assert(strcmp(processGuess(answer, guess), "GGGGG") == 0);
}






int main() {
    printf("Running Hangman unit tests...\n");

    RUN_TEST(conatainsonlychar);
    RUN_TEST(toLowerCase);
    RUN_TEST(processGuess);

    printf("All tests passed!\n");
    return 0;
}

