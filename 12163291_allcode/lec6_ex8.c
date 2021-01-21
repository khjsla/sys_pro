#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	int x1, x2, y;
	char buf[20];

	x1 = open("lec6_ex4",O_RDONLY,00777);
	x2 = open("cplec6_ex4",O_RDWR|O_CREAT|O_TRUNC,00777);

	for(;;){
		y=read(x1,buf,20);
		if(y==0) break;
		write(x2,buf,y);
	}
	return 0;
}

