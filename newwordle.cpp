#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NUM_OF_WORDS 100

bool processGuess(const char* theWord, const char* theGuess) {
	// the clue
	char clue[6] = { '_','_','_','_','_', '\0' };

	// set of flags indicating if that letter in the answer in used as clue
	bool answerFlags[5] = { false, false,false,false,false };

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
				if (theGuess[i] == theWord[i] && !answerFlags[j]) {
					// a match at another position and has not been used a clue
					clue[i] = 'Y';
					answerFlags[j] = true;
					break; // makes it so only one clue for one letter



				}
			}
		}

	}
	printf("%s\n", clue);
	return strcmp(clue, "GGGGG") == 0;

}

void playWordle(void) {


	// load words
	char** wordlist = calloc(MAX_NUM_OF_WORDS, sizeof(char*));
	int wordCount = 0;

	char* fiveLetterWord = malloc(6 * sizeof(char));

	FILE* wordsFile = fopen("wordlength5.txt", "r");

	while (fscanf(wordsFile, "%s", fiveLetterWord) != EOF && wordCount < MAX_NUM_OF_WORDS) {
		wordlist[wordCount] = fiveLetterWord;
		wordCount++;
		fiveLetterWord = malloc(6 * sizeof(char));
	}
	fclose(wordsFile);
	// start game
	// pick word randomly
	srand(time(NULL));
	char* answer = wordlist[rand() % wordCount];

	// do the game loop
	int num_of_guesses = 0;
	bool correct_guess = false;
	char* guess = malloc(6 * sizeof(char));

	while (num_of_guesses < 6 && !correct_guess) {
		//get guess from user
		printf("Input a x- letter word and press enter");
		scanf("%s", guess);
		printf("you have guessed %s\n", guess);
		num_of_guesses += 1;

		//proocess guess 
		correct_guess = processGuess(answer, guess);
	}

	//display end of game message
	if (correct_guess) {
		printf("Congratulation! Ypu guess the correct word in %d tries!\n", num_of_guesses);
	}
	else {
		printf("No more guesses... The correct word was %s\n", answer);
	}

	// clean up
	for (int i = 0; i < wordCount; i++) {
		free(wordlist[i]);
	}
	free(wordlist);
	free(fiveLetterWord);
	free(guess);

}





//void begingame(int wordlength);
//
//void playWordle(){
//	int wordlength = 0;
//	printf("Welcome to Wordle!!! \nWhat size of word do you want?\nInput a number beween 3 and 12");
//	
//	if (scanf("%d", &wordlength) != 1) {
//		printf("Invalid input please try again");
//		playWordle();
//	}
//
//
//
//}
//
//void begingame(int wordlength) {
//	FILE *possible_words;
//	switch (wordlength) {
//	case 3:
//		possible_words = fopen("wordlength3.txt", "r");
//		break;
//	case 4:
//		possible_words = fopen("wordlength4.txt", "r");
//		break;
//	case 5:
//		possible_words = fopen("wordlength5.txt", "r");
//		break;
//	case 6:
//		possible_words = fopen("wordlength6.txt", "r");
//		break;
//	case 7:
//		possible_words = fopen("wordlength7.txt", "r");
//		break;
//	case 8:
//		possible_words = fopen("wordlength8.txt", "r");
//		break;
//	case 9:
//		possible_words = fopen("wordlength9.txt", "r");
//		break;
//	case 10:
//		possible_words = fopen("wordlength10.txt", "r");
//		break;
//	case 11:
//		possible_words = fopen("wordlength11.txt", "r");
//		break;
//	case 12:
//		possible_words = fopen("wordlength12.txt", "r");
//		break;
//	}
//
//
//
//
//
//
//
//
//	
//	}
//
//}
//
//
//
//
