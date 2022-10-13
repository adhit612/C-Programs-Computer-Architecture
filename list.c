#include <stdio.h>
#include <stdlib.h>

extern int errno;

struct node *head;
struct node{
    int data;
    struct node *next;
};

void printList(){
    //printf("%s\n","reached printing stage");
    //exit(EXIT_SUCCESS);
   struct node *current = head;
   int size = 0;
   while(current != NULL){
    size ++;
    current = current->next;
   }
   //printf("size is%d\n",size);
   //exit(EXIT_SUCCESS);
   current = head;
   printf("%d %s",size,":");
   while(current != NULL){
    printf(" %d",current->data);
    current = current->next;
   }
   printf("\n");
}

void insert(int dataToBeInserted){
    struct node *nodeToBeInserted = malloc(sizeof(struct node));
    nodeToBeInserted->data = dataToBeInserted;
    nodeToBeInserted->next = NULL;
    //printf("%s\n","beginning insert");
    struct node *current = head;
    struct node *previous = NULL;

    if(head == NULL){
        //printf("%s\n","inserting new head");
        head = nodeToBeInserted;
        return;
    }

    while(current != NULL){
        if(nodeToBeInserted->data == current->data){
            free(nodeToBeInserted);
            return;
        }
        else if(nodeToBeInserted->data > current->data && current->next == NULL){
            //printf("%s\n","inserting at end");
            current->next = nodeToBeInserted;
            return;
        }
        else if(nodeToBeInserted->data > current->data && current->next != NULL){
           //printf("%s\n","greater than but still going");
           struct node *oldCurrent = current;
           current = current->next;
           previous = oldCurrent;
           //continue;
        }
        else if(nodeToBeInserted->data < current->data && previous == NULL){
            //printf("%s\n","less than and new head");
            struct node *oldCurrent = current;
            head = nodeToBeInserted;
            current = nodeToBeInserted;
            current->next = oldCurrent;
            current = current->next;
            return;
        }       
        else if(nodeToBeInserted->data < current->data && previous != NULL){
            //printf("%s\n","looping less than");
            struct node *oldCurrent = current;
            previous->next = nodeToBeInserted;
            nodeToBeInserted->next = current;
            current = current->next;
            previous = oldCurrent;
            return;
        }
        else{
            printf("insert should not happen");
            exit(EXIT_SUCCESS);
        }
    }
    //printf("%s\n","inserting done");
}

void delete(int dataToBeDeleted){
    //printf("%s\n","delete in session");
    struct node *current = head;
    struct node *previous = NULL;

    while(current != NULL){
        //printf("%s\n","while loop entered");
        if(dataToBeDeleted == current->data && current->next == NULL && previous == NULL){
            //printf("%s\n","deleted head size one");
            free(head);
            head = NULL;
            return;
        }
        else if(dataToBeDeleted == current->data && current->next != NULL && previous == NULL){
            //printf("%s\n","deleted head non size one");
            struct node *oldCurrent = head;
            head = current->next;
            free(oldCurrent);
            return;
        }
        else if(dataToBeDeleted == current->data && current->next == NULL && previous != NULL){
            //printf("%s\n","reached delete at end");
            struct node *oldCurrent = current;
            previous->next = NULL;
            free(oldCurrent);
            return;
        }
        else if(dataToBeDeleted == current->data && current->next != NULL && previous != NULL){
            //printf("%s\n","reached delete both ways");
            struct node *oldCurrent = current;
            previous->next = current->next;
            free(oldCurrent);
            return;
        }
        else if(dataToBeDeleted == current->data){
            //printf("not deleted");
            exit(EXIT_SUCCESS);
        }
        //printf("else conditional");
        previous = current;
        current = current->next;
    }
}

int main (int argc, char **argv){
    char line[128];
    size_t len = sizeof(line);

    while(fgets(line,len,stdin) != NULL){ 
            char operation; 
            int value; 
            sscanf(line,"%c %d",&operation,&value);  
            if(operation == 'i'){
                insert(value);
                printList();
            }
            else if(operation == 'd'){
                delete(value);
                printList();
            } 
            else{
                exit(EXIT_FAILURE);
            }                
    } 

    struct node *current = head;
    while(current != NULL){
        struct node *nextCurrent = current->next;
        free(current);
        current = nextCurrent;
    }
}
    //char operation;
    //int value;

    //int numOfOps = 0;

    //while(1){
    /*int f = scanf("%c %d",&operation,&value);
    if(operation == 'i'){
        //printf("inserted \n");
        insert(value);
        printList();
        printf("%s\n","");
    }
    if(operation == 'd'){
        //printf("deleted \n");
        delete(value);
        printList();
        printf("%s\n","");
    }
    numOfOps ++;
    if(numOfOps == 20){
        exit(-1);
    }*/
    //}
