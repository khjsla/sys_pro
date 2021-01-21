#include <stdio.h>
#include <string.h>

int main(){
   char buf[20];
   
   printf("enter a sentence\n");
   gets(buf);
   printf("I got %s from you. length:%d\n", buf, strlen(buf));
   
   printf("enter the same sentence again\n");
   fgets(buf, 20, stdin);
   printf("I got %s from you. length:%d\n", buf, strlen(buf));
}

