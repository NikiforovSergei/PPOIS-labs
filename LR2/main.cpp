#include "account.h"
#include "operation.h"
#include"interface.h"
#include"user.h"
#include "check.h"
#include <iostream>

using namespace std;

int main()
{
	account client;
	user clients{};
	operation execute;
	interface view;
    check checka;
	int a;
	int b;
	int admin_password = 123456;
A:
	cout << "Choose operation: " << endl;
	cout << "1-to create account " << endl;
	cout << "2-to check database" << endl;
	cout << "3-to check your balance" << endl;
	cout << "4-to change your balance" << endl;
	cout << "5-to look at interface (only if you are admin)" << endl;
    cout << "6-to look at mini-statement"<<endl;
	cin >> a;
	if (a == 5)
	{
		cout << "Enter password" << endl;
		cin >> b;
		if (b == admin_password)
		{
			goto B;
		}
		else
		{
			cout << "You dont have access!" << endl;
			goto A;
		}

	}
B:switch (a)
{
case 1:client.enter(); break;
case 2:clients.database(); break;
case 3:execute.printbalance(); break;
case 4:execute.addordeletemoneytofromdepozit(); break;
case 5:view.database(); break;
case 6:checka.checking(); break;
}
int k;
cout << "Would you like to continue? (1-Yes,2-No)" << endl;
cin >> k;
if (k == 1)
{
	goto A;
}
else if (k == 2)
{
	cout << "Thank you!" << endl;
}

}
