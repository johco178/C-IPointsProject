#include "hangman.h"
#include "newwordle.h"
#include "test_tictactoe.h"
#include "secretNumber.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

int main() {
	runwordletests();
	runttttests();
	hangmanTests();

	return 0;
}