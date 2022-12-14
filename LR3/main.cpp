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




template <typename T>
void pigeonhole(T* arr, int n)
{
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }
    int range = max - min + 1; // Find range
  
    // Create an array of vectors. Size of array
    // range. Each vector represents a hole that
    // is going to contain matching elements.
    vector<int> holes[range];
  
    // Traverse through input array and put every
    // element in its respective hole
    for (int i = 0; i < n; i++)
        holes[arr[i] - min].push_back(arr[i]);
  
    // Traverse through all holes one by one. For
    // every hole, take its elements and put in
    // array.
    int index = 0; // index in sorted array
    for (int i = 0; i < range; i++) {
        vector<int>::iterator it;
        for (it = holes[i].begin(); it != holes[i].end(); ++it)
            arr[index++] = *it;
    }
}

template <typename T>
void pigeonhole(vector<T>& arr, int s)
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
    int* arr = new int[6]{ 1, 3, 5, 2, 5, 1};
    pigeonhole<int>(arr, 6);
    cout << "pigeonhole (arr): " << endl;
    for(int i=0; i<6; i++)
    {
        cout << arr[i]<<' ';
    }
    
    vector<string> arr1 = {"b", "f", "a", "d", "e", "m"};
    cout << endl << "pigeonhole (vector): " << endl;
    pigeonhole<string>(arr1, 6);
    for (int i = 0; i < 6; i++)
    {
        cout << arr1[i] << ' ';
    }
    
    string* arr2 = new string[6]{ "b", "f", "a", "d", "e", "m" };
    cout << endl<< "gnome (arr): " << endl;
    gnome_sort<string>(arr2, 6);
    for(int i=0; i<6; i++)
    {
        cout << arr2[i]<<' ';
    }

    vector<int> arr3 = { 7, 5, 3, 1, 5, 6};
    cout << endl << "gnome (vector): " << endl;
    gnome_sort<int>(arr3, 6);
    for (int i = 0; i < 6; i++)
    {
        cout << arr3[i] << ' ';
    }

    vector<MyObj> my_obj = {MyObj(1), MyObj(3), MyObj(2), MyObj(5), MyObj(4) };
    cout << endl << "gnome vector (obj): ";
    gnome_sort<MyObj>(my_obj, 5);
    for (int i = 0; i < 5; i++)
    {
        cout << my_obj[i].key<<' ';
    }

    vector<MyObj> my_obj2 = { MyObj(1), MyObj(3), MyObj(2), MyObj(5), MyObj(4), MyObj(1)};
    cout << endl << "pigeonhole vector (obj): ";
    pigeonhole<MyObj>(my_obj2, 6);
    for (int i = 0; i < 6; i++)
    {
        cout << my_obj2[i].key << ' ';
    }
    cout << endl;
}
