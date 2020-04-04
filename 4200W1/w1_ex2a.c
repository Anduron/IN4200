#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MINIDX(oldidx, i, arr) (((arr[oldidx]) < (arr[i]))?(oldidx):(i))
#define MAXIDX(oldidx, i, arr) (((arr[oldidx]) > (arr[i]))?(oldidx):(i))

typedef struct{
  int n;
  char *timearr;
  double *temparr;
}temp_data;

int min_index_of_1darray(double *array1d, int n){

  int minimum_idx;
  double min;

  min = array1d[0];
  minimum_idx = 0;

  for (int i = 0; i<n; i++){
    minimum_idx = MINIDX(minimum_idx, i, array1d);
  }
  return minimum_idx;
}

int max_index_of_1darray(double *array1d, int n){

  int maximum_idx;
  double max;

  max = array1d[0];
  maximum_idx = 0;
  for (int i = 0; i<n; i++){
    maximum_idx = MAXIDX(maximum_idx, i, array1d);
  }
  return maximum_idx;
}


double average_value_of_1darray(double *array1d, int n){

  double average = 0;

  for (int i = 0; i < n; i++){
    average += array1d[i];
  }
  average = average/(double) n;

  return average;
}

double standard_deviation_of_1darray(double *array1d, int n, double average){

  double stddev = 0;
  double t_;

  for (int i = 0; i < n; i++){
    t_ = array1d[i] - average;
    stddev += t_*t_;
  }

  stddev = sqrt((stddev)/(double) (n-1));

  return stddev;
}

void read_from_file(char *filename, temp_data *data){

  int datacontent;
  FILE *infile = fopen(filename, "r");

  if (infile == NULL) {
      printf("OH DAMN CANT open file %s\n", filename);
      exit(0);
  }

  datacontent = fscanf(infile, "%d", &data->n);

  data->timearr = (char *)malloc(5 * data->n * sizeof(char));
  data->temparr = (double *)malloc(data->n * sizeof(double));

  for (int i = 0; i < data->n; i++){
    datacontent = fscanf(infile, "%5s %lf", &data->timearr[5*i], &data->temparr[i]);
  }

}


int main(){

  temp_data *data;
  int minidx, maxidx;
  double avg, stddev;

  data = (temp_data *)malloc(sizeof(temp_data));

  read_from_file("temperature.txt", data);

  minidx = min_index_of_1darray(data->temparr , data->n);
  maxidx = max_index_of_1darray(data->temparr , data->n);
  avg = average_value_of_1darray(data->temparr, data->n);
  stddev = standard_deviation_of_1darray(data->temparr, data->n, avg);

  for (int i = 0; i < data->n; i++){
    printf("time: %.5s, temperature: %lf \n", &data->timearr[5*i], data->temparr[i]);
  }

  printf("index of max and min temp: %i and %i \n", maxidx, minidx);
  printf("minimum temperature was: %lf, at time: %.5s \n", data->temparr[minidx], &data->timearr[5*minidx]);
  printf("maximum temperature was: %lf, at time: %.5s \n", data->temparr[maxidx], &data->timearr[5*maxidx]);
  printf("average temp was: %lf \n", avg);
  printf("standard deviation of temps was: %lf \n", stddev);


  free(data->timearr);
  free(data->temparr);
  free(data);
  return 0;
}
