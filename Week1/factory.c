/* file: factory.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 24 Apr 2021 */
/* version: 1.0 */
/* Description: This program outputs the minimum number 
of days that the factories need to produce at least P laptops */

#include <stdio.h>
#include <stdlib.h>

long binarySearch(int *gpuNumber, int *timeToProduce, int factories, __int128_t l, __int128_t r, __int128_t gpuToProduce) {
	__int128_t target = 0;
	__int128_t middle = l + (r - l) / 2;

	for(int i = 0; i < factories; i++) {
		target += gpuNumber[i] * (middle / timeToProduce[i]);
	}

	if((target < gpuToProduce) && (l == r)) {
			return l + 1;
		} else if ((target >= gpuToProduce) && (l == r)) {
			return l;
		}

	if(target < gpuToProduce) {
		return binarySearch(gpuNumber, timeToProduce, factories, 1 + middle, r, gpuToProduce);
	} else {
		return binarySearch(gpuNumber, timeToProduce, factories, l, middle, gpuToProduce);
	}
}

int main(int argc, char *argv[]) {
	unsigned long long int gpuToProduce, MAX = 9223372036854775807;
	int factories;

	scanf("%llu", &gpuToProduce);
	scanf("%d", &factories);
	int timeToProduce[factories], gpuNumber[factories];

	for(int i = 0; i < factories; i++) {
		scanf("%d %d", &gpuNumber[i], &timeToProduce[i]);
	}

	printf("%ld\n", binarySearch(gpuNumber, timeToProduce, factories, 0, MAX, gpuToProduce));
}
