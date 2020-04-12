#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "src/helper_func.h"
#include "src/read_graph_from_file1.h"
#include "src/read_graph_from_file2.h"
#include "src/count_mutual_links1.h"
#include "src/count_mutual_links2.h"
#include "src/top_n_webpages.h"

void benchmark_read_graph_from_file1(char *graph_file, int N_bench);
void benchmark_read_graph_from_file2(char *graph_file, int N_bench);
void benchmark_count_mutual_links1(char *graph_file, int N_bench);
void benchmark_count_mutual_links2(char *graph_file, int N_bench);
void benchmark_top_n_webpages(char *graph_file, int N_bench);


int main(int argc, char *argv[]){
  /*
  ARGS:
  1. name of this compiled file: run with "./benchmark.x"
  2. name of file with the function you want to benchmark e.g. "count_mutual_links2.c"
  3. name of graph file you want to benchmark on e.g. "web-NotreDame.txt"
  4. Numer of repetitions when running the function to benchmark
  A benchmark function, that takes a valid "filename", "1", "2" or "all" as input.
  Can also take an invalid "filename" but will then return a list of valid inputs.
  Runs benchmarks that print timings of each function.
  */
  if (argc < 2){

    printf("No filename provided. \nPlease provide a valid filename or 'all', '1' or '2' to run tests.\n");

    exit(0);
  }

  int N_bench;
  char *graph_file;

  if (argc < 3){
    printf("Automatically setting graph_file = data/test_graph\n");
    graph_file = "data/test_graph.txt";
  }
  else{
    graph_file = argv[2];
  }

  if (argc < 4){
    N_bench = 20; //not a very large number of reps
  }
  else{
    N_bench = atoi(argv[3]);
  }

  if (strcmp(argv[1],"read_graph_from_file1.c") == 0){
    benchmark_read_graph_from_file1(graph_file, N_bench);
  }
  else if (strcmp(argv[1],"read_graph_from_file2.c") == 0){
    benchmark_read_graph_from_file2(graph_file, N_bench);
  }
  else if (strcmp(argv[1],"count_mutual_links1.c") == 0){
    benchmark_count_mutual_links1(graph_file, N_bench);
  }
  else if (strcmp(argv[1],"count_mutual_links2.c") == 0){
    benchmark_count_mutual_links2(graph_file, N_bench);
  }
  else if (strcmp(argv[1],"top_n_webpages.c") == 0){
    benchmark_top_n_webpages(graph_file, N_bench);
  }
  else if (strcmp(argv[1],"2") == 0){
    benchmark_read_graph_from_file2(graph_file, N_bench);
    benchmark_count_mutual_links2(graph_file, N_bench);
    benchmark_top_n_webpages(graph_file, N_bench);
  }
  else if (strcmp(argv[1],"all") == 0){
    benchmark_read_graph_from_file1(graph_file, N_bench);
    benchmark_count_mutual_links1(graph_file, N_bench);
    benchmark_read_graph_from_file2(graph_file, N_bench);
    benchmark_count_mutual_links2(graph_file, N_bench);
    benchmark_top_n_webpages(graph_file, N_bench);
  }
  else{
    printf("Filename provided not found. Valid filenames is found in the following list:\n");
    printf("'read_graph_from_file1.c'\n'read_graph_from_file2.c'\n'count_mutual_links1.c'\n'count_mutual_links2.c'\n'top_n_webpages.c'\n");
    printf("type '1' to benchmark 'read_graph_from_file1.c', 'count_mutual_links1.c', 'top_n_webpages.c'\n");
    printf("type '2' to benchmark 'read_graph_from_file2.c', 'count_mutual_links2.c', 'top_n_webpages.c'\n");
    printf("type 'all' to benchmark all files.\n");
    exit(0);
  }

  return 0;
}

void benchmark_read_graph_from_file1(char *graph_file, int N_bench){
  /*
  Benchmarking read_graph_from_file1.c
  printing average of N_bench repetitions
  */
  printf("\nBenchmarking read_graph_from_file1 on %s\n", graph_file);
  char **table2D;
  int N;
  FILE *outfile;
  double t_ms;

  #if defined(_OPENMP)
  {
    double t = omp_get_wtime();
    for(int i = 0; i < N_bench; i++){
      read_graph_from_file1(graph_file, &N, &table2D);
    }
    t = omp_get_wtime() - t;
    double t_avg = ((double) t)/N_bench;
    t_ms = 1000*t_avg;
  }
  #else
  {
    clock_t t;
    t = clock();
    for(int i = 0; i < N_bench; i++){
      read_graph_from_file1(graph_file, &N, &table2D);
    }
    t = clock() - t;
    double t_avg = ((double) t)/N_bench;
    t_ms = 1000*t_avg/CLOCKS_PER_SEC;
  }
  #endif


  printf("Average time usage = %fms, with %d repetitions\n",t_ms,N_bench);

  outfile = fopen("time.txt", "w");
  if (outfile == NULL){
    exit(0);
  }
  fprintf(outfile, "%f", t_ms);


  fclose(outfile);

  free2dtable(table2D);
}


void benchmark_read_graph_from_file2(char *graph_file, int N_bench){
  /*
  Benchmarking read_graph_from_file2.c
  printing average of N_bench repetitions
  */
  printf("\nBenchmarking read_graph_from_file2 on %s\n", graph_file);
  int N, N_links, *row_ptr, *col_idx;
  FILE *outfile;
  double t_ms;

  #if defined(_OPENMP)
  {
    double t = omp_get_wtime();
    for(int i = 0; i < N_bench; i++){
      read_graph_from_file2(graph_file, &N, &N_links,&row_ptr, &col_idx);
    }
    t = omp_get_wtime() - t;
    double t_avg = ((double) t)/N_bench;
    t_ms = 1000*t_avg;
  }
  #else
  {
    clock_t t;
    t = clock();
    for(int i = 0; i < N_bench; i++){
      read_graph_from_file2(graph_file, &N, &N_links,&row_ptr, &col_idx);
    }
    t = clock() - t;
    double t_avg = ((double) t)/N_bench;
    t_ms = 1000*t_avg/CLOCKS_PER_SEC;
  }
  #endif


  printf("Average time usage = %fms, with %d repetitions\n",t_ms,N_bench);

  outfile = fopen("time.txt", "w");
  if (outfile == NULL){
    exit(0);
  }
  fprintf(outfile, "%f", t_ms);

  fclose(outfile);

  free(col_idx);
  free(row_ptr);
}


void benchmark_count_mutual_links1(char *graph_file, int N_bench){
  /*
  Benchmarking count_mutual_links1.c
  printing average of N_bench repetitions
  */
  printf("\nBenchmarking count_mutual_links1 on %s\n", graph_file);
  char **table2D;
  int N;
  FILE *outfile;
  double t_ms;

  read_graph_from_file1(graph_file, &N, &table2D);
  int *num_involvements = (int *)calloc(N,sizeof(num_involvements));

  #if defined(_OPENMP)
  {
    double t = omp_get_wtime();
    for(int i = 0; i < N_bench; i++){
      int total_mutual_links = count_mutual_links1(N,table2D,num_involvements);
    }
    t = omp_get_wtime() - t;
    double t_avg = ((double) t)/N_bench;
    t_ms = 1000*t_avg;
  }
  #else
  {
    clock_t t;
    t = clock();
    for(int i = 0; i < N_bench; i++){
      int total_mutual_links = count_mutual_links1(N,table2D,num_involvements);
    }
    t = clock() - t;
    double t_avg = ((double) t)/N_bench;
    t_ms = 1000*t_avg/CLOCKS_PER_SEC;
  }
  #endif

  printf("Average time usage = %fms, with %d repetitions\n",t_ms,N_bench);

  outfile = fopen("time.txt", "w");
  if (outfile == NULL){
    exit(0);
  }
  fprintf(outfile, "%f", t_ms);

  fclose(outfile);

  free2dtable(table2D);
  free(num_involvements);
}


void benchmark_count_mutual_links2(char *graph_file, int N_bench){
  /*
  Benchmarking count_mutual_links2.c
  printing average of N_bench repetitions
  */
  printf("\nBenchmarking count_mutual_links2 on %s\n", graph_file);
  int N, N_links, *row_ptr, *col_idx;
  FILE *outfile;
  double t_ms;

  read_graph_from_file2(graph_file, &N, &N_links,&row_ptr, &col_idx);
  int *num_involvements = (int *)calloc(N,sizeof(num_involvements));

  #if defined(_OPENMP)
  {
    double t = omp_get_wtime();
    for(int i = 0; i < N_bench; i++){
      int total_mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
    }
    t = omp_get_wtime() - t;
    double t_avg = ((double) t)/N_bench;
    t_ms = 1000*t_avg;
  }
  #else
  {
    clock_t t;
    t = clock();
    for(int i = 0; i < N_bench; i++){
      int total_mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
    }
    t = clock() - t;
    double t_avg = ((double) t)/N_bench;
    t_ms = 1000*t_avg/CLOCKS_PER_SEC;
  }
  #endif
  printf("Average time usage = %fms, with %d repetitions\n",t_ms,N_bench);

  outfile = fopen("time.txt", "w");
  if (outfile == NULL){
    exit(0);
  }
  fprintf(outfile, "%f", t_ms);
  fclose(outfile);

  free(col_idx);
  free(row_ptr);
  free(num_involvements);

}


void benchmark_top_n_webpages(char *graph_file, int N_bench){
  /*
  Benchmarking calc_top_n_webpages in top_n_webpages.c
  printing average of N_bench repetitions
  */
  printf("\nBenchmarking calc_top_n_webpages on %s\n", graph_file);
  int N, N_links, *row_ptr, *col_idx, n;
  FILE *outfile;
  double t_ms;

  read_graph_from_file2(graph_file, &N, &N_links,&row_ptr, &col_idx);
  int *num_involvements = (int *)calloc(N,sizeof(num_involvements));
  int total_mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);

  if (strcmp(graph_file,"test_graph100.txt") == 0){
    n = 20;
  }
  else if (strcmp(graph_file,"web-NotreDame.txt") == 0){
    n = 50;
  }
  else{
    n = 8;
  }
  int *top_results = (int *)calloc(n,sizeof(top_results));

  #if defined(_OPENMP)
  {
    double t = omp_get_wtime();
    for(int i = 0; i < N_bench; i++){
      calc_top_n_webpages(N,num_involvements,top_results,n);
    }
    t = omp_get_wtime() - t;
    double t_avg = ((double) t)/N_bench;
    t_ms = 1000*t_avg;
  }
  #else
  {
    clock_t t;
    t = clock();
    for(int i = 0; i < N_bench; i++){
      calc_top_n_webpages(N,num_involvements,top_results,n);
    }
    t = clock() - t;
    double t_avg = ((double) t)/N_bench;
    t_ms = 1000*t_avg/CLOCKS_PER_SEC;
  }
  #endif
  printf("Average time usage = %fms, with %d repetitions\n",t_ms,N_bench);

  outfile = fopen("time.txt", "w");
  if (outfile == NULL){
    exit(0);
  }
  fprintf(outfile, "%f", t_ms);

  fclose(outfile);

  free(col_idx);
  free(row_ptr);
  free(num_involvements);
  free(top_results);

}
