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
	
	printf("%s\n", greeting);
	@<Draw board@>@;

	while (gameover == FALSE) {
		@<Get O move, update board@>@;
		@<Process last move@>@;
		@<Prepare next move@>@;
	}
	@<Gameover routine@>@;
	return(0);
}



@ Error messages.

@<Global variables@>=
static const enum {
	O_COMMAND_OUT_OF_RANGE,
	O_COMMAND_FAULTY,
	SQUARE_NOT_EMPTY
} error_msg;

static const char *error[] = {
	"That square is not on the board. "
		"Enter A1, A2, A3, B1, B2, B3, C1, C2, or C3.",

	"I don't understand your command. "
		"Enter a label like A1 and press [ENTER].",

	"That square is already taken. Choose another."
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


@ Process command-line options.
@<Process command-line options@>=

@ Get user input for O move.

@d MAXLINE 100

@<Main variables@>=
char line[MAXLINE];
int nextOmove;

@ Check O command for validity and set |nextOmove|.
The command is entered in the form \.{A1\\n}.
\.{'A'} is 0, \.{'B'} is 3, \.{'C'} is 6.
\.{'A1'} is $0 + 0$, \.{'B2'} is $3 + 1$.

@<Get O move, update board@>=
while (1) {
	printf("Your move?\n");
	fgets(line, sizeof(line), stdin);
	if (line[2] != '\n' || 
	    line[0] < 'A' || line[0] > 'C' ||
	    line[1] < '1' || line[1] > '3' ) {
		printf("%s\n", error[O_COMMAND_OUT_OF_RANGE]);
		continue;
	}
	nextOmove = (line[0] - 'A') * 3;
	nextOmove += line[1] - '1'; 
	if (newmove(OPLAYER, nextOmove, gameboard_ptr, charboard_ptr) ==
	NOTEMPTY) {
		printf("%s\n", error[SQUARE_NOT_EMPTY]);
	} else break;
}


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
int newmove(int player, int square, int *gameboard, char *charboard);

@ The function updates the gameboard with a new move.

@d NOTEMPTY -10

@p
int newmove(int player, int square, int *gameboard, char *charboard)
{
	if (*(gameboard + square) != EMPTY) {
		return(NOTEMPTY);
	}
	*(gameboard + square) = player;
	*(charboard + charboard_index[square]) = playerchar[player];
	@<Draw board@>@;
	return(0);
}


@ Process the X and O moves of turn just completed.

@<Process last move@>=
	@<Test for win 3/3@>@;
	@<Update X positions@>@;
	@<Update O positions@>@;
	@<Eliminate X wins@>@;
	@<Eliminate O wins@>@;

@ TODO
@<Test for win 3/3@>=
/* Test X values for 3/3 */
/* Test O values for 3/3 */

@ Update X positions.

@<Update X positions@>=
/*  gameover = TRUE;   TODO temporary */


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

@ Move X to any optimal square.

@<Main variables@>=
int best_moves[] = {B2, A1, A3, C1, C3};
int total_best_moves = 5;
int i;

@ Loop through list of optimal squares and select one that is not occupied.

@<Choose free spot@>=
for (i = 0; i < total_best_moves; ++i) {
	if (newmove(XPLAYER, best_moves[i], gameboard_ptr, charboard_ptr) !=
	NOTEMPTY)
		break;
}

@* Game-over routine.
@<Gameover routine@>=
printf("Game over!\n");
