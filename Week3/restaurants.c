/* file: restaurants.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 14 May 2022 */
/* version: 1.0 */
/* Description: This program outputs the coordinates 
of the best spot for Bob to stay  */

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

void swap(int i, int j, int arr[]) {
	int h = arr[i];
	arr[i] = arr[j];
	arr[j] = h;
}

int partition(int length, int arr[]) {
	int left = 0;
	int right = length;
	int pivot = arr[0];
	while(left < right) {
		while((left < right) && (arr[left] <= pivot)) {
			left++;
		}
		while((left < right) && (pivot < arr[right - 1])) {
			right--;
		}
		if(left < right) {
			swap(left, right - 1, arr);
		}
	}
	left--;
	arr[0] = arr[left];
	arr[left] = pivot;
	return left;
}

void quickSort(int length, int *arr) {
	if(length <= 1) {
		return;
	}
	int boundary = partition(length, arr);
	quickSort(boundary, arr);
	quickSort(length - boundary - 1, &arr[boundary + 1]);
}

int main(int argc, char *argv[]) {
	int n, r, isRest, c = 0, median;
	int *x, *y;
	scanf("%d %d", &n, &r);

	x = safeMalloc(r * sizeof(int));
	y = safeMalloc(r * sizeof(int));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			scanf("%d", &isRest);
			if(isRest == 1) {
				x[c] = i;
				y[c] = j;
				c++;
			}
		}
	}
	quickSort(r, x);
	quickSort(r, y);
	median = (r + 1) / 2 - 1;
	printf("%d %d\n", x[median], y[median]);
	free(x);
	free(y);
	return 0;
}