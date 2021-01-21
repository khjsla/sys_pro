#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
  int x, x1, y;
  x=open("f1", O_RDONLY, 00777);
  x1=open("f2", O_WRONLY|O_CREAT|O_TRUNC,00777);
  char buf[512];
  int cnt=0;
  int size;

  struct stat FileStat;
  fstat(x, &FileStat);
  size = FileStat.st_size;

  for(;;){
      y=read(x,buf,1);
      //if (y==0) break;
      cnt++;
      if(cnt==size) break;
  }

  write(x1, buf, cnt);
}

