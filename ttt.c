#define MAXLINE 100 \

#define CHAR_BOARD_LENGTH 62 \

#define MAXANSWERS 8
#define NOTFOUND -1
#define MAXPERMS 24 \

/*1:*/
#line 7 "./ttt.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

/*4:*/
#line 44 "./ttt.w"

static const enum{
BAD_O_COMMAND
}error_msg;

static const char*error[]= {
"I don't understand your command."
"Enter a label like A1 and press [ENTER].",
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


/*:4*//*9:*/
#line 102 "./ttt.w"

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

/*:9*//*12:*/
#line 144 "./ttt.w"

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

/*:12*/
#line 12 "./ttt.w"

typedef enum{FALSE,TRUE}boolean;

/*16:*/
#line 167 "./ttt.w"

void newmove(int player,int square,int*gameboard,char*charboard);

/*:16*//*25:*/
#line 214 "./ttt.w"

int twoofthree(int test[],int test_array_length,int perms[][3]);

/*:25*/
#line 15 "./ttt.w"


int main(int argc,char*argv[])
{
/*6:*/
#line 74 "./ttt.w"

char line[MAXLINE];
int nextOmove;

/*:6*//*10:*/
#line 124 "./ttt.w"

int gameboard[9]= {0,0,0,0,0,0,0,0,0};
char charboard[]= 
"\n   |   |   \n"
"-----------\n"
"   |   |   \n"
"-----------\n"
"   |   |   \n\n";
int*gameboard_ptr= gameboard;
char*charboard_ptr= charboard;


/*:10*/
#line 19 "./ttt.w"

boolean gameover;
gameover= FALSE;

/*2:*/
#line 38 "./ttt.w"


/*:2*/
#line 23 "./ttt.w"

/*14:*/
#line 158 "./ttt.w"


/*:14*/
#line 24 "./ttt.w"


/*5:*/
#line 66 "./ttt.w"

printf("%s\n",greeting);


/*:5*/
#line 26 "./ttt.w"


while(gameover==FALSE){
/*7:*/
#line 80 "./ttt.w"

/*15:*/
#line 162 "./ttt.w"

printf("%s",charboard);

/*:15*/
#line 81 "./ttt.w"

while(1){
printf("Your move?\n");
fgets(line,sizeof(line),stdin);
if(line[2]!='\n'||
line[0]<'A'||line[0]> 'C'||
line[1]<'1'||line[1]> '3'){
printf("%s\n",error[BAD_O_COMMAND]);
continue;
}else break;
}

nextOmove= (line[0]-'A')*3;
nextOmove+= line[1]-'1';
newmove(OPLAYER,nextOmove,gameboard_ptr,charboard_ptr);


/*:7*/
#line 29 "./ttt.w"

/*18:*/
#line 184 "./ttt.w"

/*19:*/
#line 192 "./ttt.w"


/*:19*/
#line 185 "./ttt.w"

/*29:*/
#line 228 "./ttt.w"

newmove(XPLAYER,A1,gameboard_ptr,charboard_ptr);
gameover= TRUE;

/*:29*/
#line 186 "./ttt.w"

/*20:*/
#line 195 "./ttt.w"


/*:20*/
#line 187 "./ttt.w"

/*21:*/
#line 198 "./ttt.w"


/*:21*/
#line 188 "./ttt.w"

/*22:*/
#line 201 "./ttt.w"


/*:22*/
#line 189 "./ttt.w"


/*:18*/
#line 30 "./ttt.w"

/*23:*/
#line 205 "./ttt.w"

/*26:*/
#line 218 "./ttt.w"


/*:26*/
#line 206 "./ttt.w"

/*27:*/
#line 221 "./ttt.w"


/*:27*/
#line 207 "./ttt.w"

/*28:*/
#line 224 "./ttt.w"


/*:28*/
#line 208 "./ttt.w"


/*:23*/
#line 31 "./ttt.w"

}
/*30:*/
#line 233 "./ttt.w"
/*:30*/
#line 33 "./ttt.w"

return(0);
}

/*:1*//*17:*/
#line 172 "./ttt.w"

void newmove(int player,int square,int*gameboard,char*charboard)
{
*(gameboard+square)= player;
*(charboard+charboard_index[square])= playerchar[player];
/*15:*/
#line 162 "./ttt.w"

printf("%s",charboard);

/*:15*/
#line 177 "./ttt.w"

return;
}


/*:17*/
