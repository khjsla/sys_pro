#include <stdio.h>
#include <string.h>

void main(){
	int i;
	char text[20];
	char *token;
	char *x[10];
	int cnt=0;

	printf("input:\n");
	fflush(stdout);
	gets(text);

	token = strtok(text," ");
	x[0]=token;
	for(i=1;;i++){
		token = strtok(NULL," ");
		x[i] = token;
		cnt++;
		if(token==NULL) break;
	}

	printf("output:\n");
	fflush(stdout);

	for(i=0;i<cnt;i++)
		printf("%s\n",x[i]);
}
