#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void disp_cont(int x);

void main(int argc, char *argv[]){ 
	   int x; 

	   x=open(argv[1], O_RDONLY, 00777);  // open the specified fil
	   if (x==-1){                           // if there is an error
		   perror("error in open");           // report it
		   exit(1);                           // and stop the progr
	   }
	   disp_cont(x);

}

void disp_cont(int x){
	   char buf[20];
	   int y; 
	   for(;;){ 
		y=read(x, buf, 20);                // read max 20 bytes 
		if (y==0) break;                   // if end-of-file, get out								             
			write(1, buf, y);               // write to termina
	} 
}
