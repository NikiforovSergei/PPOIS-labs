//
// Created by Евгений on 08.10.2022.
//

#ifndef BBANK_BANKS_H
#define BBANK_BANKS_H
#include <iostream>
#include <vector>

class BankCard;
class CardAccount;

class CardAccount{
private:
    double score;
    std::vector<std::string> card;
public:
    CardAccount(double cash, std::string cardnumber, std::string pincode);
    CardAccount();;
    ~CardAccount()= default;
    double ViewScore() const;
    double AddMoney(double money);
    double WithdrawCash(double money);
    std::string GetCardNumber();
    std::string GetPinCode();
};
class BankCard{
private:
    std::string cardnumber;
public:
    BankCard(CardAccount account);
    BankCard();
    std::string GetCardNumber();
    void LinkAccout(CardAccount account);
};
class BankAtm{
private:
    std::vector<CardAccount> base;
    double cash{};
public:
    BankAtm(double starting_cash,std::vector<CardAccount> BaseOfAccounts);
};
class User{
private:
    std::string FullName;
    std::string pincode;
    BankCard card;
    double cash;
public:
    User(std::string fullname, std::string pin, BankCard currentcard, double currentcash);
    User();
    void UseCash(double amount);
    void CheckCashBalance() const;
    double GetCash();
    BankCard UseBankCard();
    void AddCash(double amount);
    void LinkCard(CardAccount cardnumber);
    std::string GetName();
};
class BANK{
    std::vector<CardAccount> base;
    long double total_money;
public:
    BANK(std::vector<CardAccount> database,  long double money);
    BANK();
    std::vector<CardAccount> AddMoneyToAccount(double amount,std::string recipient, int check);
    void WithdrawCash(double input);
    void AddCash(double  input);
    long double GetScore();
    std::vector<CardAccount> GetDataBase();
    void RefreshBase(std::vector<CardAccount> input);
};

#endif //BBANK_BANKS_H
