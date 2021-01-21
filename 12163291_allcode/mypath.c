#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>

void main(){ 
	int  i,j;
	char buf[500]; 
	char *path;
	char *token[50];


	path = getenv("PATH");
	strcpy(buf,path); //copy
	printf("PATH: %s\n",buf);

	token[0] = strtok(buf,":");
	for(i=1;;i++){
		token[i] = strtok(NULL,":");
		if(token[i]==NULL) break;
	}

	for(j=0;j<i;j++){
		 printf("PATH: %d : %s\n",j,token[j]);
	}
} 
