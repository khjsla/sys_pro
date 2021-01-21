#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h> //for done

#define SERV_TCP_PORT 80
#define SERV_ADDR "165.246.13.108"

void main(){
   int x,y;
   struct sockaddr_in serv_addr;
   char buf[50];
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
   // send msg to the server
   printf("now i am connected to the server. enter a string to send\n");
   //scanf("%s",buf);
   int i,fk;
   fk = fork(); //ch, pa

   //printf("to server:\n");
   
   if(fk==0){ //if child,
   for(i=0;i<10;i++){
   printf("if you want to send somthin, you can send that:\n");
   gets(buf);
   write(x, buf, strlen(buf));
   if (strcmp(buf,"bye")==0) { 
	   kill(getppid(),SIGTERM); 
	   break; 
	   }
      }
   }
   else{
   for(i=0;i<10;i++){
   // read from server
   printf("now reading from server\n");
   y=read(x, buf, 50);
   buf[y]=0;
   printf("from server: %s\n", buf);
   }
   }

   close(x);  // disconect the communication
}
