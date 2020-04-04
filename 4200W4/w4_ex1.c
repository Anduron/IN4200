#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(){
  int N_ops, stride;
  double *A, *B, s;
  clock_t time_1, time_2;

  N_ops = 1e6;
  stride = 10;
  s = 100;
  A = (double *)malloc(N_ops*sizeof(double));
  B = (double *)malloc(N_ops*sizeof(double));

  for(int i = 0; i<N_ops; i++){
    B[i] = (rand()%100)+1;
  }

  time_1 = clock();
  for(int i = 0; i<N_ops; i++){
    A[i] = s*B[i];
  }
  time_1 = clock() - time_1;
  double t1 = (double)time_1/CLOCKS_PER_SEC;

  time_2 = clock();
  for(int i = 0; i<N_ops; i+=stride){
    A[i] = s*B[i];
  }
  time_2 = clock() - time_2;
  double t2 = (double)time_2/CLOCKS_PER_SEC;

  int bytes1 = 2*N_ops*sizeof(*A); //Code balance*Number of ops/stride*bytes of operation
  double bandwidth1 = (double) bytes1/t1;

  int bytes2 = 2*((double)N_ops/(double) stride)*sizeof(*A); //Code balance*Number of ops/stride*bytes of operation
  double bandwidth2 = (double) bytes2/t2;

  printf("No Stride:\n");
  printf("Time of loop: %lfms \nEffective Flops: %lfGFlops\nEffective Memory Bandwidth: %lfGb/s \n",t1*1000,((double)N_ops/t1)/1e9,bandwidth1/1e9);
  printf("\nStride = %d:\n",stride);
  printf("Time of loop: %lfms \nEffective Flops: %lfGFlops\nEffective Memory Bandwidth: %lfGb/s \n",t2*1000,(((double)N_ops/(double)stride)/t2)/1e9,bandwidth2/1e9);

  free(A);
  free(B);

  return 0;
}
