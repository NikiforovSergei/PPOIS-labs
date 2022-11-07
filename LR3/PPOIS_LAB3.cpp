#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
#include <algorithm>
using namespace std;



/*template<typename Type>
Type max(Type a, Type b)
{
	return (a >= b ? a : b);
}*/


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
void piegonhole(T* arr, int s) //функция на голубиную сортировку под массив
{
	map<T, int> element_map = {};
	vector<T> element_vector = {};

	for (int i = 0; i < s; i++)
	{
		if (element_map.find(arr[i]) == element_map.end())
		{
			element_map[arr[i]] = 1;
			element_vector.push_back(arr[i]);
		}
		else
		{
			element_map[arr[i]]++;
		}
	}
	

	for (int i = 0; i < element_vector.size() - 1; i++)
	{
		for (int j = i+1; j < element_vector.size(); j++)
		{
			if(element_vector[i]>element_vector[j])
			{
				swap(element_vector[i], element_vector[j]);
			}
		}
	}



	int counter = 0;
	
	for (int i = 0; i < element_vector.size(); i++)
	{
		int amount = element_map[element_vector[i]];
		for (int j = 0; j < amount; j++)
		{
			arr[counter] = element_vector[i];
			counter++;
		}
	}
	
	
}
template <typename T>
void piegonhole(vector<T>& arr, int s) //функция на голубиную сортировку на вектор (переопределение верхней)
{
	map<T, int> element_map = {};
	vector<T> element_vector = {};

	for (int i = 0; i < s; i++)
	{
		if (element_map.find(arr[i]) == element_map.end())
		{
			element_map[arr[i]] = 1;
			element_vector.push_back(arr[i]);
		}
		else
		{
			element_map[arr[i]]++;
		}
	}


	for (int i = 0; i < element_vector.size() - 1; i++)
	{
		for (int j = i + 1; j < element_vector.size(); j++)
		{
			if (element_vector[i] > element_vector[j])
			{
				swap(element_vector[i], element_vector[j]);
			}
		}
	}



	int counter = 0;

	for (int i = 0; i < element_vector.size(); i++)
	{
		int amount = element_map[element_vector[i]];
		for (int j = 0; j < amount; j++)
		{
			arr[counter] = element_vector[i];
			counter++;
		}
	}

}

template <typename T> 
void gnome_sort(T* set, int size_of_set) //функция на gnome sort на массив
{
	int index = 1, next_index = index + 1;;
	while (index < size_of_set)
	{
		if (set[index - 1] < set[index])
		{
			index = next_index;
			next_index++;
		}
		else
		{
			swap(set[index - 1], set[index]);
			index--;
			if (index == 0)
			{
				index = next_index;
				next_index++;
			}
		}
	}
}

template <typename T>
void gnome_sort(vector<T>& set, int size_of_set) //функция на gnome sort на вектор
{
	int index = 1, next_index = index + 1;;
	while (index < size_of_set)
	{
		if (set[index - 1] < set[index])
		{
			index = next_index;
			next_index++;
		}
		else
		{
			swap(set[index - 1], set[index]);
			index--;
			if (index == 0)
			{
				index = next_index;
				next_index++;
			}
		}
	}
}


int main()
{
	vector<string> arr = {"b", "f", "a", "d", "e", "m"};
	int* arr1 = new int[6]{ 1, 3, 5, 2, 5, 1};

	piegonhole<int>(arr1, 6);
	cout << "piegonhole with vector: "<<endl;
	for(int i=0; i<6; i++)
	{
		cout << arr1[i]<<' ';
	}


	cout << endl << "piegonhole with arr: " << endl;
	piegonhole<string>(arr, 6);
	for (int i = 0; i < 6; i++) cout << arr[i] << ' ';
	


	cout << endl<< "gnome with arr: " << endl;
	string* arr2 = new string[6]{ "b", "fa", "a", "d", "e", "m" };
	gnome_sort<string>(arr2, 6);
	for(int i=0; i<6; i++)
	{
		cout << arr2[i]<<' ';
	}


	cout << endl << "gnome with vector: " << endl;
	vector<int> arr3 = { 1, 2, 3, 4, 5, 6};
	gnome_sort<int>(arr3, 6);
	for (int i = 0; i < 6; i++)
	{
		cout << arr3[i] << ' ';
	}


	cout << endl << "Gnome vector with objects: ";
	vector<MyObj> my_obj = {MyObj(1), MyObj(3), MyObj(2), MyObj(5), MyObj(4) };
	gnome_sort<MyObj>(my_obj, 5);
	for (int i = 0; i < 5; i++)
	{
		cout << my_obj[i].key<<' ';
	}


	cout << endl << "piegonhole vector with objects: ";
	vector<MyObj> my_obj2 = { MyObj(1), MyObj(3), MyObj(2), MyObj(5), MyObj(4), MyObj(1)};
	piegonhole<MyObj>(my_obj2, 6);
	for (int i = 0; i < 6; i++)
	{
		cout << my_obj2[i].key << ' ';
	}
}