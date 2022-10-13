#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv){
    char *argument = argv[1];
    int size = strlen(argument);
    int count = 0;

    for(int i = 0; i < size; i ++){
        if(!isalpha(argument[i])){
            continue;
        }
        while(count < 13){
            if(argument[i] == 'Z'){
                argument[i] = 'A';
            }
            else if(argument[i] == 'z'){
                argument[i] = 'a';
            }
            else{
                argument[i] = (char)((int)(argument[i])+1);
            }
            count ++;
        }
        count = 0;
    }

    printf("%s\n", argument);
    return 0;
}