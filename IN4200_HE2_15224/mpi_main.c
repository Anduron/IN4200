#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
#include "src/helper_func.h"
#include "src/count_friends_of_ten.h" //to check that they get same results
#include "src/mpi_count_friends_of_ten.h"

int main(int argc, char **argv){
  int m = 0, n = 0, rank, size, test_num, max_rng;
  int **v = NULL;
  int friends = 0, total_friends_of_ten = 0;
  char *test_check;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

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
      test2D_array("data/test_matrix.txt",&v,&m,&n,&test_num);
    }
  }

  friends = MPI_count_friends_of_ten(m,n,v);
  printf("MPI rank <%d>: Total number of triple friends=%d\n",rank,friends);

  MPI_Reduce(&friends,&total_friends_of_ten,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

  if (rank == 0){
    printf("Total number of triple friends=%d\n",total_friends_of_ten);
    free2dint_array(v);
  }

  MPI_Finalize ();
  return 0;
}
