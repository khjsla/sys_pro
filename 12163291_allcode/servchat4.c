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

struct client{
	char name[20];
	char age[5];
};
struct client cli[50];

void handle_protocol(int x, fd_set * pset, int state[]);
void handle_state_1(int x, fd_set *pset, char *buf, int state[]);
void handle_state_2(int x, fd_set *pset, char *buf, int state[]);
void handle_state_3(int x, fd_set *pset, char *buf, int state[]);
void handle_state_4(int x, fd_set *pset, char *buf, int state[]);
void handle_state_5(int x, fd_set *pset, char *buf, int state[]);

void main(){
	int s1,s2, i, x, y;
	struct sockaddr_in serv_addr, cli_addr;
	char buf[50];
	int state[50]={0};
	socklen_t  xx;
	printf("Hi, I am the server\n");

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family=PF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(SERV_ADDR);
	serv_addr.sin_port=htons(SERV_TCP_PORT);
	if ((s1=socket(PF_INET, SOCK_STREAM, 0))<0){
		printf("socket creation error\n");
		exit(1);
	}
	printf("socket opened successfully. socket num is %d\n", s1);

	x =bind(s1, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (x < 0){
		printf("binding failed\n");
		exit(1);
	}
	printf("binding passed\n");
	listen(s1, 5);
	xx = sizeof(cli_addr);

	fd_set rset, pset;
	int maxfd=50;

	FD_ZERO(&rset);
	FD_ZERO(&pset); 


	FD_SET(s1, &pset);
for(i=0;i<20;i++){ 
	rset=pset;  
	select(maxfd, &rset, NULL, NULL, NULL); 
	for(x=0;x<maxfd;x++){ 
		if (FD_ISSET(x, &rset)){
			if (x==s1){ 
			s2 = accept(s1, (struct sockaddr *)&cli_addr, &xx);
			state[s2]=1;
			printf("new cli at socket %d\n",s2);
			FD_SET(s2, &pset);
			}else{ 
			handle_protocol(x, &pset, state);
			}
		}
	}
}
}

void handle_protocol(int x, fd_set * pset, int state[]){
	int y; char buf[50];
	y=read(x, buf, 50); 
	buf[y]=0; 
	if (state[x]==1){ 
		handle_state_1(x, pset, buf, state);
	}else if (state[x]==2){ 
		handle_state_2(x, pset, buf, state);
	}else if (state[x]==3){ 
		handle_state_3(x, pset, buf, state);
	}
}

void handle_state_1(int x, fd_set *pset, char *buf, int state[]){
	if (strcmp(buf, "ping")==0){ 
		write(x, "pong", 4);
		state[x]=2;
	}else{
		write(x, "protocol error", 14);
		close(x);
		FD_CLR(x, pset);
	}
}
void handle_state_2(int x, fd_set *pset, char *buf, int state[]){
	if (strcmp(buf, "pang")==0){ 
		write(x, "pung. send to other cli", 23);
		state[x]=3;
	}else{
		write(x, "protocol error", 14);
		close(x);
		FD_CLR(x, pset);
	}
}
void handle_state_3(int x, fd_set *pset, char *buf, int state[]){
	//strcpy(cli[x].name, buf);
	//write(x,"age?", 4);
	//state[x]=4;
	int i;
	char newbuf[50];
	for(i=4;i<10;i++){
		sprintf(newbuf,"%s\n",buf);
		if(i!=x) write(i,newbuf,strlen(newbuf)); //다른 dlient에
	}
	if(strcmp(buf,"bye")==0){
		close(x);
		FD_CLR(x,pset);
	}
}

void handle_state_4(int x, fd_set *pset, char *buf, int state[]){
	strcpy(cli[x].age, buf);
	write(x, "start chatting", 14);
	state[x]=5;
}

void handle_state_5(int x, fd_set *pset, char *buf, int state[]){
	int i;
	char msg[1024];
	for(i=0;i<50;i++){
		if (i!=x && state[i]==5){
		sprintf(msg,"%s %s to %s %s:%s", cli[x].name,cli[x].age,cli[i].name,cli[i].age,buf); 
		write(i, msg, strlen(msg));
		}
	}
}

