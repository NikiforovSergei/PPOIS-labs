#include "account.h"
#include<iostream>
#include<fstream>


using namespace std;

void account::enter()
{

	user person1;

	cout << "Write your login" << endl;
	cin >> person1.numberuser;

	cout << "Write your password" << endl;
    cin >> person1.password;

    cout<<"Write your year"<<endl;
    cin>>person1.year;

    int check=1;

    cout<<"Write your month"<<endl;
    while (check) {

        cin >> person1.mouth;
        if (person1.mouth != 0 && person1.mouth<13) {
            check = 0;
            continue;
        }
        cout<<"Incorrect enter\n Try again"<<endl;
    }
    check = 1;
	cout << "Put money" << endl;
    while(check) {
        cin >> person1.data;
        if (person1.data>0) {
            check = 0;
            continue;
        }
        cout<<"Incorrect enter\n Try again"<<endl;
    }

	cout << endl;
	ofstream fin;
	try
	{
		fin.open("person.txt", ofstream::app);
		
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
		cout << "Error" << endl;
	}
	if (!fin.is_open())
	{
		cout << "Error" << endl;
	}
	else
	{
		fin.write((char*)&person1, sizeof(user));
	}
	fin.close();

}


