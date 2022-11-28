//
// Created by Евгений on 08.10.2022.
//

#ifndef BBANK_ATMSCREENS_H
#define BBANK_ATMSCREENS_H
#include "BANKS.h"
#include <cstdlib>
#include <conio.h>

#include <utility>
class Insert_card;
class Pincode_window;
class Main_Menu;

class ATMScreens_Base {
public:
    virtual void button1();
    virtual void button2();
    virtual void button3();
    virtual void button4();
};

class Main_Menu:ATMScreens_Base{
    std::string map = "Choose operation:\n1)Top up account balance\n2)Withdraw cash\n3)Transfer money to other card\n4+)Exit\n";
    CardAccount acc;
    User current;
    BANK BEL;
public:
    Main_Menu(User current_user, CardAccount current_account, BANK bank);
    void button1() override;
    void button2() override;
    void button3() override;
    void button4() override;
    void ShowScreen();
    User SaveUser();
    BANK SaveBankInfo();
    CardAccount SaveAccount();
};
class Pincode_window:ATMScreens_Base{
    std::string pin;
    std::string map = "Continue ?\n1)Yes\n2)No\n";
public:
    Pincode_window();
    void button1(CardAccount current_account);
    void button2() override;
};
class Insert_card:ATMScreens_Base{
    std::string map = "Insert Card\n1)Yes\n2)No\n";
public:
    Insert_card();
    static CardAccount Processing(User current, std::vector<CardAccount> accountbase);
    void button1() override;
    void button2() override;

};
class Launching_Screen:ATMScreens_Base{
    std::string map = "Welcome to at ATM\n";
public:
    Launching_Screen();
};

#endif //BBANK_ATMSCREENS_H
