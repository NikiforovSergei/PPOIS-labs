#include <iostream>
#include <vector>
#include "HeapSort.h"
#include "StoogeSort.h"
using namespace std;
int main() {
  int arr[] = {12, 11, 13, 5, 6, 7};
  int N = sizeof(arr) / sizeof(arr[0]);
  vector kk = {12, 11, 13, 5, 6, 7};
  heapSort(kk, kk.size());

  cout << "Sorted array is \n";
  printArray(kk, kk.size());


  int arrrr[] = { 2, 4, 5, 3, 1 };
  int n = sizeof(arrrr) / sizeof(arrrr[0]);


  stoogeSort(arrrr, 0, n - 1);
  printArray(arrrr, n);
  return 0;
}
