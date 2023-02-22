#include <bits/stdc++.h>
using namespace std;

int binarySearch(int arr[], int length, int goal) {
   int left = 0;
   int right = length;
   while(left <= right) {
      int mid = left + (right - left) / 2;

      if (goal == arr[mid])
         return mid;

      if (arr[mid] < goal) {
         left = mid + 1;
      } else {
         right = mid - 1;
      }
   }
   return -1;
}

int main(int argc, char *argv[]) {

   int arr[] = { 1, 2, 5, 11, 333, 1032 };
   int n = sizeof(arr) / sizeof(arr[0]);
   cout << binarySearch(arr, n - 1, 333);

   return 0;
}