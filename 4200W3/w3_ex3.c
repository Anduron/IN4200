#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

double pow100(double x){
  double xpow, x4, x32;
  xpow = x*x;
  xpow *= xpow;
  x4 = xpow;
  xpow *= xpow;
  xpow *= xpow;
  xpow *= xpow;
  x32 = xpow;
  xpow *= xpow; //64
  return (xpow*x32*x4);
}

int main(){
  int Nt;
  double x, y, Res;
  clock_t t;


  Nt = 1e5;
  y = 100;

  printf("Number of operations Nt = %i: \n\n", Nt);
  printf("The standard C-library function pow(x,y) took: \n");
  t = clock();
  for (int i = 0; i < Nt; i++){
    x = (rand() %100)+1;
    //printf("%f",x);
    Res = pow(x,y);
  }
  t = clock() - t;
  printf("time t = %f ms, with random x\n\n",(double)t/CLOCKS_PER_SEC*1000);

  printf("Homemade pow100 function took: \n");
  t = clock();
  for (int i = 0; i < Nt; i++){
    x = (rand()%100)+1;
    Res = pow100(x);
  }
  t = clock() - t;
  printf("time t = %f ms, with random x\n\n",(double)t/CLOCKS_PER_SEC*1000);

  x = 10;

  printf("The standard C-library function pow(x,y) took: \n");

  t = clock();
  for (int i = 0; i < Nt; i++){
    Res = pow(x,y);
  }
  t = clock() - t;
  printf("time t = %f ms, with x = %.2f\n\n",(double)t/CLOCKS_PER_SEC*1000,x);

  printf("Homemade pow100 function took: \n");
  t = clock();
  for (int i = 0; i < Nt; i++){
    Res = pow100(x);
  }
  t = clock() - t;
  printf("time t = %f ms, with x = %.2f\n",(double)t/CLOCKS_PER_SEC*1000,x);

  return 0;
}
