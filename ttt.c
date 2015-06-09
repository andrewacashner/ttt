#define CHAR_BOARD_LENGTH 62 \

#define MAXTRIPLES 8
#define MAXDUPLES 24
#define MIN 0
#define MAX 1 \

#define MAXLINE 100 \

/*1:*/
#line 7 "./ttt.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

/*4:*/
#line 75 "./ttt.w"

static const int charboard_index[]= {
2,6,10,
26,30,34,
50,54,58

};

static const enum{
A1,A2,A3,
B1,B2,B3,
C1,C2,C3}squareID;

static const char*square_label[]= {
"A1","A2","A3",
"B1","B2","B3",
"C1","C2","C3"

};
static const enum{EMPTY,XPLAYER,OPLAYER}playerID;
static const char playerchar[]= {' ','X','O'};

/*:4*//*7:*/
#line 135 "./ttt.w"

static const int triple[MAXTRIPLES][3]= {
{0,1,2},
{0,3,6},
{0,4,8},
{1,4,7},
{2,4,6},
{2,5,8},
{3,4,5},
{6,7,8}

};

static const int duple[MAXDUPLES][3]= {
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

static const int duple_range[8][2]= {
{0,5},
{6,8},
{9,12},
{13,15},
{16,19},
{20,20},
{21,22},
{23,23}
};




/*:7*//*8:*/
#line 193 "./ttt.w"

typedef struct square*square_ptr;
typedef struct square{
int position;
square_ptr next;
}square;

/*:8*//*27:*/
#line 492 "./ttt.w"

static const enum{NOTFOUND= -10,O_WINS}function_errors;

/*:27*//*32:*/
#line 565 "./ttt.w"

static const char*gameover_msg[]= {
"***   DRAW.    ***",
"***  X WINS.   ***",
"***  YOU WIN!  ***",
"*** Game over! ***"

};

static const enum{
MSG_DRAW,
MSG_X_WINS,
MSG_O_WINS,
MSG_GAMEOVER
}gameover_msg_label;


/*:32*//*34:*/
#line 591 "./ttt.w"

static const enum{
VERSION,
HELP,
BAD_OPTION,
O_COMMAND_OUT_OF_RANGE,
O_COMMAND_FAULTY,
SQUARE_OCCUPIED
}msg_ID;

static const char*message[]= {
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
static const char greeting[]= {
"\nTIC TAC TOE\n"
"I play X. You play O. You go first.\n"
"Use one of the labels shown below to say where you will move.\n"
"\n A1 | A2 | A3 \n-----------\n"
" B1 | B2 | B3 \n-----------\n"
" C1 | C2 | C3\n\n"
"Let's play!"
};

/*:34*/
#line 12 "./ttt.w"

typedef enum{FALSE,TRUE}boolean;

/*10:*/
#line 244 "./ttt.w"

square_ptr insert_sorted(square_ptr head,int new_position);

/*:10*//*13:*/
#line 264 "./ttt.w"

int getlistdata(square_ptr list_head,int index);

/*:13*//*15:*/
#line 279 "./ttt.w"

void print_movelist(square_ptr list);

/*:15*//*18:*/
#line 312 "./ttt.w"

void free_list(square_ptr list_head);



/*:18*//*20:*/
#line 327 "./ttt.w"

int newmove(int player,int square,int*gameboard,char*charboard);

/*:20*//*29:*/
#line 525 "./ttt.w"

int two_of_three(square_ptr list_head,int list_length,int*gameboard);


/*:29*//*31:*/
#line 559 "./ttt.w"

boolean three_of_three(square_ptr list_head,int list_length);


/*:31*/
#line 15 "./ttt.w"


int main(int argc,char*argv[])
{
/*2:*/
#line 40 "./ttt.w"

enum{EASY,MEDIUM,DIFFICULT}game_mode;

/*:2*//*5:*/
#line 105 "./ttt.w"

int gameboard[9]= {0,0,0,0,0,0,0,0,0};
char charboard[]= 
"\n   |   |   \n"
"-----------\n"
"   |   |   \n"
"-----------\n"
"   |   |   \n\n";
int*gameboard_ptr= gameboard;
char*charboard_ptr= charboard;

/*:5*//*21:*/
#line 334 "./ttt.w"

char input_line[MAXLINE];
int nextOmove;
int squares_filled;
square_ptr listOmoves= NULL;
int total_O_moves= 0;
int total_X_moves= 0;
int winner= EMPTY;

/*:21*//*23:*/
#line 380 "./ttt.w"

int best_moves[]= {B2,A1,A3,C1,C3,A2,B1,B3,C2};
int total_best_moves= 8;
int i;
square_ptr listXmoves= NULL;
int nextXmove;
int test;


/*:23*/
#line 19 "./ttt.w"


/*3:*/
#line 43 "./ttt.w"

if(argc> 1&&argv[1][0]=='-'){
switch(argv[1][1]){
case'v':
printf("%s\n",message[VERSION]);
return(0);
break;
case'h':
printf("%s\n",message[HELP]);
return(0);
break;
case'e':
game_mode= EASY;
break;
case'm':
game_mode= MEDIUM;
break;
case'd':
game_mode= DIFFICULT;
break;
default:
fprintf(stderr,"%s\n",message[BAD_OPTION]);
exit(EXIT_FAILURE);
break;
}
}else game_mode= DIFFICULT;



/*:3*/
#line 21 "./ttt.w"


printf("%s\n",greeting);
/*6:*/
#line 118 "./ttt.w"

printf("%s",charboard);


/*:6*/
#line 24 "./ttt.w"


while(1){
/*22:*/
#line 348 "./ttt.w"

while(1){

printf("\nYour move?\n");
fgets(input_line,sizeof(input_line),stdin);

if(input_line[2]!='\n'||
input_line[0]<'A'||input_line[0]> 'C'||
input_line[1]<'1'||input_line[1]> '3'){
printf("%s\n",message[O_COMMAND_OUT_OF_RANGE]);
continue;
}

nextOmove= (input_line[0]-'A')*3;
nextOmove+= input_line[1]-'1';
if(gameboard[nextOmove]==EMPTY){
newmove(OPLAYER,nextOmove,gameboard_ptr,charboard_ptr);
/*6:*/
#line 118 "./ttt.w"

printf("%s",charboard);


/*:6*/
#line 365 "./ttt.w"

++squares_filled;
++total_O_moves;
listOmoves= insert_sorted(listOmoves,nextOmove);
printf("O moves: ");
print_movelist(listOmoves);
break;
}else{
printf("%s\n",message[SQUARE_OCCUPIED]);
}

}

/*:22*/
#line 27 "./ttt.w"

/*24:*/
#line 391 "./ttt.w"

if(total_O_moves> 2){
if(three_of_three(listOmoves,total_O_moves)==TRUE){
winner= OPLAYER;
goto gameover;
}
}

/*:24*/
#line 28 "./ttt.w"

/*25:*/
#line 417 "./ttt.w"


switch(game_mode){
case EASY:
/*26:*/
#line 479 "./ttt.w"

for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}


/*:26*/
#line 421 "./ttt.w"

break;
case MEDIUM:
if(total_X_moves<1){
/*26:*/
#line 479 "./ttt.w"

for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}


/*:26*/
#line 425 "./ttt.w"

}else{
test= two_of_three(listXmoves,total_X_moves,gameboard_ptr);
if(test!=NOTFOUND){
nextXmove= test;
winner= XPLAYER;
}else/*26:*/
#line 479 "./ttt.w"

for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}


/*:26*/
#line 431 "./ttt.w"

}
break;
case DIFFICULT:
if(total_X_moves<1){
/*26:*/
#line 479 "./ttt.w"

for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}


/*:26*/
#line 436 "./ttt.w"

}else{
test= two_of_three(listXmoves,total_X_moves,gameboard_ptr);
if(test!=NOTFOUND){
nextXmove= test;
winner= XPLAYER;
}else{
test= two_of_three(listOmoves,total_O_moves,
gameboard_ptr);
if(test!=NOTFOUND){
nextXmove= test;
}else/*26:*/
#line 479 "./ttt.w"

for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}


/*:26*/
#line 447 "./ttt.w"

}
}
break;
}


newmove(XPLAYER,nextXmove,gameboard_ptr,charboard_ptr);
/*6:*/
#line 118 "./ttt.w"

printf("%s",charboard);


/*:6*/
#line 455 "./ttt.w"

++squares_filled;
++total_X_moves;
listXmoves= insert_sorted(listXmoves,nextXmove);
printf("X moves: ");
print_movelist(listXmoves);

if(winner==XPLAYER){
goto gameover;
}
if(game_mode==EASY&&total_X_moves> 2){
if(three_of_three(listXmoves,total_X_moves)==TRUE){
winner= XPLAYER;
goto gameover;
}
}
if(squares_filled> 8){
winner= EMPTY;
goto gameover;
}

/*:25*/
#line 29 "./ttt.w"

}
gameover:
/*33:*/
#line 585 "./ttt.w"

printf("\n%s\n",gameover_msg[MSG_GAMEOVER]);
printf("%s\n\n",gameover_msg[winner]);

/*:33*/
#line 32 "./ttt.w"


/*16:*/
#line 284 "./ttt.w"

free_list(listOmoves);
free_list(listXmoves);

/*:16*/
#line 34 "./ttt.w"

return(0);
}

/*:1*//*9:*/
#line 202 "./ttt.w"

square_ptr insert_sorted(square_ptr head,int new_position)
{
square_ptr list;
square_ptr new_square= malloc(sizeof(square_ptr));
new_square->position= new_position;
new_square->next= NULL;


if(head==NULL){
list= new_square;
return(list);
}else{
list= head;
}


if(new_position<list->position){
new_square->next= list;
return(new_square);
}


while(list->next!=NULL){
if(new_position<(list->next)->position){

new_square->next= list->next;
list->next= new_square;
return(head);
}else{
list= list->next;
}
}


list->next= new_square;
new_square->next= NULL;


return(head);
}

/*:9*//*12:*/
#line 251 "./ttt.w"

int getlistdata(square_ptr list_head,int index)
{
int i;
square_ptr list= list_head;
for(i= 0;list!=NULL;list= list->next,++i){
if(i==index){
return(list->position);
}
}
return(NOTFOUND);
}

/*:12*//*14:*/
#line 269 "./ttt.w"

void print_movelist(square_ptr list)
{
for(;list!=NULL;list= list->next){
printf("%s ",square_label[list->position]);
}
printf("\n");
return;
}

/*:14*//*17:*/
#line 290 "./ttt.w"

void free_list(square_ptr list)
{
square_ptr prev= NULL;

if(list==NULL)
return;
else prev= list;

while(list->next!=NULL){
prev= list;
list= list->next;
prev= NULL;
free(prev);
}
list= list->next;
list= NULL;
free(list);

return;
}

/*:17*//*19:*/
#line 319 "./ttt.w"

int newmove(int player,int position,int*gameboard,char*charboard)
{
*(gameboard+position)= player;
*(charboard+charboard_index[position])= playerchar[player];
return(0);
}

/*:19*//*28:*/
#line 498 "./ttt.w"

int two_of_three(square_ptr list_head,int list_length,int*gameboard)
{
square_ptr list= list_head;
int i,j;
int d;
int first,second,third;

for(i= 0;i<list_length-1;++i){
first= getlistdata(list,i);
for(j= i+1;j<list_length;++j){
second= getlistdata(list,j);
for(d= duple_range[first][MIN];
d<=duple_range[first][MAX];++d){
if(second==duple[d][1]){
third= duple[d][2];
if(*(gameboard+third)==EMPTY){
return(third);
}
}
}
}
}
return(NOTFOUND);
}


/*:28*//*30:*/
#line 532 "./ttt.w"

boolean three_of_three(square_ptr list_head,int list_length)
{
square_ptr list= list_head;
int i,j,k;
int t;
int a,b,c;

for(i= 0;i<list_length-2;++i){
a= getlistdata(list,i);
for(j= i+1;j<list_length-1;++j){
b= getlistdata(list,j);
for(k= j+1;k<list_length;++k){
c= getlistdata(list,k);
for(t= 0;t<MAXTRIPLES;++t){
if(a==triple[t][0]&&
b==triple[t][1]&&
c==triple[t][2]){
return(TRUE);
}
}
}
}
}
return(FALSE);
}

/*:30*/
