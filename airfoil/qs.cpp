#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <fstream>

//using std::ifstream;
void quicksort(long array[], long left, long right);
float quicksort(float array[], long left, long right);

int main(int argc, char **argv) {
  FILE *fp;
  if((fp = fopen(argv[1], "r")) == NULL) {
    printf("Can't open file"); exit(-1);
  }
  printf("%s\n", argv[1]);
  /*ifstream fp;
  fp.open(argv[0]);
  if(!fp) {
    printf("Can't open file"); exit(-1);
  }*/

// long *array = (long *) malloc(101250 * sizeof(long));
  float array[405000];
  long index = -1;
  //while(!fp.eof()) {
  for( index = 0; index < 405000; ++index) {
    fscanf(fp, "%f\n", &array[index]);
    //fp >> array[++index];
  }
/*
 for( index = 0; index < 101250; ++index) {
    printf("%ld\n", array[index]);
  }
*/
  
//  printf("%ld\n", sizeof(array)/sizeof(long));
 fclose(fp);
 //fp.close();
//  quicksort(array, 0, sizeof(array)/sizeof(long)-1);
//  printf("\n SORTED ARRAY \n");
//  for( index = 0; index < 101250; ++index) {
//    printf("%ld\n", array[index]);
//  }

  FILE *fp2;
  if((fp = fopen(argv[2], "r")) == NULL) {
    printf("Can't open file"); exit(-1);
  }
  printf("%s\n", argv[2]);
  float array2[405000], difference[405000];
  float sum = 0;
  for ( index = 0; index < 405000; ++index) {
    fscanf(fp, "%f\n", &array2[index]);
    //printf("%f\n", array2[index]);
    //difference[index] = array[index] - array2[index];
//    sum += array[index] - array2[index];
  }

//  printf("sizeof(array)/sizeof(float)-1 : %d, array2 : %d\n", sizeof(array)/sizeof(float)-1, sizeof(array2)/sizeof(float)-1);
//  quicksort(array, 0, sizeof(array)/sizeof(float)-1);
//  quicksort(array2, 0, sizeof(array2)/sizeof(float)-1);
  for ( index = 0; index < 405000; ++index) {
    if(array[index] - array2[index] != 0.0f) {
      printf("array[%d] = %.12f, array2[%d] = %.12f, diff: %.12f\n", index, array[index], index, array2[index], array[index] - array2[index]);
    }
  }
//  printf("total error %f\n", sum);
//  printf("average error %f\n", sum/4200);
}

void quicksort(long array[], long left, long right) {
  long i = left, j = right;
  long tmp;
  long pivot = array[(left+right)/2];

  while(i <= j) {
    while(array[i] < pivot) {
      i++;
    }
    while(array[j] > pivot) {
      j--;
    }
    if(i <= j) {
      tmp = array[i];
      array[i] = array[j];
      array[j] = tmp;
      i++;
      j--;
     }
  }

  if(left < j) {
    quicksort(array, left, j);
  } 
  if(i < right) {
    quicksort(array, i, right);
  }

}

float quicksort(float array[], long left, long right) {
  long i = left, j = right;
  float tmp;
  float pivot = array[(left+right)/2];

  while(i <= j) {
    while(array[i] < pivot) {
      i++;
    }
    while(array[j] > pivot) {
      j--;
    }
    if(i <= j) {
      tmp = array[i];
      array[i] = array[j];
      array[j] = tmp;
      i++;
      j--;
     }
  }

  if(left < j) {
    quicksort(array, left, j);
  }
  if(i < right) {
    quicksort(array, i, right);
  }

}
