#include "HeapSort.h"
#include "StoogeSort.h"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int choose, size;
	cout << "Please enter the size of the array";
	cin >> size;
	int* arr = new int[size];
	char* charr = new char[size];
	cout << "Please choose method of sorting: 1-For Heap Sorting method, 2-For Stooge sorting method";
	cin >> choose;
	switch (choose){
	case 1:
		HeapSort hpsort;
		hpsort.inputCheck(arr, charr, size);
		break;
	case 2:
		StoogeSort stsort;
		stsort.inputCheck(arr, charr, size);
		break;
	}
}