/*!
	@file newWordle.cpp
	@brief Wordle implementation
	@author Connor Johnstone
*/




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



// Remove static keyword for functions to be tested
#ifdef UNIT_TESTING
#define STATIC
#else
#define STATIC static
#endif



#define MAX_NUM_OF_WORDS 2500
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int word_length = 5;

/*!
	@brief converts input to lowercase
	@param the user input
	@return the user input in lower case
*/
STATIC char* toLowerCase(const char* guess) {

	const char* lowercaseguess = guess;
	const int length = strlen(lowercaseguess);
	
	char* lower = (char*)malloc(length + 1);
	lower[length] = 0;
	for (int i = 0; i < length; i++) {
		lower[i] = tolower(guess[i]);
	}

	return lower;

}
/*!
	@brief checks if user input contains only letters
	@param the user input
	@return true if it does contain onyl char false if not
*/
STATIC bool conatainsonlychar(const char* guess) {
	bool onlyalpha = false;

	const int length = strlen(guess);
	char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	for (int i = 0; i < length; i++) {
		char letter = guess[i];
		for (int j = 0; j < 26; j++) {
			if (letter == alphabet[j]) {
				onlyalpha = true;
			}
		}
		if (!onlyalpha) {
			return onlyalpha;
		}
		onlyalpha = false;

	}

	return true;




}

/*!
	@brief checks if user input is 5 letters long
	@param the user input
	@return true if it is correct length  false if not
*/
STATIC bool correctlength(const char* guess) {
	const int length = strlen(guess);
	if (length == word_length) {
		return true;
	}

	return false;
}


/*!
	@brief checks if user input is a word
	@param the user input
	@return true if it is a word falsw if not
*/

bool validWord(const char* newguess) {
	//todo add a check if word inputted is a dictionary word

	return true;

}

/*!
	@brief compares user guess to the answer
	@param the answer
	@param the users guess
	@return a string of the user guess G if letter is in correct location, Y if not in correct, _ if letter not present in answer
*/
STATIC char* processGuess(const char* theWord, const char* theGuess) {
	// the clue
	char* clue = (char*)malloc(6 * sizeof(char));

	if (clue == NULL) {
		perror("Unable to allocate memory for clue");
		exit(EXIT_FAILURE);
	}


	// Initialize the clue with '_'
	for (int i = 0; i < 5; i++) {
		clue[i] = '_';
	}
	// Add to the end to make a string
	clue[5] = '\0';


	// set of flags indicating if that letter in the answer in used as clue
	bool answerFlags[5] = {false, false,false,false,false };

	// first pass, look for matched
	for (int i = 0; i < 5; i++) {
		if (theGuess[i] == theWord[i]) {
			clue[i] = 'G';
			answerFlags[i] = true;

		}
	}

	// second pass, look for correct letter worng place
	for (int i = 0; i < 5; i++) {
		if (clue[i] == '_') {
			for (int j = 0; j < 5; j++) {
				if (theGuess[i] == theWord[j] && !answerFlags[j]) {
					// a match at another position and has not been used a clue
					clue[i] = 'Y';
					answerFlags[j] = true;
					break; // makes it so only one clue for one letter



				}
			}
		}

	}
	//printf("%s\n", clue);
	return clue;
		//strcmp(clue, "GGGGG") == 0;

}

/*!
	@brief a method to get the word 
	@return the answer to the word
*/
char* getWord() {
	int wordCount = 0;

	char* fiveLetterWord = (char*)malloc(6 * sizeof(char));
	const char* fivelettertextfile =
#include "wordlength5a2m.txt"
		;
	const char* secondfivelettertextfile =
#include "wordlength5m2z.txt"
		;

	srand(time(NULL));
	int randnumber = (rand() % 2) + 1;


	//const char* newanswer = nullptr;
	char* newanswer = NULL;


	if (randnumber == 1) {
		std::istringstream iss(fivelettertextfile);
		std::vector<std::string> lines;

		std::string line;
		while (std::getline(iss, line)) {
			lines.push_back(line);
		}
		// Seed the random number generator
		std::srand(std::time(nullptr));

		// Pick a random line
		int randomLineIndex = std::rand() % lines.size();
		std::string selectedLine = lines[randomLineIndex];

		// Tokenize the selected line to extract words
		std::istringstream lineStream(selectedLine);
		std::vector<std::string> wordsone;
		std::string word;

		while (lineStream >> word) {
			wordsone.push_back(word);

		}
		std::string randomWord = wordsone[0];
		//newanswer = randomWord.c_str();
		newanswer = (char*)malloc(randomWord.length() + 1);
		strcpy(newanswer, randomWord.c_str());


	}
	else
	{
		std::istringstream iss(secondfivelettertextfile);
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(iss, line)) {
			lines.push_back(line);
		}
		// Seed the random number generator
		std::srand(std::time(nullptr));

		// Pick a random line
		int randomLineIndex = std::rand() % lines.size();
		std::string selectedLine = lines[randomLineIndex];

		// Tokenize the selected line to extract words
		std::istringstream lineStream(selectedLine);
		std::vector<std::string> wordsone;
		std::string word;

		while (lineStream >> word) {
			wordsone.push_back(word);

		}
		std::string randomWord = wordsone[0];
		newanswer = (char*)malloc(randomWord.length() + 1);
		strcpy(newanswer, randomWord.c_str());
	}

	return newanswer;
}
/*!
	@brief plays wordle game
*/

void playWordle(void) {


	// load words
	char** wordlist = (char**)calloc(MAX_NUM_OF_WORDS, sizeof(char*));
	int wordCount = 0;

	char* fiveLetterWord = (char*)malloc(6 * sizeof(char));
	const char* fivelettertextfile =
#include "wordlength5a2m.txt"
		;
	const char* secondfivelettertextfile =
#include "wordlength5m2z.txt"
		;

	srand(time(NULL));
	int randnumber = (rand() % 2) + 1;

	
	//const char* newanswer = nullptr;
	char* newanswer = NULL;


	if (randnumber == 1){
		std::istringstream iss(fivelettertextfile);
		std::vector<std::string> lines;

		std::string line;
		while (std::getline(iss, line)) {
			lines.push_back(line);
		}
		// Seed the random number generator
		std::srand(std::time(nullptr));

		// Pick a random line
		int randomLineIndex = std::rand() % lines.size();
		std::string selectedLine = lines[randomLineIndex];

		// Tokenize the selected line to extract words
		std::istringstream lineStream(selectedLine);
		std::vector<std::string> wordsone;
		std::string word;

		while (lineStream >> word) {
			wordsone.push_back(word);

		}
		std::string randomWord = wordsone[0];
		//newanswer = randomWord.c_str();
		newanswer = (char*)malloc(randomWord.length() + 1);
		strcpy(newanswer, randomWord.c_str());


	}
	else
	{
		std::istringstream iss(secondfivelettertextfile);
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(iss, line)) {
			lines.push_back(line);
		}
		// Seed the random number generator
		std::srand(std::time(nullptr));

		// Pick a random line
		int randomLineIndex = std::rand() % lines.size();
		std::string selectedLine = lines[randomLineIndex];

		// Tokenize the selected line to extract words
		std::istringstream lineStream(selectedLine);
		std::vector<std::string> wordsone;
		std::string word;

		while (lineStream >> word) {
			wordsone.push_back(word);

		}
		std::string randomWord = wordsone[0];
		newanswer = (char*)malloc(randomWord.length() + 1);
		strcpy(newanswer, randomWord.c_str());
	}

	char guessone[6] = { '_', '_', '_', '_','_', '\0' };
	char guesstwo [6] = {'_', '_', '_', '_','_', '\0'};
	char guessthree[6] = {'_', '_', '_', '_','_', '\0'};
	char guessfour[6] = {'_', '_', '_', '_','_', '\0'};
	char guessfive[6] = {'_', '_', '_', '_','_', '\0'};
	char guesssix[6] = {'_', '_', '_', '_','_', '\0'};
	char clueone[6] = { '_', '_', '_', '_','_', '\0' };
	char cluetwo[6] = { '_', '_', '_', '_','_', '\0' };
	char cluethree[6] = { '_', '_', '_', '_','_', '\0' };
	char cluefour[6] = { '_', '_', '_', '_','_', '\0' };
	char cluefive[6] = { '_', '_', '_', '_','_', '\0' };
	char cluesix[6] = { '_', '_', '_', '_','_', '\0' };







	// do the game loop
	int num_of_guesses = 0;
	bool correct_guess = false;
	char* guess = (char*) malloc(6 * sizeof(char));

	while (num_of_guesses < 6 && !correct_guess) {
		//get guess from user
		printf("\nInput a 5-letter word and press enter \n");
		scanf("%s", guess);

		char* newguess = toLowerCase(guess);
		//printf("you have guessed %s\n", newguess);
		
		if (!conatainsonlychar(newguess)) {
			printf("Guess contains an non letter, try again.");
			continue;
		}

		if (!correctlength(newguess)) {
			printf("Word input was not the correct length. Try Agian");
			continue;
		}


		if (!validWord(newguess)) {
			continue;
		}





		num_of_guesses += 1;


		//proocess guess 
		char* clue = processGuess(newanswer, newguess);
		

		switch (num_of_guesses)
		{
		case 1:
			for (int i = 0; i < 6; i++) {
				guessone[i] = newguess[i];
				clueone[i] = clue[i];
			}
			break;
		case 2:
			for (int i = 0; i < 6; i++) {
				guesstwo[i] = newguess[i];
				cluetwo[i] = clue[i];
			}
			break;
		case 3:
			for (int i = 0; i < 6; i++) {
				guessthree[i] = newguess[i];
				cluethree[i] = clue[i];
			}
			break;
		case 4:
			for (int i = 0; i < 6; i++) {
				guessfour[i] = newguess[i];
				cluefour[i] = clue[i];
			}
			break;
		case 5:
			for (int i = 0; i < 6; i++) {
				guessfive[i] = newguess[i];
				cluefive[i] = clue[i];
			}
			break;
		case 6:
			for (int i = 0; i < 6; i++) {
				guesssix[i] = newguess[i];
				cluesix[i] = clue[i];
			}
			break;

		}

		for (int i = 0; i < 6; i++) {
			if (clueone[i] == 'G') {
				printf(ANSI_COLOR_GREEN   "%c", guessone[i]);
			}
			else if (clueone[i] == 'Y') {
				printf(ANSI_COLOR_YELLOW "%c", guessone[i]);
			}
			else if (guessone[i] == '_'){
				printf(ANSI_COLOR_RESET "%c", guessone[i]);
			}else {
				printf(ANSI_COLOR_RED "%c", guessone[i]);
			}
		}
		printf(ANSI_COLOR_RESET "\n");
		for (int i = 0; i < 6; i++) {
			if (cluetwo[i] == 'G') {
				printf(ANSI_COLOR_GREEN   "%c", guesstwo[i]);
			}
			else if (cluetwo[i] == 'Y') {
				printf(ANSI_COLOR_YELLOW "%c", guesstwo[i]);
			}
			else if (guesstwo[i] == '_') {
				printf(ANSI_COLOR_RESET "%c", guesstwo[i]);
			}
			else {
				printf(ANSI_COLOR_RED "%c", guesstwo[i]);
			}
		}
		printf(ANSI_COLOR_RESET "\n");
		for (int i = 0; i < 6; i++) {
			if (cluethree[i] == 'G') {
				printf(ANSI_COLOR_GREEN   "%c", guessthree[i]);
			}
			else if (cluethree[i] == 'Y') {
				printf(ANSI_COLOR_YELLOW "%c", guessthree[i]);
			}
			else if (guessthree[i] == '_') {
				printf(ANSI_COLOR_RESET "%c", guessthree[i]);
			}
			else {
				printf(ANSI_COLOR_RED "%c", guessthree[i]);
			}
		}
		printf(ANSI_COLOR_RESET "\n");
		for (int i = 0; i < 6; i++) {
			if (cluefour[i] == 'G') {
				printf(ANSI_COLOR_GREEN   "%c", guessfour[i]);
			}
			else if (cluefour[i] == 'Y') {
				printf(ANSI_COLOR_YELLOW "%c", guessfour[i]);
			}
			else if (guessfour[i] == '_') {
				printf(ANSI_COLOR_RESET "%c", guessfour[i]);
			}
			else {
				printf(ANSI_COLOR_RED "%c", guessfour[i]);
			}
		}
		printf(ANSI_COLOR_RESET "\n");
		for (int i = 0; i < 6; i++) {
			if (cluefive[i] == 'G') {
				printf(ANSI_COLOR_GREEN   "%c", guessfive[i]);
			}
			else if (cluefive[i] == 'Y') {
				printf(ANSI_COLOR_YELLOW "%c", guessfive[i]);
			}
			else if (guessfive[i] == '_') {
				printf(ANSI_COLOR_RESET "%c", guessfive[i]);
			}
			else {
				printf(ANSI_COLOR_RED "%c", guessfive[i]);
			}
		}
		printf(ANSI_COLOR_RESET "\n");
		for (int i = 0; i < 6; i++) {
			if (cluesix[i] == 'G') {
				printf(ANSI_COLOR_GREEN   "%c", guesssix[i]);
			}
			else if (cluesix[i] == 'Y') {
				printf(ANSI_COLOR_YELLOW "%c", guesssix[i]);
			}
			else if (guesssix[i] == '_') {
				printf(ANSI_COLOR_RESET "%c", guesssix[i]);
			}
			else {
				printf(ANSI_COLOR_RED "%c", guesssix[i]);
			}
		}
		printf(ANSI_COLOR_RESET);



		correct_guess = strcmp(clue, "GGGGG") == 0;

	}



	//display end of game message
	if (correct_guess) {
		printf("\nCongratulation! You guess the correct word in %d tries!\n", num_of_guesses);
	}
	else {
		printf("\nNo more guesses... The correct word was %s\n", newanswer);
	}


	// clean up
	for (int i = 0; i < wordCount; i++) {
		free(wordlist[i]);
	}
	free(wordlist);
	free(fiveLetterWord);
	free(guess);

}





