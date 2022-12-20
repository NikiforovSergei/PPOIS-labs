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
    history.push_front("пополнение счёта на  " + money(sum) + " USD");
    return;
}

void card::replenishment_from_transfer(int sum)
{
    cash += sum;
    history.push_front("пополнение дополнительного счёта на " + money(sum) + " USD");
    return;
}

void card::set_password(string password)
{
    password = password;
    return;
}

void card::view()
{
    cout << "Текущий аккаунт: " << cash << " USD\n       ВЫПИСКА       \n";
    for (int i = 0; i < history.size(); ++i)
        cout << history.size() - i << ": " << history[i] << endl;

    return;
}

void card::withdraw(int sum)
{
    if (cash - sum < 0)
    {
        system("cls");
        cout << "Невозможно" << endl;
        system("cls");
        history.push_front("снятие со счёта " + money(sum) + " USD провалено");
    }
    else
    {
        system("cls");
        cash -= sum;
        cout << "Выполнено" << endl;
        history.push_front("снятие со счёта " + money(sum) + " USD успешно");
    }

    return;
}

void card::get_for_transfer(int sum)
{
    if (cash - sum < 0)
    {
        system("cls");
        cout << "Невозможно" << endl;
        system("cls");
        history.push_front("перевод на другой счёт " + money(sum) + " USD провален");
    }
    else
    {
        system("cls");
        cash -= sum;
        cout << "Выполнено" << endl;
        history.push_front("перевод на другой счёт " + money(sum) + " USD успешно выполнен");
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
    cout << "Пароль: ";
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
        fout << "Текущий аккаунт: " << cash << " USD\n      ВЫПИСКА      " << endl ;
        for (int i = 0; i < history.size(); ++i)
            fout << history.size() - i << ": " << history[i] << endl;
    }
    fout << "Имя пользователя:  ";
    fout << first << " " << second << endl;
    fout << "ПИН-код: " << password;

}

void card::pin()
{
    while (!get_access())
    {
        cout << "Попробуйте ещё раз!" << endl;
    }
    cout << "Доступ предоставлен!" << endl << endl;
}

void card::change_pin()
{
    string new_pin;
    string old_pass = password;
    cout << "Введите старый ПИН: ";
    cin >> old_pass;
    cout << "Введите новый ПИН: ";
    cin >> new_pin;
    do
    {
        if (old_pass == password)
        {
            password = new_pin;
            cout << "ПИН успешно изменён" << endl;
            return;
        }
        else  cout << "Старый ПИН введён неверно. Попробуйте ещё раз" << endl; 
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
    cout << "Сумма: ";
    cin >> sum;
    a.replenishment(sum);
    system("cls");
}