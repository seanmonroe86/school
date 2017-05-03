/* Author:	Sean Monroe
 * PID:		1571224
 * Class:	COP4338 U04
 * 
 * Assignment 3 - Card Dealer
 * Shuffles a standard deck of cards using the Yates shuffle
 * algorithm. Using command-line arguments providing hand size
 * and number, cards are then dealt to the needed hands.
 * Standard output is provided after each step for verification.
 * 
 * I hereby certify that this collective work is my own and none of
 * it is the work of any other person or entity.	-SM
 */

/* dealer.h includes stdio.h for printing as well as constants
 * 		and function prototypes used in deck/hand creation/display */
#include "dealer.h"

/* command-line verification: arguments required,
 *							error code for bad arguments,
 *							error code for good arguments */
#define ARGS_REQ 3
#define ARGS_BAD 0
#define ARGS_GOOD 1

/* error code definitions - 0: no errors, 1: errors with arguments */
#define NOERROR 0
#define ERROR_ARGS 1


/* command-line array indices:	0 - validity of arguments
 * 								1 - number of cards/hand
 * 								2 - number of hands */
#define ARG_VALID 0
#define ARG_CARDS 1
#define ARG_HANDS 2

void error();
void getCommands(int, char *[], int []);


/* main()
 * Parameters: REQUIRED two integers less than 13 whose product < 52.
 * Returns: Error code based on arguments: 0 - no error, 1 - arg error
 * 
 * Verify command-line arguments.
 * End program with prompt if arguments are bad, continue otherwise.
 * Initialize a deck and temporary hand with given arguments.
 * Create a new deck, and show it (sorted).
 * Shuffle the deck, and show the result.
 * Deal cards off the top of the deck to each hand,
 * 	showing each hand after it's been dealt cards.
 * End with no errors. */
int main(int argc, char *argv[]) {
	int commands[] = {ARGS_BAD, INIT, INIT};
	getCommands(argc, argv, commands);

	if (commands[ARG_VALID] == ARGS_BAD) {
		error();
		return ERROR_ARGS;
	}

	int handCount = INIT;
	int numCards = commands[ARG_CARDS];
	int numHands = commands[ARG_HANDS];
	struct Card temp[numCards];
	struct Card deck[DECK_SIZE];

	newDeck(deck);

	printf("New and sorted deck:\n");
	showCards(deck, DECK_SIZE, NUM_VALS);

	shuffle(deck, DECK_SIZE);

	printf("Shuffled deck:\n");
	showCards(deck, DECK_SIZE, NUM_VALS);

	for (handCount = HAND_MIN; handCount <= numHands; handCount++) {
		newHand(deck, temp, numCards);
		printf("Hand #%d:\n", handCount);
		showCards(temp, numCards, numCards);
	}

	return NOERROR;
}


/* error()
 * No parameters, no return value.
 * Prints to console a prompt if user fails to enter proper arguments */
void error() {
	printf("There was an error with your input.\n");
	printf("Correct format: ./dealer a b\n");
	printf("a: Integer. Number of cards in each hand.\n");
	printf("b: Integer. Number of hands.\n");
	printf("%d <= a <= %d\n", CARD_MIN, CARD_MAX);
	printf("%d <= b <= %d\n", HAND_MIN, HAND_MAX);
	printf(" a * b <= %d\n", DECK_SIZE);
	printf("Please execute again with proper arguments.\n");
}


/* getCommands()
 * Parameters:	int argNum - number of commandline arguments
 * 				char *args[] - commandline arguments
 * 				int returnVal[] - integer array of processed args */
void getCommands(int argNum, char *args[], int returnVal[]) {
	if (argNum != ARGS_REQ) {
		return;
	}
	else {
		int argCards = atoi(args[ARG_CARDS]);
		int argHands = atoi(args[ARG_HANDS]);

		if ((argCards < CARD_MIN) || (CARD_MAX < argCards)) {
			return;
		}
		else if ((argHands < HAND_MIN) || (HAND_MAX < argHands)) {
			return;
		}
		else if (DECK_SIZE < argCards * argHands) {
			return;
		}
		else {
			returnVal[ARG_VALID] = ARGS_GOOD;
			returnVal[ARG_CARDS] = argCards;
			returnVal[ARG_HANDS] = argHands;
			return;
		}
	}
}
