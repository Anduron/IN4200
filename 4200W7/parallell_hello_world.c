#include <stdio.h>
#include <omp.h>

int main (int nargs, char **args){

  printf("Im the master thread, Im alone.\n");

  #pragma omp parallel
  {
    int num_threads, thread_id;
    num_threads = omp_get_num_threads();
    thread_id = omp_get_thread_num();
    printf("Hello world! Im thread No.%d out of %d threads.\n", thread_id, num_threads);
  }
  return 0;
}
