//COMMENTS
#include "count_mutual_links2.h"
/*
int count_mutual_links2 (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){

  int tot_mutual_links = 0;
  int counter;

  for(int i = 0; i < N; i++){
    counter = row_ptr[i+1] - row_ptr[i];
    //mutual_link_array[i] += counter;
    tot_mutual_links += 0.5*counter*(counter-1);
    for(int j = row_ptr[i]; j < row_ptr[i+1]; j++ ){
      num_involvements[col_idx[j]] += counter - 1;
    }
  }

  //free(mutual_link_array);
  return tot_mutual_links;
}
*/
int count_mutual_links2 (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){

  int tot_mutual_links = 0;
  int counter, counter2;
  int *mutual_link_array = (int *)calloc(N,sizeof(mutual_link_array))

  for(int i = 0; i < N; i++){
    counter = row_ptr[i+1] - row_ptr[i];
    mutual_link_array[i] += counter;
    tot_mutual_links += 0.5*counter*(counter-1);
  }


  free(mutual_link_array);
  return tot_mutual_links;
}
