#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "src/helper_func.h"
#include "src/read_graph_from_file1.h"

int test_read_graph_from_file1();

int main(int argc, char *argv[]){
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
    //test_read_graph_from_file2();
  }
  else if (strcmp(argv[1],"count_mutual_links1.c") == 0){
    //test_count_mutual_links1();
  }
  else if (strcmp(argv[1],"count_mutual_links2.c") == 0){
    //test_count_mutual_links2();
  }
  else if (strcmp(argv[1],"top_n_webpages.c") == 0){
    //test_top_n_webpages();
  }
  else if (strcmp(argv[1],"1") == 0){
    total_tests = 3;
    passed_tests += test_read_graph_from_file1();
    //test_count_mutual_links1();
    //test_top_n_webpages();
    printf("Tests passed: %d/%d \n", passed_tests,total_tests);
  }
  else if (strcmp(argv[1],"2") == 0){
    //test_read_graph_from_file2();
    //test_count_mutual_links2();
    //test_top_n_webpages();
  }
  else if (strcmp(argv[1],"all") == 0){
    total_tests = 3;
    passed_tests += test_read_graph_from_file1();
    //test_count_mutual_links1();
    //test_top_n_webpages();
    printf("Tests passed: %d/%d \n", passed_tests,total_tests);
  }
  else{
    printf("Filename provided not found. Valid filenames is found in the following list:\n");
    printf("'read_graph_from_file1.c'\n'read_graph_from_file2.c'\n'count_mutual_links1.c'\n'count_mutual_links2.c'\n'top_n_webpages.c'\n");
    printf("type '1' to test 'read_graph_from_file1.c', 'count_mutual_links1.c', 'top_n_webpages.c'\n");
    printf("type '2' to test 'read_graph_from_file2.c', 'count_mutual_links2.c', 'top_n_webpages.c'\n");
    printf("type 'all' to test all files");
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
  int N;
  int nedges = 0;
  int passed_tests = 0;
  char **table2D;

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

  read_graph_from_file1("data/test_graph.txt", &N,&table2D);

  int counter = 0;
  for (int i = 0; i < expected_nodes; i++){
    for (int j = 0; j < expected_nodes; j++){
      if (table2D_expected[i][j] != table2D[i][j]){
        counter = 1;
        break;
      }
    }
  }

  for (int i = 0; i < expected_nodes; i++){
    for (int j = 0; j < expected_nodes; j++){
      if (table2D[i][j] == 1){
        nedges += 1;
      }
    }
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

  return passed_tests;
}
