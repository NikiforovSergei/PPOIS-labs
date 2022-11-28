//
// Created by Евгений on 08.10.2022.
//

#include "BANKS.h"

#include <utility>

CardAccount::CardAccount(double cash, std::string cardnumber, std::string pincode) {
    score = cash;
    card = {std::move(cardnumber), std::move(pincode)};
}

CardAccount::CardAccount() {
    score = 0;
    card = {"000000000","0000"};
}

double CardAccount::ViewScore() const {
    return score;
}

double CardAccount::AddMoney(double money) {
    score+=money;
    return score;
}

double CardAccount::WithdrawCash(double money) {
    score-=money;
    return score;
}

std::string CardAccount::GetCardNumber() {
    return card[0];
}

std::string CardAccount::GetPinCode() {
    return card[1];
}

BankCard::BankCard(CardAccount account) {
    cardnumber = account.GetCardNumber();
}

BankCard::BankCard() {
    cardnumber = "000000000";
}

std::string BankCard::GetCardNumber() {
    return cardnumber;
}

void BankCard::LinkAccout(CardAccount account) {
    cardnumber = account.GetCardNumber();
}

BankAtm::BankAtm(double starting_cash, std::vector<CardAccount> BaseOfAccounts) {
    cash - starting_cash;
    base = BaseOfAccounts;
}

User::User(std::string fullname, std::string pin, BankCard currentcard, double currentcash) {
    cash = currentcash;
    card = std::move(currentcard);
    pincode = std::move(pin);
    FullName = fullname;
}

User::User() {
    cash = 0;
    pincode = "0000";
}

void User::UseCash(double amount) {
    cash-=amount;
}

void User::CheckCashBalance() const {
    std::cout<<"Current cash is "<<cash;
}

double User::GetCash() {
    return cash;
}

BankCard User::UseBankCard() {
    return card;
}

void User::AddCash(double amount) {
    cash+=amount;
}

void User::LinkCard(CardAccount cardnumber) {
    card.LinkAccout(cardnumber);
}

std::string User::GetName() {
    return FullName;
}

BANK::BANK(std::vector<CardAccount> database, long double money) {
    total_money = money;
    base = std::move(database);
}

BANK::BANK() {
    total_money = 0;
}

std::vector<CardAccount> BANK::AddMoneyToAccount(double amount, std::string recipient, int check) {
    for (auto &acc:base){
        if (acc.GetCardNumber() == recipient){
            acc.AddMoney(amount);
            check = 1;
            return base;
        }
    }
    check = 0;
    return base;
}

void BANK::WithdrawCash(double input) {
    total_money-=input;
}

void BANK::AddCash(double input) {
    total_money+=input;
}

long double BANK::GetScore() {
    return total_money;
}

std::vector<CardAccount> BANK::GetDataBase() {
    return *&base;
}

void BANK::RefreshBase(std::vector<CardAccount> input) {
    base = input;
}
