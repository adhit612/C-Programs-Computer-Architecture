#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **allocateMatrix(int dimension){
    int **matrix = malloc(dimension*sizeof(int*));
    for(int i = 0; i < dimension; i ++){
        matrix[i] = malloc(dimension * sizeof(int));
    }
    return matrix;
}

int **populateZeroMatrix(int dimension){
    int **matrix = allocateMatrix(dimension);
    for(int r = 0; r < dimension; r ++){
        for(int c = 0; c < dimension; c ++){
            matrix[r][c] = 0;
        }
    }
    return matrix;
}

void freeMatrix(int **matrix,int dimension){
    for(int r = 0; r < dimension; r ++){
            free(matrix[r]);
    }
    free(matrix);
}

void copyMatrix(int **source,int **destination,int dimension){
    for(int r = 0; r < dimension; r ++){
        for(int c = 0; c < dimension; c ++){
            destination[r][c] = source[r][c];
        }
    }
}

void printMatrix(int **matrix,int dimension){
    for(int r = 0; r < dimension; r ++){
        for(int c = 0; c < dimension; c ++){
            printf("%d",matrix[r][c]);
        }
        printf("\n");
    }
}


int **multiplyMatricies(int **a,int multiplyAmount,int rowColSize){
    int  **b = allocateMatrix(rowColSize);
    copyMatrix(a,b,rowColSize);
    int **result = allocateMatrix(rowColSize);

    while(multiplyAmount > 1){
       /* printMatrix(result,rowColSize);
        printf("\n");
                printMatrix(a,rowColSize);
                        printf("\n");

                        printMatrix(b,rowColSize);
                                printf("\n");*/

            for(int r = 0; r < rowColSize; r++){
                for(int c = 0; c < rowColSize;c++){
                    //int aColTracker = 0;
                    //int bRowTracker = 0;                  
                    /*while(bRowTracker < rowColSize){
                        result[r][c] += a[r][aColTracker] * b[bRowTracker][c];
                        //printf("values are %d %d %d \n", result[r][c], a[r][aColTracker],b[bRowTracker][c]);
                        aColTracker ++;
                        bRowTracker ++;
                    }*/
                    result[r][c] = 0;
                    for(int w = 0; w < rowColSize; w ++){
                        result[r][c] += a[r][w] * b[w][c];
                    }
                    //aColTracker = 0;
                    //bRowTracker = 0;
                }
            }
            //printf("multiple amount %d\n ",multiplyAmount);
            //printMatrix(result,rowColSize);
            //exit(EXIT_SUCCESS);
            copyMatrix(result,a,rowColSize);
            multiplyAmount --;  
    }
    freeMatrix(a,rowColSize);
    freeMatrix(b,rowColSize);
    return result;   
}



void printResultMatrix(int **a,int dimension){
    for(int r = 0; r < dimension; r++){
        for(int c = 0; c < dimension;c++){
            if(c == dimension-1){
                printf("%d" ,a[r][c]);
            }
            else{
                printf("%d " ,a[r][c]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char **argv){
    FILE *fp;
    fp = fopen(argv[1],"r");
    char line [128];
    size_t len = sizeof(line);

    int **matrix;
    int matrixRow = 0;

    int fileLineCounter = 1;
    int fileSizeNumOfLines = 0;
    int dimension = 0;
    int multipleAmount = 0;

    /*printf("file address: %s\n",argv[1]);
    fseek(fp,0,SEEK_END);
    int fileSize = ftell(fp);
    fseek(fp,0,SEEK_SET);
    printf("size is %d",fileSize);*/

    while(fgets(line,len,fp)!=NULL){
        fileSizeNumOfLines ++;
    }
    //printf("amount of lines is %d\n",fileSizeNumOfLines);
    fseek(fp,0,SEEK_SET);

    
    while(fgets(line,len,fp)!=NULL){
            if(fileLineCounter == 1){
                char *numbers = strtok(line," ");
                dimension = atoi(numbers);
                matrix = allocateMatrix(dimension);
                //printf("dimension is %d",dimension);
            }
            else if(fileLineCounter == fileSizeNumOfLines){
                char *numbers = strtok(line," ");
                multipleAmount = atoi(numbers);
                if(multipleAmount == 0){
                    printResultMatrix(populateZeroMatrix(dimension),dimension);
                    exit(EXIT_SUCCESS);
                }
                //printf("power is%d ", multipleAmount);
            }
            else{
                char *numbers = strtok(line," ");
                int matrixCol = 0;
                while(numbers != NULL){
                    int n = atoi(numbers);
                    //printf("matrix val %d",n);
                    numbers = strtok(NULL, " ");
                    matrix[matrixRow][matrixCol] = n;
                    matrixCol++;
                }
                matrixRow ++;
            }
            fileLineCounter++;
            //printf("\n");
    }
    //printf("matrix val is %d\n",matrix[1][1]);
    if(multipleAmount == 1){
        printResultMatrix(matrix,dimension);
    }
    else{
        int **resultingValue = multiplyMatricies(matrix,multipleAmount,dimension);
        printResultMatrix(resultingValue,dimension);
        freeMatrix(resultingValue,dimension);
    }
   // printf("counter is %d",fileLineCounter);
}

