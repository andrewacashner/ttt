/* sortedlist.c -- Andrew Cashner, 2015-05-29 
 * Add numbers to a linked list, keeping list sorted in ascending order.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *node_ptr;
typedef struct node {
 	int data;
	node_ptr next;
} node;

#define MAXLINE 100
#define MAXITEMS 8
#define INPUT_ERROR -1

node_ptr insert_sorted(node_ptr list, int new_data);
node_ptr remove_node(node_ptr list, int cut_data);
void printlist(node_ptr list);
int get_move(void);

int main(void) {
	int newmove;
	int listitems;
	node_ptr list = NULL;

	printf("\nAdd to list\n");
	for (listitems = 0; listitems < MAXITEMS; ++listitems) {
		newmove = get_move();
		if (newmove == INPUT_ERROR) continue;
		list = insert_sorted(list, newmove);
		printlist(list);
	}
	
	printf("\nCut from list\n");
	for (listitems = 0; listitems < MAXITEMS; ++listitems) {
		newmove = get_move();
		if (newmove == INPUT_ERROR) continue;
		list = remove_node(list, newmove); 
		printlist(list);
	}

	return(0);
}

node_ptr insert_sorted(node_ptr head, int new_data)
{
	node_ptr list;
	node_ptr new_node = malloc(sizeof(node_ptr));
	new_node->data = new_data;
	new_node->next = NULL;

	/* Create new list if there is none */
	if (head == NULL) {
		list = new_node;
		return(list);
	} else {
		list = head;
	}

	/* If new node data is less, put at head of list and return head */
	if (new_data < list->data) {
		new_node->next = list;
		return(new_node);
	}

	while (list->next != NULL) {
		if (new_data < (list->next)->data) {
			/* Insert the node mid-list, here */
			new_node->next = list->next;
			list->next = new_node;
			return(head);
		} else {
			list = list->next;
		}
	}
	/* If node is greater than all, add it to end of list */
	list->next = new_node;
	new_node->next = NULL;
		
	/* Return head of list */
	return(head);
}

		
node_ptr remove_node(node_ptr head, int cut_data)
{
	node_ptr list;
	/* If no list */
	if (head != NULL) {
		list = head;
	}
	/* If only one list item */	
	if (list->next == NULL) {
		list = NULL;
		free(list);
		return(NULL);
	}
	if (list->data == cut_data) {
		head = list->next;
		list = NULL;
		free(list);
		return(head);
	}

	while (list->next != NULL) {
		if ((list->next)->data == cut_data) {
			list->next = (list->next)->next;
			list = list->next;
			list = NULL;
			free(list);
			break;
		} else {
			list = list->next;
		}
	}
	return(head);
}

void printlist(node_ptr list)
{
	for ( ; list != NULL; list = list->next) {
		printf("%d ", list->data);
	}
	printf("\n");
	return;
}

int get_move(void) 
{
	char line[MAXLINE];
	int newmove;
	
	printf("Enter move (0-8):\n");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%d", &newmove);
	if (newmove < 0 || newmove > 8) {
		printf("Bad input '%d' -- try again.\n", newmove);
		return(INPUT_ERROR);
	} else return(newmove);
}

