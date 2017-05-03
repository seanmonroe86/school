/* Author:	Sean Monroe
 * PID:		1571224
 * Class:	COP4338 U04
 * 
 * Assignment 1 - Temperature Conversion Table
 * This program will ask the user for an integer. It will then print
 * a table of temperature conversions using the input as the step
 * amount between each row.
 *
 * I hereby certify that this collective work is my own and none of
 * it is the work of any other person or entity.	-SM
 */

#include <stdio.h>


#define LOWER	-20.0
#define UPPER	280.0
#define NOERRORS	0


int getInput();
void printColumnNames();
void printTemps(int);
float toCelsius(float);
float toFahrenheit(float);


/* Query for input, print columns, print data.
 * Contains only function calls to other operations. */
int main() {
	int tempStep = getInput();

	printColumnNames();

	printTemps(tempStep);

	return NOERRORS;
}



/* Query user for a character. Continuously query and validate
 * input until a character between '1' and '9' occurs.
 * Prints to console. */
int getInput() {
	int input = 0;
	int askAgain = 1;
	while (askAgain) {
		printf("Enter a value to step between each row.\n");
		printf("'n' must be an integer between 1 and 9.\n");
		printf("Only the first digit will be used.\nn: ");
		
		input = getchar();

		askAgain = ((input < '1') || (input > '9'));
		if (askAgain) {
			printf("\nImproper value entered. Please...\n");
		}
	}

	/* Adjust the input ASCII value to the true integer value.
	 * '0' - '0' = 0; 'n' - '0' = n, 0 > n > 10 */
	return input - '0';
}



/* Prints the very top of the table with the names of the columns.
 * Prints to console. */
void printColumnNames() {
	printf("Fahrenheit   Celsius         Celsius   Fahrenheit\n");
	printf("-------------------------------------------------\n");
}



/* Prints the remaining calculations, taking only the user-inputted step.
 * Prints to console. */
void printTemps(int step) {
	float counter = 0.0;
	for (counter = LOWER; counter <= UPPER; counter = counter + step) {
		printf("%10.1f%10.1f", counter, toCelsius(counter));
		printf("%16.1f%13.1f\n", counter, toFahrenheit(counter));
	}
}



/* Convert Fahrenheit value to Celsius
 * Parameter: float - Fahrenheit value to be converted.
 * Return: float - calculated Celsius value. */
float toCelsius(float fahrenheit) {
	return (5.0 / 9.0) * (fahrenheit - 32);
}



/* Convert Celsius value to Fahrenheit
 * Parameter: float - Celsius value to be converted.
 * Return: float - calculated Fahrenheit value. */
float toFahrenheit(float celsius) {
	return (celsius * (9.0 / 5.0)) + 32.0;
}
