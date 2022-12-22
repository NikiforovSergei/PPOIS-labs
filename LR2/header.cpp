#include "header.h"

void reversestr(string& s)
{
    for (int i = 0; i < s.length() / 2; ++i)
        swap(s[i], s[s.length() - i - 1]);
}

string money(int num)
{
    string m;

    while (num != 0)
    {
        m.push_back((num % 10) + '0');
        num /= 10;
    }

    reversestr(m);
    return m;
}


void card::replenishment(int sum)
{
    cash += sum;
    history.push_front("���������� ����� ��  " + money(sum) + " USD");
    return;
}

void card::replenishment_from_transfer(int sum)
{
    cash += sum;
    history.push_front("���������� ��������������� ����� �� " + money(sum) + " USD");
    return;
}

void card::set_password(string password)
{
    password = password;
    return;
}

void card::view()
{
    cout << "������� �������: " << cash << " USD\n       �������       \n";
    for (int i = 0; i < history.size(); ++i)
        cout << history.size() - i << ": " << history[i] << endl;

    return;
}

void card::withdraw(int sum)
{
    if (cash - sum < 0)
    {
        system("cls");
        cout << "����������" << endl;
        system("cls");
        history.push_front("������ �� ����� " + money(sum) + " USD ���������");
    }
    else
    {
        system("cls");
        cash -= sum;
        cout << "���������" << endl;
        history.push_front("������ �� ����� " + money(sum) + " USD �������");
    }

    return;
}

void card::get_for_transfer(int sum)
{
    if (cash - sum < 0)
    {
        system("cls");
        cout << "����������" << endl;
        system("cls");
        history.push_front("������� �� ������ ���� " + money(sum) + " USD ��������");
    }
    else
    {
        system("cls");
        cash -= sum;
        cout << "���������" << endl;
        history.push_front("������� �� ������ ���� " + money(sum) + " USD ������� ��������");
    }

    return;
}

void card::balance(int sum)
{
    cash = sum;
    return;
}

bool card::get_access()
{
    string password;
    cout << "������: ";
    cin >> password;
    if (password == password)
    {
        system("cls");
        return true;

    }
    system("cls");
    return false;
}

void card::info(string path)
{
    ofstream fout;
    fout.open(path);
    if (fout.is_open())
    {
        fout << "������� �������: " << cash << " USD\n      �������      " << endl ;
        for (int i = 0; i < history.size(); ++i)
            fout << history.size() - i << ": " << history[i] << endl;
    }
    fout << "��� ������������:  ";
    fout << first << " " << second << endl;
    fout << "���-���: " << password;

}

void card::pin()
{
    while (!get_access())
    {
        cout << "���������� ��� ���!" << endl;
    }
    cout << "������ ������������!" << endl << endl;
}

void card::change_pin()
{
    string new_pin;
    string old_pass = password;
    cout << "������� ������ ���: ";
    cin >> old_pass;
    cout << "������� ����� ���: ";
    cin >> new_pin;
    do
    {
        if (old_pass == password)
        {
            password = new_pin;
            cout << "��� ������� ������" << endl;
            return;
        }
        else  cout << "������ ��� ����� �������. ���������� ��� ���" << endl; 
    } while (old_pass == password);
}

void card::setname(const string& f, const string& s)
{
    first = f;
    second = s;
}

void add_money(int sum, card a)
{
    a.pin();
    cout << "�����: ";
    cin >> sum;
    a.replenishment(sum);
    system("cls");
}