#define MAXLINE 100 \

#define CHAR_BOARD_LENGTH 62 \

#define MAXANSWERS 8
#define NOTFOUND -1
#define MAXPERMS 24 \

#define OCCUPIED -10 \

/*1:*/
#line 7 "./ttt.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

/*5:*/
#line 90 "./ttt.w"

typedef struct square*square_ptr;
typedef struct square{
int position;
square_ptr next;
}square;

/*:5*//*10:*/
#line 148 "./ttt.w"

static const int charboard_index[]= 
{2,6,10,
26,30,34,
50,54,58};

static const enum{
A1,A2,A3,
B1,B2,B3,
C1,C2,C3}squareID;

static const char*square_label[]= {
"A1","A2","A3",
"B1","B2","B3",
"C1","C2","C3"};

static const enum{EMPTY,XPLAYER,OPLAYER}playerID;
static const char playerchar[]= {' ','X','O'};

/*:10*//*13:*/
#line 194 "./ttt.w"

static const int answer[8][3]= {
{0,1,2},
{0,3,6},
{0,4,8},
{1,4,7},
{2,4,6},
{2,5,8},
{3,4,5},
{6,7,8}
};

/*:13*//*35:*/
#line 333 "./ttt.w"

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

/*:35*/
#line 12 "./ttt.w"

typedef enum{FALSE,TRUE}boolean;

/*7:*/
#line 141 "./ttt.w"

square_ptr insert_sorted(square_ptr head,int new_position);

/*:7*//*17:*/
#line 217 "./ttt.w"

int newmove(int player,int square,int*gameboard,char*charboard);

/*:17*//*27:*/
#line 279 "./ttt.w"

int twoofthree(int test[],int test_array_length,int perms[][3]);

/*:27*//*33:*/
#line 323 "./ttt.w"

void print_movelist(square_ptr list);

/*:33*/
#line 15 "./ttt.w"


int main(int argc,char*argv[])
{
/*3:*/
#line 47 "./ttt.w"

char input_line[MAXLINE];
int nextOmove;
int squares_filled;
square_ptr listOmoves= NULL;

/*:3*//*12:*/
#line 175 "./ttt.w"

int gameboard[9]= {0,0,0,0,0,0,0,0,0};
char charboard[]= 
"\n   |   |   \n"
"-----------\n"
"   |   |   \n"
"-----------\n"
"   |   |   \n\n";
int*gameboard_ptr= gameboard;
char*charboard_ptr= charboard;


/*:12*//*30:*/
#line 290 "./ttt.w"

int best_moves[]= {B2,A1,A3,C1,C3,A2,B1,B3,C2};
int total_best_moves= 8;
int i;
square_ptr listXmoves= NULL;

/*:30*/
#line 19 "./ttt.w"

boolean gameover;
gameover= FALSE;

/*2:*/
#line 41 "./ttt.w"


/*:2*/
#line 23 "./ttt.w"

/*15:*/
#line 208 "./ttt.w"


/*:15*/
#line 24 "./ttt.w"


printf("%s\n",greeting);
/*16:*/
#line 212 "./ttt.w"

printf("%s",charboard);

/*:16*/
#line 27 "./ttt.w"


while(gameover==FALSE){
/*4:*/
#line 58 "./ttt.w"

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
if(newmove(OPLAYER,nextOmove,gameboard_ptr,charboard_ptr)!=
OCCUPIED){
++squares_filled;
listOmoves= insert_sorted(listOmoves,nextOmove);

printf("O moves: ");
print_movelist(listOmoves);
break;
}else{
printf("%s\n",error[SQUARE_OCCUPIED]);
}

}

/*:4*/
#line 30 "./ttt.w"

/*19:*/
#line 239 "./ttt.w"

/*20:*/
#line 247 "./ttt.w"




/*:20*/
#line 240 "./ttt.w"

/*21:*/
#line 253 "./ttt.w"



/*:21*/
#line 241 "./ttt.w"

/*22:*/
#line 257 "./ttt.w"


/*:22*/
#line 242 "./ttt.w"

/*23:*/
#line 260 "./ttt.w"


/*:23*/
#line 243 "./ttt.w"

/*24:*/
#line 263 "./ttt.w"


/*:24*/
#line 244 "./ttt.w"


/*:19*/
#line 31 "./ttt.w"

/*25:*/
#line 267 "./ttt.w"

/*28:*/
#line 283 "./ttt.w"


/*:28*/
#line 268 "./ttt.w"

/*29:*/
#line 286 "./ttt.w"


/*:29*/
#line 269 "./ttt.w"

/*31:*/
#line 298 "./ttt.w"

for(i= 0;i<total_best_moves;++i){
if(newmove(XPLAYER,best_moves[i],gameboard_ptr,charboard_ptr)!=
OCCUPIED){
++squares_filled;
listXmoves= insert_sorted(listXmoves,best_moves[i]);

printf("X moves: ");
print_movelist(listXmoves);
break;
}
}

/*:31*/
#line 270 "./ttt.w"

if(squares_filled> 8){
gameover= TRUE;
}

/*:25*/
#line 32 "./ttt.w"

}
/*34:*/
#line 327 "./ttt.w"

printf("Game over!\n");


/*:34*/
#line 34 "./ttt.w"

return(0);
}



/*:1*//*6:*/
#line 99 "./ttt.w"

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

/*:6*//*18:*/
#line 224 "./ttt.w"

int newmove(int player,int square,int*gameboard,char*charboard)
{
if(*(gameboard+square)!=EMPTY){
return(OCCUPIED);
}
*(gameboard+square)= player;
*(charboard+charboard_index[square])= playerchar[player];
/*16:*/
#line 212 "./ttt.w"

printf("%s",charboard);

/*:16*/
#line 232 "./ttt.w"

return(0);
}


/*:18*//*32:*/
#line 313 "./ttt.w"

void print_movelist(square_ptr list)
{
for(;list!=NULL;list= list->next){
printf("%s ",square_label[list->position]);
}
printf("\n");
return;
}

/*:32*/
