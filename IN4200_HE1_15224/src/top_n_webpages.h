// Include guard
#ifndef TOP_N_WEBPAGES_H
#define TOP_N_WEBPAGES_H

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

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MINIDX(oldidx, i, arr) (((arr[oldidx]) < (arr[i]))?(oldidx):(i))
#define MAXIDX(oldidx, i, arr) (((arr[oldidx]) > (arr[i]))?(oldidx):(i))

#pragma omp declare reduction(maximum : int : omp_out = omp_in > omp_out?omp_in:omp_out)

//memmove(array + removeIndex, array + removeIndex + 1, (--logicalSize - removeIndex)*sizeof(*array));

void calc_top_n_webpages(int num_webpages, int *num_involvements, int *top_results, int n);
void top_n_webpages(int num_webpages, int *num_involvements, int n);
void original_top_n_webpages(int num_webpages, int *num_involvements, int n);

#endif
