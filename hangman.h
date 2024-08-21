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

// Function to initialize the hangman game
void hangman_initialize(void);

// Function to play a single game of hangman
void hangman_play(void);

#endif // HANGMAN_H