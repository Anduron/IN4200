#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//compile with $gcc w1_ex1a.c -o ex1a -lm
//run with ./ex1a

int main()
{
  int stopping, i;
  double p, m, r, l, tolerance;
  stopping = 100;               //STOPPING CRITERION
  i = 0;                        //INITIAL ITERATION
  r = 0;                        //INITIAL VALUE
  l = 4./5;                     //THE EXPECTED VALUE
  tolerance = 1e-12;            //MARGIN OF ERROR

  while (i++ < stopping && fabs(r - l) > tolerance)
  {
    r += pow(-1,i-1) * (1/pow(2,2*(i-1))); //MATHEMATICAL FORMULA
  };

  if (fabs(r - l) > tolerance)            //TEST GIVING FEEDBACK TO USER
  {
    printf("DID NOT CONVERGE");
  } else {
    printf("CONVERGED TO EXPECTED VALUE r = %f, IN AMOUNT OF STEPS i = %i \n", r, i);
  };
  return 0;
};
