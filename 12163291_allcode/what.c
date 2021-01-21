#include <stdio.h>
#include <string.h>
int main(){
   char buf[20];
   printf("Enter a sentence\n");
   gets(buf);
   printf("You entered %s from you.\n", buf);
}

