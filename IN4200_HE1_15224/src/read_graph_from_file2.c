#include "read_graph_from_file2.h"

void read_graph_from_file2 (char *filename, int *N, int *N_links, int **row_ptr, int **col_idx){
  /*
  1. char *filename is a string containing the filename of the txt file with the
  web graph of choice to read.
  2. int *N is the pointer that stores the number of nodes found within the
  graph file. The input is expected to be the address of the declared int N.
  The value will be assigned during the reading of the file.
  3. int *N_links is the pointer that stores the number of edges found within the
  graph file. The input is expected to be the address of the declared int N_links.
  The value will be assigned during the reading of the file.
  4. int **row_ptr is a double pointer to a 1D array (or vector). The input is
  expected to be the address of the declared pointer int *row_ptr. The function
  will fill this vector with values containing information about the indices at
  which new rows start in col_idx.
  5. int **col_idx is a double pointer to a 1D array (or vector). The input is
  expected to be the address of the declared pointer int *col_idx. The function
  will fill this vector with values containing information of the column index
  of each value 1.

  Commonly the CRS format consists of three arrays a val (value) array, a row_ptr
  (row pointer) and a col_idx (column index) array. However since all values are
  1 the val array is ommitted. This is a format used to compress the information of
  sparse matrices.

  The web graph is expected to contain information on the number of nodes and
  edges on line 3 in the txt file. This line is read and we assign the positions
  of these integers to N and  N_links.
  */

  int i,j;
  FILE *infile = fopen(filename, "r");


  if (infile == NULL) {
      printf("ERROR: Failure to open file %s\n", filename); //test to see if filename exists
      exit(0);
  }

  fscanf(infile, "%*[^\n]\n"); //SKIP: line 1
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 2
  fscanf(infile, "%*s %*s %d %*s %d \n", &*N, &*N_links); //getting the values of N and N_links
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 4

  *col_idx = (int *)calloc((*N_links),sizeof(col_idx));           //allocate col_idx
  *row_ptr = (int *)calloc((*N+1),sizeof(row_ptr));               //allocate row_ptr
  int *ToNodeId = (int *)calloc((*N_links),sizeof(ToNodeId));     //allocate column of ToNodeId
  int *FromNodeId = (int *)calloc((*N_links),sizeof(FromNodeId)); //allocate column of FromNodeId

  for(size_t k = 0; k < *N_links; k++){
    fscanf(infile, "%d %d", &j, &i);  //getting the indices i and j from column is filename
    (*row_ptr)[i+1]++;                //adding up "spaces" between rows (counting number of same indices)
    ToNodeId[k] = i;                  //storing the values in the second column in filename
    FromNodeId[k] = j;                //storing the values in the first column in filename
  }

  for (int i = 1; i < (*N)+1; i++){
    (*row_ptr)[i] += (*row_ptr)[i-1]; //cumulative summation of number of links per row
  }                                   //this will give us integer values from 0 to N_links
                                      //(indices at which new rows start in col_idx)

  int *counter = calloc((*N), sizeof(*counter)); //1. this counter is there to make sure no vals in col_idx are overwritten
  for(size_t i = 0; i < *N_links; i++){          //2. + good ordering of vals in col_idx
    (*col_idx)[(*row_ptr)[ToNodeId[i]] + counter[ToNodeId[i]]] = FromNodeId[i]; //3. all vals are found in FromNodeId
    counter[ToNodeId[i]]++;                      //4. Indices are found in ToNodeId, counter offset idices ref(1)
  }

  free(FromNodeId);
  free(ToNodeId);
  free(counter);
  fclose(infile);
}
