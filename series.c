/* Check for runs two out of three, or all three for tic tac toe game 
 * Andrew Cashner, 2015-05-24 
 */

#include <stdio.h>
#include <stdlib.h>

static const enum { FALSE, TRUE } boolean;

/* Array of possible 3-in-a-row answers */
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

#define MAXPERMS 22
static const enum { PERM1, PERM2, PERM3, PERM_ANSWER } perm_index;
static const int perms[22][4] = {
	{0,1,2,0},
	{0,2,0,1},
	{0,3,2,1},
	{0,4,2,2},
	{0,6,1,1},
	{1,2,0,0},
	{1,4,2,3},
	{1,7,1,3},
	{2,4,2,4},
	{2,5,2,5},
	{2,6,1,4},
	{2,8,1,5},
	{3,4,2,6},
	{3,5,1,6},
	{3,6,0,1},
	{4,5,0,6},
	{4,6,0,4},
	{4,7,0,3},
	{5,8,0,5},
	{6,7,2,7},
	{6,8,1,7},
	{7,8,7,0}
};

int check_consecutive_triple(int a, int b, int c);


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

		if (check_consecutive_triple(a, b, c) == TRUE) {
			printf("\nTriple found: %d %d %d\n\n", a, b, c);
			++found;
		}
	}
	printf("\nFound %d %s.\n", found, found > 1 ? "triples" : "triple");

	

	return(0);
}

/* Check test array for 3 in a row that match one of answer triples */
int check_consecutive_triple(int a, int b, int c) 
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

