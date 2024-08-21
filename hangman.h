// hangman.h

#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_TRIES 6
#define MAX_DICTIONARY_SIZE 10000

// Function to initialize the game (load dictionary, set up random seed)
void initialize_game(void);

// Function to play a single game of hangman
void play_hangman(void);

// Function to select a word from the dictionary
// If desired_length is 0, it selects a random word
// Otherwise, it tries to select a word of the specified length
char* select_word(int desired_length);

// Function to print the hangman ASCII art
void print_hangman(int tries);

// Function to print the current state of the word (guessed letters and blanks)
void print_word(const char* word, const int* guessed);

// Function to check if the entire word has been guessed
int is_word_guessed(const int* guessed, int length);

// Function to convert a string to uppercase
void to_uppercase(char* str);

// Function to load words from a dictionary file
int load_dictionary(const char* filename);

#endif // HANGMAN_H