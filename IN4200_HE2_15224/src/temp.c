#include "mpi_count_friends_of_ten.h"

int MPI_count_friends_of_ten (int M, int N, int **v){
  int mutual_friends_of_ten = 0;
  int boolean, my_start, my_stop, i_max;
  int rank, size, root = 0;
  MPI_Status status;

  MPI_Comm_size (MPI_COMM_WORLD, &size);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  if (rank == root){
    i_max = M/(int) size;
    printf("%d\n",size);
    printf("i_max = %d\n",i_max);
    for (int i = 1; i < size-1; i++){
      my_start = i*(i_max);
      my_stop = (i+1)*(i_max+2);
      MPI_Send(&i_max, 1, MPI_INT, i, i, MPI_COMM_WORLD);
      MPI_Send(&my_start, 1, MPI_INT, i, i, MPI_COMM_WORLD);
      MPI_Send(&my_stop, 1, MPI_INT, i, i, MPI_COMM_WORLD);
      printf("size = %d, rank = %d, size sent = %d, start = %d, stop = %d\n",N,i,i_max,my_start,my_stop);
    }

    i_max = M - size*i_max;
    my_start = size*(i_max);
    my_stop = M;

    MPI_Send(&i_max, 1, MPI_INT, size-1, size, MPI_COMM_WORLD);
    MPI_Send(&my_start, 1, MPI_INT, size-1, size, MPI_COMM_WORLD);
    MPI_Send(&my_stop, 1, MPI_INT, size-1, size, MPI_COMM_WORLD);
    printf("size = %d, rank = %d, size sent = %d, start = %d, stop = %d\n",N,size-1,i_max,my_start,my_stop);
  }
  else{
    MPI_Recv(&i_max, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
    MPI_Recv(&my_start, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
    MPI_Recv(&my_stop, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
    printf("rank = %d, size recv = %d, start = %d, stop = %d\n",rank,i_max,my_start,my_stop);
  }

  //MPI_Waitall();
  printf("%d, %d, %d \n",i_max, size, rank);

  for (size_t i = my_start; i < my_stop; i++) {

    for (size_t j = 0; j < N; j++) {

      if (i < M-2 && j < N-2){
        boolean = (v[i][j] + v[i+1][j+1] + v[i+2][j+2]) == 10;
        mutual_friends_of_ten += boolean;
      }

      if (i >= 2 && j >= 2){
        boolean = (v[i][j] + v[i-1][j-1] + v[i-2][j-2]) == 10;
        mutual_friends_of_ten += boolean;
      }

      if (i < M-2){
        boolean = (v[i][j] + v[i+1][j] + v[i+2][j]) == 10;
        mutual_friends_of_ten += boolean;
      }

      if (j < N-2){
        boolean = (v[i][j] + v[i][j+1] + v[i][j+2]) == 10;
        mutual_friends_of_ten += boolean;
      }

    }
  }
  return mutual_friends_of_ten;
}



#include "mpi_count_friends_of_ten.h"

int MPI_count_friends_of_ten (int M, int N, int **v){
  int mutual_friends_of_ten = 0;
  int boolean, my_stop;
  int rank, size, tag1 = 1, root = 0;
  //MPI_Status status;

  MPI_Comm_size (MPI_COMM_WORLD, &size);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  MPI_Bcast(&N, 1, MPI_INT, root, MPI_COMM_WORLD);
  MPI_Bcast(&M, 1, MPI_INT, root, MPI_COMM_WORLD);

  my_stop = 2 + M/(int) size;

  if (rank == root){
    for(int i = 1; i < size; i++){
      printf("%d\n",i);
      MPI_Send(&v, my_stop, MPI_INT, i, tag1, MPI_COMM_WORLD);
    }
  }
  else{
    v = (int **)calloc(my_stop,sizeof(int*));      //allocating 2D array
    v[0] = (int *)calloc(my_stop*N,sizeof(int));     //allocating 2D array

    for(size_t i = 0; i < my_stop; i++){
      (v)[i] = &((v)[0][N*i]);       //allocating 2D array
    }

    MPI_Recv(&v, my_stop, MPI_INT, root, tag1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    for (size_t i = 0; i < my_stop; i++) {
        printf("| ");
        for (size_t j = 0; j < N; j++) {
            printf("%d ", v[i][j]);
        }
        printf("|\n");
    }
  }


  for (size_t i = 0; i < my_stop; i++) {

    for (size_t j = 0; j < N; j++) {

      if (i < M-2 && j < N-2){
        boolean = (v[i][j] + v[i+1][j+1] + v[i+2][j+2]) == 10;
        mutual_friends_of_ten += boolean;
      }

      if (i >= 2 && j >= 2){
        boolean = (v[i][j] + v[i-1][j-1] + v[i-2][j-2]) == 10;
        mutual_friends_of_ten += boolean;
      }

      if (i < M-2){
        boolean = (v[i][j] + v[i+1][j] + v[i+2][j]) == 10;
        mutual_friends_of_ten += boolean;
      }

      if (j < N-2){
        boolean = (v[i][j] + v[i][j+1] + v[i][j+2]) == 10;
        mutual_friends_of_ten += boolean;
      }

    }
  }
  return mutual_friends_of_ten;
}
