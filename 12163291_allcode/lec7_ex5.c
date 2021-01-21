#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	int x1,x2,y1,y2;
	char buf[20];
	
	int i=0;

	x1=open("test03.wav",O_RDWR,00777);
	x2=open("test033.wav",O_RDWR,00777);
	y1=lseek(x1,15112,SEEK_SET); //start sound 15112
	y2=lseek(x2,44,SEEK_SET); //from data end 44
	for(;;){
		y1=read(x1,buf,20);
		if(y1==0)break;
		write(x2,buf,y1);
	}

}

