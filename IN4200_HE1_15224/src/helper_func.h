#ifndef HELPER_FUNC_H
#define HELPER_FUNC_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

void print2dtab(char **A, int m, int n){
    for (size_t i = 0; i < m; ++i) {
        printf("| ");
        for (size_t j = 0; j < n; ++j) {
            printf("%d ", A[i][j]);
        }
        printf("|\n");
    }
}

void print_int_vector(int *A, int n){
    printf("| ");
    for (size_t i = 0; i < n; ++i) {
      printf(" %d ", A[i]);
    }
    printf("|\n");
}

void free2dtable(char **A){
  free(A[0]);
  free(A);
}

#endif
