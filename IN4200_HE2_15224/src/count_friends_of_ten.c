#include "count_friends_of_ten.h"

int count_friends_of_ten (int M, int N, int **v){
  int mutual_friends_of_ten = 0;

  for (size_t i = 1; i < M-1; i++) {
    for (size_t j = 1; j < N-1; j++) {
      if (v[i-1][j-1] + v[i][j] + v[i+1][j+1] == 10){
        mutual_friends_of_ten++;
      }
      if (v[i+1][j-1] + v[i][j] + v[i-1][j+1] == 10){
        mutual_friends_of_ten++;
      }
      if (v[i-1][j] + v[i][j] + v[i+1][j] == 10){
        mutual_friends_of_ten++;
      }
      if (v[i][j-1] + v[i][j] + v[i][j+1] == 10){
        mutual_friends_of_ten++;
      }
    }
  }

  for (size_t i = 1; i < M-1; i++) {
    if (v[i-1][0] + v[i][0] + v[i+1][0] == 10){
      mutual_friends_of_ten++;
    }
    if (v[i-1][N-1] + v[i][N-1] + v[i+1][N-1] == 10){
      mutual_friends_of_ten++;
    }
  }

  for (size_t j = 1; j < N-1; j++) {
    if (v[0][j-1] + v[0][j] + v[0][j+1] == 10){
      mutual_friends_of_ten++;
    }
    if (v[M-1][j-1] + v[M-1][j] + v[M-1][j+1] == 10){
      mutual_friends_of_ten++;
    }
  }

  return mutual_friends_of_ten;
}
