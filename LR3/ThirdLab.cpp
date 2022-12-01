#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;


class object {
public:
	int a;

	object() {
		a = 0;
	}

	object(int a) {
		this->a = a;
	}

	void print() {
		cout << a << "\t";
	}

	bool operator >=(object other)
	{
		return this->a >= other.a;
	}

	bool operator <=(object other)
	{
		return this->a <= other.a;
	}

	bool operator >(object other)
	{
		return this->a > other.a;
	}

	bool operator <(object other)
	{
		return this->a < other.a;
	}

	friend ostream& operator <<(ostream& os, object obj)
	{
		os << obj.a;
		return os;
	}

};



template <typename T>
void bubble_sort_1(T* arr, vector<T>& vec, int size) {
	T temp;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
			}
		}
	}
}

template <typename T>
void bubble_sort_2(T* arr, vector<T>& vec, int size) {
	T temp;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (arr[j] < arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
			}
		}
	}
}

template <typename T>
void menu1(int size, T*& arr, vector<T> vec) {
	bool k = true;
	int n;
	while (k == true) {

		cout << "Выберете:\n" << "1. Сортировка по возрастанию\n" << "2. Сортировка по убыванию\n" << "3. Выход\n";
		cin >> n;
		switch (n) {

		case 1:

			system("cls");
			cout << "Выберете:\n" << "1. Массив\n" << "2. Вектор\n" << "3. Выход\n";
			cin >> n;
			switch (n) {

			case 1:

				system("cls");
				bubble_sort_1(arr, vec, size);
				for (int i = 0; i < size; i++) {
					cout << arr[i] << "\t";
				}
				cout << endl;
				break;

			case 2:

				system("cls");
				bubble_sort_1(arr, vec, size);
				for (int i = 0; i < size; i++) {
					cout << vec[i] << "\t";
				}
				cout << endl;
				break;

			case 3:

				system("cls");
				k = false;
				break;

			default:

				system("cls");
				cout << "Введите цифры от 1 до 3 !!!" << endl;
				break;
			}
			break;

		case 2:

			system("cls");
			cout << "Выберете:\n" << "1. Массив\n" << "2. Вектор\n" << "3. Выход\n";
			cin >> n;
			switch (n) {

			case 1:

				system("cls");
				bubble_sort_2(arr, vec, size);
				for (int i = 0; i < size; i++) {
					cout << arr[i] << '\t';
				}
				cout << endl;
				break;

			case 2:

				system("cls");
				bubble_sort_2(arr, vec, size);
				for (int i = 0; i < size; i++) {
					cout << vec[i] << '\t';
				}
				cout << endl;
				break;

			case 3:

				system("cls");
				k = false;
				break;

			default:

				system("cls");
				cout << "Введите цифры от 1 до 3 !!!" << endl;
				break;
			}
			break;

		case 3:

			system("cls");
			k = false;
			break;

		default:

			system("cls");
			cout << "Введите цифры от 1 до 3 !!!" << endl;
			break;

		}

	}

}



template<typename T>
void patience_sort_1(T* arr, vector<T>& vec) {
	vector<stack<T>> healper;
	vector<stack<T>> sorting_plate;
	for (const auto& item : vec)
	{
		sorting_plate.push_back(stack<T>());
		healper.push_back(stack<T>());

		for (auto& heap : sorting_plate)
		{
			if (heap.empty() || (!heap.empty() && heap.top() >= item))
			{
				heap.push(item);
				break;
			}
		}

		for (auto& heap : healper)
		{
			if (heap.empty() || (!heap.empty() && heap.top() >= item))
			{
				heap.push(item);
				break;
			}
		}
	}

	cout << "Вывод пасьянса:" << endl;
	int sp_s = healper.size();
	for (size_t i = 0; i < sp_s; i++) {
		int spi_s = healper[i].size();
		for (size_t j = 0; j < spi_s; j++) {
			cout << healper[i].top() << " ";
			healper[i].pop();
		}
		if (spi_s != 0) {
			cout << endl;
		}
	}
	cout << endl;

	for (size_t i = 0; i < vec.size(); ++i)
	{
		T local_min = sorting_plate[0].top();
		int32_t heap_index = -1;

		for (size_t h = 0; h < sorting_plate.size(); ++h)
		{
			if (sorting_plate[h].empty())
			{
				break;
			}
			else if (heap_index == -1 || (heap_index != -1 && sorting_plate[h].top() < local_min))
			{
				local_min = sorting_plate[h].top();
				heap_index = h;
			}
		}

		vec[i] = local_min;
		arr[i] = local_min;
		sorting_plate[heap_index].pop();

		if (sorting_plate[heap_index].empty())
		{
			sorting_plate.erase(sorting_plate.begin() + heap_index);
		}
	}
}

template<typename T>
void patience_sort_2(T* arr, vector<T>& vec) {
	vector<stack<T>> healper;
	vector<stack<T>> sorting_plate;
	for (const auto& item : vec)
	{
		sorting_plate.push_back(stack<T>());
		healper.push_back(stack<T>());

		for (auto& heap : sorting_plate)
		{
			if (heap.empty() || (!heap.empty() && heap.top() <= item))
			{
				heap.push(item);
				break;
			}
		}

		for (auto& heap : healper)
		{
			if (heap.empty() || (!heap.empty() && heap.top() <= item))
			{
				heap.push(item);
				break;
			}
		}
	}

	cout << "Вывод пасьянса:" << endl;
	int sp_s = healper.size();
	for (size_t i = 0; i < sp_s; i++) {
		int spi_s = healper[i].size();
		for (size_t j = 0; j < spi_s; j++) {
			cout << healper[i].top() << " ";
			healper[i].pop();
		}
		if (spi_s != 0) {
			cout << endl;
		}
	}
	cout << endl;


	for (size_t i = 0; i < vec.size(); ++i)
	{
		T local_max = sorting_plate[0].top();
		int32_t heap_index = -1;

		for (size_t h = 0; h < sorting_plate.size(); ++h)
		{
			if (sorting_plate[h].empty())
			{
				break;
			}
			else if (heap_index == -1 || (heap_index != -1 && sorting_plate[h].top() > local_max))
			{
				local_max = sorting_plate[h].top();
				heap_index = h;
			}
		}

		vec[i] = local_max;
		arr[i] = local_max;
		sorting_plate[heap_index].pop();

		if (sorting_plate[heap_index].empty())
		{
			sorting_plate.erase(sorting_plate.begin() + heap_index);
		}
	}
}

template <typename T>
void menu2(int size, T*& arr, vector<T> vec) {
	bool k = true;
	int n;
	while (k == true) {

		cout << "Выберете:\n" << "1. Сортировка по возрастанию\n" << "2. Сортировка по убыванию\n" << "3. Выход\n";
		cin >> n;
		switch (n) {

		case 1:

			system("cls");
			cout << "Выберете:\n" << "1. Массив\n" << "2. Вектор\n" << "3. Выход\n";
			cin >> n;
			switch (n) {

			case 1:

				system("cls");
				patience_sort_1(arr, vec);
				for (int i = 0; i < size; i++) {
					cout << arr[i] << "\t";
				}
				cout << endl;
				break;

			case 2:

				system("cls");
				patience_sort_1(arr, vec);
				for (int i = 0; i < size; i++) {
					cout << vec[i] << "\t";
				}
				cout << endl;
				break;

			case 3:

				system("cls");
				k = false;
				break;

			default:

				system("cls");
				cout << "Введите цифры от 1 до 3 !!!" << endl;
				break;
			}
			break;

		case 2:

			system("cls");
			cout << "Выберете:\n" << "1. Массив\n" << "2. Вектор\n" << "3. Выход\n";
			cin >> n;
			switch (n) {

			case 1:

				system("cls");
				patience_sort_2(arr, vec);
				for (int i = 0; i < size; i++) {
					cout << arr[i] << '\t';
				}
				cout << endl;
				break;

			case 2:

				system("cls");
				patience_sort_2(arr, vec);
				for (int i = 0; i < size; i++) {
					cout << vec[i] << '\t';
				}
				cout << endl;
				break;

			case 3:

				system("cls");
				k = false;
				break;

			default:

				system("cls");
				cout << "Введите цифры от 1 до 3 !!!" << endl;
				break;
			}
			break;

		case 3:

			system("cls");
			k = false;
			break;

		default:

			system("cls");
			cout << "Введите цифры от 1 до 3 !!!" << endl;
			break;

		}

	}

}



int main() {
	setlocale(LC_ALL, "ru");

	while (1) {
		int size;
		cout << "size = ";
		cin >> size;
		string str;
		int n;
		cout << "1 - Сортировка пузырьком" << endl << "2 - Терпеливая сортировка" << endl;
		cin >> n;
		switch (n) {

		case 1:

			cout << "Введите тип данных:" << endl;
			cin >> str;

			if (str == "int") {
				int* arr = new int[size];
				vector<int> vec;
				vec.resize(size);

				system("cls");
				cout << "Введите элементы массива/вектора:" << endl;
				for (int i = 0; i < size; i++) {
					int val = 0;
					cin >> val;
					arr[i] = val;
					vec[i] = val;
				}
				menu1(size, arr, vec);
				for (int i = 0; i < size; i++) {
					cout << vec[i] << "\t";
				}
				cout << endl;
				break;
			}



			if (str == "float") {
				float* arr = new float[size];
				vector<float> vec;
				vec.resize(size);

				system("cls");
				cout << "Введите элементы массива:" << endl;
				for (int i = 0; i < size; i++) {
					float val = 0;
					cin >> val;
					arr[i] = val;
					vec[i] = val;
				}
				menu1(size, arr, vec);
				break;
			}



			if (str == "char") {
				char* arr = new char[size];
				vector<char> vec;
				vec.resize(size);

				system("cls");
				cout << "Введите элементы массива:" << endl;
				for (int i = 0; i < size; i++) {
					char val = '0';
					cin >> val;
					arr[i] = val;
					vec[i] = val;
				}
				menu1(size, arr, vec);
				break;
			}

			if (str == "object") {
				object* arr = new object[size];
				vector<object> vec;
				vec.resize(size);

				system("cls");
				cout << "Введите элементы массива:" << endl;
				for (int i = 0; i < size; i++) {
					object val;
					cin >> val.a;
					arr[i].a = val.a;
					vec[i].a = val.a;
				}
				menu1(size, arr, vec);
				break;
			}

			system("cls");
			cout << "Недопустимый тип данных !!!" << endl;
			cout << "Допускаются следующие типы данных: int, float и char." << endl;
			break;

		case 2:

			cout << "Введите тип данных:" << endl;
			cin >> str;

			if (str == "int") {
				int* arr = new int[size];
				vector<int> vec;
				vec.resize(size);

				system("cls");
				cout << "Введите элементы массива/вектора:" << endl;
				for (int i = 0; i < size; i++) {
					int val = 0;
					cin >> val;
					arr[i] = val;
					vec[i] = val;
				}
				menu2(size, arr, vec);
				for (int i = 0; i < size; i++) {
					cout << vec[i] << "\t";
				}
				cout << endl;
				break;
			}



			if (str == "float") {
				float* arr = new float[size];
				vector<float> vec;
				vec.resize(size);

				system("cls");
				cout << "Введите элементы массива:" << endl;
				for (int i = 0; i < size; i++) {
					float val = 0;
					cin >> val;
					arr[i] = val;
					vec[i] = val;
				}
				menu2(size, arr, vec);
				break;
			}

			if (str == "char") {
				char* arr = new char[size];
				vector<char> vec;
				vec.resize(size);

				system("cls");
				cout << "Введите элементы массива:" << endl;
				for (int i = 0; i < size; i++) {
					char val = '0';
					cin >> val;
					arr[i] = val;
					vec[i] = val;
				}
				menu2(size, arr, vec);
				break;
			}

			if (str == "object") {
				object* arr = new object[size];
				vector<object> vec;
				vec.resize(size);

				system("cls");
				cout << "Введите элементы массива:" << endl;
				for (int i = 0; i < size; i++) {
					object val;
					cin >> val.a;
					arr[i].a = val.a;
					vec[i].a = val.a;
				}
				menu2(size, arr, vec);
				break;
			}

			system("cls");
			cout << "Недопустимый тип данных !!!" << endl;
			cout << "Допускаются следующие типы данных: int, float и char." << endl;
			break;
			break;

		}

	}

}