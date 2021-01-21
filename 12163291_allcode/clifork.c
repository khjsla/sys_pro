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
   char buf2[50];
   char buf3[50];
   int f;
   int i;
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

   //f=fork();
   //if(f!=0){
   // now start ping-pong-pang-pung protocol
   printf("cli at socket %d => serv: ",x);
   gets(buf);
   write(x, buf, strlen(buf)); // send "ping"
   y=read(x, buf,50); // read "pong"
   printf("serv => cli at socket %d : ",x); 
   fflush(stdout);
   write(1,buf,y);    // show it
   
   if(strcmp(buf,"pong")!=0){
           printf("\nfrom server. END!");
	   close(x);
	   exit(0);
   }
   
   printf("\n");
   printf("cli at socket %d => serv: ",x);
   gets(buf2);
   write(x, buf2, strlen(buf2)); // send "ping"
   y=read(x, buf2, 50); // read "pung"
   //printf("we got this msg: ");
   printf("serv => cli at socket %d : ",x);
   fflush(stdout);
   write(1,buf2,y);    // show it

   if(strcmp(buf2,"pung")!=0){
           printf("\n");
	   close(x);
	   exit(0);
   }
   
   printf("\nProtocol completed. Start chatting\n");
   //}
   for(i=0;i<5;i++){
   //else{ //parent
   f=fork();
   
   if(f==0){
   printf("after pung and send to other cli with serv use: \n");
   gets(buf3); //for hello
   write(x, buf3, strlen(buf3)); // send "hello"
   }
   else
   {
   y=read(x, buf3, 50); // read "hello"
   printf("\n");
   fflush(stdout);
   write(1,buf3,y);    // show it
   printf("\nwe got upper from serv(and serv got that from the other cli\n");
   }

   if(strcmp(buf3,"bye")==0){
           break;
   }
   
   }

   close(x);  // disconect the communication
   //}
}
