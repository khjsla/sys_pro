#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(){
	int x;
	x=fork();
	if (x==0){ 
		printf("hello: %d\n", x);
	}else{ 
		printf("hi: %d \n", x);
	}
}
