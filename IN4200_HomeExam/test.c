#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "src/helper_func.h"
#include "src/read_graph_from_file1.h"
#include "src/read_graph_from_file2.h"
#include "src/count_mutual_links1.h"
#include "src/count_mutual_links2.h"
#include "src/top_n_webpages.h"

int test_read_graph_from_file1();
int test_read_graph_from_file2();
int test_count_mutual_links1();
int test_count_mutual_links2();
int test_top_n_webpages();
//IMPLEMENT TIMING OF FUNCTIONS

int main(int argc, char *argv[]){
  /*
  A verbose testfunction, that takes a valid "filename", "1", "2" or "all" as input.
  Can also take an invalid "filename" but will then return a list of valid inputs.
  Runs tests and tallies the total ammount of passed tests as output.
  */
  if (argc < 2){

    printf("No filename provided. \nPlease provide a valid filename or 'all', '1' or '2' to run tests.\n");

    exit(0);
  }

  int total_tests;
  int passed_tests = 0;

  if(strcmp(argv[1],"read_graph_from_file1.c") == 0){
    total_tests = 3;
    passed_tests = test_read_graph_from_file1();
    printf("Tests passed: %d/%d \n", passed_tests,total_tests);
  }
  else if (strcmp(argv[1],"read_graph_from_file2.c") == 0){
    total_tests = 4;
    passed_tests = test_read_graph_from_file2();
    printf("Tests passed: %d/%d \n", passed_tests,total_tests);
  }
  else if (strcmp(argv[1],"count_mutual_links1.c") == 0){
    total_tests = 2;
    passed_tests = test_count_mutual_links1();
    printf("Tests passed: %d/%d \n", passed_tests,total_tests);
  }
  else if (strcmp(argv[1],"count_mutual_links2.c") == 0){
    total_tests = 2;
    passed_tests = test_count_mutual_links2();
    printf("Tests passed: %d/%d \n", passed_tests,total_tests);
  }
  else if (strcmp(argv[1],"top_n_webpages.c") == 0){
    total_tests = 1;
    passed_tests = test_top_n_webpages();
    printf("Tests passed: %d/%d \n", passed_tests,total_tests);
  }
  else if (strcmp(argv[1],"1") == 0){
    total_tests = 6;
    passed_tests += test_read_graph_from_file1();
    passed_tests += test_count_mutual_links1();
    passed_tests += test_top_n_webpages();
    printf("\nTests passed: %d/%d \n", passed_tests,total_tests);
  }
  else if (strcmp(argv[1],"2") == 0){
    total_tests = 7;
    passed_tests += test_read_graph_from_file2();
    passed_tests += test_count_mutual_links2();
    passed_tests += test_top_n_webpages();
    printf("\nTests passed: %d/%d \n", passed_tests,total_tests);
  }
  else if (strcmp(argv[1],"all") == 0){
    total_tests = 12
    ;
    passed_tests += test_read_graph_from_file1();
    passed_tests += test_count_mutual_links1();
    passed_tests += test_read_graph_from_file2();
    passed_tests += test_count_mutual_links2();
    passed_tests += test_top_n_webpages();
    printf("\nTests passed: %d/%d \n", passed_tests,total_tests);
  }
  else{
    printf("Filename provided not found. Valid filenames is found in the following list:\n");
    printf("'read_graph_from_file1.c'\n'read_graph_from_file2.c'\n'count_mutual_links1.c'\n'count_mutual_links2.c'\n'top_n_webpages.c'\n");
    printf("type '1' to test 'read_graph_from_file1.c', 'count_mutual_links1.c', 'top_n_webpages.c'\n");
    printf("type '2' to test 'read_graph_from_file2.c', 'count_mutual_links2.c', 'top_n_webpages.c'\n");
    printf("type 'all' to test all files.\n");
    exit(0);
  }

  return 0;
}

int test_read_graph_from_file1(){
  /*
  A function to test:
  1. If the number of nodes found by read_graph_from_file1.c is the same as expected
  2. If the number of edges in the matrix from read_graph_from_file1.c is the same as expected
  3. If the matrix from read_graph_from_file1.c is as expected
  */
  int passed_tests = 0; //the value counting the number of passed tests!
  int N;
  int nedges = 0;
  char **table2D;
  clock_t start;

  int expected_nodes = 8; //Hardcoded expected values
  int expected_edges = 17;
  char table2D_expected[8][8] = {
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 1, 0},
  };

  start = clock();
  read_graph_from_file1("data/test_graph.txt", &N,&table2D);
  start = clock() - start;
  printf("\nread_graph_from_file1 took %fms to complete on test_graph.txt \n", 1000*start/(double)CLOCKS_PER_SEC);

  int counter = 0;
  for (int i = 0; i < expected_nodes; i++){
    for (int j = 0; j < expected_nodes; j++){
      if (table2D_expected[i][j] != table2D[i][j]){
        counter = 1;
        break;
      }
    }
  }

  //If the matrices are not identical testing the number of edges is unnecessary
  if (counter == 0){
    for (int i = 0; i < expected_nodes; i++){
      for (int j = 0; j < expected_nodes; j++){
        if (table2D[i][j] == 1){
          nedges += 1;
        }
      }
    }
  }
  else{
    nedges = 0;
  }

  if (N == expected_nodes){
    printf("Test passed. Expected number of nodes: %d, Found: %d.\n", expected_nodes, N);
    passed_tests += 1;
  }
  else{
    printf("Test failed. Did not find the expected number of nodes.\nExpected: %d, Found: %d\n", expected_nodes, N);
  }
  if (nedges == expected_edges){
    printf("Test passed. Expected number of egdes: %d, Found: %d.\n", expected_edges, nedges);
    passed_tests += 1;
  }
  else{
    printf("Test failed. Did not find the expected number of edges. \nExpected: %d, Found: %d\n", expected_edges, nedges);
  }
  if (counter == 0){
    printf("Test passed. Matrices are identical.\n");
    passed_tests += 1;
  }
  else{
    printf("Test failed. Matrices are NOT identical.\n");
  }

  free2dtable(table2D);
  return passed_tests;
}



int test_read_graph_from_file2(){
  /*
  A function to test:
  1. If the number of nodes found by read_graph_from_file2.c is the same as expected
  2. If the number of links found by read_graph_from_file2.c is the same as expected
  3. If the vector containing the row pointer from read_graph_from_file2.c is as expected
  4. If the vector containing the column indexes from read_graph_from_file2.c is as expected
  */
  int passed_tests = 0; //the value counting the number of passed tests!
  int N, N_links, *row_ptr, *col_idx;
  int expected_nodes = 8;
  int expected_links = 17;
  int expected_row_ptr[8+1] = {0, 1, 4, 5, 6, 9, 12, 14, 17};
  int expected_col_idx[17] = {6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6};
  clock_t start;

  start = clock();
  read_graph_from_file2("data/test_graph.txt", &N, &N_links,&row_ptr, &col_idx);
  start = clock() - start;
  printf("\nread_graph_from_file2 took %fms to complete on test_graph.txt \n", 1000*start/(double)CLOCKS_PER_SEC);

  int counter1 = 0;
  int counter2 = 0;
  for (int i = 0; i < expected_nodes+1; i++){
    if (expected_row_ptr[i] != row_ptr[i]){
      counter1 = 1;
      break;
    }
  }
  for (int i = 0; i < expected_links; i++){
    if (expected_col_idx[i] != col_idx[i]){
      counter2 = 1;
      break;
    }
  }

  if (N == expected_nodes){
    printf("Test passed. Expected number of nodes: %d, Found: %d.\n", expected_nodes, N);
    passed_tests += 1;
  }
  else{
    printf("Test failed. Did not find the expected number of nodes.\nExpected: %d, Found: %d\n", expected_nodes, N);
  }
  if (N_links == expected_links){
    printf("Test passed. Expected number of links: %d, Found: %d.\n", expected_links, N_links);
    passed_tests += 1;
  }
  else{
    printf("Test failed. Did not find the expected number of links. \nExpected: %d, Found: %d\n", expected_links, N_links);
  }
  if (counter1 == 0){
    printf("Test passed. Row pointer vectors are identical.\n");
    passed_tests += 1;
  }
  else{
    printf("Test failed. Row pointer vectors are NOT identical.\n");
  }
  if (counter2 == 0){
    printf("Test passed. Column index vectors are identical.\n");
    passed_tests += 1;
  }
  else{
    printf("Test failed. Column index vectors are NOT identical.\n");
  }

  free(col_idx);
  free(row_ptr);
  return passed_tests;
}

int test_count_mutual_links1(){
  /*
  A function to test:
  1. If the number of nodes found by read_graph_from_file2.c is the same as expected
  2. If the number of links found by read_graph_from_file2.c is the same as expected
  */
  int passed_tests = 0;
  int N;
  char **table2D;
  int expected_num_involvements[8] = {2, 0, 4, 6, 5, 2, 4, 3};
  int expected_total_mutual_links = 13;
  clock_t start;

  read_graph_from_file1("data/test_graph.txt", &N,&table2D);

  int *num_involvements = (int *)calloc(N,sizeof(num_involvements));

  start = clock();
  int total_mutual_links = count_mutual_links1 (N,table2D,num_involvements);
  start = clock() - start;
  printf("\ncount_mutual_links1 took %fms to complete on test_graph.txt \n", 1000*start/(double)CLOCKS_PER_SEC);

  int counter = 0;
  for (int i = 0; i < N; i++){
    if (expected_num_involvements[i] != num_involvements[i]){
      counter = 1;
      break;
    }
  }

  if (expected_total_mutual_links == total_mutual_links){
    printf("Test passed. Expected number of total mutual links: %d, Found: %d.\n", expected_total_mutual_links, total_mutual_links);
    passed_tests += 1;
  }
  else{
    printf("Test failed. Did not find the expected number of total mutual links.\nExpected: %d, Found: %d\n", expected_total_mutual_links, total_mutual_links);
  }
  if (counter == 0){
    printf("Test passed. Number of involvements vector is identical to the expected vector.\n");
    passed_tests += 1;
  }
  else{
    printf("Test failed. Number of involvements vector is NOT identical to the expected vector.\n");
  }

  free2dtable(table2D);
  free(num_involvements);
  return passed_tests;
}

int test_count_mutual_links2(){
  /*
  A function to test:
  1. If the number of nodes found by read_graph_from_file2.c is the same as expected
  2. If the number of links found by read_graph_from_file2.c is the same as expected
  */
  int passed_tests = 0;
  int N, N_links, *row_ptr, *col_idx;
  char **table2D;
  int expected_num_involvements[8] = {2, 0, 4, 6, 5, 2, 4, 3};
  int expected_total_mutual_links = 13;
  clock_t start;

  read_graph_from_file2("data/test_graph.txt", &N, &N_links,&row_ptr, &col_idx);

  int *num_involvements = (int *)calloc(N,sizeof(num_involvements));

  start = clock();
  int total_mutual_links = count_mutual_links2 (N, N_links, row_ptr, col_idx, num_involvements);
  start = clock() - start;
  printf("\ncount_mutual_links2 took %fms to complete on test_graph.txt \n", 1000*start/(double)CLOCKS_PER_SEC);

  int counter = 0;
  for (int i = 0; i < N; i++){
    if (expected_num_involvements[i] != num_involvements[i]){
      counter = 1;
      break;
    }
  }

  if (expected_total_mutual_links == total_mutual_links){
    printf("Test passed. Expected number of total mutual links: %d, Found: %d.\n", expected_total_mutual_links, total_mutual_links);
    passed_tests += 1;
  }
  else{
    printf("Test failed. Did not find the expected number of total mutual links.\nExpected: %d, Found: %d\n", expected_total_mutual_links, total_mutual_links);
  }
  if (counter == 0){
    printf("Test passed. Number of involvements vector is identical to the expected vector.\n");
    passed_tests += 1;
  }
  else{
    printf("Test failed. Number of involvements vector is NOT identical to the expected vector.\n");
  }

  free(row_ptr);
  free(col_idx);
  free(num_involvements);
  return passed_tests;
}


int test_top_n_webpages(){
  /*
  A function to test:
  1. If the rankings are as expected on the smaller test_graph.txt file
  */
  int passed_tests = 0;
  int N;
  char **table2D;
  int expected_idx[8] = {3,4,6,2,7,5,0,1};
  int n = 8;
  clock_t start;

  read_graph_from_file1("data/test_graph.txt", &N,&table2D);

  int *num_involvements = (int *)calloc(N,sizeof(num_involvements));
  int total_mutual_links = count_mutual_links1 (N,table2D,num_involvements);

  int *top_results = (int *)calloc(n,sizeof(top_results));

  start = clock();
  calc_top_n_webpages(N,num_involvements,top_results,n);
  start = clock() - start;
  printf("\ncalc_top_n_webpages took %fms to complete on test_graph.txt, without printing.\n", 1000*start/(double)CLOCKS_PER_SEC);

  int counter = 0;

  for (int i = 0; i < N; i++){
    if (num_involvements[expected_idx[i]] != num_involvements[top_results[i]]){
      counter = 1;
      break;
    }
  }

  if (counter == 0){
    printf("Test passed. Ranking vector is identical to the expected vector.\n");
    passed_tests += 1;
  }
  else{
    printf("Test failed. Ranking vector is NOT identical to the expected vector.\n");
  }

  free2dtable(table2D);
  free(num_involvements);
  free(top_results);
  return passed_tests;
}
