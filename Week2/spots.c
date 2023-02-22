/* file: sports.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 01 May 2021 */
/* version: 1.0 */
/* Description: This program outputs m lines, each containing 
a spot of top quality levels (the identifier and quality level 
of the spot). The spots are sorted by quality level, from highest 
to lowest.  */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Spot {
   int quality;
   int identifier;
} Spot;

typedef struct Heap {
  Spot *array;
  int front;
  int size;
} Heap;

void swap(int i, int j, Spot arr[]) {
   Spot h = arr[i];
   arr[i] = arr[j];
   arr[j] = h;
}

int partition(int length, Spot *arr) {
   int l = 0;
   int r = length;
   Spot pivot = arr[0];
   while (l < r) {
      while ((l < r) && (arr[l].quality <= pivot.quality)) {
         l++;
      }
      while ((l < r) && (pivot.quality < arr[r - 1].quality)) {
         r--;
      }
      if (l < r) {
         swap(l, r - 1, arr);
      }
   }
   l--;
   arr[0] = arr[l];
   arr[l] = pivot;
   return l;
}

void quickSort(int length, Spot *arr) {
   if (length <= 1) {
      return;
   }
   int boundary = partition(length, arr);
   quickSort(boundary, arr);
   quickSort(length - boundary - 1, &arr[boundary + 1]);
}

void upHeap(Heap *h, int i) {
   int parent = (i - 1) / 2;

   if (h->array[parent].quality > h->array[i].quality) {
      swap(parent, i, h->array);
      upHeap(h, parent);
   }
}

void downHeap(Heap *h, int i) {
   int r, l, smallest;
   l = i * 2 + 1;
   r = i * 2 + 2;

   if (l < h->size && h->array[l].quality < h->array[i].quality) {
      smallest = l;
   } else {
      smallest = i;
   }

   if (r < h->size && h->array[r].quality < h->array[smallest].quality)
      smallest = r;

   if (smallest != i) {
      swap(smallest, i, h->array);
      downHeap(h, smallest);
   }
}

Heap makeHeap(int n) {
   Heap h;
   h.array = malloc(n * sizeof(Spot));
   assert(h.array != NULL);
   h.front = 0;
   h.size = n;
   return h;
}

void enqueue(Spot n, Heap *hp) {
   int front = hp->front;
   if(front < hp->size) {
      hp->array[front] = n;
      upHeap(hp, front);
      hp->front = front + 1;
   }
}

int main(int argc, char *argv[]){
   int n, m, identifier, diffLevel;
   Spot assign;
   Heap h;

   scanf("%d %d", &n, &m);
   h = makeHeap(m);

   for(int i = 0; i < n; i++) {

      scanf("%d %d", &identifier, &diffLevel);

      assign.identifier = identifier;
      assign.quality = diffLevel;

      if(i < m) {
         enqueue(assign, &h);
      } else {
         
         if(assign.quality > h.array[0].quality) {
            h.array[0] = assign;
            downHeap(&h, 0);;
         }
      }

   }

   quickSort(h.size, h.array);

   for(int i = m - 1; i >= 0; i--) {
      printf("%d %d\n", h.array[i].identifier, h.array[i].quality);
   }
   free(h.array);
   return 0;
}