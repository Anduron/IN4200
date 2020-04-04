#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

double numerical_integration (double x_min, double x_max, int slices){

  double delta_x = (x_max-x_min)/slices;
  double x, sum = 0.0;

  for (int i=0; i<slices; i++){
    x = x_min + (i+0.5)*delta_x;
    sum = sum + 4.0/(1.0+x*x);
  }

return sum*delta_x;
}

int main(){
  /*
  int max_slices, stride;
  double In, x_min, x_max;

  max_slices = 500;
  stride = 50;
  x_min = 0;
  x_max = 1;

  for(int slices = 1; slices < max_slices +1; slices += stride){
    In = numerical_integration(x_min,x_max,slices);
    printf("numerical integration with N = %d slices, result I = %f \n", slices, In);
  }
  */
  int max_slices, stride, ndiv;
  double In, x_min, x_max, tol;

  max_slices = 1e7;
  stride = 10;
  tol = 1e-12;
  x_min = 0;
  x_max = 1;

  int slices = 1;
  In = 0;

  while(slices < max_slices &  fabs(M_PI-In)>tol){
    In = numerical_integration(x_min,x_max,slices);
    printf("numerical integration with N = %d slices:\n result I = %.12f, pi = %.12f \n", slices, In, M_PI);
    slices *= stride;
  }

  ndiv = 1e6;
  double start = __rdtsc();
  In = numerical_integration(x_min,x_max,ndiv);
  double end = __rdtsc();
  double avg_cpd = ((double) (end-start))/ndiv;
  printf("average cycles per division: %f\n", avg_cpd);

  return 0;
}
