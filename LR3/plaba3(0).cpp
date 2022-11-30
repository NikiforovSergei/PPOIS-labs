#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
#include <algorithm>
using namespace std;

class MyObj 
{
public:
	int key;
	MyObj(int key)
	{
		this->key = key;
	}
	friend bool operator < (const MyObj a, const MyObj b)
	{
		return a.key < b.key;
	}
	friend bool operator > (const MyObj a, const MyObj b)
	{
		return a.key > b.key;
	}
	friend bool operator == (const MyObj a, const MyObj b)
	{
		return a.key == b.key;
	}
};

template <typename T>
void heapify(T* arr, int n, int i)
{
	int largest = i;
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i) {
		swap(arr[i], arr[largest]);

		heapify(arr, n, largest);
	}
}

template <typename T>
void heapify(vector<T>& arr, int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i) {
		swap(arr[i], arr[largest]);

		heapify(arr, n, largest);
	}
}

template <typename T>
void heapsort(T* arr, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}

	for (int i = n - 1; i >= 0; i--) 
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

template <typename T>
void heapsort(vector<T>& arr, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}

	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

template <typename T>
void stoogesort(T* set, int start, int end)
{
	int i;
	if (end - start > 1)
	{
		i = (end - start + 1) / 3;
		stoogesort(set, start, end - i);
		stoogesort(set, start + i, end);
		stoogesort(set, start, end - i);
	}

	if (set[end] < set[start])
	{
		swap(set[end], set[start]);
	}
}

template <typename T>
void stoogesort(vector<T>& set, int start, int end)
{
	int i;
	if (end - start > 1)
	{
		i = (end - start + 1) / 3;
		stoogesort(set, start, end - i);
		stoogesort(set, start + i, end);
		stoogesort(set, start, end - i);
	}

	if (set[end] < set[start])
	{
		swap(set[end], set[start]);
	}
}


int main()
{
	int* arr1 = new int[8]{ 1, 3, 9, 2, 5, 4, 7, 6 };
	heapsort<int>(arr1, 8);
	cout << "heapsort with array: " << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << arr1[i] << ' ';
	}

	vector<string> arr2 = { "b", "f", "k", "a", "d", "g", "e", "m" };
	heapsort<string>(arr2, 8);
	cout << endl << "heapsort with vecttor: " << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << arr2[i] << ' ';
	}


	cout << endl << "stoogesort with arr: " << endl;
	string* arr3 = new string[8]{ "b", "f", "a", "d", "e", "m", "v", "t"};
	stoogesort<string>(arr3, 0, 7);
	for (int i = 0; i < 8; i++)
	{
		cout << arr3[i] << ' ';
	}


	cout << endl << "stoogesort with vector: " << endl;
	vector<int> arr4 = { 6, 9, 3, 2, 5, 4, 1, 8 };
	stoogesort<int>(arr4, 0, 7);
	for (int i = 0; i < 8; i++)
	{
		cout << arr4[i] << ' ';
	}


	cout << endl << "stoogesort vector with objects:\n";
	vector<MyObj> my_obj = {MyObj(1), MyObj(6), MyObj(3), MyObj(7), MyObj(2), MyObj(5), MyObj(4)}; 
	stoogesort<MyObj>(my_obj, 0, 6);
	for (int i = 0; i < 7; i++)
	{
		cout << my_obj[i].key << ' ';
	}


	cout << endl << "heapsort vector with objects:\n";
	vector<MyObj> my_obj2 = {MyObj(1), MyObj(6), MyObj(3), MyObj(7), MyObj(2), MyObj(5), MyObj(4)};
	heapsort<MyObj>(my_obj2, 7);
	for (int i = 0; i < 7; i++)
	{
		cout << my_obj2[i].key << ' ';
	}
}
