/* file: azores.c */
/* author: Radu Rusu (email: rusu@student.rug.nl) */
/* date: 19 May 2022 */
/* version: 1.0 */
/* Description: This program outputs */

#include <stdio.h>
#include <stdlib.h>

int maxNumberOfNodes(int d) {
   int sum = 0;
   for(int i = 0; i < d; i++) {
      sum += (int) 1 << i;
   }
   return sum;
}

int main(int argc, char* argv[]) {
   int d;
   scanf("%d", &d);

   int arrLength = maxNumberOfNodes(d);
   int *tree = malloc(arrLength * sizeof(int));
   int index = 0;

   // for(int i = 0; i < d; i++) {
   //    for(int j = 0; j < (int) 1 << i; j++) {
   //       scanf("%d", &tree[index]);
   //       index++;
   //    }
   // }
   for(int i = 0; i < arrLength; i++) {
      scanf("%d", &tree[i]);
   }

   // for(int i = 0; i < arrLength; i++) {
   //    printf("%d ", tree[i]);
   // }
   // printf("\n");
   free(tree);
   return 0;
}