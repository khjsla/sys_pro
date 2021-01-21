#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define SERV_TCP_PORT 11004
#define SERV_ADDR "165.246.38.151"

void main(){
   int s1,s2, x, y;
   struct sockaddr_in serv_addr, cli_addr;
   char buf[50];
   socklen_t  xx;

   printf("Hi, I am the server\n");
   
   bzero((char *)&serv_addr, sizeof(serv_addr));
   serv_addr.sin_family=PF_INET;
   serv_addr.sin_addr.s_addr=inet_addr(SERV_ADDR);
   serv_addr.sin_port=htons(SERV_TCP_PORT);

   //open a tcp socket
   if ((s1=socket(PF_INET, SOCK_STREAM, 0))<0){
      printf("socket creation error\n");
      exit(1);
   }
   printf("socket opened successfully. socket num is %d\n", s1);

   // bind ip
   x =bind(s1, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
   if (x < 0){
      printf("binding failed\n");
      exit(1);
   }
   printf("binding passed\n");
   listen(s1, 5);
   xx = sizeof(cli_addr);
   s2 = accept(s1, (struct sockaddr *)&cli_addr, &xx);
   printf("we passed accept. new socket num is %d\n", s2);

   // read msg from client
   printf("now reading from client\n");
   int i,fk;
   fk=fork();

   if(fk==0){
   for(i=0;i<10;i++){
   y=read(s2, buf, 50);
   buf[y]=0;
   printf("we got %s from cli\n", buf);
   if(strcmp(buf,"bye")==0) { 
	   kill(getppid(),SIGTERM);  
	   break;
	   } //for client bye done
       }
   }
   else{
   for(i=0;i<10;i++){
   // send msg to the client 
   printf("enter a string to send to client\n");
   //scanf("%s", buf);
   gets(buf);
   write(s2, buf, strlen(buf));
   }
   }
   close(s2);   // disconnect the connection
   close(s1);   // close the original socket 
}
