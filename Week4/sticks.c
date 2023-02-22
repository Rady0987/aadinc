/* file: sticks.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 14 May 2022 */
/* version: 1.0 */
/* Description: This program outputs the smallest 
number of USB sticks that the Themis TA needs to 
fit all of the files. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void *safeMalloc(int n) {
	void *p = malloc(n);
	if(p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

int powerOfTwo(int power) {
   int result = 1;
   for(int i = 0; i < power; i++) {
      result *= 2;
   }
   return result;
}

int sticksNeeded(int *histogram, int memoryOnStick, int numberOfFiles, int maxFileSize) {
   int index = 0, numberOfSticks = 0;

   while(numberOfFiles != 0) {

      int memoryInUse = 0, i = 0;
      
      index = maxFileSize - i;

      while(true) {

         index = maxFileSize - i;

         if(index < 0)
            break;
      
         if(histogram[index] > 0 && memoryOnStick >= powerOfTwo(index) + memoryInUse) {
            numberOfFiles--;
            histogram[index]--;
            memoryInUse += powerOfTwo(index);
         } else {
            i++;
         }
      }
      numberOfSticks++;
   }
   return numberOfSticks;
}

   void initHistogram(int *arr, int n) {
      for(int i = 0; i < n; i++) {
         arr[i] = 0;
      }
   }

int main(int argc, char *argv[]) {
   int memoryOnStick, numberOfFiles, *histogram, maxFileSize, tmp;
   scanf("%d %d", &memoryOnStick, &numberOfFiles);

   if(memoryOnStick == 0 && numberOfFiles == 0)
      return 0;

   maxFileSize = (int)log2(memoryOnStick);

   histogram = safeMalloc((maxFileSize + 1) * sizeof(int));
   initHistogram(histogram, maxFileSize + 1);

   for(int i = 0; i < numberOfFiles; i++) {
      scanf("%d", &tmp);
      histogram[(int)log2(tmp)]++;
   }

   printf("%d\n", sticksNeeded(histogram, memoryOnStick, numberOfFiles, maxFileSize));
   free(histogram);
   return 0;
}