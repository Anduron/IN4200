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
  /*
  A main to call the different function and print some of the results.
  */
  int N, *num_involvements, total_mutual_links;
  char **table2D;

  //part 1
  read_graph_from_file1("data/test_graph.txt", &N,&table2D);

  num_involvements = (int *)calloc(N,sizeof(num_involvements));

  printf("Web graph table:\n");
  print2dtab(table2D, N, N);

  total_mutual_links = count_mutual_links1(N,table2D, num_involvements);


  printf("\nNumber of involvements per webpage:\n");
  print_int_vector(num_involvements, N);
  printf("\nTotal number of mutual links: %d\n",total_mutual_links);

  top_n_webpages(N, num_involvements, 10);

  //free all relevant arrays from testing part 1
  free2dtable(table2D);
  free(num_involvements);


  //part 2
  int N_links, *row_ptr, *col_idx;

  read_graph_from_file2("data/web-NotreDame.txt", &N, &N_links,&row_ptr, &col_idx);
  num_involvements = (int *)calloc(N,sizeof(num_involvements));

  printf("\nN = %d, N_links = %d\n",N, N_links);

  total_mutual_links = 0; //reset
  total_mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
  printf("\nTotal number of mutual links: %d\n",total_mutual_links);

  top_n_webpages(N, num_involvements, 10);

  //free arrays from part 2
  free(row_ptr);
  free(col_idx);
  free(num_involvements);
  return 0;
}
