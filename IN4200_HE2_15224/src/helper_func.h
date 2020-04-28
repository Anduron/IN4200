#ifndef HELPER_FUNC_H
#define HELPER_FUNC_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void print2int_array(int **A, int m, int n){
    /*
    1. int **A the int double pointer that you want to print. A is an mxn 2D array.
    2. int m the height of A.
    3. int n the lenght of A.
    */
    for (size_t i = 0; i < m; ++i) {
        printf("| ");
        for (size_t j = 0; j < n; ++j) {
            printf("%d ", A[i][j]);
        }
        printf("|\n");
    }
}

int **empty2D_array(int ***A, int m, int n){
    /*
    1. int **A the int double pointer that you want to print. A is an mxn 2D array.
    2. int m the height of A.
    3. int n the lenght of A.
    */
    *A = (int **)malloc(m*sizeof(int*));      //allocating table2D
    *A[0] = (int *)malloc(m*n*sizeof(int));     //allocating table2D

    for(size_t i = 0; i < m; i++){
      (*A)[i] = &((*A)[0][n*i]);       //allocating table2D
    }
    return *A;
}

int **zeroes2D_array(int ***A, int m, int n){
    /*
    1. int **A the int double pointer that you want to print. A is an mxn 2D array.
    2. int m the height of A.
    3. int n the lenght of A.
    */
    *A = (int **)calloc(m,sizeof(int*));      //allocating table2D
    *A[0] = (int *)calloc(m*n,sizeof(int));     //allocating table2D

    for(size_t i = 0; i < m; i++){
      (*A)[i] = &((*A)[0][n*i]);       //allocating table2D
    }
    return *A;
}

int **read2D_array(char *filename, int ***A, int *m, int *n){
  FILE *infile = fopen(filename, "r");

  if (infile == NULL) {
    printf("ERROR: Failure to open file %s\n", filename); //test to see if filename exists
    exit(0);
  }

  fscanf(infile, "%*[^\n]\n"); //SKIP: line 1
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 2
  fscanf(infile, "%*s %d %*s %d \n", &*m, &*n); //getting the values of m and n

  zeroes2D_array(A,*m,*n);

  fclose(infile);
}


void print_int_vector(int *A, int n){
    /*
    1. int *A the pointer you want to print. A is an n long vector of integers.
    2. int n the lenght of A.
    */
    printf("| ");
    for (size_t i = 0; i < n; ++i) {
      printf(" %d ", A[i]);
    }
    printf("|\n");
}

void free2dint_array(int **A){
  /*
  1. int **A the double pointer char array you want to deallocate.
  Frees a double pointer in one line in main.
  */
  free(A[0]);
  free(A);
}

#endif
