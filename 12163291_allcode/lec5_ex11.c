#include <stdio.h>
#include <string.h>  // you need this header file for string functions
int main(){
     char y[10];
     //y="hello1";  // this is ok
     strcpy(y, "hello2"); // error because y has no space for "hello2"
}
