void swap(int i, int j, Assignment arr[]) {
   Assignment h = arr[i];
   arr[i] = arr[j];
   arr[j] = h;
}

int partition(int length, Assignment *arr) {
   int l = 0;
   int r = length;
   Assignment pivot = arr[0];
   while (l < r) {
      while ((l < r) && (arr[l].difficulty <= pivot.difficulty)) {
         l++;
      }
      while ((l < r) && (pivot.difficulty < arr[r - 1].difficulty)) {
         r--;
      }
      if (l < r) {
         /* (arr[l] > pivot) && (arr[r-1] <= pivot) : swap */
         swap(l, r - 1, arr);
      }
   }
   /* put pivot in r location: swap(0,l-1,arr) */
   l--;
   arr[0] = arr[l];
   arr[l] = pivot;
   return l;
}

void quickSort(int length, Assignment *arr) {
   if (length <= 1) {
      return; /* nothing to sort */
   }
   int boundary = partition(length, arr);
   quickSort(boundary, arr);
   quickSort(length - boundary - 1, &arr[boundary + 1]);
}

void heapify(Assignment *arr, int size, int i) {
   int r, l, smallest;
   l = i * 2 + 1;
   r = i * 2 + 2;
   smallest = i;
   if(l < size && arr[l].difficulty < arr[smallest].difficulty) {
      smallest = l;
   } 
   if(r < size && arr[r].difficulty < arr[smallest].difficulty)
      smallest = r;
   if(smallest != i) {
      swap(i, smallest, arr);
      heapify(arr, size, smallest);
   }
}

void heapifyHelper(Assignment *arr, int n) {
   int startIndex = (n / 2) - 1;
   for (int i = startIndex; i >= 0; i--) {
      heapify(arr, n, i);
   }
}

void heapSort(Assignment *arr, int n) {
   for (int i = n - 1; i >= 0; i--) {
      swap(0, i, arr);
      heapifyHelper(arr, i);
   }
}