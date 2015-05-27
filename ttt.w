% ttt.w -- Tic tac toe game in CWEB, Copyright (c) 2015 Andrew A. Cashner
% 2015-05-26

@* Introduction. This is \.{ttt}, a command-line tic-tac-toe game.
% TODO more

@p
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

@<Global variables@>@;
typedef enum {FALSE, TRUE} boolean;

@<Function prototypes@>@;

int main(int argc, char *argv[])
{
	@<Main variables@>@;
	boolean gameover;
	gameover = FALSE;

	@<Process command-line options@>@;
	@<Populate switching tables@>@;
	
	@<Set up first move and draw board@>@;

	while (gameover == FALSE) {
		@<Get O move, update board@>@;
		@<Process last move@>@;
		@<Prepare next move@>@;
	}
	@<Gameover routine@>@;
	return(0);
}

@* Process command-line options.
@<Process command-line options@>=

@ First move.
@<Set up first move...@>=

@ O move.
@<Get O move, update board@>=

@* Printing the game board.

@d CHAR_BOARD_LENGTH 62

@ Switching tables needed to draw the board, and update the drawing.

@<Global variables@>=
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

@ We set up the table within |main|.

@<Main variables@>=
int gameboard[9] = { 0, 0, 0,  0, 0, 0,  0, 0, 0 }; /* Start empty */
char charboard[CHAR_BOARD_LENGTH];
int *gameboard_ptr = gameboard;
char *charboard_ptr = charboard;

@ We make a local copy of the constant table set up in global variables.

@<Populate switching tables@>=
strcpy(charboard, blankboard);

@* Updating the game board.

@<Function prototypes@>=
void newmove(int player, int square, int *gameboard, char *charboard);

@ The function updates the gameboard with a new move.

@p
void newmove(int player, int square, int *gameboard, char *charboard)
{
	*(gameboard + square) = player;
	*(charboard + charboard_index[square]) = playerchar[player];
	printf("%s%s", charboard, divider);
	return;
}


@ Process the X and O moves of turn just completed.

@<Process last move@>=
	@<Test for O win 3/3@>@;
	@<Update X positions@>@;
	@<Update O positions@>@;
	@<Eliminate X wins@>@;
	@<Eliminate O wins@>@;

@ TODO
@<Test for O win 3/3@>=

@ TODO
@<Update O positions@>=

@ TODO
@<Eliminate X wins@>=

@ TODO
@<Eliminate O wins@>=

@ Prepare the next X move.

@<Prepare next move@>=
	@<Test for X runs 2/3@>@;
	@<Test for O runs 2/3@>@; 
	@<Choose free spot@>@;

@ Test for two in a row, and if found, return the third member.

@d MAXANSWERS 8
@d NOTFOUND -1
@d MAXPERMS 24

@ Switching table with winning series.

@<Global variables@>=
static const int answer[8][3] = {
	{0, 1, 2}, 
	{0, 3, 6}, 
	{0, 4, 8}, 
	{1, 4, 7}, 
	{2, 4, 6}, 
	{2, 5, 8}, 
	{3, 4, 5}, 
	{6, 7, 8} 
};

@ Function to test two in a row.

@<Function prototypes@>=
int twoofthree(int test[], int test_array_length, int perms[][3]);

@ TODO
@<Test for X runs 2/3@>=

@ TODO
@<Test for O runs 2/3@>=

@ TODO
@<Choose free spot@>=

@* Dummy move. % TODO temporary only

@<Update X positions@>=
newmove(XPLAYER, A1, gameboard_ptr, charboard_ptr);
gameover = TRUE;

@* Game-over routine.
@<Gameover routine@>=
