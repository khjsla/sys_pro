#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

void docopy(char* f1, char* f2);
void doxxd(char *f1);
void dopw(char *f1);
void dodir(char *f1);

void main(int argc, char* argv[] ){
	
	if(strcmp(argv[1],"-o")==0){
		docopy(argv[2],argv[3]);
	}
	else if(strcmp(argv[1],"-x")==0){
		doxxd(argv[2]);
	}
	else if(strcmp(argv[1],"-p")==0){
		dopw(argv[2]);
	}
	else if(strcmp(argv[1],"-d")==0){
		dodir(argv[2]);
	}	


void docopy(char* f1, char* f2){
	int x1;
	x1 = open(f1,O_RDONLY, 00777); // input file
	int x2;
	x2 = open(f2, O_WRONLY|O_CREAT|O_TRUNC, 00777); // output file
	int y;
	char buf[20];

	for(;;){
		y=read(x1,buf,20);
		if(y==0) break;
		write(x2,buf,y);
	}
}

void doxxd(char *f1){
	int x = open(f1,O_RDONLY,00777);
	int y;
	char buf;

	for(;;){
		y=read(x,&buf,1);
		if(y==0) break;
		printf("%x ",buf);
	}
	printf("\n");
}

void dopw(char *f1){
	FILE *f;
	char *x;
	char *y;
	int i;
	char buf[20];

	f=fopen(f1,"r");

	for(;;){
		x=fgets(buf,19,f);
		if(x==NULL) break;
		for(i=0;;i++){
			if(i==0){
				y=strtok(buf,":");
			}else{
				y=strtok(NULL,":");
			}

			if(y==NULL) break;
			printf("%s \n",y);
		}
	}
	fclose(f);
}

void dodir(char *f1){
	DIR *dir;
	struct dirent *dir_ent;
	dir = opendir(f1);

	if(NULL!=dir){
		while(dir_ent = readdir(dir)){
			printf("%s \n",dir_ent->d_name);
		}
		closedir(dir);
		}
}
