#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	   int x1, x2, y;
	   char buf[50];

	   x1=open("f1", O_RDONLY, 00777); // open f1 for reading
           x2=open("f2", O_RDWR | O_CREAT | O_TRUNC, 00777); // open f2 for writing
	   for(;;){
	        y=read(x1, buf, 20); // read max 20 bytes from f1
		if (y==0) break; // if end-of-file, g
		write(x2, buf, y); // writ
	          }
	   return 0;
}

