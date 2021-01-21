#include <stdio.h>
#include <string.h>  // you need this header file for string functions
int main(){
char y[10];
     printf("enter a string\n");
     scanf("%s", y);     // error  becuase y has no space for a string
     printf("you entered %s\n", y);

}
