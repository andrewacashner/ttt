/* Check for runs two out of three, or all three for tic tac toe game 
 * Andrew Cashner, 2015-05-24 
 */

#include <stdio.h>

#define MAXANSWERS 8

static const int answer[8][3] = {
	{0, 1, 2}, /* 0 */
	{0, 3, 6}, /* 1 */
	{0, 4, 8}, /* 2 */
	{1, 4, 7}, /* 3 */
	{2, 4, 6}, /* 4 */
	{2, 5, 8}, /* 5 */
	{3, 4, 5}, /* 6 */
	{6, 7, 8}  /* 7 */
};

static const enum { FALSE, TRUE } boolean;


int checktriple(int a, int b, int c);


int main(void)
{	
	int i;
	int test[7] = { /* Series to be tested */
		0, 1, 0, 4, 8, 2, 5
	};
	int testvalues = 7; /* Num of values to be tested */
	int a, b, c; /* Single test values */
	int found; /* Count number of triples found */
	
	for (i = 0; i < testvalues - 2; ++i) {
		a = test[i];
		b = test[i+1];
		c = test[i+2];
		printf("Checking %d, %d, %d...\n", a, b, c);

		if (checktriple(a, b, c) == TRUE) {
			printf("\nTriple found: %d %d %d\n\n", a, b, c);
			++found;
		}
	}
	printf("\nFound %d %s.\n", found, found > 1 ? "triples" : "triple");

	return(0);
}

int checktriple(int a, int b, int c) 
{
	int i;
	int triple_bool; /* boolean */

	for (i = 0, triple_bool = FALSE; i < MAXANSWERS; ++i) {
		if (answer[i][0] == a &&
		    answer[i][1] == b &&
		    answer[i][2] == c) {
		    	triple_bool = TRUE;
		} 
	}
	return(triple_bool);
}
