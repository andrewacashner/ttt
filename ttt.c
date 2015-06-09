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

/*2:*/
#line 47 "./ttt.w"

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

/*:2*//*5:*/
#line 107 "./ttt.w"

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




/*:5*//*6:*/
#line 165 "./ttt.w"

typedef struct square*square_ptr;
typedef struct square{
int position;
square_ptr next;
}square;

/*:6*//*17:*/
#line 368 "./ttt.w"

static const enum{NOTFOUND= -10,O_WINS}function_errors;

/*:17*//*29:*/
#line 507 "./ttt.w"

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


/*:29*//*31:*/
#line 533 "./ttt.w"

static const enum{
O_COMMAND_OUT_OF_RANGE,
O_COMMAND_FAULTY,
SQUARE_OCCUPIED
}error_msg;

static const char*error[]= {
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

/*:31*/
#line 12 "./ttt.w"

typedef enum{FALSE,TRUE}boolean;

/*8:*/
#line 216 "./ttt.w"

square_ptr insert_sorted(square_ptr head,int new_position);


/*:8*//*10:*/
#line 230 "./ttt.w"

int newmove(int player,int square,int*gameboard,char*charboard);

/*:10*//*19:*/
#line 401 "./ttt.w"

int two_of_three(square_ptr list_head,int list_length,int*gameboard);


/*:19*//*21:*/
#line 435 "./ttt.w"

boolean three_of_three(square_ptr list_head,int list_length);


/*:21*//*23:*/
#line 454 "./ttt.w"

int getlistdata(square_ptr list_head,int index);

/*:23*//*25:*/
#line 469 "./ttt.w"

void print_movelist(square_ptr list);

/*:25*//*28:*/
#line 502 "./ttt.w"

void free_list(square_ptr list_head);

/*:28*/
#line 15 "./ttt.w"


int main(int argc,char*argv[])
{
/*3:*/
#line 77 "./ttt.w"

int gameboard[9]= {0,0,0,0,0,0,0,0,0};
char charboard[]= 
"\n   |   |   \n"
"-----------\n"
"   |   |   \n"
"-----------\n"
"   |   |   \n\n";
int*gameboard_ptr= gameboard;
char*charboard_ptr= charboard;

/*:3*//*11:*/
#line 237 "./ttt.w"

char input_line[MAXLINE];
int nextOmove;
int squares_filled;
square_ptr listOmoves= NULL;
int total_O_moves= 0;
int total_X_moves= 0;
int winner= EMPTY;

/*:11*//*13:*/
#line 283 "./ttt.w"

int best_moves[]= {B2,A1,A3,C1,C3,A2,B1,B3,C2};
int total_best_moves= 8;
int i;
square_ptr listXmoves= NULL;
int nextXmove;
int test;


/*:13*/
#line 19 "./ttt.w"

enum{EASY,HARD}game_mode= HARD;
boolean bool_gameover= FALSE;

if(argc> 1){
if(strcmp(argv[1],"-e")==0){
game_mode= EASY;
}
}

printf("%s\n",greeting);
/*4:*/
#line 90 "./ttt.w"

printf("%s",charboard);


/*:4*/
#line 30 "./ttt.w"


while(bool_gameover==FALSE){
/*12:*/
#line 251 "./ttt.w"

while(1){

printf("\nYour move?\n");
fgets(input_line,sizeof(input_line),stdin);

if(input_line[2]!='\n'||
input_line[0]<'A'||input_line[0]> 'C'||
input_line[1]<'1'||input_line[1]> '3'){
printf("%s\n",error[O_COMMAND_OUT_OF_RANGE]);
continue;
}

nextOmove= (input_line[0]-'A')*3;
nextOmove+= input_line[1]-'1';
if(gameboard[nextOmove]==EMPTY){
newmove(OPLAYER,nextOmove,gameboard_ptr,charboard_ptr);
/*4:*/
#line 90 "./ttt.w"

printf("%s",charboard);


/*:4*/
#line 268 "./ttt.w"

++squares_filled;
++total_O_moves;
listOmoves= insert_sorted(listOmoves,nextOmove);
printf("O moves: ");
print_movelist(listOmoves);
break;
}else{
printf("%s\n",error[SQUARE_OCCUPIED]);
}

}

/*:12*/
#line 33 "./ttt.w"

/*14:*/
#line 294 "./ttt.w"

if(total_O_moves> 2){
if(three_of_three(listOmoves,total_O_moves)==TRUE){
bool_gameover= TRUE;
winner= OPLAYER;
break;
}
}

/*:14*/
#line 34 "./ttt.w"

/*15:*/
#line 313 "./ttt.w"


if(game_mode==EASY||total_X_moves<1){
/*16:*/
#line 355 "./ttt.w"

for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}


/*:16*/
#line 316 "./ttt.w"

}else{
test= two_of_three(listXmoves,total_X_moves,gameboard_ptr);

if(test!=NOTFOUND){
nextXmove= test;
}else{
if(game_mode==HARD){
test= two_of_three(listOmoves,total_O_moves,gameboard_ptr);
if(test!=NOTFOUND){
nextXmove= test;
}else/*16:*/
#line 355 "./ttt.w"

for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}


/*:16*/
#line 327 "./ttt.w"

}else/*16:*/
#line 355 "./ttt.w"

for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}


/*:16*/
#line 328 "./ttt.w"

}
}
newmove(XPLAYER,nextXmove,gameboard_ptr,charboard_ptr);
/*4:*/
#line 90 "./ttt.w"

printf("%s",charboard);


/*:4*/
#line 332 "./ttt.w"

++squares_filled;
++total_X_moves;
listXmoves= insert_sorted(listXmoves,nextXmove);
printf("X moves: ");
print_movelist(listXmoves);

if(total_X_moves> 2){
if(three_of_three(listXmoves,total_X_moves)==TRUE){
bool_gameover= TRUE;
winner= XPLAYER;
break;
}
}
if(squares_filled> 8){
bool_gameover= TRUE;
winner= EMPTY;
break;
}

/*:15*/
#line 35 "./ttt.w"

}
/*30:*/
#line 527 "./ttt.w"

printf("\n%s\n",gameover_msg[MSG_GAMEOVER]);
printf("%s\n\n",gameover_msg[winner]);

/*:30*/
#line 37 "./ttt.w"

/*26:*/
#line 474 "./ttt.w"

free_list(listOmoves);
free_list(listXmoves);

/*:26*/
#line 38 "./ttt.w"

return(0);
}



/*:1*//*7:*/
#line 174 "./ttt.w"

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

/*:7*//*9:*/
#line 222 "./ttt.w"

int newmove(int player,int position,int*gameboard,char*charboard)
{
*(gameboard+position)= player;
*(charboard+charboard_index[position])= playerchar[player];
return(0);
}

/*:9*//*18:*/
#line 374 "./ttt.w"

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


/*:18*//*20:*/
#line 408 "./ttt.w"

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

/*:20*//*22:*/
#line 441 "./ttt.w"

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

/*:22*//*24:*/
#line 459 "./ttt.w"

void print_movelist(square_ptr list)
{
for(;list!=NULL;list= list->next){
printf("%s ",square_label[list->position]);
}
printf("\n");
return;
}

/*:24*//*27:*/
#line 480 "./ttt.w"

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

/*:27*/
