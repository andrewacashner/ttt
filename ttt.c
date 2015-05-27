#define CHAR_BOARD_LENGTH 62 \

#define MAXANSWERS 8
#define NOTFOUND -1
#define MAXPERMS 24 \

/*1:*/
#line 7 "./ttt.w"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

/*6:*/
#line 52 "./ttt.w"

static const char blankboard[]= 
"\n   |   |   \n"
"-----------\n"
"   |   |   \n"
"-----------\n"
"   |   |   \n\n";

static const char divider[]= 
"************\n";

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

/*:6*//*18:*/
#line 142 "./ttt.w"

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

/*:18*/
#line 12 "./ttt.w"

typedef enum{FALSE,TRUE}boolean;

/*9:*/
#line 91 "./ttt.w"

void newmove(int player,int square,int*gameboard,char*charboard);

/*:9*//*19:*/
#line 156 "./ttt.w"

int twoofthree(int test[],int test_array_length,int perms[][3]);

/*:19*/
#line 15 "./ttt.w"


int main(int argc,char*argv[])
{
/*7:*/
#line 78 "./ttt.w"

int gameboard[9]= {0,0,0,0,0,0,0,0,0};
char charboard[CHAR_BOARD_LENGTH];
int*gameboard_ptr= gameboard;
char*charboard_ptr= charboard;

/*:7*/
#line 19 "./ttt.w"

boolean gameover;
gameover= FALSE;

/*2:*/
#line 38 "./ttt.w"


/*:2*/
#line 23 "./ttt.w"

/*8:*/
#line 86 "./ttt.w"

strcpy(charboard,blankboard);

/*:8*/
#line 24 "./ttt.w"


/*3:*/
#line 41 "./ttt.w"


/*:3*/
#line 26 "./ttt.w"


while(gameover==FALSE){
/*4:*/
#line 44 "./ttt.w"


/*:4*/
#line 29 "./ttt.w"

/*11:*/
#line 108 "./ttt.w"

/*12:*/
#line 116 "./ttt.w"


/*:12*/
#line 109 "./ttt.w"

/*23:*/
#line 170 "./ttt.w"

newmove(XPLAYER,A1,gameboard_ptr,charboard_ptr);
gameover= TRUE;

/*:23*/
#line 110 "./ttt.w"

/*13:*/
#line 119 "./ttt.w"


/*:13*/
#line 111 "./ttt.w"

/*14:*/
#line 122 "./ttt.w"


/*:14*/
#line 112 "./ttt.w"

/*15:*/
#line 125 "./ttt.w"


/*:15*/
#line 113 "./ttt.w"


/*:11*/
#line 30 "./ttt.w"

/*16:*/
#line 129 "./ttt.w"

/*20:*/
#line 160 "./ttt.w"


/*:20*/
#line 130 "./ttt.w"

/*21:*/
#line 163 "./ttt.w"


/*:21*/
#line 131 "./ttt.w"

/*22:*/
#line 166 "./ttt.w"


/*:22*/
#line 132 "./ttt.w"


/*:16*/
#line 31 "./ttt.w"

}
/*24:*/
#line 175 "./ttt.w"
/*:24*/
#line 33 "./ttt.w"

return(0);
}

/*:1*//*10:*/
#line 96 "./ttt.w"

void newmove(int player,int square,int*gameboard,char*charboard)
{
*(gameboard+square)= player;
*(charboard+charboard_index[square])= playerchar[player];
printf("%s%s",charboard,divider);
return;
}


/*:10*/