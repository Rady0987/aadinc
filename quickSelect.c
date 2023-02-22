#include <stdio.h>
#include <stdlib.h>

void swap(int *array, int x, int y) {
   int tmp = array[x];
   array[x] = y;
   array[y] = tmp;
}

int partition(int *array, int low, int high) {
   int x = array[high];
   int j = low - 1;
   for (int i = low; i < high; i++) {
      if(array[i] <= x) {
         j++;
         swap(array, i, j);
      }
   }
   swap(array, j + 1, high);
   return j + 1;
}

int randomPartition(int *array, int low, int high) {
   int i = rand() % high;  
   swap(array, 0, i);
   return partition(array, low, high);
}

void randomQuickSelect(int *array, int low, int high, int k) {
   if (low == high - 1) {
      return array[low];
   }

   int index = 
}


int main(int argc, char *argv[]) {
   int array[8] = {1, 4, 3, 5, 11, 0, 6, 90};

   return 0;
}