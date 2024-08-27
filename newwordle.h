#ifndef wordle_H
#define wordle_H

/*!
	@file
	@brief documentation
*/



void playWordle(void);
bool validworda(const char* guess);
bool processGuess(const char* theWord, const char* theGuess);
char* toLowerCase(const char* guess);
bool conatainsonlychar(const char* guess);
bool correctlength(const char* guess);

#endif // wordle_H