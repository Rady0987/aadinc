/* file: noster.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 14 May 2022 */
/* version: 1.0 */
/* Description: This program outputs the number of 
updates u that Noster will implement and the difference d 
between the happiness of the first update and the happiness 
of the last update in the Noster update list. */

#include <stdio.h>
#include <stdlib.h>

void *safeMalloc(int n) {
	void *p = malloc(n);
	if(p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

int binarySearch(int *arr, int *minimals , int length, int goal) {
   int left = 1;
   int right = length;
   while(left <= right) {
      int mid = left + (right - left) / 2;
      if (arr[goal] >= arr[minimals[mid]]) {
         left = mid + 1;
      } else {
         right = mid - 1;
      }
   }
   return left;
}

int updatesOptimizer(int *arr, int n, int *longestSeq) {
   int *predecessors, *minimals, length = 0;

   predecessors = safeMalloc(n * sizeof(int));
   minimals = safeMalloc((n + 1) * sizeof(int));

   for(int i = 0; i < n; i++) {
      int nextLength = binarySearch(arr, minimals, length, i);
      predecessors[i] = minimals[nextLength - 1];
      minimals[nextLength] = i;
      if(nextLength > length)
         length = nextLength;
   }

   int index = minimals[length];
   for(int i = length - 1; i >= 0; i--) {
      longestSeq[i] = arr[index];
      index = predecessors[index];
   }

   free(predecessors);
   free(minimals);
   return length;
}


int main(int argc, char *argv[]) {
	int n, *arr, *longestSeq, updates, happinessDiff;
	scanf("%d", &n);
	arr = safeMalloc(n * sizeof(int));
   longestSeq = safeMalloc(n * sizeof(int));

	for(int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	updates = updatesOptimizer(arr, n, longestSeq);
	happinessDiff = longestSeq[updates - 1] - longestSeq[0];

   printf("%d %d\n", updates, happinessDiff);

	free(arr);
	free(longestSeq);
	return 0;
}