// hangman.c
/*!
    @file hangman.cpp
	@brief Hangman game implementation
    @author Nick Garner
*/

#include "hangman.h"

// Global variables
#ifdef UNIT_TESTING
char dictionary[MAX_DICTIONARY_SIZE][MAX_WORD_LENGTH];
int dictionary_size = 0;
#else
static char dictionary[MAX_DICTIONARY_SIZE][MAX_WORD_LENGTH];
static int dictionary_size = 0;
#endif

// Remove static keyword for functions to be tested
#ifdef UNIT_TESTING
#define STATIC
#else
#define STATIC static
#endif

/*!
    @brief checks if letter is in word
    @param letter The letter to check
    @param word The word to check
    @return true if the letter is in the word, false otherwise
*/
bool isLetterInWord(char letter, const char* word) {
    while (*word) {
        if (*word == letter) {
            return true;
        }
        word++;
    }
    return false;
}

/*!
    @brief Selects a word from the dictionary based on the desired length
	@param desired_length The desired length of the word
	@return A pointer to the selected word
*/
STATIC char* selectWord(int desired_length) {
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

/*!
    @brief Prints the hangman based on the number of tries
	@param tries The number of tries
*/
void printHangman(int tries) {
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

/*!
    @brief Prints the word with guessed letters
	@param word The word to print
	@param guessed An array of guessed letters

*/
STATIC void printWord(const char* word, const int* guessed) {
    for (int i = 0; word[i]; i++) {
        printf("%c ", guessed[i] ? word[i] : '_');
    }
    printf("\n");
}

/*!
    @brief Checks if a word has been guessed
	@param guessed An array of integers representing the guessed letters
	@param length The length of the word
	@return 1 if the word has been guessed, 0 otherwise
*/
STATIC int isWordGuessed(const int* guessed, int length) {
    for (int i = 0; i < length; i++) {
        if (!guessed[i]) return 0;
    }
    return 1;
}

/*!
    @brief Converts a string to uppercase
	@param str The string to convert to uppercase
*/
STATIC void toUppercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

/*!
    @brief Loads the dictionary from a file
    @param filename The name of the file to load
    @return 1 if the dictionary was loaded successfully, 0 otherwise
*/
STATIC int loadDictionary(const char* filename, char dictionary[][MAX_WORD_LENGTH], int max_size) {
    FILE* file = fopen(filename, "r");
    if (!file) return -1;  // Return -1 on file open error

    int words_loaded = 0;
    while (words_loaded < max_size &&
        fgets(dictionary[words_loaded], MAX_WORD_LENGTH, file)) {
        dictionary[words_loaded][strcspn(dictionary[words_loaded], "\n")] = 0;
        to_uppercase(dictionary[words_loaded]);
        words_loaded++;
    }
    fclose(file);
    return words_loaded;
}

/*!
	@brief Initializes the hangman game

*/
void hangmanInitialize(void) {
    srand((unsigned int)time(NULL));
    dictionary_size = load_dictionary("../dictionary.txt", dictionary, MAX_DICTIONARY_SIZE);
    if (dictionary_size <= 0) {
        fprintf(stderr, "Failed to load dictionary. Hangman game may not function properly.\n");
    }
}

/*!
    @brief Plays the hangman game
*/

STATIC void hangmanPlay(void) {
    int play_again = 1;

    do {
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
        char wrong_guesses[MAX_TRIES] = { 0 };
        int wrong_count = 0;

        printf("Welcome to Hangman!\n");

        while (tries < MAX_TRIES) {
            printf("\nWord: ");
            print_word(word, guessed);
            printf("Tries left: %d\n", MAX_TRIES - tries);
            print_hangman(tries);

            if (wrong_count > 0) {
                printf("Wrong guesses: ");
                for (int i = 0; i < wrong_count; i++) {
                    printf("%c ", wrong_guesses[i]);
                }
                printf("\n");
            }

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
                wrong_guesses[wrong_count++] = guess;
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

        // Prompt for playing again
        int choice;
        do {
            printf("\nDo you want to play again?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            printf("Enter your choice (1 or 2): ");
            
            if (scanf("%d", &choice) != 1) {
				while (getchar() != '\n'){}
                printf("Invalid choice. Please enter 1 or 2.\n");
                choice = 0;
			} else if (choice != 1 && choice != 2) {
                printf("Invalid choice. Please enter 1 or 2.\n");
            }
        } while (choice != 1 && choice != 2);

        play_again = (choice == 1);

        } while (play_again);

    printf("Thanks for playing Hangman!\n");
    }

// Expose these functions for unit testing
#ifdef UNIT_TESTING
void set_mock_dictionary(const char mock_dict[][MAX_WORD_LENGTH], int size) {
    for (int i = 0; i < size && i < MAX_DICTIONARY_SIZE; i++) {
        strcpy(dictionary[i], mock_dict[i]);
    }
    dictionary_size = size;
}
#endif