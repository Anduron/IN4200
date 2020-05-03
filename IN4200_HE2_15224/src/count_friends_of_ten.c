#include "count_friends_of_ten.h"

int count_friends_of_ten (int M, int N, int **v){
  /*
  1. int M the height of v.
  2. int N the lenght of v.
  3. int **v the 2D MxN array that you want to find the number for friends of three on.
  Orientations tested with o as center 1. horisontal, 2. vertical, 3. main diagonal,
  4. reverse diagonal
      o . .1
    . . .
  .4  .2  .3
  */
  int mutual_friends_of_ten = 0;

  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      if (i < M-2 && j < N-2){ //tests all except padding of 2 accross far right and bottom of matrix
        mutual_friends_of_ten += (v[i][j] + v[i+1][j+1] + v[i+2][j+2]) == 10; //adds 1 if sum = 10, 0 else
      }
      if (i < M-2 && j >= 2){ //tests all except padding of 2 accross far left and bottom of matrix
        mutual_friends_of_ten += (v[i][j] + v[i+1][j-1] + v[i+2][j-2]) == 10; //adds 1 if sum = 10, 0 else
      }
      if (i < M-2){ //tests all except padding of 2 accross bottom of matrix
        mutual_friends_of_ten += (v[i][j] + v[i+1][j] + v[i+2][j]) == 10; //adds 1 if sum = 10, 0 else
      }
      if (j < N-2){ //tests all except padding of 2 accross far right of matrix
        mutual_friends_of_ten += (v[i][j] + v[i][j+1] + v[i][j+2]) == 10; //adds 1 if sum = 10, 0 else
      }
    }
  }
  return mutual_friends_of_ten;
}
