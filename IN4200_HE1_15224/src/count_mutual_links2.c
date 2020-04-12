#include "count_mutual_links2.h"

int count_mutual_links2 (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){

  int tot_mutual_links = 0;
  int counter;

  #if defined(_OPENMP)
  {
    //one of the two lines below should compile and run on an ifi machine
    #pragma omp parallel for reduction(+:tot_mutual_links, num_involvements[:N]) private(counter)
    //#pragma omp parallel for private(counter) reduction(+:tot_mutual_links)
    for(int i = 0; i < N; i++){
      counter = row_ptr[i+1] - row_ptr[i];
      tot_mutual_links += 0.5*counter*(counter-1);
      for(int j = row_ptr[i]; j < row_ptr[i+1]; j++){
        num_involvements[col_idx[j]] += counter - 1;
      }
    }
  }
  #else
  {
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
