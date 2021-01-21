#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	   int x, y;
	   char buf[50];

	      x=open("f1", O_RDONLY, 00777); // open f1 in the current directory
	      y=read(x, buf, 20); // read max 20 bytes. return actual number of bytes read in y.
	      buf[y]=0;           // make buf a string
	      printf("%s\n", buf); // and display
	      return 0;
}

