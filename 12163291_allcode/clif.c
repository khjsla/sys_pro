#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h> //for done

#include <fcntl.h>
#include <unistd.h>

#define SERV_TCP_PORT 11004
#define SERV_ADDR "165.246.38.151"

void main(){
   int x,y;
   struct sockaddr_in serv_addr;
   char buf[50];
   char servbuf[50];
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
   //commnunication
   // send msg to the server
   printf("now i am connected to the server. enter [hello] to open file\n");
   gets(buf); 
   write(x, buf, strlen(buf));	   

   y=read(x,servbuf,50);
   servbuf[y]=0; //what do you wan
   printf("serv said: %s",servbuf);

   char fname[50];
   char filename[50];
   printf("\nclient want:\n");
   gets(fname); //file
   sprintf(filename,"./%s",fname);
   write(x,filename,strlen(filename));

   int i;
   int z;
   char filecontents[50];

   for(i=0;;i++){
	   z=read(x,filecontents,50);
	   if(z==0) break;
	   filecontents[z]=0;
	   if(strcmp(filecontents,"nofile")==0) exit(1);
	   printf("%s",filecontents);
   }//stop from here
   close(x);  // disconect the communication
}
