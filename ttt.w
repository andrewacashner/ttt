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

@ Error messages.

@<Global variables@>=
static const enum {
	BAD_O_COMMAND
} error_msg;

static const char *error[] = {
	"I don't understand your command."
	"Enter a label like A1 and press [ENTER].",
};
static const char greeting[] = {
	"\nTIC TAC TOE\n"
	"I play X. You play O. You go first.\n"
	"Use one of the labels shown below to say where you will move.\n"
	"\n A1 | A2 | A3 \n-----------\n"
	" B1 | B2 | B3 \n-----------\n" 
	" C1 | C2 | C3\n\n"
	"Let's play!"
};


@ Greeting.

@<Set up first move...@>=
printf("%s\n", greeting);


@ Get user input.

@d MAXLINE 100

@<Main variables@>=
char line[MAXLINE];
int nextOmove;

@ Get O move.

@<Get O move, update board@>=
@<Draw board@>@;
while (1) {
	printf("Your move?\n");
	fgets(line, sizeof(line), stdin);
	if ( 	line[2] != '\n' || 
		line[0] < 'A' || line[0] > 'C' ||
		line[1] < '1' || line[1] > '3' ) {
		printf("%s\n", error[BAD_O_COMMAND]);
		continue;
	} else break;
}

nextOmove = (line[0] - 'A') * 3; /* \.{'A'} is 0, \.{'B'} is 3, \.{'C'} is 6 */
nextOmove += line[1] - '1'; /* \.{'A1'} is $0 + 0$, \.{'B2'} is $3 + 1$ */
newmove(OPLAYER, nextOmove, gameboard_ptr, charboard_ptr);


@* Printing the game board.

@ Switching tables needed to draw the board, and update the drawing.

@<Global variables@>=
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
|gameboard| holds |int| values for each square of the gameboard, which is either
|EMPTY|, |XPLAYER|, or |OPLAYER|.
|charboard| holds the characters to draw the board, and will be updated as new
squares of |gameboard| are filled.

@d CHAR_BOARD_LENGTH 62

@<Main variables@>=
int gameboard[9] = { 0, 0, 0,  0, 0, 0,  0, 0, 0 }; /* Start empty */
char charboard[] = 
	"\n   |   |   \n"
	"-----------\n"
	"   |   |   \n"
	"-----------\n"
	"   |   |   \n\n";
int *gameboard_ptr = gameboard;
char *charboard_ptr = charboard;


@ Switching table with winning series.

@d MAXANSWERS 8
@d NOTFOUND -1
@d MAXPERMS 24

@ These are all the triples that win the game.

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

@ Switching tables created in |main|.
@ Set up switching table of permutations.
@<Populate switching tables@>=

@ Draw the board. We simply print |charboard| to |stdout|.

@<Draw board@>=
printf("%s", charboard);

@* Updating the game board.

@<Function prototypes@>=
void newmove(int player, int square, int *gameboard, char *charboard);

@ The function updates the gameboard with a new move.

@p
void newmove(int player, int square, int *gameboard, char *charboard)
{
	*(gameboard + square) = player;
	*(charboard + charboard_index[square]) = playerchar[player];
	@<Draw board@>@;
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
