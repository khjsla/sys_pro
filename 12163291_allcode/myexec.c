#include <stdio.h>
#include <string.h>

void main(){
	char *x[10];
	int f=0;
	char buf[20];
	int i,j,k;
	char gcwd[20];

	for(k=0;k<5;k++){
	getcwd(gcwd,20);
	printf("[%s]$ ",gcwd);
	gets(buf);

	x[0] = strtok(buf," ");
	for(i=1;;i++){
		x[i]=strtok(NULL," ");
		if(x[i]==NULL) break;
	}
	
	f = fork();
	if(f==0) {
	execve(x[0], x, 0); // change to /bin/cat with one argument f1   
	}
	else sleep(1);

	printf("....my exec execs to'");
	for(j=0;j<i;j++){
		printf("%s ",x[j]);
	}
	printf("'\n");
	}
}
