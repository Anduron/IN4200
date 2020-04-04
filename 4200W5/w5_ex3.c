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

void foo (int N, double **mat, double **s, int *v) {
  int i,j;
  double val;

  for (j=0; j<N; j++){
    for (i=0; i<N; i++){
      val = 1.0*(v[j]%256);
      mat[i][j] = s[i][j]*(sin(val)*sin(val)-cos(val)*cos(val));
    }
  }
}

void bar (int N, double **mat, double **s, int *v){
  /*
  Optimized foo
  */

  int i,j;
  double val;

  for (j=0; j<N; j++){
    for (i=0; i<N; i++){
      mat[i][j] = s[i][j]*val;
    }
  }
}

void baz (int N, double **mat, double **s, int *v){
  /*
  Optimized bar
  */

  int rest;
  double val;

  rest = N%4;
  for (size_t j=0; j<N; j++){
    val = -cos(2.0*(v[j]%256));
    for (size_t i=0; i<N-rest; i+=4){
      mat[i][j] = s[i][j]*val;
      mat[i+1][j] = s[i+1][j]*val;
      mat[i+2][j] = s[i+2][j]*val;
      mat[i+3][j] = s[i+3][j]*val;
    }
    for(size_t i = N-rest; i < N; i++){
      mat[i][j] = s[i][j]*val;
    }
  }
}

void foofaster (int N, double **mat, double **s, int *v)
{
    double *val = malloc(256 * sizeof *val);
    int *vtab = malloc(N * sizeof *vtab);
    // Table of possible values. This should really be constructed once,
    // outside the scope of this function.
    for (int i = 0; i < 256; i++) {
        val[i] = -cos(2.0*i);
    }
    // Table matching values of v to values in val.
    for (size_t i = 0; i < N; i++) {
        vtab[i] = abs(v[i]%256);
    }
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            mat[j][i] = s[j][i]*val[vtab[i]];
        }
    }
    free(val);
    free(vtab);
}

void foofaster2 (int N, double **mat, double **s, int *v)
{
    double *val = malloc(256 * sizeof *val);
    int *vtab = malloc(N * sizeof *vtab);
    // Table of possible values. This should really be constructed once,
    // outside the scope of this function.
    for (int i = 0; i < 256; i++) {
        val[i] = -cos(2.0*i);
    }
    // Table matching values of v to values in val.

    for (int j = 0; j < N; j++) {
        vtab[j] = abs(v[j]%256);
        for (int i = 0; i < N; i++) {
            mat[j][i] = s[j][i]*val[vtab[i]];
        }
    }
    free(val);
    free(vtab);
}

int main(){
  int N, *v;
  double **mat, **s;
  clock_t t1, t2, t3, t4, t5;

  N = 10000;

  allocate2d(&mat,N,N);
  allocate2d(&s,N,N);
  v = (int *)calloc(N,sizeof(int));

  t1 = clock();
  foo(N,mat,s,v);
  t1 = clock() - t1;

  t2 = clock();
  bar(N,mat,s,v);
  t2 = clock() - t2;

  t3 = clock();
  baz(N,mat,s,v);
  t3 = clock() - t3;

  t4 = clock();
  foofaster(N,mat,s,v);
  t4 = clock() - t4;

  t5 = clock();
  foofaster2(N,mat,s,v);
  t5 = clock() - t5;

  printf("time of foo: %lfms \ntime of bar: %lfms \ntime of baz: %lfms \n", 1000*(double)t1/CLOCKS_PER_SEC, 1000*(double)t2/CLOCKS_PER_SEC, 1000*(double)t3/CLOCKS_PER_SEC);
  printf("time of foofaster: %lfms \ntime of foofaster2: %lfms \n", 1000*(double)t4/CLOCKS_PER_SEC, 1000*(double)t5/CLOCKS_PER_SEC);
  free2darray(mat);
  free2darray(s);
  free(v);

  return 0;
}
