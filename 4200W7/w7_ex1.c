#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>

/*
for (i=0; i < (int) sqrt(x); i++) {
  a[i] = 2.3 * x;
  if (i < 10){
    b[i] = a[i];
  }
}
flag = 0;
for (i = 0; (i<n) & (!flag); i++) {
  a[i] = 2.3 * i;
  if (a[i] < b[i]){
    flag = 1;
  }
}
for (i = 0; i < n; i++)
a[i] = foo(i);

for (i = 0; i < n; i++) {
  a[i] = foo(i);
  if (a[i] < b[i]){
    a[i] = b[i];
  }
}

for (i = 0; i < n; i++) {
  a[i] = foo(i);
  if (a[i] < b[i]){
    break;
  }
}

dotp = 0;
for (i = 0; i < n; i++){
  dotp += a[i] * b[i];
}

for (i = k; i < 2*k; i++){
  a[i] = a[i] + a[i-k];
}

for (i = k; i < n; i++){
  a[i] = b * a[i-k];
}
*/


int main (int nargs, char **args) {
    int N = 1e3;
    int *a = malloc(N * sizeof *a);
    int *b = malloc(N * sizeof *b);
    int *c = malloc(N * sizeof *c);

    for (size_t i=0; i<N; i++) {
        b[i] = (rand() % 100) + 1;
        c[i] = (rand() % 100) + 1;
    }


    #pragma omp parallel for
    for (size_t i=0; i<N; i++)
        a[i] = b[i] + c[i];

    free(a);
    free(b);
    free(c);

    return 0;
}
