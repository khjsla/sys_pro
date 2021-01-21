#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(){
	int x;
	x=fork();
	printf("hello\n");
	for(;;);
}
