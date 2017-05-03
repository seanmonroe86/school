/* Author:	Sean Monroe
 * PID:		1571224
 * Class:	COP4338 U04
 * 
 * Assignment 4 - Poker Player
 * 
 * I hereby certify that this collective work is my own and none of
 * it is the work of any other person or entity.	-SM
 */

/* cards.h gives cards.c function prototypes, structures, and
 * 	constants used in anything related to creation/management
 * 	of decks and hands of cards */
#include "cards.h"

/* Face value array to be used when printing card faces.
 * Size is one more than NUM_FACES due to inclusion of null face */
const char * STR_FACE[NUM_FACES + 1] = {" N", " A", " 2", " 3", " 4", 
										" 5", " 6", " 7", " 8", " 9", 
										"10", " J", " Q", " K"};

/* Suit value array to be used when printing card suits.
 * Size is one more than NUM_SUITS due to inclusion of null suit */
const char * STR_SUIT[NUM_SUITS + 1] = {"N", "H", "D", "C", "S"};


/* newCard()
 * Parameters:	Face - face of new card
 * 				Suit - suit of new card
 * Return val:	Card - newly-created card */
Card newCard(const Face NEW_F, const Suit NEW_S) {
	Card new;
	new.face = NEW_F;
	new.suit = NEW_S;
	return new;
}


/* newDeck()
 * Parameters:	Card [] - card array pointer to be populated
 * Returns nothing.
 * Inserts a unique Card into all indices of a provided Card array. */
void newDeck(Card deck[]) {
	Face face = ace;
	Suit suit = hearts;
	int counter = INIT;

	/* Beginning with ace of hearts, populate each index with new card */
	for (suit = hearts; suit <= NUM_SUITS; suit++) {
		for (face = ace; face <= NUM_FACES; face++) {
			deck[counter] = newCard(face, suit);
			counter++;
		}
	} 
}


/* newHand()
 * Parameters:	Card [] - deck to draw from
 * 				Card [] - hand to draw to
 * 				int	- size of the hand
 * Returns nothing.
 * Initializes the hand with null cards.
 * For each hand index, draw a card from the deck to the hand. */
void newHand(Card deck[], Card hand[], const int HANDSIZE) {
	int counter = INIT;
	for (counter = INIT; counter < HANDSIZE; counter++) {
		hand[counter] = newCard(INIT, nullSuit);
	}
	for (counter = INIT; counter < HANDSIZE; counter++) {
		draw(deck, hand);
	}
}


/* makeHands()
 * Parameters:	int - number of hands to make
 * 				int - number of cards per hand
 * 				Card[] - deck from which to draw
 * 				Card[x][y] - hand x, card y
 * Populates a group of hands using given deck. */
void makeHands(const int NUMHANDS, const int NUMCARDS, 
			   Card deck[], Card hands[NUMHANDS][NUMCARDS]) {
	int counter = INIT;
	for (counter = INIT; counter < NUMHANDS; counter++) {
		newHand(deck, hands[counter], NUMCARDS);
	}
}


/* draw()
 * Parameters:	Card [] - deck to draw from
 * 				Card [] - hand to draw to
 * Returns nothing.
 * Finds the first non-null card in the deck, then
 * 	the first null card in the hand. Copies the deck card
 * 	and adds it to the hand index.
 *  Nullifies the card in the deck. */
void draw(Card deck[], Card hand[]) {
	int handCounter = INIT;
	int deckCounter = INIT;
	
	while (deck[deckCounter].suit == nullSuit) {
		deckCounter++;
	}
	while (hand[handCounter].suit != nullSuit) {
		handCounter++;
	}

	const Face NEW_F = deck[deckCounter].face;
	const Suit NEW_S = deck[deckCounter].suit;

	deck[deckCounter].suit = nullSuit;
	hand[handCounter] = newCard(NEW_F, NEW_S);
}


/* showHands()
 * Parameters:	int - Cards per hand
 * 				int - Number of hands
 * 				Card[] - deck from which to make hands
 * Draws new hands from the deck and prints them as it goes */
void showHands(const int HANDS, const int CARDS, Card hands[HANDS][CARDS]) {
	int counter = INIT;
	for (counter = INIT; counter < HANDS; counter++) {
		printf("Hand #%d:\n", counter + 1); // counter starts at 0
		showCards(hands[counter], CARDS, HANDS);
	}
}


/* showCards()
 * Parameters:	Card [] - array of Cards to display
 * 				int - size of the array
 * 				int - number of Cards to display before carriage return
 * Returns nothing.
 * Traverses array of Cards.
 * Saves current card's suit and value, converts them to strings,
 * 	and prints the card's info.
 * After 'lineBreak' cards, carriage return. */
void showCards(Card CARDS[], const int SIZE, const int BREAK) {
	const int BREAK_NOW = BREAK - 1;
	int counter = INIT;
	Face currFace = INIT;
	Suit currSuit = INIT;

	for (counter = INIT; counter < SIZE; counter++) {
		currFace = CARDS[counter].face;
		currSuit = CARDS[counter].suit;

		// print the current card as long as it isn't of null type
		if (currSuit != nullSuit) {
			printf("%s%s ", STR_FACE[currFace], STR_SUIT[currSuit]);
		}

		// return carriage after printing lineBreak cards
		if ((counter % BREAK) == BREAK_NOW) {
			printf("\n");
		}
	}

	printf("\n");
}


/* shuffle()
 * Parameters:	struct Card [] - cards to be shuffled
 * 				int - number of cards to shuffle
 * Returns nothing.
 * Modifies an array of Cards to be in randomized order.
 * Uses the Fisher-Yates shuffle method of replacing a
 * 	randomly-selected card with a decrementing position
 * 	from the top of the deck. */
void shuffle(Card cards[], const int SIZE) {
	int count = INIT;
	int randPlace = INIT;

	// count down from the top card to second-from-bottom for swapping
	for (count = SIZE - 1; 1 < count; count--) {
		randPlace = rand() % count;
		swapCard(cards, count, randPlace);
	}
}


/* swapCard()
 * Parameters:	struct Card [] - array of cards in which to swap two cards
 * 				int - first index of card to swap
 * 				int - second index of card to swap
 * Returns nothing.
 * Easy method of trading places of two Cards in an array. */
void swapCard(Card deck[], const int SWAP1, const int SWAP2) {
	Card temp = deck[SWAP1];
	deck[SWAP1] = deck[SWAP2];
	deck[SWAP2] = temp;
}
