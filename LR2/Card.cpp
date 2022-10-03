//
// Created by User on 21.09.2022.
//

#include "Card.h"
#include <fstream>

string Card::getOwner(){
    return owner;
}

void Card::setOwner(const string &owner) {
    Card::owner = owner;
}

int Card::getCardId() const {
    return cardID;
}

void Card::setCardId(int cardId) {
    cardID = cardId;
}

double Card::getBalance() const {
    return balance;
}

void Card::setBalance(double balance) {
    Card::balance = balance;
}

int Card::getPassword() const {
    return password;
}

void Card::setPassword(int password) {
    Card::password = password;
}

void Card::setInfo(string path) {
    ifstream fin;
    fin.open("database\\"+path);
    if(fin.is_open()){
        string buff;
        getline(fin, buff);
        setCardId(atoi(buff.c_str()));
        getline(fin, buff);
        setPassword(atoi(buff.c_str()));
        getline(fin, buff);
        setOwner(buff);
        getline(fin,buff);
        setBalance(stod(buff));
    }
    fin.close();

}
