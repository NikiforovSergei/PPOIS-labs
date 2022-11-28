#include "ATMScreens.h"
#include <stdlib.h>

void ATMScreens_Base::button1() {

}

void ATMScreens_Base::button2() {
}

void ATMScreens_Base::button3() {

}

void ATMScreens_Base::button4() {

}

Main_Menu::Main_Menu(User current_user, CardAccount current_account, BANK bank) {
    current = std::move(current_user);
    BEL = std::move(bank);
    acc = current_account;
}

void Main_Menu::button1() {
    std::cout<<"How much you want to add?"<<std::endl;
    double amount;
    std::cin>>amount;
    acc.AddMoney(amount);
    current.UseCash(amount);
    BEL.AddCash(amount);
    std::cout<<"Operation is complete"<<std::endl;
}

void Main_Menu::button2() {
    std::cout<<"How much you want to withdraw?"<<std::endl;
    double amount;
    std::cin>>amount;
    acc.WithdrawCash(amount);
    current.AddCash(amount);
    BEL.WithdrawCash(amount);
    std::cout<<"Operation is complete"<<std::endl;
}

void Main_Menu::button3() {
    std::cout<<"Enter recipient's card number"<<std::endl;
    std::string recipient;
    std::cin>>recipient;
    std::cout<<"Enter amount"<<std::endl;
    double amount;
    int checker;
    std::cin>>amount;
    std::vector<CardAccount> currentbase = BEL.GetDataBase();
    currentbase = BEL.AddMoneyToAccount(amount,recipient,*&checker);
    if (checker){
        acc.WithdrawCash(amount);
        std::cout<<"Operation is complete"<<std::endl;
        BEL.RefreshBase(currentbase);
    }
    else{
        std::cout<<"There is no such card"<<std::endl;
    }
}

void Main_Menu::button4() {
    std::cout<<"Press any button to end session..."<<std::endl;
    getch();
}

void Main_Menu::ShowScreen() {
    std::cout<<map<<std::endl;
}

User Main_Menu::SaveUser() {
    return current;
}

BANK Main_Menu::SaveBankInfo() {
    return BEL;
}

CardAccount Main_Menu::SaveAccount() {
    return acc;
}

Pincode_window::Pincode_window() {
    std::cout<<"Enter Pincode\n";
    std::cin>>pin;
    std::cout<<map;
}

void Pincode_window::button1(CardAccount current_account) {
    if (pin == current_account.GetPinCode()){
    }
    else{

        std::cout<<"Incorrect pincode, access denied"<<std::endl;
        getch();
        std::exit(0);
    }
}

void Pincode_window::button2() {

    std::cout<<"Access denied"<<std::endl;
    getch();
    std::exit(0);
}

Insert_card::Insert_card() {
    std::cout<<map;
}

CardAccount Insert_card::Processing(User current, std::vector<CardAccount> accountbase) {
    for (auto & i : accountbase){
        if (i.GetCardNumber() == current.UseBankCard().GetCardNumber()){
            return i;
        }
    }
    std::cout<<"There is no such account in data base, access denied!"<<std::endl;
    std::exit(0);
}

void Insert_card::button1() {
}

void Insert_card::button2() {
    std::cout<<"Access denied"<<std::endl;
    getch();
    std::exit(0);
}

Launching_Screen::Launching_Screen() {
    std::cout<<map;
}
