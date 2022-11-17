#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>

#include <cstdlib>

using namespace std;


class MyObj //класс для проверки 
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
void selectionSort(T* arr, int size)			//сортировка выбором для массивов
{
	for (int i = 0; i < size - 1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}
		if (min_index != i)
		{
			swap(arr[i], arr[min_index]);
		}
	}
}


template <typename T>
void selectionSort(vector<T>& arr, int size)			//сортировка выбором для векторов
{
	for (int i = 0; i < size - 1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}
		if (min_index != i)
		{
			swap(arr[i], arr[min_index]);
		}
	}
}


template <typename T>
void ReverseSelectionSort(T* arr, int size)			//сортировка выбором от большего к меньшему для массивов
{
	for (int i = 0; i < size - 1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] > arr[min_index])
			{
				min_index = j;
			}
		}
		if (min_index != i)
		{
			swap(arr[i], arr[min_index]);
		}
	}
}


template <typename T>
void ReverseSelectionSort(vector<T>& arr, int size)			//сортировка выбором от большего к меньшему для векторов
{
	for (int i = 0; i < size - 1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] > arr[min_index])
			{
				min_index = j;
			}
		}
		if (min_index != i)
		{
			swap(arr[i], arr[min_index]);
		}
	}
}


template <typename T>
void bucketSort(T* arr, int n)				//блочная сортировка для векторов
{// 1) Создаём n пустых корзин 
	vector<T>* b = new vector<T>[n];
	int b_index; //отвечает за индекс (номер) корзины
	// 2) Раскладываем элементы массива по соответствующим корзинам
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b_index = 0;
			if (j != n - 1) {
				if (arr[i] > 1 + j && arr[i] < 1 + (j + 1)) {
					b_index = j;
				}
			}
			else {
				if (arr[i] > 1 + (j + 1))
					b_index = n - 1;
			}
		}
		// push_back() используется для добавления нового элемента в конец вектора
		b[b_index].push_back(arr[i]);
	}

	// 3) Сортируем отдельные корзины любой сортировкой
	for (int i = 0; i < n; i++)
		//функция sort: её принцип работы построен на алгоритме быстрой сортировки 
		sort(b[i].begin(), b[i].end());

	// 4) Соединяем отсортированные корзины в единый окончательный массив
	int index = 0; //отвечает за индекс элементов массива
	for (int i = 0; i < n; i++)
		// size() определяет текущий размер вектора
		for (int j = 0; j < b[i].size(); j++)
			arr[index++] = b[i][j];
	delete[] b;
}


template <typename T>
void ReverseBucketSort(T* arr, int n)			//блочная сортировка от большего к меньшему для массивов
{// 1) Создаём n пустых корзин 
	vector<T>* b = new vector<T>[n];
	int b_index; //отвечает за индекс (номер) корзины
	// 2) Раскладываем элементы массива по соответствующим корзинам
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b_index = 0;
			if (j != n - 1) {
				if (arr[i] > 1 + j && arr[i] < 1 + (j + 1)) {
					b_index = j;
				}
			}
			else {
				if (arr[i] > 1 + (j + 1))
					b_index = n - 1;
			}
		}
		// push_back() используется для добавления нового элемента в конец вектора
		b[b_index].push_back(arr[i]);
	}

	// 3) Сортируем отдельные корзины любой сортировкой
	for (int i = 0; i < n; i++)
		//функция sort: её принцип работы построен на алгоритме быстрой сортировки 
		sort(b[i].begin(), b[i].end(), greater<>());

	// 4) Соединяем отсортированные корзины в единый окончательный массив
	int index = 0; //отвечает за индекс элементов массива
	for (int i = 0; i < n; i++)
		// size() определяет текущий размер вектора
		for (int j = 0; j < b[i].size(); j++)
			arr[index++] = b[i][j];
	delete[] b;
}


template <typename T>
void bucketSort(vector<T>& arr, int n)				//блочная сортировка для векторов
{// 1) Создаём n пустых корзин 
	vector<T>* b = new vector<T>[n];
	int b_index; //отвечает за индекс (номер) корзины
	// 2) Раскладываем элементы массива по соответствующим корзинам
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b_index = 0;
			if (j != n - 1) {
				if (arr[i] > 1 + j && arr[i] < 1 + (j + 1)) {
					b_index = j;
				}
			}
			else {
				if (arr[i] > 1 + (j + 1))
					b_index = n - 1;
			}
		}
		// push_back() используется для добавления нового элемента в конец вектора
		b[b_index].push_back(arr[i]);
	}

	// 3) Сортируем отдельные корзины любой сортировкой
	for (int i = 0; i < n; i++)
		//функция sort: её принцип работы построен на алгоритме быстрой сортировки 
		sort(b[i].begin(), b[i].end());

	// 4) Соединяем отсортированные корзины в единый окончательный массив
	int index = 0; //отвечает за индекс элементов массива
	for (int i = 0; i < n; i++)
		// size() определяет текущий размер вектора
		for (int j = 0; j < b[i].size(); j++)
			arr[index++] = b[i][j];
	delete[] b;
}


template <typename T>
void ReverseBucketSort(vector<T>& arr, int n)				//блочная сортировка от большего к меньшему для векторов
{// 1) Создаём n пустых корзин 
	vector<T>* b = new vector<T>[n];
	int b_index; //отвечает за индекс (номер) корзины
	// 2) Раскладываем элементы массива по соответствующим корзинам
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b_index = 0;
			if (j != n - 1) {
				if (arr[i] > 1 + j && arr[i] < 1 + (j + 1)) {
					b_index = j;
				}
			}
			else {
				if (arr[i] > 1 + (j + 1))
					b_index = n - 1;
			}
		}
		// push_back() используется для добавления нового элемента в конец вектора
		b[b_index].push_back(arr[i]);
	}

	// 3) Сортируем отдельные корзины любой сортировкой
	for (int i = 0; i < n; i++)
		//функция sort: её принцип работы построен на алгоритме быстрой сортировки 
		sort(b[i].begin(), b[i].end(), greater<>());

	// 4) Соединяем отсортированные корзины в единый окончательный массив
	int index = 0; //отвечает за индекс элементов массива
	for (int i = 0; i < n; i++)
		// size() определяет текущий размер вектора
		for (int j = 0; j < b[i].size(); j++)
			arr[index++] = b[i][j];
	delete[] b;
}

int main()
{
	int choise;
	srand(time(NULL));
	cout << "How do you want to sort?\n" << "1 - Smallest to Biggest\n" << "2 - Biggest to Smallest" << endl;
	cin >> choise;
	switch (choise) {
		case 1: {
			system("cls");
			int* array = new int[7]{};
			vector<int> arr;

			for (int i = 0; i < 7; i++)
			{
				array[i] = rand() % 100;
			}

			cout << "Start array: ";
			for (int i = 0; i < 7; i++)
			{
				cout << array[i] << ' ';
			}

			for (int i = 0; i < 7; i++)
			{
				int help = (rand() % 100);
				arr.push_back(help);
			}

			cout << endl << "\nStart vector: ";
			for (int i = 0; i < 7; i++)
			{
				cout << arr[i] << ' ';
			}
			
			

			cout << endl << "\nSelection sort with arr: ";
			selectionSort<int>(array, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << array[i] << ' ';
			}


			cout << endl << "\nSelection sort with vector: ";
			selectionSort<int>(arr, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << arr[i] << ' ';
			}


			cout << endl << "\nSelection sort vector with objects: ";
			vector<MyObj> my_obj = { MyObj(2), MyObj(1), MyObj(4), MyObj(3), MyObj(5), MyObj(7), MyObj(6) };
			selectionSort<MyObj>(my_obj, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << my_obj[i].key << ' ';
			}

			int* array2 = new int[7]{};
			vector<int> vector2;

			for (int i = 0; i < 7; i++)
			{
				array2[i] = rand() % 100;
			}

			cout << endl << "\n\n\n\n\nStart array: ";
			for (int i = 0; i < 7; i++)
			{
				cout << array2[i] << ' ';
			}

			for (int i = 0; i < 7; i++)
			{
				int help = (rand() % 100);
				vector2.push_back(help);
			}

			cout << endl << "\nStart vector: ";
			for (int i = 0; i < 7; i++)
			{
				cout << vector2[i] << ' ';
			}
			cout << endl << "\nBucket sort with arr: ";
			bucketSort(array2, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << array2[i] << ' ';
			}

			cout << endl << "\nBucket sort with vector: ";
			bucketSort(vector2, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << vector2[i] << ' ';
			}

			cout << endl << "\nBucket sort vector with objects: ";
			vector<MyObj> my_obj2 = { MyObj(12), MyObj(11), MyObj(22), MyObj(21), MyObj(41), MyObj(32), MyObj(31) };
			bucketSort<MyObj>(my_obj2, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << my_obj2[i].key << ' ';
			}

			cout << "\n\n\n\n\n\n";
			break;
		}

		case 2: {
			system("cls");
			vector<int> arr = { 18, 34, 92, 35, 48, 97, 26 };
			int* array = new int[7]{ 13, 37, 21, 57, 43, 75, 69 };

			cout << "\nStart arr: ";
			for (int i = 0; i < 7; i++)
			{
				cout << array[i] << ' ';
			}

			cout << endl << "\nStart vector: ";
			for (int i = 0; i < 7; i++)
			{
				cout << arr[i] << ' ';
			}

			cout << "\nReverse selection sort with arr: ";
			ReverseSelectionSort<int>(array, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << array[i] << ' ';
			}


			cout << endl << "\nReverse selection sort with vector: ";
			ReverseSelectionSort<int>(arr, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << arr[i] << ' ';
			}

			cout << endl << "\nReverse selection sort vector with objects: ";
			vector<MyObj> my_obj_reverse = { MyObj(2), MyObj(1), MyObj(4), MyObj(3), MyObj(5), MyObj(7), MyObj(6) };
			ReverseSelectionSort<MyObj>(my_obj_reverse, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << my_obj_reverse[i].key << ' ';
			}

			

			int* arr2_reverse = new int[7]{ 56, 32, 65, 59, 31, 93, 78 };
			vector<int> arr_reverse = { 71, 22, 56, 17, 11, 98, 15 };

			cout << endl << "\nStart arr: ";
			for (int i = 0; i < 7; i++)
			{
				cout << arr2_reverse[i] << ' ';
			}

			cout << endl << "\nStart vector: ";
			for (int i = 0; i < 7; i++)
			{
				cout << arr_reverse[i] << ' ';
			}
			cout << endl << "\nReverse bucket sort with arr: ";
			ReverseBucketSort(arr2_reverse, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << arr2_reverse[i] << ' ';
			}

			cout << endl << "\nReverse bucket sort with vector: ";
			ReverseBucketSort(arr_reverse, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << arr_reverse[i] << ' ';
			}

			cout << endl << "\nReverse bucket sort vector with objects: ";
			vector<MyObj> my_obj2_reverse = { MyObj(12), MyObj(11), MyObj(22), MyObj(21), MyObj(41), MyObj(32), MyObj(31) };
			ReverseBucketSort<MyObj>(my_obj2_reverse, 7);
			for (int i = 0; i < 7; i++)
			{
				cout << my_obj2_reverse[i].key << ' ';
			}
			cout << "\n\n\n\n\n\n";
			break;
		}
		}
}