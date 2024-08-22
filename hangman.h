// hangman.h

#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 100
#define MAX_TRIES 6
#define MAX_DICTIONARY_SIZE 10000

// Function to initialize the hangman game
void hangman_initialize(void);

// Function to play a single game of hangman
void hangman_play(void);

// Function to check if a letter is in a word
bool is_letter_in_word(char letter, const char* word);

#ifdef UNIT_TESTING
// Expose these functions for unit testing
char* select_word(int desired_length);
int is_word_guessed(const int* guessed, int length);
void to_uppercase(char* str);
void set_mock_dictionary(const char mock_dict[][MAX_WORD_LENGTH], int size);
#endif

#endif // HANGMAN_H