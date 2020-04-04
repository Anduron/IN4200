#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b){
  int t=*a; *a=*b; *b=t;
}

void sort(int arr[], int beg, int end){

  if (end > beg + 1) {
    int piv = arr[beg], l = beg + 1, r = end;
    while (l < r) {
      if (arr[l] <= piv)
        l++;
      else
        swap(&arr[l], &arr[--r]);
      }
      swap(&arr[--l], &arr[beg]);
      sort(arr, beg, l);
      sort(arr, r, end);
    }
}

void permsort(int arr[], int idxarr[], int beg, int end){

  if (end > beg + 1) {
    int piv = arr[idxarr[beg]], l = beg + 1, r = end;
    while (l < r) {
      if (arr[idxarr[l]] <= piv)
        l++;
      else
        swap(&idxarr[l], &idxarr[--r]);
      }
      swap(&idxarr[--l], &idxarr[beg]);
      permsort(arr, idxarr, beg, l);
      permsort(arr, idxarr, r, end);
    }
}

int main(){
  int n = 10;
  int *arr;
  int *idxarr;

  arr = (int *)malloc(n*sizeof(int));
  idxarr = (int *)malloc(n*sizeof(int));

  for (int i = 0; i<n; i++){
    arr[i] = (rand() % 100) +1;
    idxarr[i] = i;
  }

  printf("idxarr:");
  for (int i = 0; i<n; i++){
      printf(" %d ", idxarr[i]);
  }

  printf("\narray:");
  for (int i = 0; i<n; i++){
      printf(" %d ", arr[i]);
  }
  /*
  printf("\nsorted:");
  sort(arr, 0, n);
  for (int i = 0; i<n; i++){
      printf(" %d ", arr[i]);
  }
  */

  printf("\npermsort:");
  permsort(arr,idxarr, 0, n);
  for (int i = 0; i<n; i++){
      printf(" %d ", arr[idxarr[i]]);
  }
  printf("\nindex array");
  for (int i = 0; i<n; i++){
      printf(" %d ", idxarr[i]);
  }

  printf("\n");

  free(arr);
  free(idxarr);

  return 0;
}
