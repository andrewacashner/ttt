/* sortedlist.c -- Andrew Cashner, 2015-05-29 
 * Add numbers to a linked list, keeping list sorted in ascending order.
 * For use in tic-tac-toe game, hence "square" and "position".
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct square *square_ptr;
typedef struct square {
 	int position;
	square_ptr prev;
	square_ptr next;
} square;

#define MAXLINE 100
#define MAXMOVES 8
#define INPUT_ERROR -1

square_ptr new_movelist(int new_position);
void add_square(square_ptr list, int new_position);
void remove_square(square_ptr list, int cut_position);
void printlist(square_ptr list);
int get_move(void);

int main(void) {
	int newmove;
	int totalmoves;
	square_ptr moves;

	for (totalmoves = 0; totalmoves < MAXMOVES; ++totalmoves) {
		newmove = get_move();
		if (newmove == INPUT_ERROR) continue;

		if (totalmoves == 0) {
			moves = new_movelist(newmove);
		} else {
			add_square(moves, newmove);
		}
		printlist(moves);
	}
/*
	for (totalmoves = 0; totalmoves < MAXMOVES; ++totalmoves) {
		newmove = get_move();
		if (newmove == INPUT_ERROR) continue;
		remove_square(moves, newmove); 
		printlist(moves);
	}
*/
	return(0);
}

square_ptr new_movelist(int new_position)
{
	square_ptr newlist = malloc(sizeof(square_ptr));
	newlist->position = new_position;
	newlist->next = newlist->prev = NULL;
	return(newlist);
}

void add_square(square_ptr list, int new_position)
{
	square_ptr new_square = malloc(sizeof(square_ptr));
	new_square->position = new_position;

	while (list->prev != NULL) {
		list = list->prev;
	}
	while (list != NULL) {
		if (new_position > list->position) {
			new_square->prev = list;
			new_square->next = list->next;
			list->next = new_square;
			break;
		} else {
			list->prev = new_square;
			new_square->next = list;
			new_square->prev = NULL;
			list = list->next;
		}
	}
	return;
}

void remove_square(square_ptr list, int cut_position)
{
	square_ptr trash;
	
	for ( ; list != NULL; list = list->next) {
		if ((list->next)->position == cut_position) {
			trash =  list->next;
			list->next = (list->next)->next;
			free(trash);
			break;
		}
	}
	return;
}

void printlist(square_ptr list)
{
	while (list->prev != NULL) {
		list = list->prev;
	}
	for ( ; list != NULL; list = list->next) {
		printf("%d ", list->position);
	}
	printf("\n");
	return;
}

int get_move(void) 
{
	char line[MAXLINE];
	int newmove;
	
	printf("Enter move (0-8): ");
	fgets(line, sizeof(line), stdin);
	newmove = line[strlen(line) -2] - '0';
	if (newmove < 0 || newmove > 8) {
		printf("Bad input '%d' -- try again.\n", newmove);
		return(INPUT_ERROR);
	} else return(newmove);
}

