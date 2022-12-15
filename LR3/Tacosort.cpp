#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
class Taco {
public:
	int s;
};
template <typename T>
bool check(T* k, vector<T>& vec,int n, int l) {
	bool flag = false;
	if (l == 2) {
		for (int j = 1; j < n; j++) {
			if (k[j].s >= k[j - 1].s) {
				flag = true;
			}
			else {
				flag = false;
				return flag;
			}
		}
	}else{
		for (int j = 1; j < n; j++) {
			if (vec[j].s >= vec[j - 1].s) {
				flag = true;
			}
			else {
				flag = false;
				return flag;
			}
		}
	}
	return flag;
}
template <typename T>
void tacosort(T* k, vector<T>& vec, int n, int l) {
	while (true) {
		if (l == 2) {
			swap(k[rand() % n].s, k[rand() % n].s);
			if (check(k, vec, n,l)) {
				//return *k;
				break;
			}
		}
		else {
			swap(vec[rand() % n].s, vec[rand() % n].s);
			if (check(k,vec, n,l)) {
				//return vec;
				break;
			}
		}
	}
}

static int Partition(Taco* data, int left, int right) {
	int pivot = data[right].s;
	int temp;
	int i = left;

	for (int j = left; j < right; ++j)
	{
		if (data[j].s <= pivot)
		{
			temp = data[j].s;
			data[j].s = data[i].s;
			data[i].s = temp;
			i++;
		}
	}

	data[right].s = data[i].s;
	data[i].s = pivot;

	return i;
}

static int Partition_vec(vector<Taco>& data, int left, int right) {
	int pivot = data[right].s;
	int temp;
	int i = left;

	for (int j = left; j < right; ++j)
	{
		if (data[j].s <= pivot)
		{
			temp = data[j].s;
			data[j].s = data[i].s;
			data[i].s = temp;
			i++;
		}
	}

	data[right].s = data[i].s;
	data[i].s = pivot;

	return i;
}

static void QuickSortRecursive(Taco* data, int left, int right) {
	if (left < right)
	{
		int q = Partition(data, left, right);
		QuickSortRecursive(data, left, q - 1);
		QuickSortRecursive(data, q + 1, right);
	}
}

static void QuickSortRecursive_vec(vector<Taco>& data, int left, int right) {
	if (left < right)
	{
		int q = Partition_vec(data, left, right);
		QuickSortRecursive_vec(data, left, q - 1);
		QuickSortRecursive_vec(data, q + 1, right);
	}
}

static void MaxHeapify(Taco* data, int heapSize, int index) {
	int left = (index + 1) * 2 - 1;
	int right = (index + 1) * 2;
	int largest = 0;

	if (left < heapSize && data[left].s > data[index].s)
		largest = left;
	else
		largest = index;

	if (right < heapSize && data[right].s > data[largest].s)
		largest = right;

	if (largest != index)
	{
		int temp = data[index].s;
		data[index].s = data[largest].s;
		data[largest].s = temp;

		MaxHeapify(data, heapSize, largest);
	}
}

static void MaxHeapify_vec(vector<Taco>& data, int heapSize, int index) {
	int left = (index + 1) * 2 - 1;
	int right = (index + 1) * 2;
	int largest = 0;

	if (left < heapSize && data[left].s > data[index].s)
		largest = left;
	else
		largest = index;

	if (right < heapSize && data[right].s > data[largest].s)
		largest = right;

	if (largest != index)
	{
		int temp = data[index].s;
		data[index].s = data[largest].s;
		data[largest].s = temp;

		MaxHeapify_vec(data, heapSize, largest);
	}
}

static void HeapSort(Taco* data, int count) {
	int heapSize = count;

	for (int p = (heapSize - 1) / 2; p >= 0; --p)
		MaxHeapify(data, heapSize, p);

	for (int i = count - 1; i > 0; --i)
	{
		int temp = data[i].s;
		data[i].s = data[0].s;
		data[0].s = temp;

		--heapSize;
		MaxHeapify(data, heapSize, 0);
	}
}

static void HeapSort_vec(vector<Taco>& data, int count) {
	int heapSize = count;

	for (int p = (heapSize - 1) / 2; p >= 0; --p)
		MaxHeapify_vec(data, heapSize, p);

	for (int i = count - 1; i > 0; --i)
	{
		int temp = data[i].s;
		data[i].s = data[0].s;
		data[0].s = temp;

		--heapSize;
		MaxHeapify_vec(data, heapSize, 0);
	}
}

static void InsertionSort(Taco* data, int count) {
	for (int i = 1; i < count; ++i)
	{
		int j = i;

		while ((j > 0))
		{
			if (data[j - 1].s > data[j].s)
			{
				//data[j - 1].s = pow(data[j - 1].s, data[j].s);
				//data[j].s = pow(data[j].s, data[j - 1].s);
				//data[j - 1].s = pow(data[j - 1].s, data[j].s);
				data[j - 1].s ^= data[j].s;
				data[j].s ^= data[j - 1].s;
				data[j - 1].s ^= data[j].s;
				--j;
			}
			else
			{
				break;
			}
		}
	}
}

static void InsertionSort_vec(vector<Taco>& data, int count) {
	for (int i = 1; i < count; ++i)
	{
		int j = i;

		while ((j > 0))
		{
			if (data[j - 1].s > data[j].s)
			{
				//data[j - 1].s = pow(data[j - 1].s, data[j].s);
				//data[j].s = pow(data[j].s, data[j - 1].s);
				//data[j - 1].s = pow(data[j - 1].s, data[j].s);
				data[j - 1].s ^= data[j].s;
				data[j].s ^= data[j - 1].s;
				data[j - 1].s ^= data[j].s;
				--j;
			}
			else
			{
				break;
			}
		}
	}
}

static void IntroSort(Taco* data, int count) {
	int partitionSize = Partition(data, 0, count - 1);

	if (partitionSize < 16)
	{
		InsertionSort(data, count);
	}
	else if (partitionSize > (2 * log(count)))
	{
		HeapSort(data, count);
	}
	else
	{
		QuickSortRecursive(data, 0, count - 1);
	}
}

static void IntroSort_vec(vector<Taco>& data, int count) {
	int partitionSize = Partition_vec(data, 0, count - 1);

	if (partitionSize < 16)
	{
		InsertionSort_vec(data, count);
	}
	else if (partitionSize > (2 * log(count)))
	{
		HeapSort_vec(data, count);
	}
	else
	{
		QuickSortRecursive_vec(data, 0, count - 1);
	}
}


int main()
{
	int n;
	cout << "Input amount elements in array or vector: " << endl;
	do {
		cin >> n;
		cout << endl;
		if (n < 0 || n>32767) {
			cout << "Input correct answer!!!";
		}
	} while (n < 0 || n>32767);
	Taco* k = new Taco[n];
	vector<Taco> vec;
	Taco g;
	int l;
	int a;
	cout << "What to sort: 1 - vector, 2 - array" << endl;
	do {
		cin >> l;
		switch (l) {
		case 1:
			cout << "1 - Random, 2 - Arms" << endl;
			cin >> a;
			if (a == 2) {
				for (int i = 0; i < n; i++) {
					cin >> g.s;
					vec.push_back(g);
				}
			}
			else {
				for (int i = 0; i < n; i++) {
					g.s = rand() % 100;
					vec.push_back(g);
				}
				for (int i = 0; i < n; i++) {
					cout << vec[i].s << " ";
				}
			}
			cout << endl;
			break;
		case 2:
			cout << "1 - Random, 2 - Arms" << endl;
			cin >> a;
			if (a == 2) {
				for (int i = 0; i < n; i++) {
					cin >> k[i].s;
				}
			}
			else {
				for (int i = 0; i < n; i++) {
					k[i].s = rand()%100;
				}
				for (int i = 0; i < n; i++) {
					cout << k[i].s << " ";
				}
			}
			cout << endl;
			break;
		default: cout << "Input correct answer!!!" << endl;
		}
	} while (l < 1 || l>2);
	int h;
	cout << "What sort will be used: 1 - Introsort, 2 - Tacosort" << endl;
	do{
		cin >> h;
		switch (h) {
		case 1:
			if (l == 1) {
				IntroSort_vec(vec, n);
				cout << "Sorted vector: " << endl;
				for (int i = 0; i < n; i++) {
					cout << vec[i].s << " ";
				}
				cout << endl;
				break;
			} 
			else {
				IntroSort(k, n);
				cout << "Sorted array: " << endl;
				for (int i = 0; i < n; i++) {
					cout << k[i].s << " ";
				}
				cout << endl;
				break;
			}
		case 2:
			if (l == 1) {
				tacosort(k,vec, n,l);
				cout << "Sorted vector: " << endl;
				for (int i = 0; i < n; i++) {
					cout << vec[i].s << " ";
				}
				cout << endl;
				break;
			}
			else {
				tacosort(k,vec, n,l);
				cout << "Sorted array: " << endl;
				for (int i = 0; i < n; i++) {
					cout << k[i].s << " ";
				}
				cout << endl;
				break;
			}
		default: cout << "Input correct answer!!!" << endl;
		}
	} while (h < 1 || h > 2);
}
