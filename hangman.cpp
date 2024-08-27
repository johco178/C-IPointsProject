// hangman.c

#include "hangman.h"

// Global variables
static char dictionary[MAX_DICTIONARY_SIZE][MAX_WORD_LENGTH];
static int dictionary_size = 0;

// Remove static keyword for functions we want to test
#ifdef UNIT_TESTING
#define STATIC
#else
#define STATIC static
#endif

bool is_letter_in_word(char letter, const char* word) {
    while (*word) {
        if (*word == letter) {
            return true;
        }
        word++;
    }
    return false;
}

STATIC char* select_word(int desired_length) {
    if (desired_length < 0) {
        printf("Invalid length. Selecting a random word.\n");
        return dictionary[rand() % dictionary_size];
    }

    if (desired_length == 0) {
        return dictionary[rand() % dictionary_size];
    }

    int suitable_words[MAX_DICTIONARY_SIZE];
    int suitable_count = 0;

    for (int i = 0; i < dictionary_size; i++) {
        size_t word_length = strlen(dictionary[i]);
        if (word_length == (size_t)desired_length) {
            suitable_words[suitable_count++] = i;
        }
    }

    if (suitable_count == 0) {
        printf("No words found with length %d. Selecting a random word.\n", desired_length);
        return dictionary[rand() % dictionary_size];
    }

    return dictionary[suitable_words[rand() % suitable_count]];
}

STATIC void print_hangman(int tries) {
    const char* hangman_states[] = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
    };

    printf("%s\n", hangman_states[tries]);
}

STATIC void print_word(const char* word, const int* guessed) {
    for (int i = 0; word[i]; i++) {
        printf("%c ", guessed[i] ? word[i] : '_');
    }
    printf("\n");
}

STATIC int is_word_guessed(const int* guessed, int length) {
    for (int i = 0; i < length; i++) {
        if (!guessed[i]) return 0;
    }
    return 1;
}

STATIC void to_uppercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

STATIC int load_dictionary(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return 0;

    while (fgets(dictionary[dictionary_size], MAX_WORD_LENGTH, file)) {
        dictionary[dictionary_size][strcspn(dictionary[dictionary_size], "\n")] = 0;
        to_uppercase(dictionary[dictionary_size]);
        if (++dictionary_size >= MAX_DICTIONARY_SIZE) break;
    }

    fclose(file);
    return 1;
}

void hangman_initialize(void) {
    srand((unsigned int)time(NULL));
    if (!load_dictionary("dictionary.txt")) {
        fprintf(stderr, "Failed to load dictionary. Hangman game may not function properly.\n");
    }
}

void hangman_play(void) {
    int desired_length;
    printf("Enter desired word length (0 for random): ");
    scanf("%d", &desired_length);

    const char* word = select_word(desired_length);
    int word_length = strlen(word);

    int guessed[MAX_WORD_LENGTH] = { 0 };
    int tries = 0;
    char guess;
    char guessed_letters[26] = { 0 };
    int guessed_count = 0;

    printf("Welcome to Hangman!\n");

    while (tries < MAX_TRIES) {
        printf("\nWord: ");
        print_word(word, guessed);
        printf("Tries left: %d\n", MAX_TRIES - tries);
        print_hangman(tries);
        printf("Guess a letter: ");
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
        printf("\nGame over! The word was: %s\n", word);
    }

    print_hangman(tries);
}

#ifdef UNIT_TESTING
void set_mock_dictionary(const char mock_dict[][MAX_WORD_LENGTH], int size) {
    for (int i = 0; i < size && i < MAX_DICTIONARY_SIZE; i++) {
        strcpy(dictionary[i], mock_dict[i]);
    }
    dictionary_size = size;
}
#endif