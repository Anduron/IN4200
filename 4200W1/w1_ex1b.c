#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MINIDX(oldidx, i, arr) (((arr[oldidx]) < (arr[i]))?(oldidx):(i))
#define MAXIDX(oldidx, i, arr) (((arr[oldidx]) > (arr[i]))?(oldidx):(i))

//compile with $gcc w1_ex1b.c -o ex1b -lm
//run with ./ex1b

void fill_random(int *array, int n){

  for (int i = 0; i < n; i++ ){
    array[i] = (rand()%100)+1;
  }
};

int min_1D(int *array, int n){
  int minimum;

  minimum = array[0];

  for (int i = 0; i < n; i++){
    minimum = MIN(minimum, array[i]);
  }

  return minimum;
};

int max_1D(int *array, int n){
  int maximum;

  maximum = array[0];

  for (int i = 0; i < n; i++){
    maximum = MAX(maximum, array[i]);
  }

  return maximum;
};

int main(int argc, char *argv[]){

  int n = atoi(argv[1]);

  int *rand_array, max_arr, min_arr;
  rand_array = (int *)malloc(n * sizeof(int));

  fill_random(rand_array, n);

  min_arr = min_1D(rand_array, n);

  max_arr = max_1D(rand_array, n);

  printf("random array = [");

  for (int i = 0; i < n; i++){
    printf(" %i ", rand_array[i]);
  }

  printf("]");

  printf("\n min = %i \n max = %i \n", min_arr, max_arr);

  free(rand_array);

  return 0;
};
