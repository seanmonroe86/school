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

/* Used by both .c source files to print to console */
#include <stdio.h>

/* Used by dealer.c for atoi()
 * Used by cards.c for rand() and srand() */
#include <stdlib.h>

/* Used by both .c source files to initialize integers */
#define INIT 0

/* Used by both .c files for properties of deck and hands */
#define CARD_MIN 1
#define CARD_MAX 13
#define HAND_MIN 1
#define HAND_MAX 13
#define DECK_SIZE 52
#define NUM_SUITS 4
#define NUM_VALS 13

/* nullSuit type used to indicate an 'empty card slot' */
enum Suit {
	nullSuit, hearts, diamonds, clubs, spades
};

/* face cards used by the program, the others are placeholders */
enum Face {
	nullFace, ace, two, three, four,
	five, six, seven, eight, nine,
	ten, jack, queen, king
};

struct Card {
	int val;
	enum Suit suit;
};

/* most are used by only cards.c.
 * dealer.c uses newDeck(), newHand(), showCards(), and shuffle() */
struct Card newCard(enum Suit, int);
void draw(struct Card [], struct Card []);
char getSuit(enum Suit);
void getVal(char [], enum Face);
void newDeck(struct Card []);
void newHand(struct Card [], struct Card [], int);
void showCards(struct Card [], int, int);
void shuffle(struct Card [], int);
int getRand(int);
void swapCard(struct Card[], int, int);
