#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
 char temp0[20], *temp1[10], *temp2[10];
 printf("enter src file name\n");
 //gets(temp0);
 scanf("%s",temp0);

 temp1[0]=temp0;
 
 printf("enter dest file name\n");
 //gets(temp0);
 scanf("%s",temp0);

 temp2[0]=temp0;
 
 printf("src file:%s dest file:%s\n", temp1[0], temp2[0]);

}

