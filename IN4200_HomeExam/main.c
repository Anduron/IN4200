#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "src/helper_func.h"
#include "src/read_graph_from_file1.h"
#include "src/count_mutual_links1.h"

int main(){
  int N, num_involvements;
  char **table2D;

  printf("here\n");

  read_graph_from_file1("data/web-NotreDame.txt", &N,&table2D);

  //count_mutual_links1(N,table2D,&num_involvements);

  printf("here\n");
  //print2dtab(table2D, N, N);

  free2dtable(table2D);
  return 0;
}
