#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_TRIES 6

// Function prototypes
void print_hangman(int tries);
void print_word(const char* word, const int* guessed);
int is_word_guessed(const int* guessed, int length);
void to_uppercase(char* str);

// List of words to guess
const char* word_list[] = {
    "PROGRAMMING", "COMPUTER", "LANGUAGE", "HANGMAN", "SOFTWARE",
    "HARDWARE", "KEYBOARD", "MONITOR", "MOUSE", "PRINTER"
};
const int word_count = sizeof(word_list) / sizeof(word_list[0]);

int main() {
    srand(time(NULL));

    // Select a random word from the list
    const char* word = word_list[rand() % word_count];
    int word_length = strlen(word);

    // Initialize guessed letters array
    int guessed[word_length];
    for (int i = 0; i < word_length; i++) {
        guessed[i] = 0;
    }

    int tries = 0;
    char guess;
    char guessed_letters[26] = { 0 };
    int guessed_count = 0;

    printf("Welcome to Hangman!\n");

    while (tries < MAX_TRIES) {
        printf("\nWord: ");
        print_word(word, guessed);
        printf("\nTries left: %d\n", MAX_TRIES - tries);
        print_hangman(tries);
        printf("\nGuess a letter: ");
        scanf(" %c", &guess);
        guess = toupper(guess);

        if (!isalpha(guess)) {
            printf("Please enter a valid letter.\n");
            continue;
        }

        if (strchr(guessed_letters, guess)) {
            printf("You've already guessed that letter. Try again.\n");
            continue;
        }

        guessed_letters[guessed_count++] = guess;
        int correct_guess = 0;

        for (int i = 0; i < word_length; i++) {
            if (word[i] == guess) {
                guessed[i] = 1;
                correct_guess = 1;
            }
        }

        if (!correct_guess) {
            tries++;
            printf("Wrong guess!\n");
        }

        if (is_word_guessed(guessed, word_length)) {
            printf("\nCongratulations! You've guessed the word: %s\n", word);
            break;
        }
    }

    if (tries == MAX_TRIES) {
        printf("\nYou've been hanged! The word was: %s\n", word);
    }

    print_hangman(tries);
    return 0;
}

void print_hangman(int tries) {
    switch (tries) {
    case 0:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    case 1:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    case 2:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf("  |   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    case 3:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    case 4:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    case 5:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" /    |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    case 6:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" / \\  |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    }
}

void print_word(const char* word, const int* guessed) {
    for (int i = 0; i < strlen(word); i++) {
        if (guessed[i]) {
            printf("%c ", word[i]);
        }
        else {
            printf("_ ");
        }
    }
    printf("\n");
}

int is_word_guessed(const int* guessed, int length) {
    for (int i = 0; i < length; i++) {
        if (!guessed[i]) {
            return 0;
        }
    }
    return 1;
}

void to_uppercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}
