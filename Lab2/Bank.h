#ifndef UNTITLED1_ATM_H
#define UNTITLED1_ATM_H
#include "fstream"

class UserCard {
private:
	double balance;
	int CardNumber;
	std::string CardHolder;
	int Password;
public:
	void SetCardNumber(int card_number);
	void SetCardHolder(std::string card_holder);
	void SetBalance(double balance);
	void SetPassword(int password);
	int GetCardNumber() const;
	std::string GetCardHolder() const;
	int GetPassword() const;
	double GetBalance() const;
	void SetInfo(std::string path);
};

//class User {
//private:
//public:
//};

class Atm {
private:
public:
	std::ofstream fout;
	std::ifstream fin;
	UserCard cardNow;
	void save(std::string path, UserCard card);
	void setCardNow(std::string path);
	UserCard getCardNow();
	std::string deleteSpaces(std::string path);
	void withdrawal(std::string path, double money);
	void replenishment(std::string path, double money);
	void transfer(std::string pathFrom, std::string pathTo, double money);
	void registerNewCard(int id, std::string name, double balance, int password);
	bool exists(std::string name);
	UserCard operations();
	bool authorization();
public:
	void start();
};

#endif //UNTITLED1_ATM_H