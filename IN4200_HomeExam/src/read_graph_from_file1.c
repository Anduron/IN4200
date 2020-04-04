//COMMENT STRING GOES HERE
/*
void read_graph_from_file1 (char *filename, int *N, char ***table2D){
  int nedges, i,j;
  char **temp_table2D;
  FILE *infile = fopen(filename, "r");

  if (infile == NULL) {
      printf("ERROR: Failure to open file %s\n", filename);
      exit(0);
  }

  printf("here\n");

  fscanf(infile, "%*[^\n]\n"); //SKIP: line 1
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 2
  fscanf(infile, "%*s %*s %d %*s %d \n", &*N, &nedges);
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 4

  temp_table2D = (char **)calloc((*N), sizeof(char*));
  temp_table2D[0] = (char *)calloc((*N),(*N)*sizeof(char));

  for(size_t i = 0; i < (*N); i++){
    temp_table2D[i] = &(temp_table2D[0][(*N)*i]);
  }

  printf("here\n");

  for(size_t k = 0; k < nedges; k++){
    fscanf(infile, "%d %d", &i, &j);
    temp_table2D[j][i] = 1; //The table, these indices insure a transposed version of the table
  }

  printf("here\n");
  *table2D = temp_table2D;
  fclose(infile);
}
*/
#include "read_graph_from_file1.h"

void read_graph_from_file1 (char *filename, int *N, char ***table2D){
  int nedges, i,j;
  FILE *infile = fopen(filename, "r");

  if (infile == NULL) {
      printf("ERROR: Failure to open file %s\n", filename);
      exit(0);
  }

  printf("here\n");

  fscanf(infile, "%*[^\n]\n"); //SKIP: line 1
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 2
  fscanf(infile, "%*s %*s %d %*s %d \n", &*N, &nedges);
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 4

  *table2D = (char **)calloc((*N), sizeof(char*));
  *table2D[0] = (char *)calloc((*N),(*N)*sizeof(char));

  for(size_t i = 0; i < (*N); i++){
    (*table2D)[i] = &((*table2D)[0][(*N)*i]);
  }

  printf("here\n");
  printf("N = %d, edges = %d\n",*N, nedges);

  for(size_t k = 0; k < nedges; k++){
    printf("k = %lu",k);
    fscanf(infile, "%d %d", &j, &i);
    (*table2D)[i][j] = 1; //The table, these indices insure a transposed version of the table
  }

  printf("here\n");
  fclose(infile);
}
