/* Print tic-tac-toe game board */

#include <stdio.h>
#include <string.h>

#define CHARBOARDLENGTH 62

static const char blankboard[] = 
	"\n   |   |   \n"
	"-----------\n"
	"   |   |   \n"
	"-----------\n"
	"   |   |   \n\n";

static const int charboard_index[] = 
	{ 2, 6, 10,
	 26, 30, 34,
	 50, 54, 58 };
	 
static const enum {
	A1, A2, A3, 
	B1, B2, B3,
	C1, C2, C3 } squareID;

static const enum { XPLAYER, OPLAYER, EMPTY } playerID;
static const char playerchar[] = {'X', 'O', ' '};

typedef struct {
	int square; /* A1--C3 (i.e., 0--8) */
	int player; /* XPLAYER or OPLAYER */
} boardsquare;


void printboard(boardsquare gameboard[], char charboard[]);


int main(void)
{
	int i;
	char charboard[CHARBOARDLENGTH];
	boardsquare gameboard[9];
	
	/* Initialize empty gameboard */
	for (i = 0; i < 9; ++i) {
		gameboard[i].square = EMPTY;
		gameboard[i].player = EMPTY; 
	}
	/* Initialize blank charboard */
	strcpy(charboard, blankboard);

	gameboard[0].square = A2;
	gameboard[0].player = XPLAYER;
	gameboard[1].square = B3;
	gameboard[1].player = OPLAYER;

	printboard(gameboard, charboard);

	return(0);
}




void printboard(boardsquare gameboard[], char charboard[])
{
	int i;
	int currentsquare;
	
	for (i= 0; i < 9; ++i) { 
		if (gameboard[i].square == EMPTY) break;
		currentsquare = charboard_index[gameboard[i].square];
		charboard[currentsquare] = playerchar[gameboard[i].player];
 	} 

	printf("%s", charboard);
	return;
}
