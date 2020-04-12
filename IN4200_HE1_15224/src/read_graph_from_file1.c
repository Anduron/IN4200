#include "read_graph_from_file1.h"

void read_graph_from_file1 (char *filename, int *N, char ***table2D){
  /*
  1. char *filename is a string containing the filename of the txt file with the
  web graph of choice to read.
  2. int *N is the pointer that stores the number of nodes found within the
  graph file. The input is expected to be the address of the declared int N.
  The value will be assigned during the reading of the file.
  3. char ***table2D is the triple pointer to a 2D array. The input is expected
  to be the address of the declared double pointer char **table2D. The function
  will fill this 2D table with values 1 or 0 depending on the links in the web graph.

  The web graph is expected to contain information on the number of nodes and
  edges on line 3 in the txt file. This line is read and we assign the positions
  of these integers to N and nedges (number of edges or simply the number of links).
  */

  int nedges, i,j;
  FILE *infile = fopen(filename, "r");

  if (infile == NULL) {
      printf("ERROR: Failure to open file %s\n", filename); //test to see if filename exists
      exit(0);
  }

  fscanf(infile, "%*[^\n]\n"); //SKIP: line 1
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 2
  fscanf(infile, "%*s %*s %d %*s %d \n", &*N, &nedges); //getting the values of N and N_links
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 4

  *table2D = (char **)calloc((*N), sizeof(char*));      //allocating table2D
  *table2D[0] = (char *)calloc((*N)*(*N),sizeof(char)); //allocating table2D

  for(size_t i = 0; i < (*N); i++){
    (*table2D)[i] = &((*table2D)[0][(*N)*i]);           //allocating table2D
  }

  for(size_t k = 0; k < nedges; k++){
    fscanf(infile, "%d %d", &j, &i);  //finding the indices of the outbound and inbound links
    (*table2D)[i][j] = 1;             //these indices insure a transposed version of the table
  }                                   //these indices are assinged the value 1 in the table

  fclose(infile);
}
