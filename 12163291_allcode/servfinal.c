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
	int state;
	int partner;
};

int find_socket(char *name);
void handle_protocol(int x, fd_set * pset, struct client cli[]);
void handle_state_1(int x, fd_set *pset, char *buf, struct client cli[]);
void handle_state_2(int x, fd_set *pset, char *buf, struct client cli[]);
void handle_state_3(int x, fd_set *pset, char *buf, struct client cli[]);
void handle_state_4(int x, fd_set *pset, char *buf, struct client cli[]);
void handle_state_5(int x, fd_set *pset, char *buf, struct client cli[]);
void handle_state_6(int x, fd_set *pset, char *buf, struct client cli[]);
void handle_state_7(int x, fd_set *pset, char *buf, struct client cli[]);
void handle_state_8(int x, fd_set *pset, char *buf, struct client cli[]);

void main(){
	int s1,s2, i, x, y;
	struct sockaddr_in serv_addr, cli_addr;
	char buf[50];
	socklen_t  xx;
	struct client cli[50];

	for(i=0;i<50;i++) cli[i].state=0; //init

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
	for(i=0;i<100;i++){ 
		rset=pset; 
		select(maxfd, &rset, NULL, NULL, NULL);
		for(x=0;x<maxfd;x++){ 
			if (FD_ISSET(x, &rset)){
				if (x==s1){ 
					s2 = accept(s1, (struct sockaddr *)&cli_addr, &xx);
					cli[s2].state=1;
					printf("new cli at socket %d\n",s2);
					FD_SET(s2, &pset);  
				}else{
					handle_protocol(x, &pset, cli);
				}
			}
		}
	}
}

void handle_protocol(int x, fd_set * pset, struct client cli[]){
	int y; 
	char buf[50];
	y=read(x, buf, 50); 
	buf[y]=0; 
	if (cli[x].state==1){ 
		handle_state_1(x, pset, buf, cli);
	}else if (cli[x].state==2){ 
		handle_state_2(x, pset, buf, cli);
	}else if (cli[x].state==3){
		handle_state_3(x, pset, buf, cli);
	}else if (cli[x].state==4){ 
		handle_state_4(x, pset, buf, cli);
	}else if (cli[x].state==5){
		handle_state_5(x, pset, buf, cli);
	}else if (cli[x].state==6){
		handle_state_6(x, pset, buf, cli);
	}else if (cli[x].state==7){
		handle_state_7(x, pset, buf, cli);
	}else if (cli[x].state==8){
		handle_state_8(x, pset, buf, cli);
	}
}

void handle_state_1(int x, fd_set *pset, char *buf, struct client cli[]){
	if (strcmp(buf, "hello")==0){
		printf("received hello from socket %d\n",x);
		fflush(stdout); 
		write(x, "name(ID)?", 9);
		printf("sent name(ID)? to socket %d\n",x);
		fflush(stdout);
		cli[x].state=2;
	}else{
		printf("error to socket %d\n",x);
		fflush(stdout);
		write(x, "protocol error", 14);
		close(x);
		FD_CLR(x, pset);
	}
}

void handle_state_2(int x, fd_set *pset, char *buf, struct client cli[]){
	printf("name(id) of socket %d is %s\n",x,buf);
	fflush(stdout);
	int i;
	int chk=0;
	char login[100];
	char *token;
	char *z[30];
	int xcnt=0;

	int read;
	FILE *fp;
	fp=fopen("login.txt","r");
	while(feof(fp)==0){
	//fgets(login,sizeof(login),fp);
	read = fread(login,sizeof(char),100,fp);
	}

	//printf("login.txt: %s\n",login);

	token = strtok(login," ");
	z[0] = token;
	for(i=1;;i++){
		token = strtok(NULL," ");
		z[i] = token;
		xcnt++; //배열개수
		if(token==NULL) break;
	}

	//name(id) registered check
	for(i=0;i<xcnt;i++){
		//printf("%s\n",z[i]);
		//이미 있는 아이디면 chk1
		if(strcmp(buf,z[i])==0) chk=1;
		else{ chk=0; } //아니면 그대로 0
	}

	if(chk==0){
		write(x,"regi",4);//to cli
		printf("sent want regi to socket %d\n",x);
		fflush(stdout);
		cli[x].state=6;
	}
	else{
		write(x,"chat",4);
		printf("sent ready? to socket %d\n",x);
		fflush(stdout);
		cli[x].state=3;
	}

	fclose(fp);
}

void handle_state_3(int x, fd_set *pset, char *buf, struct client cli[]){
	int i;
	char namelist[200]={0};

	if(strcmp(buf,"yes")==0){
		write(x,"cli name list:",14);
		for(i=0;i<50;i++){
			if(cli[i].state>=3){
				sprintf(namelist,"%s %s",namelist,cli[i].name);
			}
		}
		printf("received yes from socket %d\n",x);
		fflush(stdout);
		write(x,namelist,strlen(namelist));
		write(x,"\n",1);
		cli[x].state=4;
	}
	else{
		printf("error to socket %d\n",x);
		fflush(stdout);
		write(x, "protocol error", 14);
		close(x);
		FD_CLR(x, pset);
	}
}

void handle_state_4(int x, fd_set *pset, char *buf, struct client cli[]){
	int i,y;
	int flag_cmp=0;

	printf("got name- %s from sk %d\n",buf,x);
	fflush(stdout);

	for(i=0;i<50;i++){
		if(strcmp(buf,cli[i].name)==0){
			write(x,"go(chat)\n",9);
			flag_cmp=1;
			cli[x].partner=i;
			cli[x].state=5;
			break;
		}
	}

	if(flag_cmp==0){
		printf("error to socket %d\n",x);
		fflush(stdout);
		write(x, "protocol error : no name", 24);
		close(x);
		FD_CLR(x, pset);
	}
}

void handle_state_5(int x, fd_set *pset, char *buf, struct client cli[]){
	char newbuf[80];
	sprintf(newbuf,"%s : %s\n",cli[x].name,buf);
	write(cli[x].partner,newbuf,strlen(newbuf));
}

void handle_state_6(int x, fd_set *pset, char *buf, struct client cli[]){
	//regi
	if(strcmp(buf,"yes")==0){
		write(x,"write ID n PW",13); //to cli
		cli[x].state=7; //for pw
	}else{
		printf("cli %d dont want regi\n",x);
		fflush(stdout);
		write(x,"bye",3); //to cli
		close(x);
		FD_CLR(x,pset);
	}
}

void handle_state_7(int x, fd_set *pset, char *buf, struct client cli[]){

	char newbuf[50];
	FILE *fp;
	fp = fopen("login.txt","a+");
	strcpy(cli[x].name,buf);

	sprintf(newbuf,"%s ",buf);
	fputs(newbuf,fp);
	cli[x].state=8; //for pw

	fclose(fp);
}

void handle_state_8(int x, fd_set *pset, char *buf, struct client cli[]){
	char newbuf[50];
	FILE *fp;
	fp = fopen("login.txt","a+");

	sprintf(newbuf,"%s ",buf);
	fputs(newbuf,fp);
	write(x,"save done. chat ready?",22);
	cli[x].state=3; //for chat

	fclose(fp);
}

