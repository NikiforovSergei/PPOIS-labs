#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class In_place_merge_sort {
public:

    template<typename T>

    void merge(T& arr, int start, int middle, int end)
    {
      
        if (arr[middle] <= arr[middle + 1]) {
            return;
        }
        while (start <= middle && (middle + 1) <= end) {
            if (arr[start] <= arr[middle + 1]) {
                start++;
            }
            else {
                int value = arr[middle + 1];
                int index = middle + 1;

                while (index != start) {
                    arr[index] = arr[index - 1];
                    index--;
                }
                arr[start] = value;

                int start2 = middle + 1;
                start++;
                middle++;
                start2++;
            }
        }
    }

    template<typename T>
    void inplacemergeSort(T& arr, int left, int right)
    {
        if (left < right) {
            int middle = left + (right - left) / 2;

            inplacemergeSort(arr, left, middle);
            inplacemergeSort(arr, middle + 1, right);

            merge(arr, left, middle, right);
        }
    }
};

class Bogosort {
public:
    template<typename T>
    bool isSorted(T& a, int n)
    {
        while (--n > 0)
            if (a[n] < a[n - 1])
                return false;
        return true;
    }

    template<typename T>
    void shuffle(T& a, int n)
    {
        for (int i = 0; i < n; i++)
            swap(a[i], a[rand() % n]);
    }

    template<typename T>
    void bogosort(T& a, int n)
    {
        while (!isSorted(a, n))
            shuffle(a, n);
    }
};

void print(int A[], int size, int variant)
{
    if (variant == 1) {
        cout << "Sorting array by In-place merge:\n";
        for (int i = 0; i < size; i++)
            cout << " " << A[i];
        cout << "\n";
    }
    else {
        cout << "Sorting array by Bogosort:\n";
        for (int i = 0; i < size; i++)
            cout << " " << A[i];
        cout << "\n";
    }
}

void printVector(vector<int> A, int size, int variant)
{
    if (variant == 1) {
        cout << "Sorting vector by In-place merge:\n";
        for (int i = 0; i < size; i++)
            cout << " " << A[i];
        cout << "\n";
    }
    else {
        cout << "Sorting vector by Bogosort:\n";
        for (int i = 0; i < size; i++)
            cout << " " << A[i];
        cout << "\n";
    }
}

int main()
{
    In_place_merge_sort inplace;
    Bogosort bogosort;

    vector<int> beta = { 40, 56, 23, 5, 79, 45, 53, 52, 78, 91, 13 };
    int arr[] = { 123, 1, 3, 52, 88, 23, 36, 12, 98 };

    int arr_size = sizeof(arr) / sizeof(arr[0]);

    inplace.inplacemergeSort(arr, 0, arr_size - 1);
    inplace.inplacemergeSort(beta, 0, beta.size() - 1);

    print(arr, arr_size, 1);
    printVector(beta, beta.size(), 1);

    bogosort.bogosort(arr, arr_size);
    bogosort.bogosort(beta, beta.size());

    print(arr, arr_size, 2);
    printVector(beta, beta.size(), 2);
    return 0;
}