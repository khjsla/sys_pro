#include <stdio.h>
#include <string.h>  // you need this header file for string functions
int main(){
 char *x[100];
 int i=0;
 for(;;){
 printf("enter names\n");
 scanf("%s",x[i]);
 if(strcmp(x[i]=="end")){{for(int j=0;j<i;j++)printf("%s",x[j]);}break;}
 i++;
 }
}
