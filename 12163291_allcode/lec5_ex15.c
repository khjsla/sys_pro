#include <stdio.h>
#include <string.h>  // you need this header file for string functions
int main(){
      char x[100];
      int i=0;
       
      printf("enter a sentence\n");
      gets(x);	
      int slen=strlen(x);
      
      printf("sentence length after gets:%d\n", slen);
      for(i=0;i<slen;i++){
         printf("%x ", x[i]);
      }
      
      printf("\nenter the same sentence\n");
      fgets(x, 99, stdin); // read max 99 char’s. 
      slen=strlen(x);
      
      printf("sentence length after fgets:%d\n", slen);
      for(i=0;i<slen;i++){
         printf("%x ", x[i]);
      }

}
