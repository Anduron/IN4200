#include "read_graph_from_file2.h"

void read_graph_from_file2 (char *filename, int *N, int *N_links, int **row_ptr, int **col_idx){
  int i,j;
  FILE *infile = fopen(filename, "r");


  if (infile == NULL) {
      printf("ERROR: Failure to open file %s\n", filename);
      exit(0);
  }

  fscanf(infile, "%*[^\n]\n"); //SKIP: line 1
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 2
  fscanf(infile, "%*s %*s %d %*s %d \n", &*N, &*N_links);
  fscanf(infile, "%*[^\n]\n"); //SKIP: line 4

  *col_idx = (int *)calloc((*N_links),sizeof(col_idx));
  *row_ptr = (int *)calloc((*N+1),sizeof(row_ptr));
  int *ToNodeId = (int *)calloc((*N_links),sizeof(ToNodeId));
  int *FromNodeId = (int *)calloc((*N_links),sizeof(FromNodeId));

  for(size_t k = 0; k < *N_links; k++){
    fscanf(infile, "%d %d", &j, &i);
    (*row_ptr)[i+1]++;
    ToNodeId[k] = i;
    FromNodeId[k] = j;
  }

  for (int i = 1; i < (*N)+1; i++){
    (*row_ptr)[i] += (*row_ptr)[i-1];
  }

  int *counter = calloc((*N), sizeof(*counter));
  for(size_t i = 0; i < *N_links; i++){
    (*col_idx)[(*row_ptr)[ToNodeId[i]] + counter[ToNodeId[i]]] = FromNodeId[i];
    counter[ToNodeId[i]]++;
  }

  free(FromNodeId);
  free(ToNodeId);
  free(counter);
  fclose(infile);
}
