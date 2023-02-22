/* file: garbage.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 05 June 2022 */
/* version: 1.0 */
/* Description: This program outputs */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#define min(x, y) (x > y ? y : x)

typedef struct Queue {
    int* array;
    int back;
    int front;
    int size;
} Queue;

void *safeMalloc(int n) {
	void *p = malloc(n);
	if(p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

Queue newQueue(int s) {
    Queue q;
    q.array = safeMalloc(s * sizeof(int));
    q.back = 0; 
    q.front = 0;
    q.size = s;
    return q;
}

void doubleQueueSize(Queue *q) {
    int i;
    int oldSize = q->size;
    q->size = 2 * oldSize;
    q->array = realloc(q->array, q->size * sizeof(int));
    for(i = 0; i < q->back; i++) {
        q->array[oldSize + i] = q->array[i];
    }
    q->back = q->back + oldSize;
}

int isEmptyQueue(Queue q) {
    return (q.back == q.front);
}

void enqueue(int item, Queue *q) {
    q->array[q->back] = item;
    q->back = (q->back + 1) % q->size;
    if(q->back == q->front)
        doubleQueueSize(q);
}

int dequeue(Queue *q) {
    int item;
    if(isEmptyQueue(*q)) {
       printf("queue empty\n");
       abort();
    }
    item = q->array[q->front];
    q->front = (q->front + 1) % q->size;
    return item;
}

int **makeNewGrid(int height, int width) { 
	int **grid;
	grid = safeMalloc(height * sizeof(int *)); 
	for (int row = 0; row < height; row++) {
		grid[row] = safeMalloc(width * sizeof(int));
	}
	return grid;
}

void initGrid(int **arr, int n) {
    for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
    }
}

void readGrid(int **grid, int height, int width) {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			scanf("%d", &grid[i][j]);
		}
	}
}

void destroyGrid(int **arr, int width) { 
	for (int i = 0; i < width; i++){
		free(arr[i]); 
	}
	free(arr);
}

void transformArr(int **arr, int n, int *trashLoc, int s, int *trashDump, int t) {
    for(int i = 0; i < s; i++) {
        arr[n][trashLoc[i]] = INT_MAX;
    }
    for(int i = 0; i < t; i++) {
        arr[trashDump[i]][n + 1] = INT_MAX;
    }
}

bool search(int **rezNetwork, int n, int *path, int s, int t) {
    Queue q = newQueue(n);
    bool visited[n];

    for(int i = 0; i < n; i++) {
        visited[i] = false;
    }

    enqueue(s, &q);
    visited[s] = true;
    path[s] = -1;
 
    while(!isEmptyQueue(q)) {
        int i = dequeue(&q);

        for(int j = 0; j < n; j++) {
            if(visited[j] == false && rezNetwork[i][j] > 0) {
 
                if(j == t) {
                    path[j] = i;
                    free(q.array);
                    return true;
                }
                enqueue(j, &q);
                path[j] = i;
                visited[j] = true;
            }
        }
    }
 
    free(q.array);
    return false;
}

int fulkerson(int **graph, int n, int s, int t) {
    int **rezNetwork, *path, max = 0; 
    path = safeMalloc(n * sizeof(int));
    rezNetwork = makeNewGrid(n, n);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            rezNetwork[i][j] = graph[i][j];
        }
    }
 
 
    while(search(rezNetwork, n, path, s, t)) {

        int flow = INT_MAX;
        for(int j = t; j != s; j = path[j]) {
            int i = path[j];
            flow = min(flow, rezNetwork[i][j]);
        }
 
        for(int j = t; j != s; j = path[j]) {
            int i = path[j];
            rezNetwork[i][j] -= flow;
            rezNetwork[j][i] += flow;
        }
 
        max += flow;
    }
 
    destroyGrid(rezNetwork, n);
    free(path);
    return max;
}

int main(int argc, char *argv[]) {
    int n, s, t;
    scanf("%d %d %d", &n, &s, &t);
    //n += 2;
    
    int **arr = makeNewGrid(n + 2, n + 2);
    initGrid(arr, n + 2);

    int *trashLoc = safeMalloc(s * sizeof(int));
    int *trashDump = safeMalloc(t * sizeof(int));

    for(int i = 0; i < s; i++) {
        scanf("%d", &trashLoc[i]);
    }
    for(int i = 0; i < t; i++) {
        scanf("%d", &trashDump[i]);
    }
    transformArr(arr, n, trashLoc, s, trashDump, t);  
    readGrid(arr, n, n);

    printf("%d\n", fulkerson(arr, n + 2, n, n + 1));
    destroyGrid(arr, n + 2);
    free(trashDump);
    free(trashLoc);
    return 0;
}