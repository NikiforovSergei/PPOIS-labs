#include "HeapSort.h"
#include "StoogeSort.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int choose, size;
	cout << "Please enter the size of the array\n";
	cin >> size;
	int* arr = new int[size];
	char* charr = new char[size];
	cout << "Please choose method of sorting: \n\t1 - Heap Sorting method, \n\t2 - Stooge sorting method\n";
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