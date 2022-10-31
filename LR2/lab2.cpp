#include "Header.h"

int main()
{
    balance a, b;
    string password, first_name, second_name;
    int tmp, tmp2, tmp3 = 0, tmp4, cash = 0, cash2 = 0, l;

    cout << "Enter the first and the second names of card's user: ";
    cin >> first_name >> second_name;
    a.setname(first_name, second_name);
    b.setname(first_name, second_name);
    system("cls");

    cout << "Enter the password you want: ";
    cin >> password;
    a.setpass(password);
    system("cls");

    cout << "Enter the password you want for the second wallet: ";
    cin >> password;
    b.setpass(password);
    system("cls");

    cout << "Cash on your account is: ";
    cin >> cash;
    a.setcash(cash);
    cout << "Cash on your second account is: ";
    cin >> cash2;
    b.setcash(cash2);
    system("cls");

    cout << "press \n\t1 to pass\n\tother to exit\n";
    cin >> tmp;
    system("cls");

    if (tmp == 1) {
       
        do
        {
        
            cout << "\n-----\npress\n\t1 to add \n\t2 to withdraw\n\t3 to view history\n\t4 to get full card information\n\t5 to change PIN\n\t6 to transfer from first account to second\n\t"<<
                "7 to transfer from second account to first\n\t8 to exit\n";
            cin >> tmp;
            system("cls");

            cout << "Choose the wallet:\n\t1 main\n\t2 second" << endl;
            cin >> l;

            if (tmp == 1)
            {
                if (l == 1) {

                    a.pin();
                    cout << "Amount: ";
                    cin >> tmp2;
                    a.add(tmp2);
                    system("cls");
                }
                else if (l == 2) {
                    b.pin();
                    cout << "Amount: ";
                    cin >> tmp2;
                    b.add(tmp2);
                    system("cls");
                }
                continue;
            }

            else if (tmp == 2)
            {
                if (l == 1) {
                    a.pin();
                    cout << "Amount: ";
                    cin >> tmp2;
                    a.get(tmp2);
                    system("cls");
                }
                else if (l == 2) 
                {
                    b.pin();
                    cout << "Amount: ";
                    cin >> tmp2;
                    b.get(tmp2);
                    system("cls");
                }
                continue;
            }
            else if (tmp == 3)
            {
                if (l == 1) 
                {
                    a.pin();
                    a.view();
                }

                else if (l == 2) 
                {
                    b.pin();
                    b.view();
                }
                continue;
            }
            else if (tmp == 4) 
            {
                if (l == 1)
                {
                    a.pin();
                    a.get_information("user_information.txt");
                }

                else if (l == 2) 
                {
                    b.pin();
                    b.get_information("user_information.txt");
                }
                continue;
            }
            else if (tmp == 5) 
            {
                if(l == 1)
                    a.change_pin();
                else if (l == 2)
                    b.change_pin();
                continue;
            }
            else if (tmp == 6) 
            {
                cout << "Amount: ";
                cin >> tmp4;
                a.get_for_transfer(tmp4);
                b.add_from_transfer(tmp4);
            }
            else if (tmp == 7)
            {
                cout << "Amount: ";
                cin >> tmp4;
                b.get_for_transfer(tmp4);
                a.add_from_transfer(tmp4);
            }
        } while (tmp != 8);
    }
}
