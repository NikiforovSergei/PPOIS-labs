#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
	int i;
	Vector v1(4, 8, 16);
	Vector v2(7, 8, 9);
	Vector v4(1, 2, 3);
	Vector v5(1, 2, 3);
	Vector v6(2, 4, 8);
	Vector v7(4, 8, 16);
	Vector v3, v8, v9;

	Vector sr1(6, 5, 6);
	Vector sr2(4, 5, 6);

	Vector s1(10, 12, 15);
	Vector s2(2, 4, 3);

	Cos L;

	v3 = v1 + v2;
	v9 = v1 - v2;
	v8 = v1 * v2;
	v5 *= 2;
	v7 /= v6;
	L = s1 ^ s2;

	cout << "Rezultati v1 i v2(>)";
	if (v1 > v2)
		cout << "    | True, v1>v2\n";
	else cout << "    | False, v1!>v2\n";
	cout << "Rezultati sr1 i sr2(>=)";
	if (sr1 >= sr2)
		cout << " | True, sr1>=sr2\n";
	else cout << " | False, sr1!>=sr2\n";
	cout << "Rezultati v1 i v2(<)";
	if (v1 < v2)
		cout << "    | True, v1<v2\n";
	else cout << "    | False, v1!<v2\n";
	cout << "Rezultati sr1 i sr2(<=)";
	if (sr1 <= sr2)
		cout << " | True, sr1<=sr2\n";
	else cout << " | False, sr1!<=sr2\n";

	cout << "1.Pokazat'vector v1\n2.Dlina vectora v1\n3.Pokazat' vector v2\n4.Dlina vectora v2\n5.Summa vectorov v1 i v2\n6.Raznost' vectorov v1 i v2\n7.Proizvedenie vectorov v1 i v2\n8.Proizvedenie vectora v5 na chislo 2\n9.Chastnoe vectorov v7 i v6\n10.Cosinus mezhdu vectorami s1 i s2." << endl;
	
	
	while (true)
	{
		
		cout << "Vvedite nomer proceduri: ";
		cin >> i;
		
		switch (i)
		{
		case 1:
			v1.view_vector();
			break;
		case 2:
			cout << "Length:" << v1.length_v() << "\n";
			break;
		case 3:
			v2.view_vector();
			break;
		case 4:
			cout << "Length:" << v2.length_v() << "\n";
			break;
		case 5:
			v3.view_vector();
			break;
		case 6:
			v9.view_vector();
			break;
		case 7:
			v8.view_vector();
			break;
		case 8:
			v5.view_vector();
			break;
		case 9:
			v7.view_vector();
			break;
		case 10:
			L.prosmotrcos();
			break;
		default:
			return 0;
			break;
		}
	}
}
