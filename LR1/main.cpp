#include <iostream>
#include "Fraction.h"
#include "Source.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	int arg = 0;
	string input;
	Fraction firstFraction, secondFraction;
	cout << "Введите дробь/дроби:\n";
	getline(cin, input);
	firstFraction.value = findFirstFraction(input);
	secondFraction.value = findSecondFraction(input);
	cout << "Выберите функцию\n";
	cout << "\n1)sum\n2)dif\n3)multi\n4)often\n5)isLarger\n6)isLess\n7)larger or equal\n8)less or equal\n9)increment\n10)decrement\n11)pre-increment\n12)pre-decrement\n\n";
	cin >> arg;
	switch (arg)
	{
	case 1: cout << (firstFraction + secondFraction).value; break;
	case 2: cout << (firstFraction - secondFraction).value; break;
	case 3: cout << (firstFraction * secondFraction).value; break;
	case 4: cout << (firstFraction / secondFraction).value; break;
	case 5: cout << (firstFraction > secondFraction); break;
	case 6: cout << (firstFraction < secondFraction); break;
	case 7: cout << (firstFraction >= secondFraction); break;
	case 8: cout << (firstFraction <= secondFraction); break;
	case 9: cout << (firstFraction++).value; break;
	case 10: cout << (firstFraction--).value; break;
	case 11: cout << (++firstFraction).value; break;
	case 12: cout << (--firstFraction).value; break;
	default: break;
	}
}
