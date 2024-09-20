

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdbool.h>
//#include <vector>
//#include <iostream>
//#include <sstream>
//#include <time.h>
//#include <cstdlib> 
//#include <ctime> 




//STATIC char* get_word(int number) {
//
//
//	return wordbuilder_dictionary[number % wordbuilder_dictionary_size];
//}
/*!
	@brief Loads the wordlength5 from a file
	@param filename The name of the file to load
	@return 1 if the text file was loaded successfully, 0 otherwise
*/

//STATIC int load_all_5letter_words(const char* filename) {
//	FILE* file = fopen(filename, "r");
//	if (!file) return 0;
//
//	while (fgets(wordle_dictionary[wordle_dictionary_size], MAX_wordle_WORD_LENGTH, file)) {
//		wordle_dictionary[wordle_dictionary_size][strcspn(wordle_dictionary[wordle_dictionary_size], "\n")] = 0;
//		if (++wordle_dictionary_size >= MAX_wordle_DICTIONARY_SIZE) break;
//	}
//
//	fclose(file);
//	return 1;
//}



/*!
	@brief Initializes the Wordle game

*/
//void wordle_initialize(void) {
//	srand((unsigned int)time(NULL));
//	if (!load_all_5letter_words("../wordlength5.txt")) {
//		fprintf(stderr, "Failed to load dictionary. Wordle game may not function properly.\n");
//	}
//}