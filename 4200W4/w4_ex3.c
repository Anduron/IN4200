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

void free2darray(double **A){
  free(A[0]);
  free(A);
}


double **matmul2d(double **A, double **B, int Anx, int ABn, int Bny){

  double **C;
  allocate2d(&C,Anx,Bny);

  for(int i = 0; i < Anx; i++){
    for(int j = 0; j < Bny; j++){
      for(int k = 0; k < ABn; k++){
        C[i][j] += A[i][k]*B[k][j];
      }
    }
  }
  return C;
}

double **fastmatmul2d(double **A, double **B, int Anx, int ABn, int Bny){
  int left = Bny%4;
  double **C;
  allocate2d(&C,Anx,Bny);

  for(int i = 0; i < Anx; i++){
    for(int j = 0; j < Bny-left; j+=4){
      for(int k = 0; k < ABn; k++){
        C[i][j] += A[i][k]*B[k][j];
        C[i][j+1] += A[i][k]*B[k][j+1];
        C[i][j+2] += A[i][k]*B[k][j+2];
        C[i][j+3] += A[i][k]*B[k][j+3];
      }
    }
    for(int j = Bny - left; j < left; j++){
      for(int k = 0; k < ABn; k++){
        C[i][j] += A[i][k]*B[k][j];
      }
    }
  }
  return C;
}

int main(){
  int nx, ny;
  double **A, **B;
  clock_t t1, t2;

  nx = 100;
  ny = 100;

  allocate2d(&A,nx,ny);
  allocate2d(&B,ny,nx);

  //loop fusion
  for(int i = 0; i < nx; i++){
    for(int j = 0; j < ny; j++){
      A[i][j] = (double) (rand()%10);
      B[j][i] = (double) (rand()%10);
    }
  }


  printf("\nArray A: \n");
  //print2d(A,nx,ny);
  printf("\nArray B: \n");
  //print2d(B,ny,nx);

  t1 = clock();
  double **C = matmul2d(A,B,nx,ny,nx);
  t1 = clock() - t1;

  printf("\nArray C = A@B with : \n");
  //print2d(C,nx,nx);

  t2 = clock();
  double **D = fastmatmul2d(A,B,nx,ny,nx);
  t2 = clock() - t2;

  printf("\nArray C = A@B, with fast matmul function: \n");
  //print2d(D,nx,nx);

  printf("\ntime used on matmul2d: t1 = %lfms \ntime used of fastmatmul2d: t2 = %lfms\n", (double) t1/CLOCKS_PER_SEC*1000, (double) t2/CLOCKS_PER_SEC*1000);

  free2darray(A);
  free2darray(B);
  free2darray(C);
  return 0;
}
