#ifndef PPOIS_LABA3_2_SORTING_H
#define PPOIS_LABA3_2_SORTING_H
#include <iostream>
#include "MyObject.h"
#include "vector"
#include "random"
#include <algorithm>
using namespace std;

template <typename T>
void show_sequence(T container, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << container[i].key << " ";
    }
    std::cout << "\n";
}


template <typename T>
bool isSorted(T arValues, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arValues[i] > arValues[i + 1]) {
            return false;
        }
    }
    return true;
}

template <typename T>
void BozoSort(T &arValues, int size) {
    int slot1 = 0;
    int slot2 = 0;


    srand(time(NULL));


    while (!isSorted(arValues,size)) {
        slot1 = rand() % size;
        slot2 = rand() % size;

        MyObject temp(arValues[slot1]);
        arValues[slot1] = arValues[slot2];
        arValues[slot2] = temp;
    }
}


template <typename T>
void Merge(T &A,int left, int mid,int r)
{

    int n1,n2,i,j,k;
    n1=mid-left+1; //size of left array=n1
    n2=r-mid; //size of right array=n2
    vector<MyObject> L;
    vector<MyObject> R;
    for(i=0;i<n1;i++)
    {
        L.push_back(A[left+i]);
    }
    for(j=0;j<n2;j++)
    {
        R.push_back(A[mid+j+1]);
    }
    i=0,j=0;
    //Comparing and merging them
    //into new array in sorted order
    for(k=left;i<n1 && j<n2;k++)
    {
        if(L[i]<R[j])
        {
            A[k]=L[i++];
        }
        else
        {
            A[k]=R[j++];
        }
    }
    //If Left Array L[] has more elements than Right Array R[]
    //then it will put all the
    // reamining elements of L[] into A[]
    while(i<n1)
    {
        A[k++]=L[i++];
    }
    //If Right Array R[] has more elements than Left Array L[]
    //then it will put all the
    // reamining elements of L[] into A[]
    while(j<n2)
    {
        A[k++]=R[j++];
    }
}


template <typename T>
void MergeSort(T &array,int const begin, int const end)
{
    if (begin >= end)
        return;
    auto mid = begin + (end - begin) / 2;
    MergeSort(array, begin, mid);
    MergeSort(array, mid + 1, end);
    Merge(array, begin, mid, end);
}

template <typename T>
void Reverse(T &array, int size){
    for (int low = 0, high = size - 1; low < high; low++, high--) {
        swap(array[low], array[high]);
    }
}

//template <typename T>
//void merge(T a[], const int low, const int mid, const int high)
//{
//    vector<T> temp;
//
//    int left = low;
//    int right = mid+1;
//    int current = 0;
//    // Merges the two arrays into temp[]
//    while(left <= mid && right <= high) {
//        if(a[left].key <= a[right].key) {
//            temp[current] = a[left];
//            left++;
//        }
//        else { // if right element is smaller that the left
//            temp[current] = a[right];
//            right++;
//        }
//        current++;
//    }
//
//    // Completes the array
//
//    // Extreme example a = 1, 2, 3 || 4, 5, 6
//    // The temp array has already been filled with 1, 2, 3,
//    // So, the right side of array a will be used to fill temp.
//    if(left > mid) {
//        for(int i=right; i <= high;i++) {
//            temp[current] = a[i];
//            current++;
//        }
//    }
//        // Extreme example a = 6, 5, 4 || 3, 2, 1
//        // The temp array has already been filled with 1, 2, 3
//        // So, the left side of array a will be used to fill temp.
//    else {
//        for(int i=left; i <= mid; i++) {
//            temp[current] = a[i];
//            current++;
//        }
//    }
//    // into the original array
//    for(int i=0; i<=high-low;i++) {
//        a[i+low] = temp[i];
//    }
//
//}
//
//template <typename T>
//void merge_sort(T a[], const int low, const int high)
//{
//    if(low >= high) return;
//    int mid = (low+high)/2;
//    merge_sort(a, low, mid);  //left half
//    merge_sort(a, mid+1, high);  //right half
//    merge(a, low, mid, high);  //merge them
//}

#endif //PPOIS_LABA3_2_SORTING_H
