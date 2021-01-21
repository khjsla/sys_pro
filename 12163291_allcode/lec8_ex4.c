#include <stdio.h>

void main(int argc, char * argv[]){ // this program receives command line arguments
   printf("hi\n");
   printf("%d\n", argc);     // number of arguments: 1
   printf("%s\n", argv[0]);  // the first argument: program name
   printf("%s\n", argv[1]);  // the second command line argument
   printf("%s\n", argv[2]);  // the second command line argument
}
