/* Author:	Sean Monroe
 * PID:		1571224
 * Class:	COP4338 U04
 * 
 * Assignment 4 - Poker Player
 * 
 * I hereby certify that this collective work is my own and none of
 * it is the work of any other person or entity.	-SM
 */

/* Give poker.c access to face+suit enums, card+deck structs,
 * and function prototypes. */
#include "cards.h"

/* playPoker()
 * Parameters:	int - number of hands
 * 				int - number of cards in each hand
 * 				Card [][] - array of Card arrays for hands
 * Returns nothing.
 * Calls helper functions from within poker.c to sort hands,
 * 	evaluate winning conditions, break ties, and determine
 * 	the winner. All hands are printed at each stage for
 * 	verification. */
void playPoker(int numHands, int numCards, Card hands[][numCards]) {
	int counter = INIT;

	for (counter = INIT; counter < numHands; counter++) {
		sortHand(hands[counter]);
		showCards(hands[counter], numCards, numCards);
	}
}


/* sortHand()
 * Parameters:	Card [] - hand to be sorted
 * Returns nothing.
 * Uses an expanded but simple insertion sort to order
 * 	cards in increasing value. This function assumes a
 * 	hand size of 5, which is a safe assumption as this
 * 	is found within poker.c, intended for 5 card stud.
 * Fun fact: Wikipedia states this algorithm is generally
 * 	followed by bridge players to sort their hands.
 */
void sortHand(Card hand[]) {
	int handCount = INIT;
	int cardCount = INIT;

	for (handCount = INIT; handCount < CARD_STUD; handCount++) {
		cardCount = handCount;
		Face compOne = hand[cardCount].face;
		Face compTwo = hand[cardCount - 1].face;

		while ((cardCount > INIT) && (compTwo > compOne)) {
			swapCard(hand, cardCount, cardCount - 1);

			cardCount--;
			compOne = hand[cardCount].face;
			compTwo = hand[cardCount - 1].face;
		}
	}
}


/* evalHand()
 */
float evalHand(Card hand[]) {

}


/* tieBreak()
 */
int tieBreak(Card first[], Card second[]) {

}
