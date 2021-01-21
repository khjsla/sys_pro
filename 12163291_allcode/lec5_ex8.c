#include <stdio.h>
#include <string.h>  // you need this header file for string functionsint 
int  main(){
char x[10];    // x is a character array with 10 rooms
scanf("%s",x);
int y = strlen(x);
int cnt=0;
for(int i=0; i<3;i++){
if(cnt==0) printf("a");
if(cnt==1) printf("b");
if(cnt==2) printf("c"); 
for(int j=1;j<y;j++){
printf("%c",x[j]);
}
cnt++;
printf("\n");
}
}
