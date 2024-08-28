#ifndef wordle_H
#define wordle_H

/*!
	@file
	@brief documentation
*/



void playWordle(void);
bool validworda(const char* guess);
char* processGuess(const char* theWord, const char* theGuess);
char* toLowerCase(const char* guess);
bool conatainsonlychar(const char* guess);
bool correctlength(const char* guess);
char* getWord();

int runwordletests();
#ifdef UNIT_TESTING
// Expose these functions for unit testing
char* processGuess(const char* theWord, const char* theGuess);
char* toLowerCase(const char* guess);
bool conatainsonlychar(const char* guess);

#endif

#endif // wordle_H