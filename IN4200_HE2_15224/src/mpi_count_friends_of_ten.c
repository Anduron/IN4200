#include "mpi_count_friends_of_ten.h"

#define ROOT 0
#define FROM_MASTER 1

int MPI_count_friends_of_ten(int M, int N, int **v){
  /*
  1. int M the height of v.
  2. int N the lenght of v.
  3. int **v the 2D MxN array that you want to find the number for friends of three on.
  This function uses a MASTER or split up the work between each worker. They carry out
  the count friends of ten algorithm in parallel. We use ghostpoints to do this. The
  algorithm uses one matrix index (i,j) as starting point per calculation.
  Ghostpoints cannot be starting points but can be accessed by the algorithm for calculation.
  Meaning in practice we cannot iterate over ghospoints but they are needed for borders
  between two parallel areas.
  */
  int friends = 0; //Number of friends found by one worker
  int rank, numprocs, numworkers, chunk, rest, offset, ghostpoints, tag, worker_rows;

  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  numworkers = numprocs-1;

  MPI_Bcast(&N, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

  //MASTER
  if (rank == ROOT){
    chunk = M / numworkers; //a parallel area where one worker is allowed access
    rest = M % numworkers;  //the rest of the matrix if not evenly split
    offset = 0;             //Where each parallel area start

    tag = FROM_MASTER;
    for (int worker=1; worker<=numworkers; worker++){
      worker_rows = (worker <= rest) ? chunk+1 : chunk;                           //rows split up per worker
      ghostpoints = (worker < (numworkers) && (M-offset-worker_rows)>=2) ? 2 : 0; //each row gets ghospoints or not
      worker_rows += ghostpoints;
      MPI_Send(&offset, 1, MPI_INT, worker, tag, MPI_COMM_WORLD);
      MPI_Send(&worker_rows, 1, MPI_INT, worker, tag, MPI_COMM_WORLD);
      MPI_Send(&ghostpoints, 1, MPI_INT, worker, tag, MPI_COMM_WORLD);
      MPI_Send(&v[offset][0], worker_rows*N, MPI_INT, worker, tag, MPI_COMM_WORLD);
      offset += worker_rows-ghostpoints;  //sending all information needed for algo, then calculating next starting point
    }
  }//end if root

  //WORKER
  if (rank > ROOT){
    //recieves information from MASTER
    MPI_Recv(&offset, 1, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &status);
    MPI_Recv(&worker_rows, 1, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &status);
    MPI_Recv(&ghostpoints, 1, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &status);

    //allocates array based on information recieved
    v = (int **)malloc((worker_rows) * sizeof(int *));
    v[0] = (int *)malloc((worker_rows)*N * sizeof(int));
    for (int i=1; i<worker_rows; i++){
      v[i] = v[i-1]+N;
    }

    //recieves array from MASTER
    MPI_Recv(&v[0][0], worker_rows*N, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &status);

    //count friends of ten algo explained in count_friends_of_ten.c
    for (size_t i = 0; i < worker_rows-ghostpoints; i++) {
      for (size_t j = 0; j < N; j++) {

         if (i < worker_rows-2 && j < N-2){
           friends += (v[i][j] + v[i+1][j+1] + v[i+2][j+2]) == 10;
         }

         if (j >= 2 && i < worker_rows-2){
           friends += (v[i][j] + v[i+1][j-1] + v[i+2][j-2]) == 10;
         }

         if (i < worker_rows-2){
           friends += (v[i][j] + v[i+1][j] + v[i+2][j]) == 10;
         }

         if (j < N-2){
           friends += (v[i][j] + v[i][j+1] + v[i][j+2]) == 10;
         }
       }
     }
   free(v[0]);
   free(v);
   }//end worker

  return friends;
}
