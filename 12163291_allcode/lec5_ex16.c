#include <stdio.h>
#include <string.h>  // you need this header file for string functions
int main(){
 char x[100];
 char y[100];
 int i=0;

 printf("Enter a sentense\n");
 scanf("%s",x);
 
 for(i=0;i<strlen(x);i++){
 y[i]=x[i]; //save
 }
 
 printf("You entered %s\nThere were %d words:\n",x,strlen(x));
 
 char *ptr = strtok(x," ");
 while(ptr != NULL){
 printf("%s\n",ptr);
   ptr = strtok(NULL," ");
 }
 
 printf("The origin was %s",y);
 
}
