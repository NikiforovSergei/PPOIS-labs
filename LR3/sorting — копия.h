#ifndef PPOIS_LABA3_2_SORTING_H
#define PPOIS_LABA3_2_SORTING_H
#include <iostream>
#include "MyObject.h"
#include <vector>
#include "random"
#include <algorithm>

using namespace std;

template <typename T>
void show_sequence(T container, int size) 
{
    for (int i = 0; i < size; ++i) 
        std::cout << container[i].key << " ";
    std::cout << "\n";
}

template <typename T>
bool isSorted(T arValues, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (arValues[i] > arValues[i + 1]) 
            return false;
    }
    return true;
}

template <typename T>
void BozoSort(T& arValues, int size) {
    int slot1 = 0;
    int slot2 = 0;
    srand(time(NULL));

    while (!isSorted(arValues, size)) {
        slot1 = rand() % size;
        slot2 = rand() % size;

        MyObject temp(arValues[slot1]);
        arValues[slot1] = arValues[slot2];
        arValues[slot2] = temp;
    }
}

template <typename T>
void Merge(T& A, int left, int mid, int r)
{

    int n1, n2, i, j, k;
    n1 = mid - left + 1;
    n2 = r - mid;
    vector<MyObject> L;
    vector<MyObject> R;
    for (i = 0; i < n1; i++)
    {
        L.push_back(A[left + i]);
    }
    for (j = 0; j < n2; j++)
    {
        R.push_back(A[mid + j + 1]);
    }
    i = 0, j = 0;

    for (k = left; i < n1 && j < n2; k++)
    {
        if (L[i] < R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }

    while (i < n1)
        A[k++] = L[i++];

    while (j < n2)
        A[k++] = R[j++];
}

template <typename T>
void MergeSort(T& array, int const begin, int const end)
{
    if (begin >= end)
        return;
    auto mid = begin + (end - begin) / 2;
    MergeSort(array, begin, mid);
    MergeSort(array, mid + 1, end);
    Merge(array, begin, mid, end);
}

#endif