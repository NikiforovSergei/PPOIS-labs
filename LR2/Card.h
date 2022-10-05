//
// Created by User on 21.09.2022.
//

#ifndef PPOIS_LAB2_CARD_H
#define PPOIS_LAB2_CARD_H

#include <string>

using namespace std;

class Card {
private:
    string owner;
    int cardID;
    double balance;
    int password;
public:
    string getOwner();

    void setOwner(const string &owner);

    int getCardId() const;

    void setCardId(int cardId);

    double getBalance() const;

    void setBalance(double balance);

    int getPassword() const;

    void setPassword(int password);

    void setInfo(string path);
};


#endif //PPOIS_LAB2_CARD_H
