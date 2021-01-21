#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	int x,y;
	char buf=0;
	int i=0;

	x=open("test03.wav",O_RDWR,00777);
	y=lseek(x,44,SEEK_SET); //data end = 44

	for(int i=0;i<15112;i++){
		write(x,&buf,1);
	}
}

