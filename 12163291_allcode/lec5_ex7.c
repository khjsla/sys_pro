#include <stdio.h>
#include <string.h>  // you need this header file for string functions
int main(){

	for(;;){
		char x[10];
		bool flag =false;

		printf("Enter a string.\n");
		scanf("%s",x);
		printf("You entered %s, len =%d\n",x,strlen(x));


		if(strcmp(x,"hello")==true){
			flag=true;
		}

		if(flag==true){
			printf("hello bye\n");
			break;
		}else{
			printf("no hello\n");
		}
	}
}
