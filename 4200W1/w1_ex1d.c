#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(){

  int l, m, n;
  double ***A;

  l = 3;
  m = 3;
  n = 3;

  A = (double ***)malloc(l * sizeof(double **) * sizeof(double *));
  A[0] = (double **)malloc(l * m * sizeof(double *));
  A[0][0] = (double *)malloc(l * m * n * sizeof(double));

  for (int i = 1; i < l; i ++) {
    A[i] = &(A[0][m * i]);
  }
  for (int j = 1; j < l*m; j++) {
    A[0][j] = &(A[0][0][n * j]);
  }

  for (int i = 0; i < l; i++){
    for (int j = 0; j < m; j++){
      for (int k = 0; k < n; k++){
          A[i][j][k] = i+j+k;
      }
    }
  }

  printf("[");
  for (int i = 0; i < l; i++){
    printf("[");
    for (int j = 0; j < m; j++){
      printf("[");
      for (int k = 0; k < n; k++){
          printf(" %f ", A[i][j][k]);
      }
      printf("]\t");
    }
    printf("]\n");
  }
  printf("]\n");

  return 0;
}
