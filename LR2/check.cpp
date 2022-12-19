//
// Created by prohor on 18.11.21.
//
#include <iostream>
#include "check.h"
#include<fstream>

using namespace std;

void check::checking(){
    int number;
    check chock;
    cout << "Enter your login" << endl;
    cin >> number;
    ifstream foutw;
    try
    {
        foutw.open("check.txt",ofstream::app);

    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
        cout << "Error" << endl;
    }
    if (!foutw.is_open())
    {
        cout << "Error" << endl;
    }
    else
    {
        try
        {
            while (foutw.read((char*)&chock, sizeof(check)))
            {
                if (chock.person_id == number)
                {
                    if (chock.operation == 1){
                        cout<<"RM-number: "<< chock.rm_number << " "<<" Cash out"<< endl;
                    }
                    if (chock.operation == 2){
                        cout<<"RM-number: "<< chock.rm_number << " "<<"  Cash in"<<endl;
                    }
                    if (chock.operation == 3){
                        cout<<"RM-number: "<< chock.rm_number << " "<<"  Cash transfer"<<endl;
                    }
                    if (chock.operation == 5){
                        cout<<"RM-number: "<< chock.rm_number << " "<<"  Balance"<<endl;
                    }
                    if (chock.operation == 4){
                        cout<<"RM-number: "<< chock.rm_number << " "<<"  Phone recharge"<<endl;
                    }
                    if (chock.operation == 6){
                        cout<<"RM-number: "<< chock.rm_number << " "<<"  Invalid operation"<<endl;
                    }
                    if (chock.operation == 7){
                        cout<<"RM-number: "<< chock.rm_number << " "<<"  New password"<<endl;
                    }
                }
            }
        }
        catch (const std::exception& ex)
        {
            cout << ex.what() << endl;
            cout << "Error" << endl;
        }

    }
    foutw.close();
}
