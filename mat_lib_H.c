#include <math.h>

void allocate3d(double ****AA,int nx, int ny, int nz){
  double ***A;

  A = (double ***)calloc(nx,sizeof(double **)*sizeof(double*));
  A[0] = (double **)calloc(nx*ny,sizeof(double *));
  A[0][0] = (double *)calloc(nx*ny*nz,sizeof(double));

  for(int i = 0; i < nx; i++){
    A[i] = &(A[0][ny*i]);
  }
  for(int j = 0; j<nx*ny; j++){
    A[0][j] = &(A[0][0][nz*j]);
  }
  *AA = A;
}

void allocate2d(double ***AA, int nx, int ny){
  double **A;
  A = (double **)calloc(nx,sizeof(double*));
  A[0] = (double *)calloc(nx*ny,sizeof(double));

  for(int i = 0; i<nx; i++){
    A[i] = &(A[0][ny*i]);
  }
  *AA = A;
}

void free3darray(double ***A){
  free(A[0][0]);
  free(A[0]);
  free(A);
}

void free2darray(double **A){
  free(A[0]);
  free(A);
}
