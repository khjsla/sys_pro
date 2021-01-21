#include <stdio.h>
#include <string.h>  // you need this header file for string functions
void main(){
  printf("Enter a string\n");
  
  char buf[20]; //for stirng in
  gets(buf);

  int x = strlen(buf);//x is string len

  int i;

  for(i=0;i<x;i++){
    printf("%c\n",buf[i]);
  }
}
