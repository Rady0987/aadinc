/* file: challenges.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 19 May 2022 */
/* version: 1.0 */
/* Description: This program outputs the length of the kth 
shortest time frame on day d for each request made by
B. Kunte. */

#include <stdio.h>
#include <stdlib.h>

typedef struct Challenge {
    int s;
    int e;
    int shortness;
} Challenge;

void *safeMalloc(int n) {
	void *p = malloc(n);
	if(p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

void swap(int i, int j, Challenge arr[]) {
	Challenge h = arr[i];
	arr[i] = arr[j];
	arr[j] = h;
}

int partition(int length, Challenge arr[]) {
	int left = 0;
	int right = length;
	Challenge pivot = arr[0];
	while(left < right) {
		while((left < right) && (arr[left].shortness <= pivot.shortness)) {
			left++;
		}
		while((left < right) && (pivot.shortness < arr[right - 1].shortness)) {
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

void quickSort(int length, Challenge *arr) {
	if(length <= 1) {
		return;
	}
	int boundary = partition(length, arr);
	quickSort(boundary, arr);
	quickSort(length - boundary - 1, &arr[boundary + 1]);
}

int main(int argc, char *argv[]) {
	int m, n, s, e, k, d, counter = 0;
	Challenge *arr;
	scanf("%d", &n);
	arr = safeMalloc(n * sizeof(Challenge));
	for(int i = 0; i < n; i++) {
		scanf("%d %d", &s, &e);
		arr[i] = (Challenge){.s = s, .e = e, .shortness = e - s + 1};
	}

	quickSort(n, arr);

	scanf("%d", &m);

	for(int i = 0; i < m; i++) {
		scanf("%d %d", &k, &d);
		counter = 0;
		for(int j = 0; j < n; j++) {

			if(d >= arr[j].s && d <= arr[j].e)
					counter++;

			if(counter == k) {
					printf("%d\n", arr[j].shortness);
					break;
			}

		}
		if(k != counter)
			printf("%d\n", -1);
	}
	free(arr);
	return 0;
}