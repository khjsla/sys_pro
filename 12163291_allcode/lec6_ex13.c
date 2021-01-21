#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	int x1, y1, y2, y3, z;
	int s, size;

	char fname[20];
	char buf[20];
        
	printf("enter file name to split\n");
	scanf("%s",fname);
	x1 = open(fname,O_RDWR,00777);

	struct stat FileStat; //for stat
	fstat(x1, &FileStat); //fastat
	size = FileStat.st_size; //size

	s=strlen(fname);
	fname[s]='1';
	fname[s+1]=0;
	y1=open(fname,O_RDWR|O_CREAT,00777);
	fname[s]='2';
	y2=open(fname,O_RDWR|O_CREAT,00777);
	fname[s]='3';
	y3=open(fname,O_RDWR|O_CREAT,00777);

	int i=0;
	for(i=0;i<size/3;i++){
		z=read(x1,buf,1);
		write(y1,buf,z);
	}
	for(i=size/3;i<size*(2/3);i++){
		z=read(x1,buf,1);
		write(y2,buf,z);
	}
	for(i=size*(2/3);i<size;i++){
		z=read(x1,buf,1);
		write(y3,buf,z);
	}
	fname[s] =0;
	printf("%s is split into %s1, %s2, %s3\n",fname,fname,fname,fname);

}

