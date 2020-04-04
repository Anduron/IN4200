#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  int n = 100000;
  FILE *binfile, *asciifile;
  double *arr;
  double *outfile;
  clock_t start, a_r_time, a_w_time, b_r_time, b_w_time;

  arr = (double *)malloc(n*sizeof(double));

  for(int i = 0; i<n; i++){
    arr[i] = (rand()%100)+1;

  }

  binfile = fopen("test_binary.bin","wb");

  start = clock();
  fwrite(arr,sizeof(double),n,binfile);
  b_w_time = clock() - start;
  fclose(binfile);

  binfile = fopen("test_binary.bin","rb");
  outfile = (double *)malloc(n*sizeof(double));

  start = clock();
  fread(outfile,sizeof(double), n, binfile);
  b_r_time = clock() - start;
  fclose(binfile);

  asciifile = fopen("test_ascii.txt","w");

  start = clock();
  for (int i = 0; i<n; i++){
    fprintf(asciifile,"%lf", arr[i]);
  }
  a_w_time = clock() - start;
  fclose(asciifile);

  asciifile = fopen("test_ascii.txt","r");
  outfile = (double *)malloc(n*sizeof(double));

  start = clock();
  for (int i = 0; i<n; i++){
    fscanf(asciifile,"%lf", &outfile[i]);
  }
  a_r_time = clock() - start;

  free(arr);
  free(outfile);

  printf("binary read: %lf ms, binary write %lf ms \n", 1000*b_r_time/(double) CLOCKS_PER_SEC, 1000*b_w_time/(double) CLOCKS_PER_SEC);
  printf("ASCII read: %lf ms, ASCII write %lf ms \n", 1000*a_r_time/(double) CLOCKS_PER_SEC,1000*a_w_time/(double) CLOCKS_PER_SEC);

  return 0;
}
