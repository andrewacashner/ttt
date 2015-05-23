/* Print tic-tac-toe game board */

#include <stdio.h>
#include <string.h>

#define CHAR_BOARD_LENGTH 62

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

static const enum { EMPTY, XPLAYER, OPLAYER } playerID;
static const char playerchar[] = {' ', 'X', 'O'};


void printboard(int gameboard[]);


int main(void)
{
	int gameboard[9] = { 0, 0, 0,  0, 0, 0,  0, 0, 0 }; /* Start empty */

	gameboard[A1] = XPLAYER;
	gameboard[B3] = OPLAYER;
	gameboard[C1] = XPLAYER;

	printboard(gameboard);

	return(0);
}


/* Print the game board: 
 * Copy the blank board and substitute X or O for spaces wherever
 * squares are filled in gameboard[] 
 */
void printboard(int gameboard[])
{
	int i;
	int currentsquare, currentplayer;
	char charboard[CHAR_BOARD_LENGTH];
	strcpy(charboard, blankboard);
	
	for (i= 0; i < 9; ++i) { 
		currentsquare = charboard_index[i];
		currentplayer = gameboard[i];
		charboard[currentsquare] = playerchar[currentplayer];
 	} 

	printf("%s", charboard);
	return;
}
