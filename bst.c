#include <stdio.h>
#include <stdlib.h>

struct node *rootMain;
struct node{
    int data;
    struct node *left;
    struct node *right;
};

struct node *insert(struct node *rootNode,int dataToBeInserted){
    if(rootNode == NULL){
        printf("inserted\n");
        struct node *nodeToBeInserted = malloc(sizeof(struct node));
        nodeToBeInserted->data = dataToBeInserted;
        nodeToBeInserted->left = NULL;
        nodeToBeInserted->right = NULL;
        //printf("insertion of new node complete\n");
        return nodeToBeInserted;
    }
    if(dataToBeInserted < rootNode->data){
       // printf("inserting less than %d \n",rootNode->data);
        rootNode->left = insert(rootNode->left,dataToBeInserted);
    }
    else if(dataToBeInserted > rootNode->data){
        //printf("inserting greater than %d \n",rootNode->data);
        rootNode->right = insert(rootNode->right,dataToBeInserted);
    }
    else if(dataToBeInserted == rootNode->data){
        printf("not inserted\n");
    }
    return rootNode;
}

void search(struct node *rootNode,int dataToBeSearchedFor){
    if(rootNode == NULL){
        printf("absent\n");
        return;
    }
    if(dataToBeSearchedFor == rootNode->data){
        printf("present\n");
        return;
    }

    if(dataToBeSearchedFor < rootNode->data){
        search(rootNode->left,dataToBeSearchedFor);
    }
    else{
        search(rootNode->right,dataToBeSearchedFor);
    }
}

struct node *getMinimumNode(struct node *root){
    struct node *currentNode = root;
    while(currentNode != NULL && currentNode->left != NULL){
        currentNode = currentNode->left;
    }
    return currentNode;
}


struct node *delete(struct node*rootNode, int valueToBeDeleted){
    if(rootNode == NULL){
        printf("absent\n");
        return rootNode;
    }

    if(valueToBeDeleted < rootNode->data){
        rootNode->left = delete(rootNode->left,valueToBeDeleted);
    }
    else if(valueToBeDeleted > rootNode->data){
        rootNode->right = delete(rootNode->right,valueToBeDeleted);
    }
    else{
        if(rootNode->left == NULL){
            struct node *temp = rootNode->right;
            free(rootNode);
            printf("deleted\n");
            return temp;
        }
        else if(rootNode->right == NULL){
            struct node *temp = rootNode->left;
            free(rootNode);
            printf("deleted\n");
            return temp;
        }
        else{
            struct node *temp = getMinimumNode(rootNode->right);
            rootNode->data = temp->data;
            rootNode->right = delete(rootNode->right,temp->data);
        }
    }
    return rootNode;
}

void printBst(struct node *rootNode){
    if(rootNode == NULL){
        return;
    }

    //printf("printing tree %d\n", rootNode->data);
    printf("(");
    printBst(rootNode->left);
    //printf("printed left side \n");
    printf("%d",rootNode->data);
    printBst(rootNode->right);
    printf(")");
    //printf("printed right side \n");
}



int main(int argc, char **argv){
    char line[128];
    size_t len = sizeof(line);

    while(fgets(line,len,stdin) != NULL){ 
            char operation; 
            int value; 
            sscanf(line,"%c %d",&operation,&value);  
            if(operation == 'i'){
                //printf("value is %d\n",value);
                rootMain = insert(rootMain, value);
            }            
            else if(operation == 's'){
                search(rootMain,value);
            }
            else if(operation == 'p'){
                printBst(rootMain);
                printf("\n");
            }
            else if(operation == 'd'){
                rootMain = delete(rootMain,value);
            }
            else{
                exit(EXIT_FAILURE);
            }
    } 
    //printBst(rootMain);
}   