#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void main(int argc, char *argv[]){ 
	   int x1,x2,y1,y2; 
	   char buf; 
	   int i;

	   x1=open(argv[1], O_RDONLY, 00777);  // open the specified fil
	   if (x1==-1){                           // if there is an error
		   perror("error in open");           // report it
		   exit(1);                           // and stop the progra
	}

	   for(;;){ 
		y1=read(x1, &buf, 1);                // read max 20 bytes 
		if (y1==0) break;                   // if end-of-file, get out								             
		//write(1, buf);               // write to termina
		printf("%x ", buf);
	   }
	   printf("\n");
} 
