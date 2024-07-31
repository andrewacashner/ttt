% ttt.w -- Tic tac toe game in CWEB, Copyright (c) 2015 Andrew A. Cashner
% 2015-05-26

@* Introduction. This is \.{ttt}, a command-line tic-tac-toe game by Andrew A.
Cashner, \today.

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
	
	@<Process command-line options, set game mode@>@;

	printf("%s\n", greeting);
	@<Draw board@>@;

	while (1) {
		@<Get O move, update board@>@;
		@<Check for O win@>@;
		@<Prepare next move@>@;
	}
	gameover:
		@<Gameover routine@>@;
	
	@<Clean up@>@;
	return(0);
}

@ Set mode of game play (easy, medium, hard) based on command-line option.

@<Main variables@>=
enum {EASY, MEDIUM, DIFFICULT} game_mode;

@ @<Process command-line...@>=
if (argc > 1 && argv[1][0] == '-') {
	switch (argv[1][1]) {
		case 'v':
			printf("%s\n", message[VERSION]);
			return(0);
			break;
		case 'h':
			printf("%s\n", message[HELP]);
			return(0);
			break;
		case 'e': 
			game_mode = EASY;
			break;
		case 'm': 
			game_mode = MEDIUM;
			break;
		case 'd':
			game_mode = DIFFICULT;
			break;
		default:
			fprintf(stderr, "%s\n", message[BAD_OPTION]);
			exit(EXIT_FAILURE);
			break;
	}
} else game_mode = DIFFICULT;



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
|triple| is a switching table with the winning triple series.
|duple| is a table of permutations of these triples in which the first two are in
ascending order (to find runs of 2 out of 3).
|duple_range| gives the range of |x| indices to the |duple| array for each
digit, so that if we are search for series beginning with 0, for example, we
only search |duple[duple_range[0][MIN]]| to |duple[duple_range[0][MAX]]|.

@d MAXTRIPLES 8
@d MAXDUPLES 24
@d MIN 0
@d MAX 1

@<Global variables@>=
static const int triple[MAXTRIPLES][3] = {
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

static const int duple[MAXDUPLES][3] = {
	{0,1,2},
	{0,2,1},
	{0,3,6},
	{0,6,3},
	{0,4,8},
	{0,8,4},
	{1,2,0},
	{1,4,7},
	{1,7,4},
	{2,4,6},
	{2,5,8},
	{2,6,4},
	{2,8,5},
	{3,4,5},
	{3,5,4},
	{3,6,0},
	{4,5,3},
	{4,6,6},
	{4,7,1},
	{4,8,0},
	{5,8,2},
	{6,7,8},
	{6,8,7},
	{7,8,6}
};

static const int duple_range[8][2] = {
	{0,5},
	{6,8}, 
	{9,12}, 
	{13,15}, 
	{16,19},
	{20,20},
	{21,22},
	{23,23}
};




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

@* Linked-list utilities.

@ Extract data from linked list of player moves at a particular index.

@p
int getlistdata(square_ptr list_head, int index)
{
	int i;
	square_ptr list = list_head;
	for (i = 0; list != NULL; list = list->next, ++i) {
		if (i == index) {
			return(list->position);
		}
	}
	return(NOTFOUND);
}

@ @<Function prototypes@>=
int getlistdata(square_ptr list_head, int index);

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

@ Free linked-list memory.

@<Clean up@>=
free_list(listOmoves);
free_list(listXmoves);

@ Function to free linked list.

@p
void free_list(square_ptr list)
{
	square_ptr prev = NULL;

	if (list == NULL) 
		return;
	else prev = list;

	while (list->next != NULL) {
		prev = list;
		list = list->next;
		prev = NULL;
		free(prev);
	}
	list = list->next;
	list = NULL;
	free(list);

	return;
}

@ @<Function prototypes@>=
void free_list(square_ptr list_head);



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
		printf("%s\n", message[O_COMMAND_OUT_OF_RANGE]); @+
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
		printf("%s\n", message[SQUARE_OCCUPIED]);
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
	if (three_of_three(listOmoves, total_O_moves) == TRUE) {
		winner = OPLAYER;
		goto gameover;
	}
}

@ Prepare next X move.
How clever we are depends on the setting of |game_mode|.
In |EASY| mode we just pick any free spot according to a list of optimal spots
(first the center, then the corners).
In |MEDIUM| mode first we test to see if we (X) can get a winning triple (that
is, if we have 2 out of 3 of one of the winning series); if not then we pick any
free spot. In this case we know X wins, so we jump to the |gameover| routine.

In |DIFFICULT| mode we first test to see if the {\it other} player (O) can get a
winning triple, and if so we block it. If not, then we do everything as in
|MEDIUM| mode.
We use the function |two_of_three| to do these tests.

Finally, we add |nextXmove| to the list of X moves and update the board.
In |EASY| mode, we test for a winning triple of X moves.
If all the squares are filled, the game is over automatically.


@<Prepare next move@>=

switch (game_mode) {
	case EASY:
		@<Pick any free spot@>@;
		break;
	case MEDIUM:
		if (total_X_moves < 1) {
			@<Pick any free spot@>@;
		} else {
			test = two_of_three(listXmoves, total_X_moves, gameboard_ptr);
			if (test != NOTFOUND) {
				nextXmove = test;
				winner = XPLAYER;
			} else @<Pick any free spot@>@;
		}
		break;
	case DIFFICULT:
		if (total_X_moves < 1) {
			@<Pick any free spot@>@;
		} else {
			test = two_of_three(listXmoves, total_X_moves, gameboard_ptr);
			if (test != NOTFOUND) {
				nextXmove = test;
				winner = XPLAYER;
			} else {
				test = two_of_three(listOmoves, total_O_moves,
				gameboard_ptr);
				if (test != NOTFOUND) {
					nextXmove = test;
				} else @<Pick any free spot@>@;
			}
		}
		break;
}

	
newmove(XPLAYER, nextXmove, gameboard_ptr, charboard_ptr);
@<Draw board@>@;
++squares_filled;
++total_X_moves;
listXmoves = insert_sorted(listXmoves, nextXmove);
printf("X moves: ");
print_movelist(listXmoves);

if (winner == XPLAYER) {
	goto gameover;
}
if (game_mode == EASY && total_X_moves > 2) {
	if (three_of_three(listXmoves, total_X_moves) == TRUE) {
		winner = XPLAYER;
		goto gameover;
	}
}
if (squares_filled > 8) {
	winner = EMPTY;
	goto gameover;
}

@ Choose any available free position from a list arranged with the most optimal
spots (the middle and corners) first.

@<Pick any free spot@>=
for (i = 0; i < total_best_moves; ++i) {
	test = best_moves[i];
	if (gameboard[test] == EMPTY) {
		nextXmove = test;
		break;
	}
}


@* Tests for two and three in a row.
The first function, |two_of_three|, tests for two in a row, and if found and that position is not occupied, return the third member.

@<Global variables@>=
static const enum { NOTFOUND = -10, O_WINS } function_errors;

@ The function checks every permutation of pairs in the list of current player
moves against the relevant range of the |duple| array.

@p
int two_of_three(square_ptr list_head, int list_length, int *gameboard)
{
	square_ptr list = list_head; /* List of player moves */
	int i, j; /* Loop counters for list indices */
	int d; /* Loop counter for |duples| indices */
	int first, second, third; /* Test values at list indices */
	
	for (i = 0; i < list_length - 1; ++i) {
		first = getlistdata(list, i);
		for (j = i + 1; j < list_length; ++j) {
			second = getlistdata(list, j);
			for (d = duple_range[first][MIN]; 
			     d <= duple_range[first][MAX]; ++d) {
				if (second == duple[d][1]) {
					third = duple[d][2];
					if (*(gameboard + third) == EMPTY) {
						return(third);
					}
				}
			}
		}
	}
	return(NOTFOUND);
}


@ @<Function prototypes@>=
int two_of_three(square_ptr list_head, int list_length, int *gameboard);


@* Test for winning triple.
This is like |two_of_three| except it tests three values at a time.

@p
boolean three_of_three(square_ptr list_head, int list_length)
{
	square_ptr list = list_head; /* List of player moves */
	int i, j, k; /* Loop counters for list indices */
	int t; /* Loop counter for triples */
	int a, b, c; /* Test values at list indices */

	for (i = 0; i < list_length - 2; ++i ) {
		a = getlistdata(list, i);
		for (j = i + 1; j < list_length - 1; ++ j) {
			b = getlistdata(list, j);
			for (k = j + 1; k < list_length; ++k) {
				c = getlistdata(list, k);
				for (t = 0; t < MAXTRIPLES; ++t) {
					if (a == triple[t][0] &&
						b == triple[t][1] &&
						c == triple[t][2]) {
							return(TRUE);
					}
				}
			}
		}
	}
	return(FALSE);
}

@ @<Function prototypes@>=
boolean three_of_three(square_ptr list_head, int list_length);


@* Game-over routine.

@<Global variables@>=
static const char *gameover_msg[] = {
@/	"***   DRAW.    ***",
@/	"***  X WINS.   ***",
@/	"***  YOU WIN!  ***",
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
	VERSION,
	HELP,
	BAD_OPTION,
	O_COMMAND_OUT_OF_RANGE,
	O_COMMAND_FAULTY,
	SQUARE_OCCUPIED
} msg_ID;

static const char *message[] = {
	"ttt -- Command-line Tic Tac Toe\n"
	"Version 1 (2015) by Andrew A.  Cashner",

	"ttt -- Command-line Tic Tac Toe\n"
	"Options: -h help, -e easy mode, -m medium mode, -d difficult mode.\n"
	"Computer always plays X, you play O.\n"
	"Select a square on the board by its label, such as 'A1' or 'C3'.",

	"Unrecognized command-line option.\n"
	"Acceptable options: -e -m -h (for easy, medium, and hard modes); "
	"or invoke with no options.",

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


