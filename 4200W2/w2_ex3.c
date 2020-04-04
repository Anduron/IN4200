#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void print3d(double ***A,int l,int m,int n){

  printf("\n[");
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
}

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

void free3darray(double ***A){
  free(A[0][0]);
  free(A[0]);
  free(A);
}

void initialize_magic_trig(double ***v, int nx, int ny, int nz){

  double denominator = ((nx-1)*(ny-1)*(nz-1));

  for(int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        v[i][j][k] = 2.0 + sin((i*j*k*M_PI)/denominator);
      }
    }
  }
}

/*
void solve_stencil(double ***u, double ***v, int nx, int ny, int nz, int Nt){
  //Alternate solution
  int size = nx*ny*nz;
  double c = (1.0/6.0);
  //double ***tmp;

  for(int n = 0; n < Nt; n++){
    for(int i = 1; i < nx-2; i++){
      for(int j = 1; j < ny-2; j++){
        for(int k = 1; k < nz-2; k++){
          u[i][j][k] = v[i][j][k] + c*(v[i-1][j][k] + v[i][j-1][k] + v[i][j][k-1] -
            6*v[i][j][k] + v[i+1][j][k] + v[i][j+1][k] + v[i][j][k+1]);
        }
      }
    }
  memcpy(&v,&u,sizeof(u));
  }
  print3d(v,nx,ny,nz); //this one will return the result of u after stencil is complete
}
*/

void solve_stencil(double ***u, double ***v, int nx, int ny, int nz, int Nt){
  //Alternate solution
  int size = nx*ny*nz;
  double c = (1.0/6.0);

  for(int n = 0; n < Nt; n++){
    for(int i = 1; i < nx-2; i++){
      for(int j = 1; j < ny-2; j++){
        for(int k = 1; k < nz-2; k++){
          u[i][j][k] = v[i][j][k] + c*(v[i-1][j][k] + v[i][j-1][k] + v[i][j][k-1] -
            6*v[i][j][k] + v[i+1][j][k] + v[i][j+1][k] + v[i][j][k+1]);
        }
      }
      for(int ii=0; ii<nx;ii++){
        for(int jj=0; jj<ny;jj++){
          memcpy(v[ii][jj],u[ii][jj],sizeof(double)*nz);
        }
      }
    }
  }
}

int main(){
  int l, m, n, Nt;
  double ***u = NULL;
  double ***v = NULL;
  clock_t t;

  Nt = 5;
  l = 5;
  m = 5;
  n = 5;

  allocate3d(&u,l,m,n);
  allocate3d(&v,l,m,n);

  initialize_magic_trig(v,l,m,n);

  print3d(u,l,m,m); //this one will return the initialzed zero array
  print3d(v,l,m,m); //this one will return the result of v after the

  t = clock();
  solve_stencil(u,v,l,m,n,Nt);
  t = (clock() - t);

  double time = ((double) t) / CLOCKS_PER_SEC;

  print3d(u,l,m,m); //this one will return the re
  print3d(v,l,m,m); //

  double flo = Nt*(l-2)*(m-2)*(n-2)*9;
  double flops = (double)flo/time;

  printf("floating point operations = %f\ntime elapsed = %f \nflops of the stencil = %f \n",flo,time,flops);

  free3darray(v);
  free3darray(u);

  return 0;
}
