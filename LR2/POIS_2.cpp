#include "bankomat.h"
#include <fstream>

int main(int argv, char** args)
{
    std::setlocale(LC_ALL, "ru");

    long card_number;
    int card_cvv;
    std::string card_date;
    int client_pin;

    std::ifstream from("card_1.txt");
    if (from.is_open()) {
        from >> card_number >> card_cvv >> card_date >> client_pin;
        from.close();
    }

    long account_number;
    double client_money;
    long repository_money;


    std::ifstream from1("ATM_info.txt");
    if (from1.is_open()) {
        from1 >> account_number >> client_money >> repository_money;
        from.close();
    }

    int choice;
    std::cout << "Здравствуйте, вас приветствует иит_банк!" << std::endl;
    while(true) {
        std::cout << "Введите номер карты, с которой хотите работать: " << std::endl;
        int number;
        std::cin >> number;
        if (card_number == number) {
            Card card(card_number, card_cvv, card_date);
            Account account(account_number, client_money);
            Client client(client_pin, card, account);
            Repository repository(repository_money);
            Bankomat bankomat(repository);
            while (true)
            {
                std::cout << "Выберите операцию, которую желаете выполнить: " << std::endl;
                std::cout << "1) Снять деньги" << std::endl;
                std::cout << "2) Положить деньги" << std::endl;
                std::cout << "3) Проверить баланс" << std::endl;
                std::cout << "4) Завершить работу и забрать карту" << std::endl;
                std::cout << "5) Вывести данные о карте" << std::endl;
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    system("cls");
                    try
                    {
                        bankomat.get_money(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                case 2:
                {
                    system("cls");
                    try
                    {
                        bankomat.put_money(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                case 3:
                {
                    system("cls");
                    try
                    {
                        bankomat.check_balance(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                case 4:
                {
                    std::cout << "Всего доброго!" << std::endl;
                    system("cls");
                    return 0;
                }
                case 5:
                {
                    system("cls");
                    try
                    {
                        bankomat.cc(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                default: system("cls"); std::cout << "Ошибка ввода" << std::endl; system("pause"); system("cls");
                }
            }
        }
        else {
            std::ifstream from_2("card_2.txt");
            if (from_2.is_open()) {
                from_2 >> card_number >> card_cvv >> card_date >> client_pin;
                from_2.close();
            }
        }
        if (card_number == number) {
            Card card(card_number, card_cvv, card_date);
            Account account(account_number, client_money);
            Client client(client_pin, card, account);
            Repository repository(repository_money);
            Bankomat bankomat(repository);
            while (true)
            {
                std::cout << "Выберите операцию, которую желаете выполнить: " << std::endl;
                std::cout << "1) Снять деньги" << std::endl;
                std::cout << "2) Положить деньги" << std::endl;
                std::cout << "3) Проверить баланс" << std::endl;
                std::cout << "4) Завершить работу и забрать карту" << std::endl;
                std::cout << "5) Вывести данные о карте" << std::endl;
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    system("cls");
                    try
                    {
                        bankomat.get_money(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                case 2:
                {
                    system("cls");
                    try
                    {
                        bankomat.put_money(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                case 3:
                {
                    system("cls");
                    try
                    {
                        bankomat.check_balance(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                case 4:
                {
                    std::cout << "Всего доброго!" << std::endl;
                    system("cls");
                    return 0;
                }
                case 5:
                {
                    system("cls");
                    try
                    {
                        bankomat.cc(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                default: system("cls"); std::cout << "Ошибка ввода" << std::endl; system("pause"); system("cls");
                }
            }
        }
        else {
            std::ifstream from_3("card_3.txt");
            if (from_3.is_open()) {
                from_3 >> card_number >> card_cvv >> card_date >> client_pin;
                from_3.close();
                Card card(card_number, card_cvv, card_date);
                Account account(account_number, client_money);
                Client client(client_pin, card, account);
                Repository repository(repository_money);
                Bankomat bankomat(repository);
            }
        }
        if (card_number == number) {
            Card card(card_number, card_cvv, card_date);
            Account account(account_number, client_money);
            Client client(client_pin, card, account);
            Repository repository(repository_money);
            Bankomat bankomat(repository);
            while (true)
            {
                std::cout << "Выберите операцию, которую желаете выполнить: " << std::endl;
                std::cout << "1) Снять деньги" << std::endl;
                std::cout << "2) Положить деньги" << std::endl;
                std::cout << "3) Проверить баланс" << std::endl;
                std::cout << "4) Завершить работу и забрать карту" << std::endl;
                std::cout << "5) Вывести данные о карте" << std::endl;
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    system("cls");
                    try
                    {
                        bankomat.get_money(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                case 2:
                {
                    system("cls");
                    try
                    {
                        bankomat.put_money(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                case 3:
                {
                    system("cls");
                    try
                    {
                        bankomat.check_balance(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                case 4:
                {
                    std::cout << "Всего доброго!" << std::endl;
                    system("cls");
                    return 0;
                }
                case 5:
                {
                    system("cls");
                    try
                    {
                        
                        bankomat.cc(client);
                    }
                    catch (std::invalid_argument err) { std::cout << err.what() << std::endl; }
                    system("pause");
                    system("cls");
                    break;
                }
                default: system("cls"); std::cout << "Ошибка ввода" << std::endl; system("pause"); system("cls");
                }
            }
        }
        else {
            std::cout << "Эта карта не обслуживается в данном банке!!" << std::endl;
        }
    }
}