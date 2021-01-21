#include <stdio.h>
#include <signal.h>
void foo(int signum){
	printf("I am ok\n");
}
void main(){
	signal(2, foo);   // prepare for signal number 2. same as signal(SIGINT, foo)
	signal(15, foo);   // prepare for signal number 2. same as signal(SIGINT, foo)
	signal(1, foo);   // prepare for signal number 2. same as signal(SIGINT, foo)
	for(;;);
}

