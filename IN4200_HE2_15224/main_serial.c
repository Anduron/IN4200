#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "src/helper_func.h"
#include "src/count_friends_of_ten.h"

int main(int argc, char *argv[]){
  int m, n, test_num, max_rng;
  int **v;
  int total_friends_of_ten = 0;
  char *test_check;

  if (argc < 4){
    test_check = "no test";
  }
  else{
    test_check = argv[3];
  }

  if(strcmp(test_check,"test") == 0){

    printf("Testing a case of a known matrix\n");
    test2D_array("data/test_matrix.txt",&v,&m,&n,&test_num);

    print2int_array(v,m,n);

    total_friends_of_ten = count_friends_of_ten(m,n,v);

    if (test_num == total_friends_of_ten){
      printf("found expected number of total friends of ten = %d\n", total_friends_of_ten);
    }
    else{
      printf("test failed, expected friends of ten not found. \nexpected: %d, got %d\n\n",test_num, total_friends_of_ten);
    }
    printf("----------------------------------\n");
    free2dint_array(v);
  }

  m = atoi(argv[1]);
  n = atoi(argv[2]);
  max_rng = 7;
  zeroes2D_array(&v,m,n); //allocates a 2D int array of zeroes

  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      v[i][j] = (rand()%max_rng)+1; //No elements = 0
    }
  }

  total_friends_of_ten = count_friends_of_ten(m,n,v);

  printf("Testing a case of a random matrix\n");
  printf("for an %dx%d matrix with random elements between 1 and %d\n", m, n, max_rng);
  printf("total friends of ten = %d\n", total_friends_of_ten);

  free2dint_array(v);
  return 0;
}
