/* Author:	Sean Monroe
 * PID:		1571224
 * Class:	COP4338 U04
 * 
 * Assignment 4 - Poker Player
 * 
 * I hereby certify that this collective work is my own and none of
 * it is the work of any other person or entity.	-SM
 */

/* Used by both .c source files to print to console */
#include <stdio.h>

/* Used by dealer.c for atoi()
 * Used by cards.c for random numbers */
#include <stdlib.h>

/* string.h used to convert integers to strings for printing */
#include <string.h>

/* time.h used for seeding the rand() function used in shuffling */
#include <time.h>

/* Used by both .c source files to initialize integers */
#define INIT 0

/* Used by both .c files for properties of deck and hands */
#define CARD_STUD 5
#define HAND_MIN 1
#define HAND_MAX 7
#define DECK_SIZE 52
#define NUM_SUITS 4
#define NUM_FACES 13
#define EMPTY_STRING "  "

/* Face cards identified by the program, others used as integer values */
typedef enum Face {
	nullFace, ace, deuce, trey, boat,
	nickel, sax, mullet, snowman, niner,
	dime, jack, queen, king
} Face;

/* nullSuit type used to indicate an 'empty card slot' */
typedef enum Suit {
	nullSuit, hearts, diamonds, clubs, spades
} Suit;

/* Basic card structure indicating face value and suit */
typedef struct Card {
	enum Face face;
	enum Suit suit;
} Card;

/* Defined in main.c */
void error();
void getCommands(int, char *[], int []);
void seed();

/* Defined in cards.c */
Card newCard(Face, Suit);
void newHand(Card [], Card [], int);
void draw(Card [], Card []);
void newDeck(Card []);
void showCards(Card [], int, int);
void shuffle(Card [], int);
void swapCard(Card[], int, int);
void makeHands(int M, int N, Card [], Card [M][N]);
void showHands(int M, int N, Card[M][N]);

/* Defined in poker.c */
void playPoker(int M, int N, Card[M][N]);
void sortHand(Card []);
float evalHand(Card []);
int tieBreak(Card [], Card []);
