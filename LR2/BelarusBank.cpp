#include <iostream>
#include "CashMachine.h"
#include "BankCard.h"
#include "Bank.h"

using std::cin;
using std::cout; 

enum Menu { CashByCode = 1, TransferOfFunds, CashWithdrawal, AmountOnAccount };

int main()
{
    Bank Belarus_Bank;
    BankCard CardBelarusBank(2222);
    BelarusBank ATMBelarusBank;

    ATMBelarusBank.InsertCard(CardBelarusBank, Belarus_Bank);


    while (CardBelarusBank.GetUsing())
    {
        cout << "\n1 - Cash by code\t 2 - Transfer of funds\t 3 - Cash withdrawal\t 4 - Amount on account\t 0 - Return the card\n";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case Menu::CashByCode:
            ATMBelarusBank.CashByCode(Belarus_Bank);
            break;
        
        case Menu::TransferOfFunds:
            ATMBelarusBank.TransferOfFunds(Belarus_Bank);
            break;

        case Menu::CashWithdrawal:
            ATMBelarusBank.CashWithdrawal(Belarus_Bank);
            break;  

        case Menu::AmountOnAccount:
            ATMBelarusBank.AmountOfMoney(Belarus_Bank);
            break;

        default:
            ATMBelarusBank.ReturnCard(CardBelarusBank);
            cout << "Thanks for using Belarus Bank";
            break;
        }
    }

    return 0;
}