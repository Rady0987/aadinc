/* file: scalpers.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 24 Apr 2021 */
/* version: 1.0 */
/* Description: This program outputs the day on which 
the most websites are selling a GPU(an integer), then 
a space, followed by the quantity of GPUs for sale that day.  */

#include <stdio.h>
#include <stdlib.h>

// Function to swap two variables
void swap(int i, int j, int arr[]) {
   int h = arr[i];
   arr[i] = arr[j];
   arr[j] = h;
}

int partition(int arr[], int left, int right) {
   int pivot = abs(arr[right]);
   int i = left - 1;

   for (int j = left; j <= right - 1; j++) {
      if (abs(arr[j]) < pivot) {
         i++;
         swap(i, j, arr);
      }
   }
   swap(i + 1, right, arr);
   return (i + 1);
}

// Adapted quick sort function to the problem
void quickSort(int left, int right, int arr[]) {
   if (left < right) { 

      int boundary = partition(arr, left, right);

      quickSort(left, boundary - 1, arr);
      quickSort(boundary + 1, right, arr);
   }
}

int main(int argc, char *argv[]) {
   int n, startDay, endDay, stores = 0, maxStores = 0, bestDay = 0;
   int index = 0, size, *arr;

   scanf("%d", &n);
   size = 2 * n;
   arr = malloc(size * sizeof(int));
   
   // Reading the website days and storing in an array
   for (int i = 0; i < n; i++) { 
      scanf("%d %d", &startDay, &endDay);
      arr[index] = startDay;
      // Making the closing day value negative to differentiate from the opening
      arr[index + 1] = -1 * (endDay + 1); 
      index += 2;
   }

   quickSort(0, size - 1, arr);

   // Iterate over the scalping days
   for (int i = 0; i < size; i++) { 
      int day = arr[i];

      // Modify the number of current stores according to the value of the day
      if (day < 0) { 
         stores--;
      } else {
         stores++;
      }

      // Check if the current number of stores is greater than the max and if 
      // all periods are opened and closed properly
      if ((stores > maxStores) && (abs(arr[i + 1]) != abs(day))) {
         bestDay = abs(day);
         maxStores = stores;
      }
   }
   
   printf("%d %d\n", bestDay, maxStores);
   free(arr);

   return 0;
}