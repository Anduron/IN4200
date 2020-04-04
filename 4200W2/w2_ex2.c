#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef double datatype;

int main(){
  int n = 1e7;
  clock_t start, handwrittentime, memcpytime;

  datatype *a = malloc(n*sizeof(*a));
  datatype *b = malloc(n*sizeof(*b));

  for (int i = 0; i < n; i++){
    a[i] = (rand()%100)+1;
    b[i] = (rand()%100)+1;
    //printf("a: %lf\t b: %lf\n", a[i], b[i] );
  }
  //printf("\n here \n");

  start = clock();
  for (int i = 0; i < n; i++){
    b[i] = a[i];
    //printf("a: %lf\t b: %lf\n", a[i], b[i] );
  }
  handwrittentime = clock() - start;

  //printf("\n here \n");

  for (int i = 0; i < n; i++){
    a[i] = (rand()%100)+1;
    b[i] = (rand()%100)+1;
    //printf("a: %lf\t b: %lf\n", a[i], b[i] );
  }

  //printf("\n here \n");

  start = clock();
  b = memcpy(b,a,n*sizeof(*a));
  memcpytime = clock() - start;

  /*
  for (int i = 0; i < n; i++){
    printf("a: %lf\t b: %lf\n", a[i], b[i] );
  }
  */
  printf("time for built in memcpy function: %lf \n", 1000*memcpytime/(double)CLOCKS_PER_SEC);
  printf("time for handwritten function: %lf \n", 1000*handwrittentime/(double)CLOCKS_PER_SEC);

  free(a);
  free(b);

  return 0;
}
