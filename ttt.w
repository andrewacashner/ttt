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

	@<Process command-line options@>@;
	@<Populate switching tables@>@;
	
	printf("%s\n", greeting);
	@<Draw board@>@;

	while (bool_gameover == FALSE) {
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
square_ptr listOmoves = NULL;
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
	if (newmove(OPLAYER, nextOmove, gameboard_ptr, charboard_ptr) !=
		OCCUPIED) {
		++squares_filled;
		listOmoves = insert_sorted(listOmoves, nextOmove);
		printf("O moves: ");
		print_movelist(listOmoves);
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

static const char *square_label[] = {
	"A1", "A2", "A3",
	"B1", "B2", "B3",
	"C1", "C2", "C3" };

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


@* Process the X and O moves of turn just completed, and prepare next X move.

@<Main variables@>=
int best_moves[] = {B2, A1, A3, C1, C3, A2, B1, B3, C2};
int total_best_moves = 8;
int i;
square_ptr listXmoves = NULL;
int nextXmove;
boolean bool_next_move_found = FALSE;


@ @<Process last move@>=
/* Test O values for 3/3 */
printf("Checking for O win...\n");
if (check_triple(listOmoves) == TRUE) {
	bool_gameover = TRUE;
	winner = OPLAYER;
}

@ Prepare next move.
Loop through list of optimal squares and select one that is not occupied.

@<Prepare next move@>=
/* Check if O has 2/3; if so, move to missing 3rd spot */
nextXmove = twoofthree(listOmoves, perms);

/* If there is no 2/3 run for O, check if X has 2/3 and move to third spot to win */
if (nextXmove == ERROR) {
	nextXmove = twoofthree(listXmoves, perms);
} else {
	bool_next_move_found = TRUE;
	bool_gameover = TRUE;
	winner = XPLAYER;
}

/* If there is no 2/3 run for O or X, then choose any favored free spot from
 * |best_moves| */
 if (nextXmove == ERROR) {
	for (i = 0; i < total_best_moves; ++i) {
		nextXmove = best_moves[i];
		if (newmove(XPLAYER, nextXmove, gameboard_ptr, charboard_ptr) !=
		OCCUPIED) {
			bool_next_move_found = TRUE;
			break;
		}
	}
}

/* Test |nextXmove| and update board */
if (bool_next_move_found == TRUE) {
	++squares_filled;
	listXmoves = insert_sorted(listXmoves, best_moves[i]);
	printf("X moves: ");
	print_movelist(listXmoves);
} else { /* DEBUG */
	printf("Error finding X move");
	exit(EXIT_FAILURE);
}


/* Test X values for 3/3 
printf("Checking for X win...\n");
if (check_triple(listXmoves) == TRUE) {
	bool_gameover = TRUE;
	winner = XPLAYER;
} else if (squares_filled > 8) {
	bool_gameover = TRUE;  
}
*/

if (squares_filled > 8) {
	bool_gameover = TRUE;  
	winner = EMPTY;
}

@ Function to test player's board positions for winning series, 3 out of 3.

@p
boolean check_triple(square_ptr head)
{
	square_ptr list;
	int i;
	int a, b, c; /* Test values */
	boolean bool_win;

	if (head == NULL) {
		return(EXIT_FAILURE);
	} else {
		list = head;
	}
	
	a = list->position;
	if (list->next == NULL) {
		b = c = 0;
	} else {
		list = list->next;
		b = list->position;
		if (list->next != NULL) {
			list = list->next;
			c = list->position;
		} else c = 0;
	}

	printf("Checking these values: %d %d %d\n", a, b, c);

	for (bool_win = FALSE; list != NULL; list = list->next) {
		for (i = 0; i < MAXANSWERS; ++i) {
			if (answer[i][0] == a && 
			    answer[i][1] == b && 
			    answer[i][2] == c) {
				printf("Triple found.\n");
				bool_win = TRUE;
				return(bool_win);
			} 
		}
		/* If no match found, try next set of three consecutive
		 * positions from linked list */
		if (list->next != NULL) {
			list = list->next;
			a = b;
			b = c;
			c = list->position;
		} else break;
	}

	return(bool_win);
}

@ @<Function prototypes@>=
boolean check_triple(square_ptr head);




@ Function to test for two in a row, and if found, return the third member.

@d ERROR -6

@p
int twoofthree(square_ptr head, int perms[][3])
{
	int i, p;
	square_ptr list;

	if (head == NULL) {
		return(ERROR);
	} else {
		list = head;
	}

	for (i = 0; list != NULL; list = list->next, ++i) { /* Test values */
		for (p = 0; p < MAXPERMS; ++p) { /* $2/3$ perms $x$ indices */
			if (list->position == perms[p][0]) {
				if (list->next != NULL 
				&& (list->next)->position == perms[p][1]) {
					return(perms[p][2]);
				}
			}
		}
	}
	return(ERROR);
}

@ @<Function prototypes@>=
int twoofthree(square_ptr head, int perms[][3]);


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

@<Gameover routine@>=
		
printf("\n*** Game over! ***\n");
if (winner == EMPTY) {
	printf("***   DRAW.    ***\n");
} else printf("***  %c WINS.   ***\n\n", playerchar[winner]);


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


