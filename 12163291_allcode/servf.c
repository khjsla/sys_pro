#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include <fcntl.h> //O_W....
#include <unistd.h> //write,  open() etc


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
   int i;
   int z;
   for(i=0;i<4;i++){
   s2 = accept(s1, (struct sockaddr *)&cli_addr, &xx);
   z=fork();

   if(z==0){
   printf("we passed accept. new socket num is %d\n", s2);

// communacation //
//   
   int f;
   char filepath[50]; //path
   char filecontents[50]; //content
   // read msg from client
   printf("now reading from client\n");
   y=read(s2, buf, 50);
   buf[y]=0;
   printf("we got %s from cli(%d)\n", buf,i);
   if(strcmp(buf,"hello")==0) {
	   write(s2,"what file do you want?",23);

	   y=read(s2,filepath,50);
	   filepath[y]=0;
	   printf("client want to open this file: %s\nand what contents in that file:\n",filepath);

	   f=open(filepath,O_RDONLY, 00777);
	   if(f!=1){
		   for(;;){
		   y=read(f,filecontents,50);
		   filecontents[y]=0;

		   write(s2,filecontents,y);

		   printf("%s",filecontents);
		   } //stop from here
		   printf("\nfile open success!\n");
	   }
	   else {
		   printf("file open error!\n");
		    write(s2,"nofile",7);
		    }
   }
   else{
   close(s2);   // disconnect the connection
   close(s1);   // close the original socket 
   exit(1);
   }
   // send msg to the client 
   //scanf("%s", buf);
   //close(s2);   // disconnect the connection
   //close(s1);   // close the original socket 
   exit(1);
   }
   else close(s2);
   } 
   close(s1);
}
