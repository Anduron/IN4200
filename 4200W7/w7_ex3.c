#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>


// The function as give in the exercise.
void dense_mat_vec(int m, int n, double *x, double *A, double *y)
{
    int i, j;
    for (i=0; i<m; i++){
        double tmp = 0.;
        for (j=0; j<n; j++)
            tmp += A[i*n+j] * y[j];
        x[i] = tmp;
    }
}

// The function as give in the exercise.
void dense_mat_vec_omp(int m, int n, double *x, double *A, double *y)
{
    int i, j;
    for (i=0; i<m; i++){
        double tmp = 0.;
        for (j=0; j<n; j++)
            tmp += A[i*n+j] * y[j];
        x[i] = tmp;
    }
}


int main(){



  return 0;
}
