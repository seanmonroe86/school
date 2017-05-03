/* Author:	Sean Monroe
 * PID:		1571224
 * Class:	COP4338 U04
 * 
 * Assignment 2 - Deriving Mathematical Constant 'e'
 * This program will calculate e using the Taylor Series
 * 1 / n!, n = 0 -> inf. It will be handled by a do-while
 * loop that will end when (1 / n!) is less than machine
 * epsilon. The calculated value will be printed alongside
 * the math.h constant M_E, as well as the number of loops
 * needed to have reached the tenth decimal place.
 *
 * I hereby certify that this collective work is my own and
 * none of it is the work of any other person or entity.
 * 
 * -SM	*/
#include <stdio.h>
#include <math.h>

#define NOERROR 0
#define INITIALIZED 1.0
#define NUMERATOR 1.0
#define TENSIGS 0.000000001
#define NOTFOUND 0

double getE();
void output(double);
int checkTenth(double);

/* main()
 * No parameters
 * Returns int - error code
 * Calls helper functions	*/
int main() {

	double e = getE();
	output(e);

	return NOERROR;
}


/* getE()
 * No parameters
 * Returns double - calculated value of e
 * Prints to console.
 * Saves initial state of current calculated value,
 * 	adds a new term, compares the sum to saved state.
 * 	Leaves loop when equal - machine epsilon reached.
 * 	When 10th decimal place reached, counter value
 * 	printed. */
double getE() {

	double eFormer = INITIALIZED;
	double eLatter = INITIALIZED;
	double reciprocal = INITIALIZED;
	long int accumulator = INITIALIZED;
	int loopCounter = INITIALIZED;
	int significance = NOTFOUND;

	do {
		eFormer = eLatter;

		// Adds 1.0 / loopCounter! to eLatter
		accumulator *= loopCounter;
		reciprocal = (NUMERATOR / accumulator);
		eLatter += reciprocal;

		// If current term just became smaller than 10^-9, mark it
		if ((reciprocal <= TENSIGS) && (significance == NOTFOUND)) {
			significance = loopCounter;
		}

		loopCounter++;
	} while (eFormer != eLatter);

	/* Due to being unable to return more than one
	 * value *cough python cough*, and finding it poor
	 * form to call many print functions from within a
	 * calculation function, only the term that reaches
	 * the 10th significant digit will be printed here,
	 * leaving the calculated e to be printed in the
	 * actual output function. */
	printf("It took %d terms to ", significance);
	printf("reach ten significant digits.\n");

	return eLatter; // eFormer == eLatter, doesn't matter which
}



/* output()
 * Input double - calculated e
 * Returns none
 * Prints to console - calculated e, M_E, and counter value */
void output(double out) {

	printf("Calculated e: %.20f\n", out);
	printf("Expected M_E: %.20f\n", M_E);

}
