#include "count_mutual_links1.h"

int count_mutual_links1 (int N, char **table2D, int *num_involvements){

  int tot_mutual_links = 0;
  int links_to;

  #if defined(_OPENMP)
  {
    //one of the two lines below should compile and run on an ifi machine
    #pragma omp parallel for private(links_to) reduction(+: tot_mutual_links, num_involvements[:N])
    //#pragma omp parallel for private(links_to) reduction(+: tot_mutual_links)
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
  #else
  {
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
