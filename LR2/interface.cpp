#include"interface.h"
#include<iostream>
#include<fstream>

using namespace std;

void interface::database()
{
	user person1;
	cout << "All information (admin access only)" << endl;
	ifstream fin;
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
		try
		{
			while (fin.read((char*)&person1, sizeof(user)))
			{
				cout << "User Number : " << person1.numberuser << "  ";
				cout << "User Password : " << person1.password << " ";
				cout << "User Deposit : " << person1.data << " ";
                cout << "User Date of Birth : " <<person1.mouth << "/" <<person1.year << endl;
			}
		}
		catch (const std::exception&ex)
		{
			cout << ex.what() << endl;
			cout << "Error" << endl;
		}

	}
	fin.close();

}
