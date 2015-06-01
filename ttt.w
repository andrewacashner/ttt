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



@ Process command-line options.
@<Process command-line options@>=

@ Get user input for O move.

@d MAXLINE 100

@<Main variables@>=
char input_line[MAXLINE];
int nextOmove;
int squares_filled; /* Total squares filled on board */

@ Check O command for validity and set |nextOmove|.
The command is entered in the form \.{A1\\n}.
\.{'A'} is 0, \.{'B'} is 3, \.{'C'} is 6.
\.{'A1'} is $0 + 0$, \.{'B2'} is $3 + 1$.

@<Get O move, update board@>=
while (1) {  
@#
	printf("Your move?\n"); 
	fgets(input_line, sizeof(input_line), stdin); 
@#
	if (input_line[2] != '\n' ||
	    input_line[0] < 'A' || input_line[0] > 'C' ||
	    input_line[1] < '1' || input_line[1] > '3' ) {  
		printf("%s\n", error[O_COMMAND_OUT_OF_RANGE]); @+
		continue;
	} 
@#
	nextOmove = (input_line[0] - 'A') * 3;
	nextOmove += input_line[1] - '1'; 
	if (newmove(OPLAYER, nextOmove, gameboard_ptr, charboard_ptr) !=
		OCCUPIED) {
		++squares_filled;
		listOmoves = insert_sorted(listOmoves, newOmove);
		break;
	} else {
		printf("%s\n", error[SQUARE_OCCUPIED]);
	}
@#
}

@ Insert new moves into list of moves for a particular player, keeping list
sorted in ascending order.

@<Global variables@>=
typedef struct square *square_ptr;
typedef struct square {
	int position;
	square_ptr next;
} square;

@ Function to insert items into linked list.

@p
square_ptr insert_sorted(square_ptr head, int new_position)
{
	square_ptr list;
	square_ptr new_square = malloc(sizeof(square_ptr));
	new_square->position = new_position;
	new_square->next = NULL;

	/* Create new list if there is none */
	if (head == NULL) {
		list = new_square;
		return(list);
	} else {
		list = head;
	}

	/* If new position is less, put at head of list and return head */
	if (new_position < list->position) {
		new_square->next = list;
		return(new_square);
	}

	/* Loop through to find mid-list insertion point */
	while (list->next != NULL) {
		if (new_position < (list->next)->data) {
			/* Insert the node mid-list, here */
			new_square->next = list->next;
			list->next = new_square;
			return(head);
		} else { 
			list = list->next;
		}
	}

	/* If node is greatest of all, add it to end of list */
	list->next = new_square;
	new_square->next = NULL;

	/* Return head of list */
	return(head);
}

@ @<Function prototypes@>=
square_ptr insert_sorted(square_ptr head, int new_position);

@* Printing the game board.

@ Set up switching tables needed to draw the board, and update the drawing.

@ @<Global variables@>=
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

@ @<Main variables@>=
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
These are all the triples that win the game.

@d MAXANSWERS 8
@d NOTFOUND -1
@d MAXPERMS 24

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

@d OCCUPIED -10

@p
int newmove(int player, int square, int *gameboard, char *charboard)
{
	if (*(gameboard + square) != EMPTY) {
		return(OCCUPIED);
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
	if (squares_filled > 8) {
		gameover = TRUE;  
	}

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
int best_moves[] = {B2, A1, A3, C1, C3, A2, B1, B3, C2};
int total_best_moves = 8;
int i;

@ Loop through list of optimal squares and select one that is not occupied.

@<Choose free spot@>=
for (i = 0; i < total_best_moves; ++i) {
	if (newmove(XPLAYER, best_moves[i], gameboard_ptr, charboard_ptr) !=
	OCCUPIED)
		break;
}
++squares_filled;

@* Game-over routine.
@<Gameover routine@>=
printf("Game over!\n");


@ Error messages.

@<Global variables@>=
static const enum {
	O_COMMAND_OUT_OF_RANGE,
	O_COMMAND_FAULTY,
	SQUARE_OCCUPIED
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


