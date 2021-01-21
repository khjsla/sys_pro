#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h> //***

void main(){ 
	int x,y,status, i,j,k,q;
	int wordcnt;
	char buf[50]; 
	char path[50];
	char *argv[10];
	char *tokenpath[50];
	char *p;
	char copypath[500];
	char command[50];

	for(i=0;i<10;i++){ // use a finite loop instead of an infinite one
		printf("$");
		gets(buf);
		 
		if(strcmp(buf,"exit")==0) break;
		
		argv[0] = strtok(buf," ");
		for(q=1;;q++){
			argv[q]= strtok(NULL," ");
			if(argv[q]==NULL)break;
		}

		p = getenv("PATH");
		strcpy(copypath, p);
				
		tokenpath[0] = strtok(copypath,":");
		for(j=1;;j++){
			tokenpath[j]=strtok(NULL,":");
			if(tokenpath[j]==NULL) break;
		}

		x=fork(); 
		if (x==0){ // child
			for(k=0;k<j;k++){ 
			sprintf(command,"%s/%s",tokenpath[k],argv[0]);
			y=execve(command, argv, 0); 
			if (y<0){ 
				perror("exec failed"); 
				exit(1); 
			} 
			}
		}
		else if(strcmp(argv[q-1],"&")==0){}//마지막에 &가 있는 경우 
		else wait(&status); 
	} 
} 
