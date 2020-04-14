#include "top_n_webpages.h"

void top_n_webpages(int num_webpages, int *num_involvements, int n){
  /*
  1. int num_webpages this is the number of webpages in the webgraph previously
  called N and is the length of the num_involvements vector
  2. int *num_involvements is the number of involvements vector found by count_mutual_links1
  or count_mutual_links2
  3. int n is how long the list of the top n elements should be, this value is
  changed if n is larger than the ammount of webpages

  calls a function that finds the top n webpages from a vector containing the number
  of involvements per webpage. This can also be described as the n maximum numbers
  in num_involvements. Then these values are printed.
  */
  if(n>num_webpages){
    n = num_webpages;
    printf("n cannot be larger than num_webpages, n is set equal to num_webpages %d\n",num_webpages);
  }

  int *top_results = (int *)malloc(n*sizeof(top_results)); //allocates an n long array to store the top n elements

  calc_top_n_webpages(num_webpages, num_involvements, top_results, n);

  for (size_t i = 0; i < n; i++){ //prints top_results
    printf("Ranking: %ld, Webpage number: %d, Number of involvements: %d\n", i+1, top_results[i], num_involvements[top_results[i]]);
  }
  free(top_results);
}


void calc_top_n_webpages(int num_webpages, int *num_involvements, int *top_results, int n){
  /*
  1. int num_webpages this is the number of webpages in the webgraph previously
  called N and is the length of the num_involvements vector
  2. int *num_involvements is the number of involvements vector found by count_mutual_links1
  or count_mutual_links2
  3. int *top_results is the n long pointer where we store the indices of the top n elemens.
  this vector needs top be allocated before calling this function.
  4. int n is how long the list of the top n elements should be, this value is
  changed if n is larger than the ammount of webpages

  calculates all top n elements in a webpage graph, then stores these elements
  the top_results vector. This function is made for benchmarking purposes.
  */

  int *dummy_array = (int *)malloc(num_webpages*sizeof(dummy_array));

  memcpy(dummy_array, num_involvements, num_webpages*sizeof(num_involvements)); //to avoid changing the original

  int top_webpage = 0;

  #if defined(_OPENMP)
  {
    int n_thread = omp_get_max_threads();
    int *temp_top_results = malloc(n*n_thread*sizeof(*temp_top_results)); //stores index of top results across all threads

    #pragma omp parallel
    {
      int thread_id = omp_get_thread_num();
      for (int i = 0; i < n; i++){
        if(thread_id<n_thread-1){
          for (int j = thread_id*num_webpages/n_thread; j < (thread_id+1)*num_webpages/n_thread; j++){ //allocates a part of list to each thread
            if (dummy_array[top_webpage]<dummy_array[j]){  //Finds maximum value of copy
              top_webpage = j;                              //sets top_webpage as index of maximum value
            }
          }
        }
        else{
          for (int j = thread_id*num_webpages/n_thread; j < num_webpages; j++){ //same as above for remaining part of list
            if (dummy_array[top_webpage]<dummy_array[j]){
              top_webpage = j;
            }
          }
        }
        temp_top_results[n*thread_id+i] = top_webpage;  //stores index of maximum value
        dummy_array[top_webpage] = -1;  //maximum element is set to -1 so it will not be found again
      }
      #pragma omp barrier
      #pragma omp master
      {//no longer parallel
        memcpy(dummy_array, num_involvements, num_webpages*sizeof(num_involvements)); //remake copy
        for (int i = 0; i < n; i++){  //iterates n times over nxn_thread long array of indices
          for (int j = 0; j < n*n_thread; j++){
            if (dummy_array[top_webpage] < dummy_array[temp_top_results[j]]){ //finds which of the nxnthread indices contains max value
              top_webpage = temp_top_results[j];  //top webage is set
            }
          }
          top_results[i] = top_webpage; //store index of top webpage in true top n index array
          dummy_array[top_webpage] = -1; //maximum element is set to -1 so it will not be found again
        }
      }
    }
    free(temp_top_results);
  }
  #else
  {
    for (size_t i = 0; i < n; i++){
      for (size_t j = 0; j < num_webpages; j++){
        top_webpage = MAXIDX(top_webpage, j, dummy_array); //Finds the index of maximum element in the copy of num_involvements
      }
      top_results[i] = top_webpage;   //store index of top webpage in top n index array
      dummy_array[top_webpage] = -1;  //maximum element is set to -1 so it will not be found again
    }                                 //if many of the same index are found this part ensures that it will not be picked twice
  }
  #endif

  free(dummy_array);
}


void original_top_n_webpages(int num_webpages, int *num_involvements, int n){
  /*
  1. int num_webpages this is the number of webpages in the webgraph previously
  called N and is the length of the num_involvements vector
  2. int *num_involvements is the number of involvements vector found by count_mutual_links1
  or count_mutual_links2
  3. int n is how long the list of the top n elements should be, this value is
  changed if n is larger than the ammount of webpages

  finds the top n webpages from a vector containing the number of involvements per
  webpage. This can also be described as the n maximum numbers in num_involvements.
  Then these values are printed. This function is considered too verbose for benchmarking
  And is mostly here to satisfy the parameters given.
  */
  if(n>num_webpages){ //Insuring that our list of top n elements cant be longer than the number of webpages
    n = num_webpages;
    printf("n cannot be larger than num_webpages, n is set equal to num_webpages %d\n",num_webpages);
  }

  int *dummy_array = (int *)malloc(num_webpages*sizeof(dummy_array)); //this is here to avoid destroying the original vector

  dummy_array = memcpy(dummy_array, num_involvements, num_webpages*sizeof(num_involvements)); //copy of the original vector

  int top_webpage = 0;
  for (size_t i = 0; i < n; i++){
    for (int j = 0; j < num_webpages; j++){
      top_webpage = MAXIDX(top_webpage, j, dummy_array); //Finds the index of maximum element in the copy of num_involvements
    }
    printf("Ranking: %ld, Webpage number: %d, Number of involvements: %d\n", i+1, top_webpage+1, dummy_array[top_webpage]);
    num_involvements[i] = dummy_array[top_webpage];
    dummy_array[top_webpage] = -1;  //maximum element is set to -1 so it will not be found again
  }

  free(dummy_array);
}
