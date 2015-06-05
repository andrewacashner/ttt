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
	boolean bool_gameover;
	bool_gameover = FALSE;

	@<Populate switching tables@>@;
	
	printf("%s\n", greeting);
	@<Draw board@>@;

	while (bool_gameover == FALSE) {
		@<Get O move, update board@>@;
		@<Check for O win@>@;
		@<Prepare next move@>@;
	}
	@<Gameover routine@>@;
	return(0);
}



@* Printing the game board.
Set up switching tables needed to draw the board, and update the drawing.

@<Global variables@>=
static const int charboard_index[] = { 
@/	  2, 6, 10,
@/	 26, 30, 34,
@/	 50, 54, 58 
@/
};
	 
static const enum {
@/	A1, A2, A3, 
@/	B1, B2, B3,
@/	C1, C2, C3 } squareID;

static const char *square_label[] = {
@/	"A1", "A2", "A3",
@/	"B1", "B2", "B3",
@/	"C1", "C2", "C3" 
@/
};
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
@/	"\n   |   |   \n"
@/	"-----------\n" 
@/	"   |   |   \n" 
@/	"-----------\n" 
@/	"   |   |   \n\n";
int *gameboard_ptr = gameboard;
char *charboard_ptr = charboard;

@ Draw the board. We simply print |charboard| to |stdout|.

@<Draw board@>=
printf("%s", charboard);


@* Test for winning combinations.
Set up a switching table with the winning triple series.
Set up a table of permutations of these triples in which the first two are in
ascending order (to find runs of 2/3).

@d MAXANSWERS 8

@<Global variables@>=
static const int answer[8][3] = {
@/	{0, 1, 2}, 
@/	{0, 3, 6}, 
@/	{0, 4, 8}, 
@/	{1, 4, 7}, 
@/	{2, 4, 6}, 
@/	{2, 5, 8}, 
@/	{3, 4, 5}, 
@/	{6, 7, 8} 
@/
};

@ Set up switching table of permutations; we have to do this in |main|.

@d MAXPERMS 24

@<Main variables@>=
int perms[MAXPERMS][3]; /* Permutations of answer triples where [0] < [1] */
int a, b, c; /* Single test values */
int j; /* Loop counter */

@ @<Populate switching tables@>=

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

@* Create linked lists of each player's current board positions.
We will insert new moves into list of moves for a particular player, keeping
the list sorted in ascending order.

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
		if (new_position < (list->next)->position) {
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


@* Updating the game board.

@p
int newmove(int player, int position, int *gameboard, char *charboard) 
{
	*(gameboard + position) = player;
	*(charboard + charboard_index[position]) = playerchar[player];
	return(0); 
}

@ @<Function prototypes@>=
int newmove(int player, int square, int *gameboard, char *charboard);

@* Get user input for O move.

@d MAXLINE 100

@<Main variables@>=
char input_line[MAXLINE];
int nextOmove;
int squares_filled; /* Total squares filled on board */
square_ptr listOmoves = NULL;
int total_O_moves = 0;
int total_X_moves = 0; /* Counter per player of moves on board */
int winner = EMPTY;

@ Check O command for validity and set |nextOmove|.
The command is entered in the form \.{A1\\n}.
\.{'A'} is 0, \.{'B'} is 3, \.{'C'} is 6.
\.{'A1'} is $0 + 0$, \.{'B2'} is $3 + 1$.

@<Get O move, update board@>=
while (1) {  
@#
	printf("\nYour move?\n"); 
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
	if (gameboard[nextOmove] == EMPTY) {
		newmove(OPLAYER, nextOmove, gameboard_ptr, charboard_ptr);
		@<Draw board@>@;
		++squares_filled;
		++total_O_moves;
		listOmoves = insert_sorted(listOmoves, nextOmove);
		printf("O moves: ");
		print_movelist(listOmoves);
		break;
	} else {
		printf("%s\n", error[SQUARE_OCCUPIED]);
	}
@#
}

@* Process the X and O moves of turn just completed, and prepare next X move.

@<Main variables@>=
int best_moves[] = {B2, A1, A3, C1, C3, A2, B1, B3, C2};
int total_best_moves = 8;
int i;
square_ptr listXmoves = NULL;
int nextXmove;
int test;


@ See if O wins by having three in a row.

@<Check for O win@>=
if (total_O_moves > 2) {
	test = two_of_three(OPLAYER, listOmoves, perms, gameboard_ptr);
	if (test == O_WINS) {
		bool_gameover = TRUE;
		winner = OPLAYER;
	} 
}

@ Prepare next move.
Test O values for 3/3; if so, O wins.
If not, check if X has 2/3; if so, move to missing 3rd spot to win.
If there is no 2/3 run for X, check if O has 2/3 and move to third spot to block
O from winning.
If there is no 2/3 run for O or X, then choose any favored free spot from
|best_moves|.
Finally, add |nextXmove| to the list of X moves and update the board.
If all the squares are filled, the game is over automatically.

@<Prepare next move@>=

if (total_X_moves < 1) {
	@<Pick any free spot@>@;
} else {
	test = two_of_three(XPLAYER, listXmoves, perms, gameboard_ptr);

	if (test != NOTFOUND) {
		printf("I found a matching triple of X positions.\n");
		nextXmove = test;
		bool_gameover = TRUE;
		winner = XPLAYER;
	} else {
		test = two_of_three(XPLAYER, listOmoves, perms, gameboard_ptr);
		if (test != NOTFOUND) {
			printf("I found a matching duple of O positions and I will block the win.\n");
			nextXmove = test;
		} else {
			@<Pick any free spot@>@;
		}
	}
}

newmove(XPLAYER, nextXmove, gameboard_ptr, charboard_ptr);
@<Draw board@>@;
++squares_filled;
++total_X_moves;
listXmoves = insert_sorted(listXmoves, nextXmove);
printf("X moves: ");
print_movelist(listXmoves);

if (squares_filled > 8) {
	bool_gameover = TRUE;  
	winner = EMPTY;
}

@ Choose any available free position from a list arranged with the most optimal
spots (the middle and corners) first.

@<Pick any free spot@>=
printf("I found no matches; I will pick any good free spot.\n");
for (i = 0; i < total_best_moves; ++i) {
	test = best_moves[i];
	if (gameboard[test] == EMPTY) {
		nextXmove = test;
		break;
	}
}


@* Function to test for two in a row, and if found, return the third member.

@<Global variables@>=
static const enum { NOTFOUND = -10, O_WINS } function_errors;

@ If the player tested is |OPLAYER| then, the function also checks the
|listOmoves| to see if |OPLAYER| has the third member also, meaning that O wins.
In that case the function returns |O_WINS|.
If no series of two is found, it returns |NOTFOUND|.

@p
int two_of_three(int player, square_ptr head, int perms[][3], int *gameboard)
{
	int i, p;
	int third; /* Third member of triple when first two are found */
	square_ptr list;

	if (head == NULL) {
		return(NOTFOUND);
	} else {
		list = head;
	}

	for (i = 0; list != NULL; list = list->next, ++i) { /* Test values */
		for (p = 0; p < MAXPERMS; ++p) { /* $x$ indices of perms*/
			if (list->position == perms[p][0]) {
				if (list->next != NULL 
				&& (list->next)->position == perms[p][1]) {
					third = perms[p][2];
					@<Test this permutation@>@;
				}
			}
		}
	}
	return(NOTFOUND);
}

@ If we find a pair of the player's board positions that matches one of the
winning permutations, then we test the permutation.
If the player is |OPLAYER| then we only want to know if the third position is
already occupied by O, because in that case O wins the game.
If the player is |XPLAYER|, then the third position is the next X move if it is
empty.

@<Test this permutation@>=
if (player == OPLAYER) {
	if (*(gameboard + third) == OPLAYER) {
		return(O_WINS);
	} else {
		continue;
	}
} else {
	if (*(gameboard + third) == EMPTY) {
		return(third);
	} else {
		continue; /* Next |p| */
	}
} 

@ @<Function prototypes@>=
int two_of_three(int player, square_ptr head, int perms[][3], int *gameboard);


@ Print current list of moves (for testing purposes only).

@p
void print_movelist(square_ptr list)
{
	for ( ; list != NULL; list = list->next) {
		printf("%s ", square_label[list->position]);
	}
	printf("\n");
	return;
}

@ @<Function prototypes@>=
void print_movelist(square_ptr list);

@* Game-over routine.

@<Global variables@>=
static const char *gameover_msg[] = {
@/	"***   DRAW.    ***",
@/	"***  X WINS.   ***",
@/	"***  O WINS.   ***",
@/	"*** Game over! ***"
@/ 
};

static const enum {
@/ 	MSG_DRAW,
@/	MSG_X_WINS,
@/	MSG_O_WINS,
@/	MSG_GAMEOVER
} gameover_msg_label;


@ |winner| will by |EMPTY|, |XPLAYER|, or |OPLAYER|; we can use these as indices
to |gameover_msg|.

@<Gameover routine@>=
printf("\n%s\n", gameover_msg[MSG_GAMEOVER]);		
printf("%s\n\n", gameover_msg[winner]);

@* Error messages.

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


