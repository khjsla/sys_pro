#include <stdio.h>
#include <string.h>  // you need this header file for string functions
int main(){
   char *strarr[10]={NULL};
   strarr[0]="hello";
   strarr[1]="bye";
   //strcpy(strarr[1],"bye");
   printf("%s %s\n", strarr[0], strarr[1]);

}
