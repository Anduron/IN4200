# IN4200: Home Exam 2, Spring 2020

**Counting Mutual Web Linkage Occurences**

**Candidate 15224**

**Disclaimer**
This project was embarked on in collaboration with candidate 15244.
Our individual programs may therefore bear a strong resemblance in
both presentation and content.

### Contents
- Data

  - test_matrix.txt
    - A small test matrix with a predictable result

  - test_matrix_11x7.txt
    - A small 11x7 test matrix with a predictable result



- src

  - [count_friends_of_ten.c]
    - file containing a function for finding the number of triple friends of ten (three in a row adding up to ten) in a matrix

  - [count_friends_of_ten.h]
    - header for count_friends_of_ten.c


  - [mpi_count_friends_of_ten.c]
    - file containing a function for finding the number of triple friends of ten in a matrix using a parallel algorithm where a MASTER splits up work between each WORKER.

  - [mpi_count_friends_of_ten.h]
    - header for mpi_count_friends_of_ten.c

  - [helper_func.h]
    - A header file containing functions used to read, print, and allocate matrices in main_serial.c or mpi_main.c



- Files in main folder

  - [main_serial.c]
    - file for running and printing the main results of the serial functions found in main folder that was created during this exam

  - [mpi_main.c]
    - file for running and printing the main results of the parallel MPI functions found in main folder that was created during this exam


## Usage

- [main_serial.c]
  - when in IN4200_HE2_15224 type into terminal: "make main_serial.x" to compile, "./main_serial.x m n <test?>" to run serial code, where m is the height of the matrix (num rows) and n is the width of the matrix (num columns) and <test?> is whether or not you want to use a test matrix (m and n is mandatory however test is not and can be omitted)

- [mpi_main.c]
  - when in IN4200_HE2_15224 type into terminal: "make mpi_main.x" to compile, "mpirun -np <numprocs> ./mpi_main.x m n <test?>" to run parallel code where m is the height of the matrix (num rows) and n is the width of the matrix (num columns) and <test?> is whether or not you want to use a test matrix (m and n is mandatory however test is not and can be omitted). Here <test?> means that you will not create a random matrix, and m and n can be completely random. <numprocs> is the number of processes to use (e.g. 1, 4 or 8).
  On ifi computer run with (compilation should still be same):
  "/usr/lib64/openmpi/bin/mpirun -np <numprocs> ./mpi_main.x m n <test?>"
