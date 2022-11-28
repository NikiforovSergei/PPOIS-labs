#include <iostream>
#include "Obj.h"
#include "CombSort.h"
#include "TournamentSort.h"

template<class T>
void printArray(T* objArray, int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << objArray[i] << "  ";
	}
	std::cout << "\n";
}
template<class T>
void printVector(std::vector<T> &objVector)
{
	for (int i = 0; i < objVector.size(); ++i)
	{
		std::cout << objVector[i] << "  ";
	}
	std::cout << "\n";
}

using namespace std;

int main()
{
	cout << "\t\tInitial data\n";
	vector<int> vec1 = {5,6,1,2,9,10,12,34,11};
	printVector(vec1);
	vector<double> vec2 = { -3.1,-10.56,-10.57,-10.567,1,-2 };
	printVector(vec2);
	int arr1[5] = {-3,-2,1,-5,10};
	printArray(arr1,5);
	double arr2[5] = {-4.5,-4.56,-4,0,10};
	printArray(arr2, 5);
	vector<Obj<int>> vec3 = {Obj<int>(5),Obj<int>(-10),Obj<int>(0),Obj<int>(1) ,Obj<int>(2),Obj<int>(3)};
	printVector(vec3);
	vector<Obj<double>> vec4 = { Obj<double>(5.12),Obj<double>(-5.12),Obj<double>(5.13),Obj<double>(5.31)};
	printVector(vec4);
	//sorting by CombSort
	cout << "\t\tSorted data(combSort):\n";
	combSort(vec1);
	printVector(vec1);
	combSort(vec2);
	printVector(vec2);
	combSort(arr1, 5);
	printArray(arr1, 5);
	combSort(arr2, 5);
	printArray(arr2, 5);
	combSort(vec3);
	printVector(vec3);
	combSort(vec4);
	printVector(vec4);
	//clearing arrays and vectors 
	vec1.clear();
	vec2.clear();
	vec3.clear();
	vec4.clear();
	//
	cout << "\t\tInitial data\n";
	vec1 = { 5,6,1,2,9,10,12,34,11 };
	printVector(vec1);
	vec2 = { -3.1,-10.56,-10.57,-10.567,1,-2 };
	printVector(vec2);
	int* arr3 = new int[5] { -3, -2, 1, -5, 10 };
	printArray(arr3, 5);
	double* arr4= new double[5] { -4.5, -4.56, -4, 0, 10 };
	printArray(arr4, 5);
	vec3 = { Obj<int>(5),Obj<int>(-10),Obj<int>(0),Obj<int>(1) ,Obj<int>(2),Obj<int>(3) };
	printVector(vec3);
	vec4 = { Obj<double>(5.12),Obj<double>(-5.12),Obj<double>(5.13),Obj<double>(5.31) };
	printVector(vec4);
	cout << "\t\tSorted data(TournamentSort):\n";
	TournamentSort(vec1,vec1.size());
	printVector(vec1);
	TournamentSort(vec2,vec2.size());
	printVector(vec2);
	arr3 = TournamentSort(arr3, 5);
	printArray(arr3, 5);
	arr4 = TournamentSort(arr4, 5);
	printArray(arr4, 5);
	TournamentSort(vec3,vec3.size());
	printVector(vec3);
	TournamentSort(vec4,vec4.size());
	printVector(vec4); 
	return 0;
}