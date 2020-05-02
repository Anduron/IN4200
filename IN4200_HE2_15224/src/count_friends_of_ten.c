#include "count_friends_of_ten.h"

int count_friends_of_ten (int M, int N, int **v){
  int mutual_friends_of_ten = 0;
  int boolean;

  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      if (i < M-2 && j < N-2){
        boolean = (v[i][j] + v[i+1][j+1] + v[i+2][j+2]) == 10;
        mutual_friends_of_ten += boolean;
      }
      if (i < M-2 && j >= 2){
        boolean = (v[i][j] + v[i+1][j-1] + v[i+2][j-2]) == 10;
        mutual_friends_of_ten += boolean;
      }
      if (i < M-2){
        boolean = (v[i][j] + v[i+1][j] + v[i+2][j]) == 10;
        mutual_friends_of_ten += boolean;
      }
      if (j < N-2){
        boolean = (v[i][j] + v[i][j+1] + v[i][j+2]) == 10;
        mutual_friends_of_ten += boolean;
      }
    }
  }
  return mutual_friends_of_ten;
}
