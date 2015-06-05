#define CHAR_BOARD_LENGTH 62 \

#define MAXANSWERS 8 \

#define MAXPERMS 24 \

#define MAXLINE 100 \

/*1:*/
#line 7 "./ttt.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

/*2:*/
#line 42 "./ttt.w"

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
#line 96 "./ttt.w"

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

/*:5*//*8:*/
#line 151 "./ttt.w"

typedef struct square*square_ptr;
typedef struct square{
int position;
square_ptr next;
}square;

/*:8*//*19:*/
#line 351 "./ttt.w"

static const enum{NOTFOUND= -10,O_WINS}function_errors;

/*:19*//*25:*/
#line 429 "./ttt.w"

static const char*gameover_msg[]= {
"***   DRAW.    ***",
"***  X WINS.   ***",
"***  O WINS.   ***",
"*** Game over! ***"

};

static const enum{
MSG_DRAW,
MSG_X_WINS,
MSG_O_WINS,
MSG_GAMEOVER
}gameover_msg_label;


/*:25*//*27:*/
#line 455 "./ttt.w"

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

/*:27*/
#line 12 "./ttt.w"

typedef enum{FALSE,TRUE}boolean;

/*10:*/
#line 202 "./ttt.w"

square_ptr insert_sorted(square_ptr head,int new_position);


/*:10*//*12:*/
#line 216 "./ttt.w"

int newmove(int player,int square,int*gameboard,char*charboard);

/*:12*//*22:*/
#line 408 "./ttt.w"

int two_of_three(int player,square_ptr head,int perms[][3],int*gameboard);


/*:22*//*24:*/
#line 424 "./ttt.w"

void print_movelist(square_ptr list);

/*:24*/
#line 15 "./ttt.w"


int main(int argc,char*argv[])
{
/*3:*/
#line 72 "./ttt.w"

int gameboard[9]= {0,0,0,0,0,0,0,0,0};
char charboard[]= 
"\n   |   |   \n"
"-----------\n"
"   |   |   \n"
"-----------\n"
"   |   |   \n\n";
int*gameboard_ptr= gameboard;
char*charboard_ptr= charboard;

/*:3*//*6:*/
#line 113 "./ttt.w"

int perms[MAXPERMS][3];
int a,b,c;
int j;

/*:6*//*13:*/
#line 223 "./ttt.w"

char input_line[MAXLINE];
int nextOmove;
int squares_filled;
square_ptr listOmoves= NULL;
int total_O_moves= 0;
int total_X_moves= 0;
int winner= EMPTY;

/*:13*//*15:*/
#line 269 "./ttt.w"

int best_moves[]= {B2,A1,A3,C1,C3,A2,B1,B3,C2};
int total_best_moves= 8;
int i;
square_ptr listXmoves= NULL;
int nextXmove;
int test;


/*:15*/
#line 19 "./ttt.w"

boolean bool_gameover;
bool_gameover= FALSE;

/*7:*/
#line 118 "./ttt.w"



for(i= 0,j= 0;i<MAXANSWERS;++i){
a= answer[i][0];
b= answer[i][1];
c= answer[i][2];
perms[j][0]= a;
perms[j][1]= b;
perms[j][2]= c;
++j;
perms[j][0]= a;
perms[j][1]= c;
perms[j][2]= b;
++j;
perms[j][0]= b;
perms[j][1]= c;
perms[j][2]= a;
++j;
}


for(i= 0;i<MAXPERMS;++i){
for(j= 0;j<3;++j){
printf("%d ",perms[i][j]);
}
printf("\n");
}

/*:7*/
#line 23 "./ttt.w"


printf("%s\n",greeting);
/*4:*/
#line 85 "./ttt.w"

printf("%s",charboard);


/*:4*/
#line 26 "./ttt.w"


while(bool_gameover==FALSE){
/*14:*/
#line 237 "./ttt.w"

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
#line 85 "./ttt.w"

printf("%s",charboard);


/*:4*/
#line 254 "./ttt.w"

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

/*:14*/
#line 29 "./ttt.w"

/*16:*/
#line 280 "./ttt.w"

if(total_O_moves> 2){
test= two_of_three(OPLAYER,listOmoves,perms,gameboard_ptr);
if(test==O_WINS){
bool_gameover= TRUE;
winner= OPLAYER;
}
}

/*:16*/
#line 30 "./ttt.w"

/*17:*/
#line 299 "./ttt.w"


if(total_X_moves<1){
/*18:*/
#line 338 "./ttt.w"

printf("I found no matches; I will pick any good free spot.\n");
for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}


/*:18*/
#line 302 "./ttt.w"

}else{
test= two_of_three(XPLAYER,listXmoves,perms,gameboard_ptr);

if(test!=NOTFOUND){
printf("I found a matching triple of X positions.\n");
nextXmove= test;
bool_gameover= TRUE;
winner= XPLAYER;
}else{
test= two_of_three(XPLAYER,listOmoves,perms,gameboard_ptr);
if(test!=NOTFOUND){
printf("I found a matching duple of O positions and I will block the win.\n");
nextXmove= test;
}else{
/*18:*/
#line 338 "./ttt.w"

printf("I found no matches; I will pick any good free spot.\n");
for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}


/*:18*/
#line 317 "./ttt.w"

}
}
}

newmove(XPLAYER,nextXmove,gameboard_ptr,charboard_ptr);
/*4:*/
#line 85 "./ttt.w"

printf("%s",charboard);


/*:4*/
#line 323 "./ttt.w"

++squares_filled;
++total_X_moves;
listXmoves= insert_sorted(listXmoves,nextXmove);
printf("X moves: ");
print_movelist(listXmoves);

if(squares_filled> 8){
bool_gameover= TRUE;
winner= EMPTY;
}

/*:17*/
#line 31 "./ttt.w"

}
/*26:*/
#line 449 "./ttt.w"

printf("\n%s\n",gameover_msg[MSG_GAMEOVER]);
printf("%s\n\n",gameover_msg[winner]);

/*:26*/
#line 33 "./ttt.w"

return(0);
}



/*:1*//*9:*/
#line 160 "./ttt.w"

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

/*:9*//*11:*/
#line 208 "./ttt.w"

int newmove(int player,int position,int*gameboard,char*charboard)
{
*(gameboard+position)= player;
*(charboard+charboard_index[position])= playerchar[player];
return(0);
}

/*:11*//*20:*/
#line 359 "./ttt.w"

int two_of_three(int player,square_ptr head,int perms[][3],int*gameboard)
{
int i,p;
int third;
square_ptr list;

if(head==NULL){
return(NOTFOUND);
}else{
list= head;
}

for(i= 0;list!=NULL;list= list->next,++i){
for(p= 0;p<MAXPERMS;++p){
if(list->position==perms[p][0]){
if(list->next!=NULL
&&(list->next)->position==perms[p][1]){
third= perms[p][2];
/*21:*/
#line 393 "./ttt.w"

if(player==OPLAYER){
if(*(gameboard+third)==OPLAYER){
return(O_WINS);
}else{
continue;
}
}else{
if(*(gameboard+third)==EMPTY){
return(third);
}else{
continue;
}
}

/*:21*/
#line 378 "./ttt.w"

}
}
}
}
return(NOTFOUND);
}

/*:20*//*23:*/
#line 414 "./ttt.w"

void print_movelist(square_ptr list)
{
for(;list!=NULL;list= list->next){
printf("%s ",square_label[list->position]);
}
printf("\n");
return;
}

/*:23*/
