#include "mpi_count_friends_of_ten.h"

#define ROOT 0
#define FROM_MASTER 1
#define FROM_SLAVE 2

int MPI_count_friends_of_ten(int M, int N, int** v)
{
  int friends = 0;
  int **vpart=NULL, **vfull;
  int taskid, numtasks, numworkers, chunk, rest, offset, ghostpoints, tag, slave_rows;

  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  numworkers = numtasks-1;

  MPI_Bcast(&N, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

  // MASTER
  if (taskid == ROOT){
    chunk = M / numworkers;
    rest = M % numworkers;
    offset = 0;
    //HERE!!!

    tag = FROM_MASTER;
    for (int dest=1; dest<=numworkers; dest++)
      {
         //(dest == (numworkers)) ? (ghostpoints = 2) : (ghostpoints = 0);
         slave_rows = (dest <= rest) ? chunk+1 : chunk;
         ghostpoints = (dest < (numworkers) && (M-offset-slave_rows)>=2) ? 2 : 0;
         slave_rows += ghostpoints;
         printf("id %d, ghostpoints=%d\n", dest, ghostpoints);

         MPI_Send(&offset, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
         MPI_Send(&slave_rows, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
         MPI_Send(&ghostpoints, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
         MPI_Send(&v[offset][0], slave_rows*N, MPI_INT, dest, tag, MPI_COMM_WORLD);
         offset += slave_rows-ghostpoints;
      }

      tag = FROM_SLAVE;

  }//end if root

  // SLAVE
  if (taskid > ROOT){
      tag = FROM_MASTER;
      MPI_Recv(&offset, 1, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&slave_rows, 1, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &status);
      MPI_Recv(&ghostpoints, 1, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &status);

      printf("taskid <%d>\n", taskid);
      printf("offset: %d\n", offset);
      printf("slave_rows: %d\n", slave_rows);

      // allocate
      vpart = (int **)malloc((slave_rows) * sizeof(int *));
      vpart[0] = (int *)malloc((slave_rows)*N * sizeof(int));
      for (int i=1; i<slave_rows; i++){
        vpart[i] = vpart[i-1]+N;
      }

      MPI_Recv(&vpart[0][0], slave_rows*N, MPI_INT, ROOT, tag, MPI_COMM_WORLD, &status);

     // print chunked array
     for (int i=0; i<slave_rows; i++){
       printf("| ");
       for (int j=0; j<N; j++){
         printf("%d ", vpart[i][j]);
       }
       printf("|\n");
     }

     for (size_t i = 0; i < slave_rows-ghostpoints; i++) {

       for (size_t j = 0; j < N; j++) {
         //printf("i=%ld, j=%ld\n",i,j);
         if (i < slave_rows-2 && j < N-2){
           friends += (vpart[i][j] + vpart[i+1][j+1] + vpart[i+2][j+2]) == 10;
         }

         if (j >= 2 && i < slave_rows-2){
           friends += (vpart[i][j] + vpart[i+1][j-1] + vpart[i+2][j-2]) == 10;
         }

         if (i < slave_rows-2){
           friends += (vpart[i][j] + vpart[i+1][j] + vpart[i+2][j]) == 10;
         }

         if (j < N-2){
           friends += (vpart[i][j] + vpart[i][j+1] + vpart[i][j+2]) == 10;
         }
       }
     }
   free(vpart[0]);
   free(vpart);
   }//end slave

  return friends;
}
