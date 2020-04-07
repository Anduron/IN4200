//COMMENTS
#include "top_n_webpages.h"

void top_n_webpages(int num_webpages, int *num_involvements, int n){
  /*
  The function for printing the top n webpages ranked from number of involvements.
  All calculations have been split into a different function calc_top_n_webpages
  that function also returns an index array of the top webpages.
  */
  if(n>num_webpages){
    n = num_webpages;
    printf("n cannot be larger than num_webpages, n is set equal to num_webpages %d\n",num_webpages);
  }

  int *top_results = (int *)malloc(n*sizeof(top_results));

  calc_top_n_webpages(num_webpages, num_involvements, top_results, n);

  for (size_t i = 0; i < n; i++){
    printf("Ranking: %ld, Webpage number: %d, Number of involvements: %d\n", i+1, top_results[i], num_involvements[top_results[i]]);
  }
  free(top_results);
}


void calc_top_n_webpages(int num_webpages, int *num_involvements, int *top_results, int n){
  /*
  This function is made because we dont want to print the results each time we benchmark
  the top_n_webpages function. We have essentially made another function doing the same
  thing that top_n_webpages were supposed to do, but this one is more test and benchmark
  friendly because it will just return the results instead of printing them.
  */

  int *dummy_array = (int *)malloc(num_webpages*sizeof(dummy_array));

  memcpy(dummy_array, num_involvements, num_webpages*sizeof(num_involvements));

  int top_webpage = 0;
  for (size_t i = 0; i < n; i++){
    for (int j = 0; j < num_webpages; j++){
      top_webpage = MAXIDX(top_webpage, j, dummy_array);
    }
    top_results[i] = top_webpage;
    dummy_array[top_webpage] = -1;
  }

  free(dummy_array);
}


void original_top_n_webpages(int num_webpages, int *num_involvements, int n){
  /*
  This is the original and more conforming version of top_n_webpages.
  Since there is no overhead for calling a function in this one
  it should be slightly faster than the other one.
  However it is too verbose for benchmarking.
  An important difference in function is that this one will change the num_involvements
  array itself.
  */
  if(n>num_webpages){
    n = num_webpages;
    printf("n cannot be larger than num_webpages, n is set equal to num_webpages %d\n",num_webpages);
  }

  int *dummy_array = (int *)malloc(num_webpages*sizeof(dummy_array));

  dummy_array = memcpy(dummy_array, num_involvements, num_webpages*sizeof(num_involvements));

  int top_webpage = 0;
  for (size_t i = 0; i < n; i++){
    for (int j = 0; j < num_webpages; j++){
      top_webpage = MAXIDX(top_webpage, j, dummy_array);
    }
  printf("Ranking: %ld, Webpage number: %d, Number of involvements: %d\n", i+1, top_webpage+1, dummy_array[top_webpage]);
  num_involvements[i] = dummy_array[top_webpage];
  dummy_array[top_webpage] = -1;
  }

  free(dummy_array);
}
