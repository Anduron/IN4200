#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "src/helper_func.h"
#include "src/read_graph_from_file1.h"
#include "src/count_mutual_links1.h"
#include "src/read_graph_from_file2.h"
#include "src/count_mutual_links2.h"
#include "src/top_n_webpages.h"

int main(){
  int N, *num_involvements, total_mutual_links;
  char **table2D;

  read_graph_from_file1("data/test_graph.txt", &N,&table2D);

  num_involvements = (int *)calloc(N,sizeof(num_involvements));

  printf("Web graph table:\n");
  print2dtab(table2D, N, N);

  total_mutual_links = count_mutual_links1(N,table2D, num_involvements);


  printf("\nNumber of involvements per webpage:\n");
  print_int_vector(num_involvements, N);
  printf("\nTotal number of mutual links: %d\n",total_mutual_links);

  top_n_webpages(N, num_involvements, 10);

  free2dtable(table2D);
  free(num_involvements);


  //part 2
  int N_links, *row_ptr, *col_idx;
  num_involvements = (int *)calloc(N,sizeof(num_involvements));

  read_graph_from_file2("data/test_graph.txt", &N, &N_links,&row_ptr, &col_idx);

  printf("\n");
  for (size_t i = 0; i < N+1; i++) {
    printf("%d  ",row_ptr[i]);
  }
  printf("\n");
  for (size_t j = 0; j < N_links; j++) {
    printf("%d  ",col_idx[j]);
  }
  printf("\n");

  total_mutual_links = 0; //reset
  total_mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
  printf("\nTotal number of mutual links: %d\n",total_mutual_links);

  printf("\n");
  for (size_t j = 0; j < N; j++) {
    printf("%d  ",num_involvements[j]);
  }
  printf("\n");

  free(row_ptr);
  free(col_idx);
  free(num_involvements);
  return 0;
}