#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>

int main(){
  int num_threads, thread_id, chunksize, scheduler, N;
  N = 1e6;
  chunksize = 10;

  int *a = malloc(N * sizeof *a);
  int *b = malloc(N * sizeof *b);
  double dotprod = 0;

  for (size_t i=0; i<N; i++) {
      a[i] = (rand() % 100) + 1;
      b[i] = (rand() % 100) + 1;
  }

  double t1 = omp_get_wtime();
  #pragma omp parallel for reduction(+ : dotprod) schedule(static, chunksize)
  for (size_t i=0; i<N; i++){
    dotprod += a[i] * b[i];
  }
  t1 = omp_get_wtime() - t1;

  num_threads = omp_get_num_threads();
  thread_id = omp_get_thread_num();

  printf("number of threads: %d \nchunksize: %d \nscheduler: %d \ntime t1: %lfms \n", num_threads, chunksize, scheduler, 1000*t1);

  free(a);
  free(b);

  return 0;
}
