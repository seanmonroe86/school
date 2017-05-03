/* Author:	Sean Monroe
 * PID:		1571224
 * Class:	COP4338 U04
 * 
 * Assignment 4 - Poker Player
 * 
 * I hereby certify that this collective work is my own and none of
 * it is the work of any other person or entity.	-SM
 */

/* cards.h includes stdio.h for printing as well as constants
 * 		and function prototypes used in deck/hand creation/display */
#include "cards.h"

/* command-line verification: arguments required,
 *							error code for bad arguments,
 *							error code for good arguments */
#define ARGS_REQ 3
#define ARGS_BAD 0
#define ARGS_GOOD 1

/* error code definitions - 0: no errors, 1: errors with arguments */
#define NOERROR 0
#define ERROR_ARGS 1

/* first argument of argv */
#define ARG_NAME 0

/* command-line array indices:	0 - validity of arguments
 * 								1 - number of cards/hand
 * 								2 - number of hands */
#define ARG_VALID 0
#define ARG_CARDS 1
#define ARG_HANDS 2

/* main()
 * Parameters: REQUIRED two integers less than 13 whose product < 52.
 * Returns: Error code based on arguments: 0 - no error, 1 - arg error
 * 
 * Verifies input arguments, performs assignment tasks with helpers */
int main(int argc, char *argv[]) {
	int commands[] = {ARGS_BAD, INIT, INIT};
	getCommands(argc, argv, commands);

	if (commands[ARG_VALID] == ARGS_BAD) {
		error(argv[ARG_NAME]);
		return ERROR_ARGS;
	}

	seed();

	const int NUMCARDS = commands[ARG_CARDS];
	const int NUMHANDS = commands[ARG_HANDS];
	Card deck[DECK_SIZE];
	Card hands[NUMCARDS][NUMHANDS];

	printf("New and sorted deck:\n");
	newDeck(deck);
	showCards(deck, DECK_SIZE, NUM_FACES);

	printf("Shuffled deck:\n");
	shuffle(deck, DECK_SIZE);
	showCards(deck, DECK_SIZE, NUM_FACES);

	makeHands(NUMHANDS, NUMCARDS, deck, hands);	
	showHands(NUMHANDS, NUMCARDS, hands);

	playPoker(NUMHANDS, NUMCARDS, hands);

	return NOERROR;
}


/* error()
 * Parameters:	char [] - first argument of command line,
 * 						i.e. the name of the program
 * Returns nothing.
 * Prints to console a prompt if user fails to enter proper arguments */
void error(const char game[]) {
	printf("There was an error with your input.\n");
	printf("Correct format: %s a b\n", game);
	printf("a: Integer. Number of cards in each hand.\n");
	printf("b: Integer. Number of hands.\n");
	printf("a == %d\n", CARD_STUD);
	printf("%d <= b <= %d\n", HAND_MIN, HAND_MAX);
	printf(" a * b <= %d\n", DECK_SIZE);
	printf("Please execute again with proper arguments.\n");
}


/* getCommands()
 * Parameters:	int argNum - number of commandline arguments
 * 				char *args[] - commandline arguments
 * 				int returnVal[] - integer array of processed args
 * Modifies input returnVal array with processed arguments, or error */
void getCommands(int argNum, char *args[], int returnVal[]) {
	if (argNum == ARGS_REQ) {
		const int CARDS = atoi(args[ARG_CARDS]);
		const int HANDS = atoi(args[ARG_HANDS]);

		const int C_VALID = (CARDS == CARD_STUD);
		const int H_VALID = ((HAND_MIN <= HANDS) && (HANDS <= HAND_MAX));
		const int D_VALID = ((CARDS * HANDS) <= DECK_SIZE);

		if (C_VALID && H_VALID && D_VALID) {
			returnVal[ARG_VALID] = ARGS_GOOD;
			returnVal[ARG_CARDS] = CARDS;
			returnVal[ARG_HANDS] = HANDS;
		}
	}
}


/* seed()
 * Parameters: None
 * Returns nothing.
 * Seeds the program's random function.
 * Called immediately and only once. */
void seed() {
	time_t seed;
	srand((unsigned)time(&seed));
}
