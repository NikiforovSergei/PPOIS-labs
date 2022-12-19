#include <iostream>
#include <vector>

using namespace std;

class ShellSort {
public:
	template <typename T>
	void shell(T& other, int count) {
		for (int step = count / 2; step > 0; step /= 2) {
			for (int i = step; i < count; i++) {
				int j = i;
				while (j >= step && other[j - step] > other[i]) {
					swap(other[j], other[j - step]);
					j -= step;
				}

			}
		}
	}
};


class RadixSort {
public:
	template <typename T>
	int getmax(T& other, int count) {
		int max = other[0];
		for (int i = 0; i < count; i++) {
			if (other[i] > max) {
				max = other[i];
			}
		}
		return max;
	}

	template <typename T>
	void countsort(T& other, int n, int exp) {
		int i;
		int* output = new int[n];
		int number[10] = { 0 };
		for (i = 0; i < n; i++) {
			number[(other[i] / exp) % 10]++;
		}
		for (i = 1; i < 10; i++) {
			number[i] += number[i - 1];
		}
		for (i = n - 1; i >= 0; i--) {
			output[number[(other[i] / exp) % 10] - 1] = other[i];
			number[(other[i] / exp) % 10]--;
		}
		for (i = 0; i < n; i++) {
			other[i] = output[i];
		}
	}

	template <typename T>
	void radix(T& other, int count) {
		int exp, m;
		m = getmax(other, count);
		for (exp = 1; m / exp > 0; exp *= 10) {
			countsort(other, count, exp);
		}
	}

};

void printArray(int A[], int size)
{
	for (int i = 0; i < size; i++) {
		cout << " " << A[i];
	}
	cout << endl;
}

void printVector(vector<int> A, int size)
{
	for (int i = 0; i < size; i++) {
		cout << " " << A[i];
	}
	cout << endl;
}

int main() {
	ShellSort sort1;
	vector<int> v = { 12, 1, 13, 52, 61, 7 };
	int arr[] = { 12, 1, 13, 52, 61, 7 };
	int size = 6;
	cout << "Shell:" << endl;
	sort1.shell(arr, size);
	cout << "Array: ";
	printArray(arr, size);
	sort1.shell(v, v.size());
	cout << "Vector: ";
	printVector(v, v.size());


	RadixSort sort2;
	cout << "LSD:" << endl;
	sort2.radix(arr, size);
	cout << "Array: ";
	printArray(arr, size);
	sort2.radix(v, v.size());
	cout << "Vector: ";
	printVector(v, v.size());
	return 0;
}
