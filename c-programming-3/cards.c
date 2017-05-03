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

/* dealer.h gives cards.c function prototypes, structures, and
 * 	constants used in anything related to creation/management
 * 	of decks and hands of cards */
#include "dealer.h"

/* time.h used for seeding the rand() function used in shuffling */
#include <time.h>

/* string.h used to convert integers to strings for printing */
#include <string.h>

#define VAL_START 1

#define HEARTS 'H'
#define DIAMONDS 'D'
#define CLUBS 'C'
#define SPADES 'S'
#define S_ERROR 'E'

#define ACE " A"
#define JACK " J"
#define QUEEN " Q"
#define KING " K"

/* newCard()
 * Parameters:	enum Suit - suit of new card
 * 				int - value of new card
 * Return val:	struct Card - newly-created card */
struct Card newCard(enum Suit inSuit, int inVal) {
	struct Card new;
	new.val = inVal;
	new.suit = inSuit;

	return new;
}


/* newDeck()
 * Parameters:	struct Card [] - card array pointer to be populated
 * Returns nothing.
 * Inserts a unique card into all indices of a provided array. */
void newDeck(struct Card resultDeck[]) {
	enum Suit suitCount = INIT;
	int valCount = INIT;
	int deckCount = INIT;

	/* Beginning with 1 of hearts, populate each index with new card */
	for (suitCount = hearts; suitCount <= NUM_SUITS; suitCount++) {
		for (valCount = VAL_START; valCount <= NUM_VALS; valCount++) {
			resultDeck[deckCount] = newCard(suitCount, valCount);
			deckCount++;
		}
	} 
}


/* newHand()
 * Parameters:	struct Card [] - deck to draw from
 * 				struct Card [] - hand to draw to
 * 				int	- size of the hand
 * Returns nothing.
 * Initializes the hand with null cards.
 * For each hand index, draw a card from the deck to the hand. */
void newHand(struct Card deck[], struct Card hand[], int handSize) {
	int count = INIT;
	for (count = INIT; count < handSize; count++) {
		hand[count] = newCard(nullSuit, INIT);
	}
	for (count = INIT; count < handSize; count++) {
		draw(deck, hand);
	}
}


/* draw()
 * Parameters:	struct Card [] - deck to draw from
 * 				struct Card [] - hand to draw to
 * Returns nothing.
 * Finds the first non-null card in the deck, then
 * 	the first null card in the hand. Copies the deck card
 * 	and adds it to the hand index.
 *  Nullifies the card in the deck. */
void draw(struct Card resultDeck[], struct Card resultHand[]) {
	int handCounter = INIT;
	int deckCounter = INIT;
	
	while (resultHand[handCounter].suit != nullSuit) {
		handCounter++;
	}

	while (resultDeck[deckCounter].suit == nullSuit) {
		deckCounter++;
	}

	int newVal = resultDeck[deckCounter].val;
	enum Suit newSuit = resultDeck[deckCounter].suit;

	resultHand[handCounter] = newCard(newSuit, newVal);
	resultDeck[deckCounter].suit = nullSuit;
}


/* showCards()
 * Parameters:	struct Card [] - array of Cards to display
 * 				int - size of the array
 * 				int - number of Cards to display before carriage return
 * Returns nothing.
 * Traverses array of Cards.
 * Saves current card's suit and value, converts them to strings,
 * 	and prints the card's value.
 * After 'lineBreak' cards, carriage return. */
void showCards(struct Card cards[], int size, int lineBreak) {
	int counter = INIT;
	int val = INIT;
	char printSuit = INIT;
	char printVal[2];
	enum Suit currSuit = INIT;

	for (counter = INIT; counter < size; counter++) {
		currSuit = cards[counter].suit;
		val = cards[counter].val;

		if (currSuit != nullSuit) {
			printSuit = getSuit(currSuit);
			getVal(printVal, val);

			printf("%s%c ", printVal, printSuit);

			if ((counter % lineBreak) == (lineBreak - 1)) {
				printf("\n");
			}
		}
	}

	printf("\n");
}


/* getSuit()
 * Parameters:	enum Suit - suit value of card
 * Returns:		char - character representation of card's suit
 * Checks the Suit value and returns the appropriate char value */
char getSuit(enum Suit suit) {
	if (suit == hearts) {
		return HEARTS;
	}
	else if (suit == diamonds) {
		return DIAMONDS;
	}
	else if (suit == clubs) {
		return CLUBS;
	}
	else if (suit == spades) {
		return SPADES;
	}
	else {
		return S_ERROR;
	}
}


/* getVal()
 * Parameters:	char [] - pointer to string form of card value
 * 				enum Face - face value of card to be converted
 * Returns nothing.
 * Checks the card's value and modifies string parameter with
 * 	appropriate string of integer or face value */
void getVal(char result[], enum Face val) {
	if (val == ace) {
		strcpy(result, ACE);
	}
	else if (val == jack) {
		strcpy(result, JACK);
	}
	else if (val == queen) {
		strcpy(result, QUEEN);
	}
	else if (val == king) {
		strcpy(result, KING);
	}
	else {
		sprintf(result, "%2d", val);
	}
}


/* shuffle()
 * Parameters:	struct Card [] - cards to be shuffled
 * 				int - number of cards to shuffle
 * Returns nothing.
 * Modifies an array of Cards to be in randomized order.
 * Uses the Fisher-Yates shuffle method of replacing a
 * 	randomly-selected card with a decrementing position
 * 	from the bottom of the deck.
 * Randomly-selected card index chosen by a seeded rand() function */
void shuffle(struct Card cards[], int size) {
	int count = INIT;
	int randPlace = INIT;

	for (count = size - CARD_MIN; CARD_MIN < count; count--) {
		randPlace = getRand(count);
		swapCard(cards, count, randPlace);
	}
}


/* getRand()
 * Parameters:	int - maximum value of random number
 * Returns:		int - randomly-chosen number from 0-max
 * Seeds rand() with time(), generates a random number,
 * 	and uses modulus with the max parameter to ensure it
 * 	doesn't exceed the size of the deck */
int getRand(int max) {
	int random = INIT;
	time_t seed = time(NULL);
	srand(seed);

	random = rand() % max;
	return random;
}


/* swapCard()
 * Parameters:	struct Card [] - array of cards in which to swap two cards
 * 				int - first index of card to swap
 * 				int - second index of card to swap
 * Returns nothing.
 * Easy method of trading places of two Cards in an array. */
void swapCard(struct Card deck[], int swap1, int swap2) {
	struct Card temp = deck[swap1];
	deck[swap1] = deck[swap2];
	deck[swap2] = temp;
}
