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
#include <signal.h> //for sigterm

#define SERV_TCP_PORT 11004
#define SERV_ADDR "165.246.38.151"

void main(){
   int x,y;
   struct sockaddr_in serv_addr;
   char buf[50];
   char buf2[50];
   char buf3[50];
   printf("Hi, I am the client\n");
   
   bzero((char *)&serv_addr, sizeof(serv_addr));
   serv_addr.sin_family=PF_INET;
   serv_addr.sin_addr.s_addr=inet_addr(SERV_ADDR);
   serv_addr.sin_port=htons(SERV_TCP_PORT);

   //open a tcp socket
   if ((x=socket(PF_INET, SOCK_STREAM, 0))<0){
      printf("socket creation error\n");
      exit(1);
   }
   printf("socket opened successfully. socket num is %d\n", x);

   //connect to the server
   if (connect(x, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
      printf("can't connect to the server\n");
      exit(1);
   }
   // now start ping-pong-pang-pung protocol
   printf("enter ping\n");
   gets(buf);
   write(x, buf, strlen(buf)); // send "ping"
   y=read(x, buf,50); // read "pong"
   //printf("we got this msg: ");
   write(1,buf,y);    // show it
   
   if(strcmp(buf,"pong")!=0){
           printf("\nfrom server. END!");
	   close(x);
	   exit(0);
   }
   
   printf("\n");
   printf("enter pang\n");
   gets(buf2);
   write(x, buf2, strlen(buf2)); // send "ping"
   y=read(x, buf2, 50); // read "pung"
   //printf("we got this msg: ");
   write(1,buf2,y);    // show it

   if(strcmp(buf2,"pung")!=0){
           printf("\n");
	   close(x);
	   exit(0);
   }
   
   char namebuf[50];
   printf("\n");
   printf("enter name\n");
   gets(namebuf);
   write(x, namebuf, strlen(namebuf)); // send "ping"
   write(1,namebuf,y);    // show name
   
   char agebuf[10];
   printf("\n");
   printf("enter age\n");
   gets(agebuf);
   write(x, agebuf, strlen(agebuf)); // send age
   write(1,agebuf,y);    // show age
    
   int f;
   int i;
   f=fork();
   if(f!=0){ //pa
	   for(i=0;i<5;i++){
	   printf("\nto other cli: ");
	   gets(buf);
	   write(x,buf,strlen(buf));
	   if(strcmp(buf,"bye")==0){
		   printf("bye, done\n");
		   kill(f,SIGTERM);
		   break;
	   }
	   }
   }
   else {
	   for(i=0;i<5;i++){
	   y=read(x,buf,50);
	   buf[y]=0;
	   write(1,buf,strlen(buf));
	   printf("\ngot from other cli through serv");
	   if(strcmp(buf,"bye")==0){
		   printf("bye, done\n");
		   close(x);
		   exit(0);
	   } 
	   }
   }
   close(x);  // disconect the communication
}

