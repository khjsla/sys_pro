#include <stdio.h> 
#include <unistd.h> 
#include <string.h>

void main(){ 
	int x,y,status, i,j;
	char buf[50]; 
	char real_buf[50];
	char * argv[10]; 

	for(i=0;i<10;i++){ // use a finite loop instead of an infinite one
		printf("$");
		gets(buf);
		 
		if(strcmp(buf,"exit")==0) break;

		sprintf(real_buf, "/bin/%s",buf);

		argv[0] = strtok(real_buf," ");
		for(j=1;;j++){
			argv[j] = strtok(NULL," ");
			if(argv[j]==NULL) break;
		}

		x=fork(); 
		if (x==0){ // child 
			printf("I am child to execute %s\n", real_buf); 
			y=execve(real_buf, argv, 0); 
			if (y<0){ 
				perror("exec failed"); 
				exit(1); 
			} 
		}
		else if(strcmp(argv[j-1],"&")==0){}//마지막에 &가 있는 경우 
		else wait(&status); 
	} 
} 
