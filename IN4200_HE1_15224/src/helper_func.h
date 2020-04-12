#ifndef HELPER_FUNC_H
#define HELPER_FUNC_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

void print2dtab(char **A, int m, int n){
    /*
    1. char **A the char double pointer that you want to print. A is an mxn 2D table.
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

void free2dtable(char **A){
  /*
  1. char **A the double pointer char array you want to deallocate.
  Frees a double pointer in one line in main.
  */
  free(A[0]);
  free(A);
}

#endif
