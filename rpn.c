#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct stack myStack;
struct stack{
    int *stackData;
    int index;
};

void push(int val){
    if(myStack.index == (sizeof(myStack.stackData)-1)){
        printf("stack is full \n");
        exit(EXIT_FAILURE);
    }
    myStack.index ++;
    myStack.stackData[myStack.index] = val;
    //printf("push %d %d\n",myStack.index,val);
}

int pop(){
    if(myStack.index == -1){
        printf("stack is empty \n");
        return __INT32_MAX__;
        //exit(EXIT_FAILURE);
    }
    int lastVal = myStack.stackData[myStack.index];
    myStack.index --;
    //printf("pop %d %d\n",myStack.index,lastVal);
    return lastVal;
}

int isValidOperator(char c){
     if(c == '+' || c == '-' || c == 'x' || c == '/' ){
        return 1;
     }
     else{
        return 0;
     }
}

void printStack(){
    for(int i = 0; i <= myStack.index; i ++){
        printf("%d",myStack.stackData[i]);
    }
    printf("\n");
}

int stackSize(){
    return myStack.index+1;
}

int main(int argc, char **argv){
    myStack.index = -1;
    char digitStore[258];
    int digitStoreCount = 0;

    if(argc < 2){
        exit(EXIT_FAILURE);
    }
    char *inputString = argv[1];
    //printf("inputString %s %ld character %c\n",inputString, strlen(inputString)-1,inputString[strlen(inputString)-1]);
    if(isValidOperator(inputString[strlen(inputString)-1]) == 0){
        exit(EXIT_FAILURE);
    }

    myStack.stackData = (int *)malloc(strlen(inputString) * sizeof(int));

    for(int i = 0; i < strlen(inputString); i++){
        if(isdigit(inputString[i])){
            //printf("digit is %c\n",inputString[i]);
            digitStore[digitStoreCount] = inputString[i];
            digitStoreCount ++;     
        }
        else if(inputString[i] == ',' || isValidOperator(inputString[i])){
            //printf("comma deleted \n");
            //printf("number = %d\n",atoi(digitStore));
            digitStore[digitStoreCount] = '\0';
            if(strlen(digitStore) != 0){
                push(atoi(digitStore));
                digitStoreCount = 0;
            }
        }

        if(inputString[i] == '+'){
            //printf("we're adding \n");
            if(stackSize() < 2){
                exit(EXIT_FAILURE);
            }
            int a = pop();
            int b = pop();
            int sum = a + b;
            //printf("doing sub %d %d %d\n",a,b,sum);
            push(sum);
            //printStack();
        }
        else if(inputString[i] == '-'){
            //printf("we're subtracting \n");
            if(stackSize() < 2){
                exit(EXIT_FAILURE);
            }
            int a = pop();
            int b = pop();
            int difference = b - a;
            //printf("doing sub %d %d %d\n",b,a,difference);
            push(difference);
            //printStack();
        }
        else if(inputString[i] == 'x'){
            //printf("we're multiplying \n");
            if(stackSize() < 2){
                exit(EXIT_FAILURE);
            }
            int a = pop();
            int b = pop();
            int product = a * b;
            //printf("doing mult %d %d %d\n",a,b,product);
            push(product);
            //printStack();
        }
        else if(inputString[i] == '/'){
            //printf("we're dividing \n");
            if(stackSize() > 2){
                exit(EXIT_FAILURE);
            }
            int a = pop();
            int b = pop();
            if(a == 0){
                exit(EXIT_FAILURE);
            }
            int quotient = b / a;
            //printf("doing div %d %d %d\n",a,b,quotient);
            push(quotient);
        }
    }
    if(myStack.index != 0){
        exit(EXIT_FAILURE);
    }
    printStack();
    free(myStack.stackData);
    //15,2+9
    //17,1,1-/
}
