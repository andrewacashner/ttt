#define MAXLINE 100 \

/*1:*/
#line 3 "./mwe.w"

#include <stdio.h> 

int main(void){
/*3:*/
#line 19 "./mwe.w"

char input_line[MAXLINE];
int newmove;

/*:3*/
#line 7 "./mwe.w"

/*4:*/
#line 23 "./mwe.w"

while(1){
printf("Your move?\n");
fgets(input_line,sizeof(input_line),stdin);
if(input_line[2]!='\n'||
input_line[0]<'A'||input_line[0]> 'C'||
input_line[1]<'1'||input_line[1]> '3'){
printf("Move out of range. Try again.\n");
}else{
newmove= (input_line[0]-'A')*3;
newmove+= input_line[1]-'1';
printf("Move to square number %d\n",newmove);
break;
}
}/*:4*/
#line 8 "./mwe.w"

return(0);
}

/*:1*/
