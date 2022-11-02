#include "HeapSort.h"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
template <class Type>
void HeapSort::swap(Type* a, Type* b){
  int temp = *a;
  *a = *b;
  *b = temp;
}
void HeapSort::heapify(int arr[], int N, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < N && arr[left] > arr[largest])
		largest = left;
	if (right < N && arr[right] > arr[largest])
		largest = right;
	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, N, largest);
	}
}
void HeapSort::heapify(char arr[], int N, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < N && arr[left] > arr[largest])
		largest = left;
	if (right < N && arr[right] > arr[largest])
		largest = right;
	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, N, largest);
	}
}
void HeapSort::heapSort(int arr[], int N)
{
	for (int i = N / 2 - 1; i >= 0; i--)
		heapify(arr, N, i);
	for (int i = N - 1; i >= 0; i--) {
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}
void HeapSort::heapSort(char arr[], int N)
{
	for (int i = N / 2 - 1; i >= 0; i--)
		heapify(arr, N, i);
	for (int i = N - 1; i >= 0; i--) {
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}
void HeapSort::printArray(int arr[], int N)
{
	string out, space = " ";
	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";
	cout << out;
	printf("\n");
}
void HeapSort::printArray(char arr[], int N)
{
	string out, space = " ";
	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";
	cout << out;
	printf("\n");
}
void HeapSort::inputCheck(int arr[],char charr[],int size) {
	if (cin >> arr[0])
	{
		for (size_t i = 1; i < size; ++i)
			cin >> arr[i];
		heapSort(arr, size);
		printf("Sorted array is\n");
		printArray(arr, size);
	}
	else {
		cin.clear();
		for (size_t i = 0; i < size; ++i)
			cin >> charr[i];
		heapSort(charr, size);
		printf("Sorted array is\n");
		printArray(charr, size);
	}
}