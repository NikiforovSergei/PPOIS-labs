//
// Created by Ivan Titlov on 12.12.22.
//

#ifndef POISLAB3__HEAPSORT_H_
#define POISLAB3__HEAPSORT_H_

#include <iostream>

template<typename T>
void heapify(T &arr, int N, int i) {

  int largest = i;

  int l = 2 * i + 1;

  int r = 2 * i + 2;

  if (l < N && arr[l] > arr[largest])
    largest = l;

  if (r < N && arr[r] > arr[largest])
    largest = r;

  if (largest != i) {
    std::swap(arr[i], arr[largest]);

    heapify(arr, N, largest);
  }
}

template<typename T>
void heapSort(T &arr, int N) {

  for (int i = N / 2 - 1; i >= 0; i--)
    heapify(arr, N, i);
    // Один за другим извлекаем элементы из кучи
  for (int i = N - 1; i > 0; i--) {
      // Перемещаем текущий корень в конец
    std::swap(arr[0], arr[i]);
      // вызываем процедуру heapify на уменьшенной куче
    heapify(arr, i, 0);
  }
}

template<typename T>
void printArray(T &arr, int N) {
  for (int i = 0; i < N; ++i)
    std::cout << arr[i] << " ";
  std::cout << "\n";
}

#endif //POISLAB3__HEAPSORT_H_
