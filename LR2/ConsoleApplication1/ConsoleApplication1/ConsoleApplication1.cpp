#include "Header.h"
#include <fstream>

int main(int argv, char** args)
{
	std::setlocale(LC_ALL, "ru");

    long card_number;
    int card_cvv;
    std::string card_date;
    int client_pin;

    std::ifstream from(args[1]);
    if (from.is_open()) {
        from >> card_number >> card_cvv >> card_date >> client_pin;
        from.close();
    }

    long account_number;
    double client_money;
    long repository_money;
    

    std::ifstream from1(args[2]);
    if (from1.is_open()) {  
        from1 >> account_number >> client_money >> repository_money;
        from.close();
    }

    Card card(card_number, card_cvv, card_date);
    Account account(account_number, client_money);
    Client client(client_pin, card, account);
    Repository repository(repository_money);
    Bankomat bankomat(repository);

    int choice;
    while (true) 
    {
        std::cout << "1) Снять деньги" << std::endl;
        std::cout << "2) Положить деньги" << std::endl;
        std::cout << "3) Проверить баланс" << std::endl;
        std::cout << "4) Выход" << std::endl;
        std::cin >> choice;
        switch (choice) 
        {
        case 1: 
        {
            system("cls");
            bankomat.get_money(client);
            system("pause");
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            bankomat.put_money(client);
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            system("cls");
            bankomat.check_balance(client);
            system("pause");
            system("cls");
            break;
        }
        case 4:
        {
            system("cls");
            return 0;
        }
        default: system("cls"); std::cout << "Ошибка ввода" << std::endl; system("pause"); system("cls");
        }
    }



}
