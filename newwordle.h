#ifndef wordle_H
#define wordle_H

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
bool validword(const char* guess);
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
/*!
	@brief a method to get the word
	@return the answer to the word
*/
char* getWord();

int runwordletests();
#ifdef UNIT_TESTING
// Expose these functions for unit testing
char* processGuess(const char* theWord, const char* theGuess);
char* toLowerCase(const char* guess);
bool conatainsonlychar(const char* guess);
bool conatainsonlychar(const char* guess);

#endif

#endif // wordle_H