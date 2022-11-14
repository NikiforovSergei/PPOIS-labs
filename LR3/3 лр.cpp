#include <iostream>
#include <vector>
using namespace std;
class In_place_merge {
public:
    template<typename T>
    void merge(T& arr, int start, int mid, int end)
    {
        int start2 = mid + 1;
        if (arr[mid] <= arr[start2]) {
            return;
        }
        while (start <= mid && start2 <= end) {
            if (arr[start] <= arr[start2]) {
                start++;
            }
            else {
                int value = arr[start2];
                int index = start2;

                while (index != start) {
                    arr[index] = arr[index - 1];
                    index--;
                }
                arr[start] = value;

                start++;
                mid++;
                start2++;
            }
        }
    }

    template<typename T>
    void mergeSort(T& arr, int l, int r)
    {
        if (l < r) {
            int m = l + (r - l) / 2;

            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);

            merge(arr, l, m, r);
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

void printArray(int A[], int size, int variant)
{
    if (variant == 1) {
        cout << "Sorting by In-place merge sorting:\n";
        for (int i = 0; i < size; i++)
            cout << " " << A[i];
        cout << "\n";
    } else {
    cout << "Sorting by Bogosort:\n";
    for (int i = 0; i < size; i++)
        cout << " " << A[i];
    cout << "\n";
    }
}

void printArray(vector<int> A, int size, int variant)
{
    if (variant == 1) {
        cout << "Sorting by In-place merge sorting:\n";
        for (int i = 0; i < size; i++)
            cout << " " << A[i];
        cout << "\n";
    }
    else {
        cout << "Sorting by Bogosort:\n";
        for (int i = 0; i < size; i++)
            cout << " " << A[i];
        cout << "\n";
    }
}

int main()
{
    In_place_merge sort1;
    vector<int> beta = { 12, 11, 13, 5, 6, 7 };
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    sort1.mergeSort(arr, 0, arr_size - 1);
    sort1.mergeSort(beta, 0, beta.size() - 1);
    printArray(arr, arr_size, 1);
    printArray(beta, beta.size(), 1);
    Bogosort sort2;
    sort2.bogosort(arr, arr_size);
    sort2.bogosort(beta, beta.size());
    printArray(arr, arr_size, 2);
    printArray(beta, beta.size(), 2);
    return 0;
}