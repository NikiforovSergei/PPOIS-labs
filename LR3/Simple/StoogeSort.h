//
// Created by Egor Vasilkov on 3.12.22.
//

#ifndef POISLAB3__STOOGESORT_H_
#define POISLAB3__STOOGESORT_H_

#include <iostream>

// Function to implement stooge sort
template<typename T>
void stoogeSort(T &arr, int l, int h)
{
  if (l >= h)
    return;

  if (arr[l] > arr[h])
    std::swap(arr[l], arr[h]);

  if (h - l + 1 > 2) {
    int t = (h - l + 1) / 3;

    stoogeSort(arr, l, h - t);

    stoogeSort(arr, l + t, h);

    stoogeSort(arr, l, h - t);
  }
}




#endif //POISLAB3__STOOGESORT_H_
