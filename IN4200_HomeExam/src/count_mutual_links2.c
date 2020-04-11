#include "count_mutual_links2.h"

int count_mutual_links2 (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){

  int tot_mutual_links = 0;
  int counter;

  #if defined(_OPENMP)
  {
    #pragma omp parallel for reduction(+:tot_mutual_links, num_involvements[:N]) private(counter)
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
