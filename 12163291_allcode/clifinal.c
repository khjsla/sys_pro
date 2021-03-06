#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/select.h>

#define SERV_TCP_PORT 11004
#define SERV_ADDR "165.246.38.151"

void main(){
	int x,y;
	struct sockaddr_in serv_addr;
	char buf[50];
	printf("Hi, I am the client\n");

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family=PF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(SERV_ADDR);
	serv_addr.sin_port=htons(SERV_TCP_PORT);

	if ((x=socket(PF_INET, SOCK_STREAM, 0))<0){
		printf("socket creation error\n");
		exit(1);
	}
	printf("socket opened successfully. socket num is %d\n", x);

	if (connect(x, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("can't connect to the server\n");
		exit(1);
	}

	printf("send hello\n");
	fflush(stdout);
	gets(buf);
	write(x, buf, strlen(buf)); 

	y=read(x, buf,50);  //name? 
	write(1,buf,y);   
	printf("\n");

	printf("send name(id):\n");
	fflush(stdout);
	gets(buf); //name in
	write(x, buf, strlen(buf)); 
	
	char bufwhat[4];
	y=read(x, bufwhat, 4);  //regi?? or chati
	bufwhat[y]=0;
	//printf("\n check '%s'\n",bufwhat);
		
	if(strcmp(bufwhat,"regi")!=0){ //회원가입 
	printf("regi yes or no?\n"); //regi
	fflush(stdout);
	gets(buf); //yes or no
	write(x, buf, strlen(buf)); //yes to serv
	
	y=read(x, buf, 50); //write IDand PW or Bye
	write(1,buf,y);
	printf("\n");

	char bufid[50];
	char bufpw[50];
	printf("send id:\n");
	fflush(stdout);
	gets(bufid); //id
	write(x, bufid, strlen(bufid)); //to serv

	printf("send pw:\n");
	fflush(stdout);
	gets(bufpw); //pw
	write(x, bufpw, strlen(bufpw)); //to serv
	
	y=read(x, buf, 50);  //save done...
	write(1,buf,y);
	printf("\n");

	printf("send yes or no\n");
	fflush(stdout);
	gets(buf); //yes or no
	write(x, buf, strlen(buf)); //client list
	 
	y=read(x, buf, 50); //lisg
	write(1,buf,y);
	printf("\n");

	printf("send chat partner name:\n");
	fflush(stdout);
	gets(buf);
	write(x, buf, strlen(buf)); 

	y=read(x, buf, 50); //go
	write(1,buf,y);
	printf("chat start\n");
	fflush(stdout);

	int ch,i;
	ch=fork();
	if (ch==0){ 
		for(i=0;i<20;i++){
		y=read(x, buf, 50);
		write(1,buf,y);
		}
		if(strcmp(buf,"bye")==0){
			close(x);
			exit(0);
		}
	}else{  
		for(i=0;i<20;i++){
		gets(buf);
		write(x, buf, strlen(buf));
		}
		if(strcmp(buf,"bye")==0){
			close(x);
			exit(0);
		}
	}
}
	else{
	printf("chat yes or no\n");
	fflush(stdout);
	gets(buf); //yes or no
	write(x, buf, strlen(buf)); //client list
	
	y=read(x, buf, 50); //list 
	write(1,buf,y);
	printf("\n");

	printf("send chat partner name:\n");
	fflush(stdout);
	gets(buf);
	write(x, buf, strlen(buf)); 

	y=read(x, buf, 50); //go
	write(1,buf,y);
	printf("chat start\n");
	fflush(stdout);

	int ch,i;
	ch=fork();
	if (ch==0){ 
		for(i=0;i<20;i++){
		y=read(x, buf, 50);
		write(1,buf,y);
		}
		if(strcmp(buf,"bye")==0){
			close(x);
			exit(0);
		}
	}else{  
		for(i=0;i<20;i++){
		gets(buf);
		write(x, buf, strlen(buf));
		}
		if(strcmp(buf,"bye")==0){
			close(x);
			exit(0);
		}
	}
	}
close(x); 
}

