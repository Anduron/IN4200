#include "count_mutual_links1.h"

int count_mutual_links1 (int N, char **table2D, int *num_involvements){

  int tot_mutual_links = 0;

  int *links_from = (int *)calloc(N,sizeof(*links_from));
  int links_to;

  #if defined(_OPENMP)
  {
    #pragma omp parallel for reduction(+: tot_mutual_links, links_from[:N], num_involvements[:N]) private(links_to)
    for(size_t i = 0; i < N; i++){
      memset(links_from, 0, N*sizeof(*links_from));
      links_to = 0;
      for(size_t j = 0; j < N; j++){
        if (table2D[i][j]){ //if its 0 its False
          links_to++;
          links_from[j] = 1;
        }
      }
      for(size_t k = 0; k < N; k++){
        if(links_from[k]){
          num_involvements[k] += links_to - 1;
        }
      }
      tot_mutual_links += 0.5*links_to*(links_to - 1);
    }
  }
  #else
  {
    for(size_t i = 0; i < N; i++){
      memset(links_from, 0, N*sizeof(*links_from));
      links_to = 0;
      for(size_t j = 0; j < N; j++){
        if (table2D[i][j]){ //if its 0 its False
          links_to++;
          links_from[j] = 1;
        }
      }
      for(size_t k = 0; k < N; k++){
        if(links_from[k]){
          num_involvements[k] += links_to - 1;
        }
      }
      tot_mutual_links += 0.5*links_to*(links_to - 1);
    }
  }
  #endif


  free(links_from);
  return tot_mutual_links;
}
