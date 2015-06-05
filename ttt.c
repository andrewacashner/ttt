#define CHAR_BOARD_LENGTH 62 \

#define MAXANSWERS 8
#define MAXPERMS 24
#define NOTFOUND -1 \

#define MAXPERMS 24 \

#define MAXLINE 100 \

#define ERROR -6 \

/*1:*/
#line 7 "./ttt.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

/*2:*/
#line 42 "./ttt.w"

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

/*:2*//*5:*/
#line 95 "./ttt.w"

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
#line 141 "./ttt.w"

typedef struct square*square_ptr;
typedef struct square{
int position;
square_ptr next;
}square;

/*:8*//*25:*/
#line 436 "./ttt.w"

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

/*:25*/
#line 12 "./ttt.w"

typedef enum{FALSE,TRUE}boolean;

/*10:*/
#line 192 "./ttt.w"

square_ptr insert_sorted(square_ptr head,int new_position);


/*:10*//*12:*/
#line 207 "./ttt.w"

int newmove(int player,int square,int*gameboard,char*charboard);

/*:12*//*19:*/
#line 370 "./ttt.w"

boolean check_triple(square_ptr head);




/*:19*//*21:*/
#line 405 "./ttt.w"

int twoofthree(square_ptr head,int perms[][3]);


/*:21*//*23:*/
#line 421 "./ttt.w"

void print_movelist(square_ptr list);

/*:23*/
#line 15 "./ttt.w"


int main(int argc,char*argv[])
{
/*3:*/
#line 69 "./ttt.w"

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
#line 111 "./ttt.w"

int perms[MAXPERMS][3];
int a,b,c;
int j;

/*:6*//*13:*/
#line 214 "./ttt.w"

char input_line[MAXLINE];
int nextOmove;
int squares_filled;
square_ptr listOmoves= NULL;
int winner= EMPTY;

/*:13*//*15:*/
#line 257 "./ttt.w"

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
#line 116 "./ttt.w"



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

/*:7*/
#line 23 "./ttt.w"


printf("%s\n",greeting);
/*4:*/
#line 82 "./ttt.w"

printf("%s",charboard);


/*:4*/
#line 26 "./ttt.w"


while(bool_gameover==FALSE){
/*14:*/
#line 226 "./ttt.w"

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
++squares_filled;
listOmoves= insert_sorted(listOmoves,nextOmove);
printf("O moves: ");
print_movelist(listOmoves);
/*4:*/
#line 82 "./ttt.w"

printf("%s",charboard);


/*:4*/
#line 247 "./ttt.w"

break;
}else{
printf("%s\n",error[SQUARE_OCCUPIED]);
}

}

/*:14*/
#line 29 "./ttt.w"

/*16:*/
#line 266 "./ttt.w"


printf("Checking for O win...\n");
if(check_triple(listOmoves)==TRUE){
bool_gameover= TRUE;
winner= OPLAYER;
}

/*:16*/
#line 30 "./ttt.w"

/*17:*/
#line 276 "./ttt.w"



test= twoofthree(listOmoves,perms);
printf("%s = test = twoofthree(listOmoves, perms)\n",square_label[test]);

if(test!=ERROR){
nextXmove= test;
}else{

test= twoofthree(listXmoves,perms);
if(test!=ERROR){
nextXmove= test;
bool_gameover= TRUE;
winner= XPLAYER;
}else{


for(i= 0;i<total_best_moves;++i){
test= best_moves[i];
if(gameboard[test]==EMPTY){
nextXmove= test;
break;
}
}
}
}


newmove(XPLAYER,nextXmove,gameboard_ptr,charboard_ptr);
/*4:*/
#line 82 "./ttt.w"

printf("%s",charboard);


/*:4*/
#line 306 "./ttt.w"

++squares_filled;
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
/*24:*/
#line 426 "./ttt.w"


printf("\n*** Game over! ***\n");
if(winner==EMPTY){
printf("***   DRAW.    ***\n");
}else printf("***  %c WINS.   ***\n\n",playerchar[winner]);


/*:24*/
#line 33 "./ttt.w"

return(0);
}



/*:1*//*9:*/
#line 150 "./ttt.w"

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
#line 198 "./ttt.w"

int newmove(int player,int square,int*gameboard,char*charboard)
{

*(gameboard+square)= player;
*(charboard+charboard_index[square])= playerchar[player];
return(0);
}

/*:11*//*18:*/
#line 319 "./ttt.w"

boolean check_triple(square_ptr head)
{
square_ptr list;
int i;
int a,b,c;
boolean bool_win;

if(head==NULL){
return(EXIT_FAILURE);
}else{
list= head;
}

a= list->position;
if(list->next==NULL){
b= c= 0;
}else{
list= list->next;
b= list->position;
if(list->next!=NULL){
list= list->next;
c= list->position;
}else c= 0;
}

printf("Checking these values: %d %d %d\n",a,b,c);

for(bool_win= FALSE;list!=NULL;list= list->next){
for(i= 0;i<MAXANSWERS;++i){
if(answer[i][0]==a&&
answer[i][1]==b&&
answer[i][2]==c){
printf("Triple found.\n");
bool_win= TRUE;
return(bool_win);
}
}


if(list->next!=NULL){
list= list->next;
a= b;
b= c;
c= list->position;
}else break;
}

return(bool_win);
}

/*:18*//*20:*/
#line 380 "./ttt.w"

int twoofthree(square_ptr head,int perms[][3])
{
int i,p;
square_ptr list;

if(head==NULL){
return(ERROR);
}else{
list= head;
}

for(i= 0;list!=NULL;list= list->next,++i){
for(p= 0;p<MAXPERMS;++p){
if(list->position==perms[p][0]){
if(list->next!=NULL
&&(list->next)->position==perms[p][1]){
return(perms[p][2]);
}
}
}
}
return(ERROR);
}

/*:20*//*22:*/
#line 411 "./ttt.w"

void print_movelist(square_ptr list)
{
for(;list!=NULL;list= list->next){
printf("%s ",square_label[list->position]);
}
printf("\n");
return;
}

/*:22*/
