#include "Header.h"

void reversestr(string& s)
{
    for (int i = 0; i < s.length() / 2; ++i)
        swap(s[i], s[s.length() - i - 1]);
}

string itos(int num)
{
    string ot;

    while (num != 0)
    {
        ot.push_back((num % 10) + '0');
        num /= 10;
    }

    reversestr(ot);
    return ot;
}


void balance::add(int sum) 
{
    cash += sum;
    history.push_front("replenishment of the account on " + itos(sum) + " usd");
    return;
}

void balance::add_from_transfer(int sum)
{
    cash += sum;
    history.push_front("replenishment from another account " + itos(sum) + " usd");
    return;
}

void balance::setpass(string password)
{
    pass = password;
    return;
}

void balance::view()
{
    cout << "Current account: " << cash << " usd\n=====HISTORY=====\n";
    for (int i = 0; i < history.size(); ++i)
        cout << history.size() - i << ": " << history[i] << "\n";

    return;
}

void balance::get(int sum)
{
    if (cash - sum < 0)
    {
        system("cls");
        cout << "Impossible\n";
        system("cls");
        history.push_front("withdrawn from the account " + itos(sum) + " usd failed");
    }
    else
    {
        system("cls");
        cash -= sum;
        cout << "Done\n"; 
        history.push_front("withdrawn from the account " + itos(sum) + " usd success");
    }

    return;
}

void balance::get_for_transfer(int sum)
{
    if (cash - sum < 0)
    {
        system("cls");
        cout << "Impossible\n";
        system("cls");
        history.push_front("transfer to another wallet " + itos(sum) + " usd failed");
    }
    else
    {
        system("cls");
        cash -= sum;
        cout << "Done\n";
        history.push_front("transfer to another wallet " + itos(sum) + " usd success");
    }

    return;
}

void balance::setcash(int sum)
{
    cash = sum;
    return;
}

bool balance::get_access()
{
    string password;
    cout << "Pass: ";
    cin >> password;
    if (password == pass)
    {
        system("cls");
        return true;
        
    }
    system("cls");
    return false;
}

void balance::get_information(string path) 
{
    ofstream fout;
    fout.open(path);
    if (fout.is_open()) 
    {
        fout << "Current account: " << cash << " usd\n=====HISTORY=====\n";
        for (int i = 0; i < history.size(); ++i)
            fout << history.size() - i << ": " << history[i] << "\n";
    }
    fout << "The name of user:\n";
    fout << first_name << " " << second_name << endl;
    fout << "PIN is " << pass;

}

void balance::pin()
{
    while (!get_access())
    {
        cout << "Try again!\n";
    }
    cout << "access granted\n\n";
}

void balance::change_pin()
{
    string new_pin;
    string old_pass = pass;
    cout << "Enter old PIN: ";
    cin >> old_pass;
    cout << "Enter new PIN: ";
    cin >> new_pin;
    do
    {
        if (old_pass == pass)
        {
            pass = new_pin;
            cout << "PIN succesfully changed!" << endl;
            return;
        }
        else { cout << "Old PIN is wrong. Try again!" << endl; }
    } while (old_pass == pass);
}

void balance::setname(const string& f, const string& s)
{
    first_name = f;
    second_name = s;
}

void add_money(int tmp, balance a) 
{
    a.pin();
    cout << "Amount: ";
    cin >> tmp;
    a.add(tmp);
    system("cls");
}
