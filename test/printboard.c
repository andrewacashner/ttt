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

static const char divider[] = 
	"************\n";

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


void newmove(int player, int square, int *gameboard, char *charboard);

int main(void)
{
	int gameboard[9] = { 0, 0, 0,  0, 0, 0,  0, 0, 0 }; /* Start empty */
	char charboard[CHAR_BOARD_LENGTH];
	int *gameboard_ptr = gameboard;
	char *charboard_ptr = charboard;

	strcpy(charboard, blankboard);

	newmove(XPLAYER, A1, gameboard_ptr, charboard_ptr);
	newmove(OPLAYER, B3, gameboard_ptr, charboard_ptr);
	newmove(XPLAYER, C1, gameboard_ptr, charboard_ptr);
	
	return(0);
}

void newmove(int player, int square, int *gameboard, char *charboard)
{
	*(gameboard + square) = player;
	*(charboard + charboard_index[square]) = playerchar[player];
	printf("%s%s", charboard, divider);
	return;
}

