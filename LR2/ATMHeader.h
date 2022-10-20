#pragma once
using namespace std;

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <clocale>
#include <iomanip>

class account;
class card;
class cm;
class PIN;
class Bank;
class client;
class session;

/// ///////////////////////////ACCOUNT///////////////////////////////

class account
{
private:
	double sum;
	int accounts_number[16];
public:
	void setAccountsNumber(int* num);
	void setAccountsSum(double sum);
	void changeAccountsSum(double sum);

	const double getAccountsSum();
	const int* getAccountsNumber();

};

/// //////////////////////////////PIN//////////////////////////////////

class PIN
{
private:
	int pin[4];
public:
	void setPIN(int* pin);
	const int* getPIN();
	bool isEqual(const PIN& pin2);
	int PIN_attempt = 0;

};


/// ///////////////////////////////CARD////////////////////////


class card
{
private:
	account cards_account;
	int cards_number[16];
	PIN cards_pin;
public:
	card();
	card(session & sss, string cardname);

	void setCardsAccount(account account);
	void setCardsNumber(int* num);
	void setCardsPIN(PIN pin);

	const account getCardsAccount();
	const int* getCardsNumber();
	const PIN getCardsPIN();

	void readCard(session &sss, string cardname);
};

/// ////////////////////////CLIENT/////////////////////////////////////////

class client
{
private:
	string FIO;
	card clients_card;
public:
	void setFIO(string fio);
	void setClientsCard(card card);

	const string getFIO();
	const card getClientsCard();
};
/// <summary>
/// //////////////////////////////SESSION//////////////////////////////
/// </summary>
class session
{
private:
	account userAcc;
	PIN userPIN;
	client user;
	card userCard;
	Bank *userBank;
	vector<string> user_history;

	void insertPIN(PIN& pin, string& str_pin, int* int_pin);


public:

	//~session();
	void clear();
	void setUser(client &user);
	void setAcc(account &acc);
	void setUserPIN(PIN &pin);
	void setUserCard(card &card);
	void setUserBank(Bank *bank);
	void addUserHistory(string hyst);

	const client getUser();
	const account getAcc();
	const PIN getUserPIN();
	const card getUserCard();
    Bank* getUserBank();
	const vector<string> getUserHistory();

	void checkUserInBank();
	const bool checkAccInBank(account& acc, double sum, Bank& bank);

	bool askPIN(); //////// будет аргументом функции для запуска банкомата

};

/// ///////////////////////////////////BANK////////////////////////

class Bank
{
private:
	vector <client> client_info;
	vector <vector<string>> sessions_history;
public:
	Bank(session &sss);
	void buildBankBase();

	void setLink(session& sss);
	void addSessionsHistory(session& sss);
	void setClientInfo(session& sss, char flag);

	const vector<vector <string>> getWholeHistory();
	const vector <client> getClientHistory();
};
//////////////////////////////////CM//////////////////////////
class cm
{
private:
	const void printGeneralInfo(ofstream& file, session& sss);
	const void printCheque(session & sss, double how_many, char flag);
	const void InputPhoneNumber(string& number);
	const void Q_PrintCheque(double how_many, session& sss, char flag);

public:

	const void showBalanceOnScreen(session & sss);
	const void printBalanceInFile(session& sss);
	const void getExtract(session& sss);

	const void getCash(session& sss);

	const void MobileCommunications(session& sss);

	const void TransferOfFunds(session& sss);

	const PIN InputPIN();
	const void ChangePIN(session& sss);
};