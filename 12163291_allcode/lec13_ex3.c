#include <stdio.h>
#include <signal.h>
void foo(){
	wait();
}

void main(){
	int x,y;

	x = fork();
	if (x==0) for(;;);  // first child
	else{
		y=fork();
		if (y==0) for(;;);  // second child
		else signal(17,foo);
	}
	for(;;);     // parent
}
