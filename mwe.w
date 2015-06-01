@* MWE. 
Why doesn't \.{CWEAVE} process this ungainly |while| loop correctly?

@p
#include <stdio.h>

int main(void) 
{
	@<Main variables@>@;
	@<Get next move from user input@>@;
	return(0);
}

@ Get and validate user input, set |newmove|.
The command is entered in the form \.{A1\\n}.
\.{'A'} is 0, \.{'B'} is 3, \.{'C'} is 6.
\.{'A1'} is $0 + 0$, \.{'B2'} is $3 + 1$.

@d MAXLINE 100

@ @<Main variables@>=
char input_line[MAXLINE];
int newmove;

@ @<Get next move...@>=
while (1) {  
	printf("Your move?\n"); 
	fgets(input_line, sizeof(input_line), stdin); 
	if (input_line[2] != '\n' ||
	    input_line[0] < 'A' || input_line[0] > 'C' ||
	    input_line[1] < '1' || input_line[1] > '3' ) {  
		printf("Move out of range. Try again.\n");
	} else {
		newmove = (input_line[0] - 'A') * 3;
		newmove += input_line[1] - '1'; 
		printf("Move to square number %d\n", newmove);
		break;
	}
}
