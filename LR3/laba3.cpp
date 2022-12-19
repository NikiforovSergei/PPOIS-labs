

#include<vector>
#include <iostream>
using namespace std;
template <typename T>
class PatienceSorting {
public:
	vector<T> Vector(T* A, int size) {
		vector<T> b;
		for (int i = 0; i < size; i++)
		{
			b.push_back(A[i]);
		}
		return b;
	}
vector<T> merge_piles(vector<vector<T> >& v)
{
	vector <T> ans;
	while (1) {
	
		T minu = v[0][v[0].size() - 1];
		int index = 0;
		for (int i = 0; i < v.size(); i++) {
			if (minu > v[i][v[i].size() - 1]) {
				minu = v[i][v[i].size() - 1];
				index = i;
			}
		}
		ans.push_back(minu);
		v[index].pop_back();
		if (v[index].empty()) {
			v.erase(v.begin() + index);
		}
		if (v.size() == 0)
			break;
	}
	return ans;
}

vector<T> patienceSorting(vector<T> arr)
{


	vector<vector<T> > piles;

	for (int i = 0; i < arr.size(); i++) {
		if (piles.empty()) {
			vector<T> temp;
			temp.push_back(arr[i]);
			piles.push_back(temp);
		}
		else {
			int flag = 1;
			for (int j = 0; j < piles.size(); j++) {
				if (arr[i] < piles[j][piles[j].size() - 1]) {
					piles[j].push_back(arr[i]);
					flag = 0;
					break;
				}
			}
			if (flag) {
				vector<T> temp;
				temp.push_back(arr[i]);
				piles.push_back(temp);
			}
		}
	}
	arr = merge_piles(piles);
	return arr;
}
  
};

template <typename T>
class BubbleSorting {
public:
	vector<T> Vector(T* A, int size) {
		vector<T> b;
		for (int i = 0; i < size; i++)
		{
			b.push_back(A[i]);
		}
		return b;
	}
	vector<T> Bubble_Sort(vector<T> array) {
		for (int step = 0; step <array.size(); ++step) {
			for (int i = 0; i <array.size()-1; ++i) {
				if (array[i] > array[i + 1]) {
					T temp = array[i];
					array[i] = array[i + 1];
					array[i + 1] = temp;
				}
			}
		}
		return array;
	}
};


void print(vector<int> A, int variant)
{
	if (variant == 1) {
		cout << "Sorting by Patience Sorting:\n";
		for (int i = 0; i < A.size(); i++)
			cout << " " << A[i];
		cout << "\n";
	}
	else {
		cout << "Sorting by Bubble Sort:\n";
		for (int i = 0; i < A.size(); i++)
			cout << " " << A[i];
		cout << "\n";
	}
}

int main()
{
	PatienceSorting<int> Patience_Sort;
	BubbleSorting<int> Bubble_Sort;

	vector<int> beta = { 40, 56, 23, 5, 79, 45, 53, 52, 78, 91, 13 };
	int arr[] = {123, 1, 3, 52, 88, 23, 36, 12, 98};

	int arr_size = sizeof(arr) / sizeof(arr[0]);
	
	
	print(Patience_Sort.patienceSorting(Patience_Sort.Vector(arr, arr_size)), 1);
	print(Patience_Sort.patienceSorting(beta), 1);


	print(Bubble_Sort.Bubble_Sort(Bubble_Sort.Vector(arr, arr_size)),2);
	print(Bubble_Sort.Bubble_Sort(beta), 2);
	return 0;
}