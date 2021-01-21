#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	int x1, x2, y;
	char fname[20];
	unsigned char buf[20];

	printf("enter file name\n");
	scanf("%s",fname);
	x1 = open(fname,O_RDONLY,00777);

	for(;;){
		y=read(x1,buf,20);
		scanf("%x",buf);
		if(y==0) break;
		//write(1,buf,y);
		printf("%x",buf);
	}
	return 0;
}

