#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
#include "src/helper_func.h"
#include "src/mpi_count_friends_of_ten.h"

int main(int argc, char **argv){
  /*
  A main to call the different function and print some of the results for the parallel algo.
  */
  int m = 0, n = 0, rank, size, test_num, max_rng;
  int **v = NULL;
  int friends = 0, total_friends_of_ten = 0;
  char *test_check;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0){


    if (argc < 4){
      m = atoi(argv[1]);
      n = atoi(argv[2]);
      max_rng = 7;
      zeroes2D_array(&v,m,n); //allocates a 2D int array of zeroes

      for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
          v[i][j] = (rand()%max_rng)+1; //No elements = 0
        }
      }
    }
    else{
      printf("Testing a case of a known matrix\n");
      test2D_array("data/test_matrix_11x7.txt",&v,&m,&n,&test_num);
    }
  }

  friends = MPI_count_friends_of_ten(m,n,v);

  MPI_Reduce(&friends,&total_friends_of_ten,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD); //Sums num friends from each WORKER

  if (rank > 0){
    printf("MPI rank <%d>: WORKER FOUND Number of triple friends=%d\n",rank,friends);
  }

  MPI_Barrier(MPI_COMM_WORLD); //Attempt to get pretty print
  if (rank == 0){
    printf("MPI rank <%d>: MASTER RECIEVED Total number of triple friends=%d\n",rank,total_friends_of_ten);
    free2dint_array(v);
  }

  MPI_Finalize();
  return 0;
}
