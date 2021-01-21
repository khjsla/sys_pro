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

	printf("enter ping\n");
	gets(buf);
	write(x, buf, strlen(buf));
	y=read(x, buf,50); 
	write(1,buf,y);    
	printf("\n");

	printf("enter pang\n");
	gets(buf);
	write(x, buf, strlen(buf));
	y=read(x, buf, 50); 
	write(1,buf,y);
	printf("\n");

	printf("enter name\n");
	gets(buf);
	write(x, buf, strlen(buf)); 
	y=read(x, buf, 50); 
	write(1,buf,y);
	printf("\n");

	printf("enter age\n");
	gets(buf);
	write(x, buf, strlen(buf)); 
	y=read(x, buf, 50);
	write(1,buf,y);
	printf("\n");

	int ch,i;
	ch=fork();
	if (ch==0){ 
		for(i=0;i<20;i++){
		y=read(x, buf, 50);
		write(1,buf,y);
		}
	}else{  
		for(i=0;i<20;i++){
		gets(buf);
		write(x, buf, strlen(buf));
		}
	}
close(x); 
}

