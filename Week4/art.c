/* file: art.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 19 May 2022 */
/* version: 1.0 */
/* Description: This program outputs the maximum number 
of replicas you can do without getting caught. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Painting {
   int difficulty;
   int skill;
} Painting;

typedef struct Heap
{
  Painting *paintings;
  int front;
  int size;
} Heap;

void *safeMalloc(long long unsigned int n) {
	void *p = malloc(n);
	if(p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

void swap(int i, int j, Painting arr[]) {
   Painting h = arr[i];
   arr[i] = arr[j];
   arr[j] = h;
}

void upHeap(Heap *h, int i) {
   int parent = (i - 1) / 2;

   if (h->paintings[parent].difficulty == h->paintings[i].difficulty) {
      if(h->paintings[parent].skill < h->paintings[i].skill) {
         swap(parent, i, h->paintings);
         upHeap(h, parent);
      }
   }

   if (h->paintings[parent].difficulty > h->paintings[i].difficulty) {
      swap(parent, i, h->paintings);
      upHeap(h, parent);
   }
}

void downHeap(Heap *h, int i) {
   int r, l, smallest;
   l = i * 2 + 1;
   r = i * 2 + 2;

   if (l < h->size && h->paintings[l].difficulty < h->paintings[i].difficulty) {
      smallest = l;
   } else {
      smallest = i;
   }

   if (r < h->size && h->paintings[r].difficulty < h->paintings[smallest].difficulty)
      smallest = r;

   if (smallest != i) {
      swap(smallest, i, h->paintings);
      downHeap(h, smallest);
   }
}

Heap makeHeap(int n) {
   Heap h;
   h.paintings = safeMalloc(n * sizeof(Painting));
   assert(h.paintings != NULL);
   h.front = 0;
   h.size = n;
   return h;
}

void enqueue(Painting n, Heap *hp) {
   int fr = hp->front;
   if(fr < hp->size) {
      hp->paintings[fr] = n;
      upHeap(hp, fr);
      hp->front = fr + 1;
   }
}

void initHeap(Heap *h, int n) {
   for(int i = 0; i < n; i++) {
      h->paintings[i].difficulty = 10000001;
      h->paintings[i].skill = 10000001;
   }
}

void dequeue(Heap *hp) {
   if(hp->front > 0) {
      hp->front--;
      initHeap(hp, 1);
      downHeap(hp, 0);
   }
}

int best(Heap oil, Heap waterColor, int mySkill, int n, bool pSwitch) {
   int rez = 0, skill;
   skill = mySkill;
   for(int i = 0; i < n; i++) {
      if(oil.paintings[0].difficulty <= skill && !pSwitch) {
         rez++;
         skill += oil.paintings[0].skill;
         dequeue(&oil);
         pSwitch = true;
      }

      if(waterColor.paintings[0].difficulty <= skill && pSwitch) {
         rez++;
         skill += waterColor.paintings[0].skill;
         dequeue(&waterColor);
         pSwitch = false;
      }
   }
   return rez;
} 

Heap copyHeap(Heap *h) {
   Heap temp;
   temp.front = h->front;
   temp.size = h->size;
   temp.paintings = safeMalloc(h->size * sizeof(Painting));
   assert(temp.paintings != NULL);
   for(int i = 0; i < h->size; i++) {
      temp.paintings[i] = h->paintings[i];
   }
   return temp;
}

int main(int argc, char *argv[]){
   int n, mySkill, style, skillReward, difficulty, rez, rez1;
   Painting p;
   Heap oil, waterColor; 

   scanf("%d %d", &n, &mySkill);

   oil = makeHeap(n);
   waterColor = makeHeap(n);

   initHeap(&oil, n);
   initHeap(&waterColor, n);

   for(int i = 0; i < n; i++) {
      scanf("%d %d %d", &style, &difficulty, &skillReward);
      p.difficulty = difficulty;
      p.skill = skillReward;
      if(style == 0) {
         enqueue(p, &oil);
      } else {
         enqueue(p, &waterColor);
      }
   }

   Heap tmpWaterColor, tmpOil;
   tmpWaterColor = copyHeap(&waterColor);
   tmpOil = copyHeap(&oil);

   rez = best(oil, waterColor, mySkill, n, true);
   rez1 = best(tmpOil, tmpWaterColor, mySkill, n, false);

   if(rez > rez1) {
      printf("%d\n", rez);
   } else {
      printf("%d\n", rez1);
   }
   free(oil.paintings);
   free(waterColor.paintings);
   free(tmpWaterColor.paintings);
   free(tmpOil.paintings);
   return 0;
}