#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "src/helper_func.h"
#include "src/count_friends_of_ten.h"

int main(){
  int m, n, max_rng;
  int **v;
  int total_friends_of_ten = 0;

  //m = 6;
  //n = 9;
  //max_rng = 7;
  //zeroes2D_array(&v,m,n); //allocates a 2D int array of zeroes
  //
  //for (size_t i = 0; i < m; i++) {
  //  for (size_t j = 0; j < n; j++) {
  //    v[i][j] = (rand()%max_rng)+1; //No elements = 0
  //  }
  //}
  read2D_array("data/test_matrix.txt",&v,&m,&n);

  print2int_array(v,m,n);

  total_friends_of_ten = count_friends_of_ten(m,n,v);
  printf("total friends of ten = %d\n", total_friends_of_ten);

  free2dint_array(v);
  return 0;
}
