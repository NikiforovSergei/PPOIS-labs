#include "StoogeSort.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

void StoogeSort::stoogesort(int arr[], int l, int h)
{
	if (l >= h)
		return;
	if (arr[l] > arr[h])
		swap(arr[l], arr[h]);
	if (h - l + 1 > 2) {
		int t = (h - l + 1) / 3;
		stoogesort(arr, l, h - t);
		stoogesort(arr, l + t, h);
		stoogesort(arr, l, h - t);
	}
}

void StoogeSort::stoogesort(char charr[], int l, int h)
{
	if (l >= h)
		return;
	if (charr[l] > charr[h])
		swap(charr[l], charr[h]);
	if (h - l + 1 > 2) {
		int t = (h - l + 1) / 3;
		stoogesort(charr, l, h - t);
		stoogesort(charr, l + t, h);
		stoogesort(charr, l, h - t);
	}
}

void StoogeSort::printArray(int arr[], int N)
{
	string out, space = " ";
	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";
	cout << out;
	printf("\n");
}
void StoogeSort::printArray(char charr[], int N)
{
	string out, space = " ";
	for (int i = 0; i < N; i++)
		cout << charr[i] << " ";
	cout << out;
	printf("\n");
}

void StoogeSort::inputCheck(int arr[], char charr[], int size) {
    cout << "Enter " << size << " elements\n";
	if (cin >> arr[0])
	{
		for (size_t i = 1; i < size; ++i)
			cin >> arr[i];
		stoogesort(arr, 0, size - 1);
		printArray(arr, size);
	}
	else {
		cin.clear();
		for (size_t i = 0; i < size; ++i)
			cin >> charr[i];
		stoogesort(charr, 0, size - 1);
		printArray(charr, size);
	}
}