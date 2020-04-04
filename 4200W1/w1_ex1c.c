#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//compile with $gcc w1_ex1c.c -o ex1c -lm
//run with ./ex1c

void fill_cols(double**,int,int);
void fill_rows(double**,int,int);

int main()
{
  int m, n, t;
  clock_t start, timer_c, timer_r;
  double tr, tc, **A;

  m = 10000;
  n = 10000;
  t = 20;

  A = (double **)malloc(m * sizeof(double *));
  A[0] = (double *)malloc(m * n * sizeof(double)); // This is the actual underlying 1d array of size m * n.

  for (int i = 1; i < m; i ++) {
      A[i] = &(A[0][n * i]);
  }

  for (int t_ = 0; t_ < t; t_++){
    start = clock();

    fill_cols(A, m, n);

    timer_c = clock() - start;

    start = clock();

    fill_rows(A,m,n);

    timer_r = clock() - start;

    tr += ((double)timer_r)/CLOCKS_PER_SEC;
    tc += ((double)timer_c)/CLOCKS_PER_SEC;

  }

  printf("time for rows = %f \n time for columns = %f \n", tr/t,tc/t);

  free(A[0]);
  free(A);
  return 0;
}

void fill_cols(double **arr2d, int m, int n){
  for (int j = 0; j < n; j++){
    for (int i = 0; i < m; i++){
      arr2d[i][j] = i*j;
    }
  }
}

void fill_rows(double **arr2d, int m, int n){
  for (int i = 0; i < m; i++){
    for (int j = 0; j < n; j++){
      arr2d[i][j] = i*j;
    }
  }
}
