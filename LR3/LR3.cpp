#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
#include <algorithm>
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




template <typename Element>
void piegonhole(Element* mas, int s) //piegone sort массив
{
	map<Element, int> element_map = {};
	vector<Element> element_vector = {};

	for (int i = 0; i < s; i++)
	{
		if (element_map.find(mas[i]) == element_map.end())
		{
			element_map[mas[i]] = 1;
			element_vector.push_back(mas[i]);
		}
		else
		{
			element_map[mas[i]]++;
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
			mas[counter] = element_vector[i];
			counter++;
		}
	}


}
template <typename Element>
void piegonhole(vector<Element>& mas, int s) //piegonhole sort вектор
{
	map<Element, int> element_map = {};
	vector<Element> element_vector = {};

	for (int i = 0; i < s; i++)
	{
		if (element_map.find(mas[i]) == element_map.end())
		{
			element_map[mas[i]] = 1;
			element_vector.push_back(mas[i]);
		}
		else
		{
			element_map[mas[i]]++;
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
			mas[counter] = element_vector[i];
			counter++;
		}
	}

}

template <typename Element>
void gnome_sort(Element* set, int size_of_set) //gnome sort массив
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

template <typename Element>
void gnome_sort(vector<Element>& set, int size_of_set) // gnome sort вектор
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
	vector<string> arr = { "c", "f", "a", "d", "z", "m" , "k", "t"};
	int* arr1 = new int[8] { 1, 3, 5, 2, 5, 1, 8, 9};
	cout << "1) Unsorted vector:" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << arr1[i] << ' ';
	}
	cout << endl;

	piegonhole<int>(arr1, 8);
	cout << "Piegonhole sort with vector: " << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << arr1[i] << ' ';
	}
	cout << endl;



	cout << endl;
	cout << "2) Unsorted arr:" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl << "Piegonhole sort with arr: " << endl;
	piegonhole<string>(arr, 8);
	for (int i = 0; i < 8; i++) cout << arr[i] << ' ';
	cout << endl;


	string* arr2 = new string[7]{ "b", "z", "a", "d", "e", "m" , "k" };
	cout << endl;
	cout << "3) Unsorted arr:" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << arr2[i] << ' ';
	}
	cout << endl << "Gnome sort with arr: " << endl;
	gnome_sort<string>(arr2, 7);
	for (int i = 0; i < 7; i++)
	{
		cout << arr2[i] << ' ';
	}
	cout << endl;

	cout << endl;
	vector<int> arr3 = { 5,9,7,3,4,8,1};
	cout << "4) Unsorted vector:" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << arr3[i] << ' ';
	}
	cout << endl << "Gnome sort with vector: " << endl;	
	gnome_sort<int>(arr3, 7);
	for (int i = 0; i < 7; i++)
	{
		cout << arr3[i] << ' ';
	}
	cout << endl;

	cout << endl;
	vector<MyObj> my_obj = { MyObj(0), MyObj(5), MyObj(2), MyObj(5), MyObj(4), MyObj(6) };
	cout << "5) Unsorted vector:" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << my_obj[i].key << ' ';
	}
	cout << endl << "Gnome sort vector with objects: ";
	gnome_sort<MyObj>(my_obj, 6);
	for (int i = 0; i < 6; i++)
	{
		cout << my_obj[i].key << ' ';
	}
	cout << endl;

	cout << endl;
	vector<MyObj> my_obj2 = { MyObj(1), MyObj(3), MyObj(0), MyObj(5), MyObj(4), MyObj(0), MyObj(7), MyObj(9) };
	cout << "6) Unsorted vector:" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << my_obj2[i].key << ' ';
	}
	cout << endl << "Piegonhole sort vector with objects: ";
	piegonhole<MyObj>(my_obj2, 8);
	for (int i = 0; i < 8; i++)
	{
		cout << my_obj2[i].key << ' ';
	}
	cout<<endl;
}