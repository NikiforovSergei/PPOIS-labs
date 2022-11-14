#include <iostream>
#include "Model.h"
using namespace std;



int main()
{
	cout << "Enter path: ";
	cin >> settings::path;

	Model model(settings::path);

	system("pause");
	return 0;
}