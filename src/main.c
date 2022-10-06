#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

#define ARRAY_SIZE 100000000

unsigned short int* radix_sort(unsigned short int* array,
  unsigned int start_index, unsigned int end_index, unsigned int byte_number) {

  if( start_index >= end_index || byte_number == 0 ) {
    return array;
  }

  unsigned int start = start_index;
  unsigned int end = end_index;
  unsigned short int temp;

  while( start < end ) {
    if( array[start] & byte_number ) {
      temp = array[start];
      array[start] = array[end];
      array[end] = temp;
      end --;
    } else {
      start ++;
    }
  }

  if( array[start] & byte_number ) {
    radix_sort(array, start_index, end-1, byte_number>>1);
    radix_sort(array, start, end_index, byte_number>>1);
  } else {
    radix_sort(array, start_index, end, byte_number>>1);
    radix_sort(array, start+1, end_index, byte_number>>1);
  }

  return array;
}

int main(int argc, char* argv[]) {

  printf("Radix Sort - O(kn) Sorting Algorithm\n");

  /* PREPARING THE DATA */

  srand((unsigned int) time(NULL));

  unsigned short int byte_number = 1 << 15;
  unsigned int start_index = 0;
  unsigned int end_index = ARRAY_SIZE - 1;

  unsigned short int* array = (unsigned short int*) malloc(sizeof(unsigned short int) * ARRAY_SIZE);
  for(int i = 0; i < ARRAY_SIZE; i ++) {
    array[i] = rand();
  }

  /* THE ALGORITHM */

  printf("Computing...");
  clock_t start = clock();

  radix_sort(array, start_index, end_index, byte_number);

  clock_t end = clock();
  printf(" completed in %.4f seconds\n", ((double)end-start)/CLOCKS_PER_SEC);

  /* PRINTING THE RESULT */

  bool the_algorithm_worked = true;
  for(int i = 1; i < ARRAY_SIZE; i ++) {
    if( array[i-1] > array[i] ) {
      the_algorithm_worked = false;
      break;
    }
  }

  if( the_algorithm_worked ) {
    printf("The algorithm works successfully\n");
  } else {
    printf("The algorithm did not work\n");
  }

  fflush(stdout);
  return EXIT_SUCCESS;
}
