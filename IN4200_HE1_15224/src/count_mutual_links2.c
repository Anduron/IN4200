#include "count_mutual_links2.h"

int count_mutual_links2 (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){
  /*
  1. int N is the number of nodes found from read_graph_from_file2
  2. int N_links is the number of links found from read_graph_from_file2
  3. int *row_ptr is the row pointer vector found by read_graph_from_file2
  4. int *col_idx is the column index vector found by read_graph_from_file2
  5. int *num_involvements is a 1D array of size N allocated outside
  this function. The values in num_involvements are found in this function.

  Returns the total number of mutual links or tot_mutual_links

  takes a row_ptr vector and a col_idx vector, counts number of mutual links using a
  modified triangle number formula, and finds number of involvements based on
  number of nodes per row and location in the col_idx vector.
  */

  int tot_mutual_links = 0;
  int counter;

  #if defined(_OPENMP)
  {
    //one of the two lines below should compile and run on an ifi machine
    #pragma omp parallel for reduction(+:tot_mutual_links, num_involvements[:N]) private(counter)
    //#pragma omp parallel for private(counter) reduction(+:tot_mutual_links)
    for(int i = 0; i < N; i++){
      counter = row_ptr[i+1] - row_ptr[i];           //gives us number of links per row row_start-row_end
      tot_mutual_links += 0.5*counter*(counter-1);   //triangle numbers starting at 0 for 1 node
      for(int j = row_ptr[i]; j < row_ptr[i+1]; j++){
        num_involvements[col_idx[j]] += counter - 1; //gives us the number of links per row for each link - 1
      }
    }
  }
  #else
  { //
    for(int i = 0; i < N; i++){
      counter = row_ptr[i+1] - row_ptr[i];
      tot_mutual_links += 0.5*counter*(counter-1);
      for(int j = row_ptr[i]; j < row_ptr[i+1]; j++){
        num_involvements[col_idx[j]] += counter - 1;
      }
    }
  }
  #endif

  return tot_mutual_links;
}
