#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void allocate2d(double ***AA, int nx, int ny){
  double **A;
  A = (double **)calloc(nx,sizeof(double*));
  A[0] = (double *)calloc(nx*ny,sizeof(double));

  for(int i = 0; i<nx; i++){
    A[i] = &(A[0][ny*i]);
  }
  *AA = A;
}

void free2darray(double **A){
  free(A[0]);
  free(A);
}

void print2d(double **A, int nx, int ny){
  printf("[");
  for (int i = 0; i < nx; i++){
    printf("[");
    for (int j = 0; j < ny; j++){
      printf(" %f ", A[i][j]);
      }
    printf("]\t");
    }
  printf("]\n");
}

int main(){
  /*
  for (j=0; j<N; j++){
    for (i=0; i<=j; i++){
      y[j] += A[j][i]*B[i]
    }
  }
  */

  int nx, ny;
  double **A, *B, *y;

  ny = nx = 5;

  allocate2d(&A,ny,nx);
  B = (double *)calloc(nx,sizeof(double));
  y = (double *)calloc(ny,sizeof(double));

  for(int i = 0; i < nx; i++){
    B[i] = (rand()%10);
    for(int j = 0; j < ny; j++){
      A[j][i] = (rand()%10);
    }
  }


  print2d(A,ny,nx);


  int rest = ny%4;
  for (size_t j = 0; j<ny-rest; j+=4){
    for (size_t i = 0; i <= j; i++){
      y[j] += A[j][i]*B[i];
      y[j+1] += A[j+1][i]*B[i];
      y[j+2] += A[j+2][i]*B[i];
      y[j+3] += A[j+3][i]*B[i];
    }
  }
  for (int j = ny - rest; j < ny; j++){
    for (int i = 0; i <= j; i++){
      y[j] += A[j][i]*B[i];
    }
  }

  printf("here");

  free2darray(A);
  free(B);
  free(y);

  return 0;
}
