#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void printArray(double arr[], int size) {

  for (int i = 0; i < size; i++) {
    printf("%f ", arr[i]);
  }
  printf("\n");
}
void swap(double * x, double * y) {
  double t;
  t = * x;
  * x = * y;
  * y = t;
}
void compare(double arr[], int i, int j, bool dir) {
  if (dir == (arr[i] > arr[j]))
    swap( & arr[i], & arr[j]);
}

void bitonicMerge(double arr[], int low, int count, bool dir) {
  if (count >1) {
    int index = count / 2;
    for (int i = low; i < low + index; i++)
      compare(arr, i, i + index, dir);
    bitonicMerge(arr, low, index, dir);
    bitonicMerge(arr, low + index, index, dir);
  }
}

void bitonicSort(double arr[], int low, int count, bool direction) {
  if (count >1) {
    int index = count / 2;
    bitonicSort(arr, low, index, 1);
    bitonicSort(arr, low + index, index, 0);
    bitonicMerge(arr, low, count, direction);
  }
}

int main(int argc, char ** argv) {

  bool debug = 0;
  clock_t start, end;
  long double cpu_time_used;
  double * arr;
  int N=65536;
  FILE *f;
  const char * filename = "serialRunningTimes.txt";
  f = fopen(filename,"w");
  for(int n =0; n<10;n++)
    {  N =N*2;
    srandom(1);

    
    arr = (double * ) malloc(N * sizeof(double));
    /*generate random array between 0 and 1*/
    for (int i = 0; i < N; i++) {
      arr[i] = ((double) random()) / (RAND_MAX);
    }
    /*generate sorted array between 0 and 1*/
    // arr[0]=0;
    // double stepS;
    //  stepS = (1.0 - 0.0) / (double)N;
    // for (int i = 0; i < N; i++) {
    //   arr[i] = arr[i-1]+stepS;
    // }
    if (debug) {
      printf("Orignal Array: ");
      printArray(arr, N);
    }
    bool direction = 1; /* true for ascending , false for descending*/
    start = clock();
    bitonicSort(arr, 0, N, direction);
    end = clock();
    if (debug) {
      printf("Sorted Array: ");
      printArray(arr, N);
    }
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Number of elements: %d\n",N);
    printf("Time taken: %Lf seconds.\n", cpu_time_used);
    fprintf(f,"%d \t %Lf\n",N,cpu_time_used);
    }
    fclose(f);
  return 0;
}