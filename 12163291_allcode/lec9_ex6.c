#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(){
	int x,y;
	x=fork();
	y=fork();
	printf("hello: %d %d\n", x, y);
}
