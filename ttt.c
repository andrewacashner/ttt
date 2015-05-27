#define MAXLINE 100 \

#define CHAR_BOARD_LENGTH 62 \

#define MAXANSWERS 8
#define NOTFOUND -1
#define MAXPERMS 24 \

#define NOTEMPTY -10 \

/*1:*/
#line 7 "./ttt.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

/*2:*/
#line 42 "./ttt.w"

static const enum{
O_COMMAND_OUT_OF_RANGE,
O_COMMAND_FAULTY,
SQUARE_NOT_EMPTY
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


/*:2*//*7:*/
#line 112 "./ttt.w"

static const int charboard_index[]= 
{2,6,10,
26,30,34,
50,54,58};

static const enum{
A1,A2,A3,
B1,B2,B3,
C1,C2,C3}squareID;

static const enum{EMPTY,XPLAYER,OPLAYER}playerID;
static const char playerchar[]= {' ','X','O'};

/*:7*//*10:*/
#line 154 "./ttt.w"

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

/*:10*/
#line 12 "./ttt.w"

typedef enum{FALSE,TRUE}boolean;

/*14:*/
#line 177 "./ttt.w"

int newmove(int player,int square,int*gameboard,char*charboard);

/*:14*//*24:*/
#line 239 "./ttt.w"

int twoofthree(int test[],int test_array_length,int perms[][3]);

/*:24*/
#line 15 "./ttt.w"


int main(int argc,char*argv[])
{
/*4:*/
#line 76 "./ttt.w"

char line[MAXLINE];
int nextOmove;
int squares_filled;

/*:4*//*8:*/
#line 134 "./ttt.w"

int gameboard[9]= {0,0,0,0,0,0,0,0,0};
char charboard[]= 
"\n   |   |   \n"
"-----------\n"
"   |   |   \n"
"-----------\n"
"   |   |   \n\n";
int*gameboard_ptr= gameboard;
char*charboard_ptr= charboard;


/*:8*//*27:*/
#line 250 "./ttt.w"

int best_moves[]= {B2,A1,A3,C1,C3,A2,B1,B3,C2};
int total_best_moves= 8;
int i;

/*:27*/
#line 19 "./ttt.w"

boolean gameover;
gameover= FALSE;

/*3:*/
#line 70 "./ttt.w"


/*:3*/
#line 23 "./ttt.w"

/*12:*/
#line 168 "./ttt.w"


/*:12*/
#line 24 "./ttt.w"


printf("%s\n",greeting);
/*13:*/
#line 172 "./ttt.w"

printf("%s",charboard);

/*:13*/
#line 27 "./ttt.w"


while(gameover==FALSE){
/*5:*/
#line 86 "./ttt.w"

while(1){
printf("Your move?\n");
fgets(line,sizeof(line),stdin);
if(line[2]!='\n'||
line[0]<'A'||line[0]> 'C'||
line[1]<'1'||line[1]> '3'){
printf("%s\n",error[O_COMMAND_OUT_OF_RANGE]);
continue;
}
nextOmove= (line[0]-'A')*3;
nextOmove+= line[1]-'1';
if(newmove(OPLAYER,nextOmove,gameboard_ptr,charboard_ptr)==
NOTEMPTY){
printf("%s\n",error[SQUARE_NOT_EMPTY]);
}else{
++squares_filled;
break;
}
}


/*:5*/
#line 30 "./ttt.w"

/*16:*/
#line 199 "./ttt.w"

/*17:*/
#line 207 "./ttt.w"




/*:17*/
#line 200 "./ttt.w"

/*18:*/
#line 213 "./ttt.w"



/*:18*/
#line 201 "./ttt.w"

/*19:*/
#line 217 "./ttt.w"


/*:19*/
#line 202 "./ttt.w"

/*20:*/
#line 220 "./ttt.w"


/*:20*/
#line 203 "./ttt.w"

/*21:*/
#line 223 "./ttt.w"


/*:21*/
#line 204 "./ttt.w"


/*:16*/
#line 31 "./ttt.w"

/*22:*/
#line 227 "./ttt.w"

/*25:*/
#line 243 "./ttt.w"


/*:25*/
#line 228 "./ttt.w"

/*26:*/
#line 246 "./ttt.w"


/*:26*/
#line 229 "./ttt.w"

/*28:*/
#line 257 "./ttt.w"

for(i= 0;i<total_best_moves;++i){
if(newmove(XPLAYER,best_moves[i],gameboard_ptr,charboard_ptr)!=
NOTEMPTY)
break;
}
++squares_filled;

/*:28*/
#line 230 "./ttt.w"

if(squares_filled> 8){
gameover= TRUE;
}

/*:22*/
#line 32 "./ttt.w"

}
/*29:*/
#line 266 "./ttt.w"

printf("Game over!\n");/*:29*/
#line 34 "./ttt.w"

return(0);
}



/*:1*//*15:*/
#line 184 "./ttt.w"

int newmove(int player,int square,int*gameboard,char*charboard)
{
if(*(gameboard+square)!=EMPTY){
return(NOTEMPTY);
}
*(gameboard+square)= player;
*(charboard+charboard_index[square])= playerchar[player];
/*13:*/
#line 172 "./ttt.w"

printf("%s",charboard);

/*:13*/
#line 192 "./ttt.w"

return(0);
}


/*:15*/
