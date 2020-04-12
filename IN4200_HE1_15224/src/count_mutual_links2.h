// Include guard
#ifndef COUNT_MUTUAL_LINKS2_H
#define COUNT_MUTUAL_LINKS2_H

//================================
// Include dependencies
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

//================================
// Function prototypes

int count_mutual_links2 (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements);

#endif
