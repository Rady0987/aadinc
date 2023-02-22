/* file: covid.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 19 May 2022 */
/* version: 1.0 */
/* Description: This program outputs a single integer 
representing the maximum number of zombies in your army, 
after reaching the lower right corner. */

#include <stdio.h>
#include <stdlib.h>
#define max(x, y) (x > y ? x : y)

void *safeMalloc(int n) {
	void *p = malloc(n);
	if (p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

void minPath(int *board, int i, int j, int cell) {
    int north, east;
    if(cell == 0 || (i == 0 && j == 0)) {
        board[j] = cell;
    } else {

        //diagonals
        if(i > 0 && j > 0) {
            board[j] = max(board[j - 1] + cell - 1, board[j] + cell - 1);
        }

        //first column
        if(i != 0 && j == 0) {
            if(board[j] != 0 && board[j] + cell - 1 > 0) {
                board[j] = board[j] + cell - 1;
            } else {
                board[j] = 0;
            }
        }

        //first line
        if(i == 0 && j != 0) {
            if(board[j - 1] != 0 && board[j - 1] + cell - 1 > 0) {
                board[j] = board[j - 1] + cell - 1;
            } else {
                board[j] = 0;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int n, m, *board, cell;

    scanf("%d %d", &n, &m);

    board = safeMalloc(m * sizeof(int));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &cell);
            minPath(board, i, j, cell);
        }
    }

    printf("%d\n", board[m - 1]);

    free(board);
    return 0;
}