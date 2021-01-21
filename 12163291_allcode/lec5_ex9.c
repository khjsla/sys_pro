#include <stdio.h>
#include <string.h>  // you need this header file for string functions
int main(){
     char *x, *y, *z;
     x="hello"; y="hi"; z="bye";
     printf("%s %s %s\n", x, y, z);
     printf("%p %p %p\n", x, y, z);

}
