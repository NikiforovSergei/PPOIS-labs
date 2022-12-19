#include "operation.h"
#include<iostream>
#include<fstream>
#include <algorithm>
#include "check.h"
#include <regex>

using namespace std;

void operation::addordeletemoneytofromdepozit()
{
	user person,person2;
	int number,number2;
    class check chock;
    cout << "Enter your login"<<endl;
	cin >> number;
    srand(time(0));
    ifstream fin1("person.txt",ios::binary);
    ifstream fin2("person.txt",ios::binary);
	ofstream fout1("temporary.txt",ios::binary);
    ofstream foutc("check.txt", ios::binary|std::ios::app);
	while (!fin1.eof())
	{
		try
		{
        fin1.read((char*)&person, sizeof(user));
		if (number != person.numberuser and !fin1.eof())
		{
			fout1.write((char*)&person, sizeof(user));
		}
		if (number == person.numberuser and !fin1.eof())
		{
			int i;
			cout << "What would you like to do? \n 1-take money \n"
                    " 2-put money\n"
                    " 3-take money your friends\n"
                    " 4-take money mobilephone " << endl;
			cin >> i;
			int k = 0;
            string mobilephone;
            chock.person_id = person.numberuser;
            chock.rm_number = rand()%10000;
			int templmoney;
            int templmoney2;
			if (i == 1) {
                templmoney = person.data;
                chock.operation = 1;
                cout << "How much money would you like to take?" << endl;
                cin >> k;
                if (person.data > k) {
                    person.data = templmoney - k;
                    foutc.write((char *) &chock, sizeof(class check));
                }else{
                    chock.operation = 6;
                    cout << "RM-number "<< chock.rm_number <<endl;
                    foutc.write((char*)&chock, sizeof(class check));
                }
            }
			if (i == 2)
			{

				templmoney = person.data;
				cout << "How much money would you like to put?" << endl;
				cin >> k;
				person.data = templmoney + k;
                chock.operation = 2;
                cout << "RM-number "<< chock.rm_number <<endl;
                foutc.write((char*)&chock, sizeof(class check));
			}
            if(i == 3){
                cout<<"your friends login"<<endl;
                cin>>number2;
                while (fin2.read((char*)&person2, sizeof(user)))
                {
                if (person2.numberuser == number2)
                {
                    templmoney = person.data;
                    templmoney2 = person2.data;
                    cout << "How much money would you like to put?" << endl;
                    cin >> k;
                    if(person.data > k) {
                        chock.operation = 3;
                        person.data = templmoney - k;
                        person2.data = templmoney2 + k;
                        cout << "RM-number " << chock.rm_number << endl;
                        foutc.write((char *) &chock, sizeof(class check));
                    }else{
                        chock.operation = 6;
                        cout << "RM-number "<< chock.rm_number <<endl;
                        foutc.write((char*)&chock, sizeof(class check));
                    }
                }
            }
        }
        if (i == 4)
            {
                templmoney = person.data;
                cout<< "your mobile phone"<<endl;
                cin>>mobilephone;
                int v=0;
                while(v<0) {
                    try {
                        if (std::regex_match(mobilephone, std::regex("^[+]*[(]{0,1}[0-9]{1,4}[)]{0,1}[-\\s\\./0-9]*$")))
                            throw "Can not take sqrt of negative number"; // выбрасывается исключение типа const char*
                        std::cout << "valid phone number" << '\n';
                        v++;
                    }
                    catch (const char *exception) // обработчик исключений типа const char*
                    {
                        std::cerr << "Error: " << exception << '\n';
                    }
                }
                cout << "How much money would you like to take your mobile phone?" << endl;
                cin >> k;
                if(person.data > k){
                person.data = templmoney - k;
                chock.operation = 4;
                cout << "RM-number "<< chock.rm_number <<endl;
                foutc.write((char*)&chock, sizeof(class check));
                }else{
                    chock.operation = 6;
                    cout << "RM-number "<< chock.rm_number <<endl;
                    foutc.write((char*)&chock, sizeof(class check));
                }
            }
        if (i == 5){
            cout << "New password" << endl;
            cin >> k;
            person.password = k;
            chock.operation = 7;
            cout << "RM-number "<< chock.rm_number <<endl;
            foutc.write((char*)&chock, sizeof(class check));
        }
      
			fout1.write((char*)&person, sizeof(user));
		}
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			cout << "Error" << endl;
		}
	}
	fin1.close();
	fout1.close();

	ifstream fin("temporary.txt");
	ofstream fout("person.txt");
	while (!fin.eof())
	{
		try
		{
		fin.read((char*)&person, sizeof(user));
		if (!fin.eof())
		{
			fout.write((char*)&person, sizeof(user));
		}
		}
		catch (const std::exception&ex)
		{
			cout << ex.what() << endl;
			cout << "Error" << endl;
		}
	}
	fin.close();
	fout.close();
    foutc.close();
}

void operation::printbalance()
{
	user person;
	int number;
    class check chock;
    cout << "Enter your login" << endl;
	cin >> number;
    srand(time(0));
    ofstream foutc("check.txt",std::ios::app);
	ifstream finn;

	try
	{
		finn.open("person.txt", ofstream::app);

	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
		cout << "Error" << endl;
	}
	if (!finn.is_open())
	{
		cout << "Error" << endl;
	}
	else
	{
		try
		{
		while (finn.read((char*)&person, sizeof(user)))
		{
			if (person.numberuser == number)
			{
                chock.operation = 5;
                chock.person_id = person.numberuser;
                chock.rm_number = rand()%10000;
				cout << "User Number is " << person.numberuser << endl;
				cout << "Your balance is " << person.data << endl;
                foutc.write((char*)&chock, sizeof(class check));
                cout << "RM-number "<< chock.rm_number <<endl;
			}
		}
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			cout << "Error" << endl;
		}

	}
	finn.close();
    foutc.close();
}
