#include "count_mutual_links1.h"

int count_mutual_links1 (int N, char **table2D, int *num_involvements){
  /*
  1. int N is the number of nodes found from read_graph_from_file1
  2. char **table2D is the 2D array found in read_graph_from_file1
  3. int *num_involvements is a 1D array of size N allocated outside
  this function. The values in num_involvements are found in this function.

  Returns the total number of mutual links or tot_mutual_links

  takes a NxN matrix vith values = 1 or 0, counts number of mutual links using a
  modified triangle number formula, and finds number of involvements based on
  location of ones and how many ones per row.
  */


  int tot_mutual_links = 0;
  int links_to;

  #if defined(_OPENMP)
  { //pragmas to avoid false sharing, depending on version of c one of these lines below must be used
    #pragma omp parallel for private(links_to) reduction(+: tot_mutual_links, num_involvements[:N])
    //#pragma omp parallel for private(links_to) reduction(+: tot_mutual_links)
    for(size_t i = 0; i < N; i++){
      links_to = 0;
      for(size_t j = 0; j < N; j++){
          links_to += table2D[i][j];           //adding the number of ones per row
      }
      for(size_t k = 0; k < N; k++){
        if(table2D[i][k]){                     //each time there is a 1 in a row
          num_involvements[k] += links_to - 1; //add up the full number of ones per row -1
        }
      }
      tot_mutual_links += 0.5*links_to*(links_to - 1); //triangle numbers starting at 0 for 1 node
    }
  }
  #else
  { //serial version of the code has essentially same algorithm
    for(size_t i = 0; i < N; i++){
      links_to = 0;
      for(size_t j = 0; j < N; j++){
          links_to += table2D[i][j];
      }
      for(size_t k = 0; k < N; k++){
        if(table2D[i][k]){
          num_involvements[k] += links_to - 1;
        }
      }
      tot_mutual_links += 0.5*links_to*(links_to - 1);
    }
  }
  #endif

  return tot_mutual_links;
}
