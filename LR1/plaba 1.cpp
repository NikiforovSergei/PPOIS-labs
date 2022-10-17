#include <iostream>
#include "Mnogochlen.h"

int main()
{
	int n, kod;
	double m;
	setlocale(LC_ALL, "Russian");
	cout << "введите степень многочлена А" << endl;
	cin >> n;
	int n1 = n + 1;
	Mnogochlen A(n);
	cout << "введите коэффициенты (их должно быть " << n1 << ")" << endl;
	for (int i = 0; i <= n; i++)
	{
		cin >> m;
		A.set(i, m);
	}
	cout << "введите степень многочлена B" << endl;
	cin >> n;
	n1 = n + 1;
	Mnogochlen B(n);
	cout << "введите коэффициенты (их должно быть " << n1 << ")" << endl;
	for (int i = 0; i <= n; i++)
	{
		cin >> m;
		B.set(i, m);
	}
	cout << "A: ";
	A.print();
	cout << "B: ";
	B.print();
	 
	do
	{
		cout << endl << "1-просмотр А и В" << endl << "2-вычисление значение А при заданном аргументе" << endl;
		cout << "3-получение значения коэффициента A" << endl << "4-сумма А и В" << endl << "5-прибавление В к А" << endl;
		cout << "6-разность А и В" << endl << "7-вычитание В из А" << endl << "8-произведение А и В" << endl;
		cout << "9-умножение А на В" << endl << "10-частное А и В" << endl << "11-деление А на В" << endl;
		cout << "12-А равно B" << endl << "13-А не равно В" << endl;
		cin >> kod;
		switch(kod)
		{
		case 1:
		{
			cout << "A: ";
			A.print();
			cout << "B: ";
			B.print();
			break;
		}
		case 2:
		{
			double x;
			cout << "введите аргумент";
			cin >> x;
			cout << A(x) << endl;
			break;
		}
		case 3:
		{
			int i;
			cout << "введите номер коэффициента";
			cin >> i;
			cout << A[i] << endl;
			break;
		}
		case 4:
		{
			Mnogochlen C = A + B;
			C.print();
			break;
		}
		case 5:
		{
			A += B;
			break;
		}
		case 6:
		{
			Mnogochlen C = A - B;
			C.print();
			break;
		}
		case 7:
		{
			A -= B ;
			break;
		}
		case 8:
		{
			Mnogochlen C = A * B;
			C.print();
			break;
		}
		case 9:
		{
			A *= B;
			break;
		}
		case 10:
		{
			Mnogochlen C = A / B;
			C.print();
			break;
		}
		case 11:
		{
			A /= B;
			break;
		}
		case 12:
		{
			if (A == B)
				cout << "да" << endl;
			else
				cout << "нет" << endl;
			break;
		}
		case 13:
		{
			if (A != B)
				cout << "да" << endl;
			else
				cout << "нет" << endl;
			break;
		}
		}
	} while (kod <= 13 && kod != 0);
}

