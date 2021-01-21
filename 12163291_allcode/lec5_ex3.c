#include <stdio.h>
#include <string.h>  // you need this header file for string functions
void main(){
char x[10];    // x is a character array with 10 rooms
int i;
for(i=0;i<10;i++){
   x[i]=i+97;
}
for(i=0;i<10;i++){  
   printf("%d %c \n", x[i], x[i]);  // print each character with its ascii number
}

}
