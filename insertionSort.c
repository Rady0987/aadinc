#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *array, int n) {
   for (int i = 1; i < n; i++) {
      int key = array[i];
      int j = i - 1;
      while (j >= 0 && array[j] > key) {
         array[j + 1] = array[j];
         j--;
      }
      array[j + 1] = key;
   }
}

int main(int argc, char *argv[]) {
   int array[8] = {1, 4, 3, 5, 11, 0, 6, 90};
   insertionSort(array, 8);
   printf("Array: %d", array[0]);
   for(int i = 1; i < 8; i++) {
      printf(", %d", array[i]);
   }
   printf("\n");
   return 0;
}