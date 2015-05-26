/* Check for runs two out of three, or all three for tic tac toe game 
 * Andrew Cashner, 2015-05-24 
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } boolean;

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

#define NOTFOUND -1
#define MAXPERMS 24

int twoofthree(int test[], int test_array_length, int perms[][3]);
int check_consecutive_triple(int a, int b, int c);


int main(void)
{	
	int i, j; /* Loop counters */
	int a, b, c; /* Single test values */
	int nextmove;

	int test[3] = { /* Series to be tested */
		0, 3, 4
	};
	const int test_array_length = 3; /* Num of values to be tested */

	int perms[24][3]; /* Permutations of answer triples where [0] < [1] */

	/* Build table of permutations */
	for (i = 0, j = 0; i < MAXANSWERS; ++i) {	
		a = answer[i][0];
		b = answer[i][1];
		c = answer[i][2];
		perms[j][0] = a;
		perms[j][1] = b;
		perms[j][2] = c;
		++j;
		perms[j][0] = a;
		perms[j][1] = c;
		perms[j][2] = b;
		++j;
		perms[j][0] = b;
		perms[j][1] = c;
		perms[j][2] = a;
		++j;
	}

	nextmove = twoofthree(test, test_array_length, perms);
	if (nextmove != NOTFOUND) {
		printf("Next move is %d\n", nextmove);
	} else {
		printf("No pair found.\n");
	}

	

	return(0);
}

int twoofthree(int test[], int test_array_length, int perms[][3])
{
	int i, p;

	for (i = 0; i < test_array_length; ++i) { /* Test values */
		for (p = 0; p < MAXPERMS; ++p) { /* 2/3 perms x indices */
			if (test[i] == perms[p][0] &&
			    test[i + 1] == perms[p][1]) {
				return(perms[p][2]);
			} 
		}
	}
	return(NOTFOUND);
}
				
