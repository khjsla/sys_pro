#include <stdio.h>
#include <string.h>  // you need this header file for string functions
void main(){
printf("Enter a string\n");
char buf[20]; //for stirng in
gets(buf);
printf("the len is %d\n",strlen(buf));
}
