#ifndef wordle_H
#define wordle_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <cstdlib> 
#include <ctime> 

#define MAX_wordle_WORD_LENGTH 100

#define MAX_wordle_DICTIONARY_SIZE 4695

extern bool* test_has_letter_been_guessed;



void wordle_initialize(void);

char* get_word(int desiredength);

int load_all_5letter_words(const char* filename);




/*!
	@file
	@brief documentation
*/


/*!
	@brief plays wordle game
*/
void playWordle(void);
/*!
	@brief checks if user input is a word
	@param the user input
	@return true if it is a word falsw if not
*/
bool validWord(const char* guess);
/*!
	@brief compares user guess to the answer
	@param the answer
	@param the users guess
	@return a string of the user guess G if letter is in correct location, Y if not in correct, _ if letter not present in answer
*/

char* processGuess(const char* theWord, const char* theGuess);
/*!
	@brief converts input to lowercase
	@param the user input
	@return the user input in lower case
*/
char* toLowerCase(const char* guess);
/*!
	@brief checks if user input contains only letters
	@param the user input
	@return true if it does contain onyl char false if not
*/
bool conatainsonlychar(const char* guess);
/*!
	@brief checks if user input is 5 letters long
	@param the user input
	@return true if it is correct length  false if not
*/
bool correctlength(const char* guess);

void updateLettersGuessed(const char* theGuess);

char* lettersNotGuessed();




int runwordletests();
#ifdef UNIT_TESTING
// Expose these functions for unit testing
char* processGuess(const char* theWord, const char* theGuess);
char* toLowerCase(const char* guess);
bool conatainsonlychar(const char* guess);
bool conatainsonlychar(const char* guess);
bool validWord(const char* guess);
char* get_word(int number);
void set_wordle_mock_dictionary(const char mock_dict[][MAX_wordle_WORD_LENGTH], int size);
void updateLettersGuessed(const char* theGuess);
char* lettersNotGuessed();
void resetTestArrays()
#endif

#endif // wordle_H