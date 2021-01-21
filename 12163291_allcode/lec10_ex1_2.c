#include <stdio.h>
void main(){
	char *k[10];
	k[0]="/bin/ls";
	k[1]=0;
	execve(k[0], k, 0); // change to /bin/ls with no additional argument
}

