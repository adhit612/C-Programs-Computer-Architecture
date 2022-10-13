#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, char **argv){
   if(sizeof(argv) == 1){
    return EXIT_FAILURE;
   }
    else{
        for(int i = 1; i < argc; i ++){
            for(int j = i+1; j < argc; j ++){
                int compare = strcmp(argv[i],argv[j]);
                if(compare > 0){
                    char *temp = argv[j];
                    argv[j] = argv[i];
                    argv[i] = temp;
                }
            }
        }
   }

   for(int i = 1; i < argc; i ++){
        printf("%s\n",argv[i]);
    }
}