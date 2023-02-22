/* file: arrest.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 19 May 2022 */
/* version: 1.0 */
/* Description: This program outputs a single integer 
that indicates the number of protesters that will be arrested.
*/

#include <stdio.h>
#include <stdlib.h>

void *safeMalloc(int n) {
	void *p = malloc(n);
	if (p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

char **makeNewGrid(int height, int width) { 
	char **grid;
	grid = safeMalloc(height * sizeof(char *)); 
	for (int row = 0; row < height; row++) {
		grid[row] = safeMalloc(width * sizeof(char));
	}
	return grid;
}

void readGrid(char **grid, int height, int width, int *protesters) {
	char c;
	for(int i = 0; i < height ; i++) {
		for(int j = 0; j < width; j++) {
			c = getchar();
			grid[i][j] = c;

			if(grid[i][j] == '-')
				(*protesters)++;

			if(j == width - 1) 
				getchar();
		}
	}
}

void destroyGrid(char **arr, int width) { 
	for (int i = 0; i < width; i++){
		free(arr[i]); 
	}
	free(arr);
}

void countProtesters(char **grid, int size, int x, int y, int *c) {

   if(x >= size || x < 0 || y >= size || y < 0) {
   	return;
	}

	if(grid[x][y] != '-' || grid[x][y] == '+') {
		return;
	}

   grid[x][y] = '+';
	(*c)++;

   countProtesters(grid, size, x + 1, y, c); 
   countProtesters(grid, size, x - 1, y, c);  
   countProtesters(grid, size, x, y + 1, c);  
   countProtesters(grid, size, x, y - 1, c);
   return;
}

int main(int argc, char *argv[]) {
	int n, c = 0, protesters = 0;
	char **grid;
	scanf("%d", &n);
	getchar();
   grid = makeNewGrid(n, n);
   readGrid(grid, n, n, &protesters);

	for(int i = 0; i < n; i++) {
		countProtesters(grid, n, i, 0, &c);
	} //top line

	for(int i = 0; i < n; i++) {
		countProtesters(grid, n, i, n - 1, &c);
	} //down line

	for(int j = 0; j < n; j++) {
		countProtesters(grid, n, 0, j, &c);
	} //left column

	for(int j = 0; j < n; j++) {
		countProtesters(grid, n, n - 1, j, &c);
	} //right column

	printf("%d\n", protesters - c);
   destroyGrid(grid, n);
   return 0;
}