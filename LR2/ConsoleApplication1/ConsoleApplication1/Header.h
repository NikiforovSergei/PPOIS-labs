#pragma once
#ifndef __BANKOMAT_H__
#define __BANKOMAT_H__
#define ATTEMPTS 3
#include <iostream>
#include <string>

class Card 
{
public:
	Card();
	Card(const long& number, const int& cvv, const std::string& data);
	long get_card_number() const;
	int get_cvv() const;
	std::string get_data() const;
private:
	int cvv;
	std::string data;
	long number;
};

class Account 
{
public:
	Account();
	Account(const long& number,const double& balance);

	double get_balance() const;
	long get_number() const;
	void increase_balance(const double& money);
	void decrease_balance(const double& money);
private:
	long number;
	double balance;
};

class Client
{
public:
	Client(const int& pin_code, const Card& card,const Account& account);

	int get_pin() const;
	Card get_card() const;
	Account& get_account();
private:
	int pin_code;
	Card card;
	Account account;
};

class Repository
{
public:
	Repository();
	Repository(const long& money);

	void get_money(const double& money);
	void put_money(const double& money);
	double amount_money() const;
private:
	long money;
};

class Screen
{
public:
	virtual void show_info(Client& client) = 0;
};

class InputPinScreen : public Screen
{
public:
	InputPinScreen();

	void show_info(Client& client) override;
	bool check_pin();
private:
	bool pin_checker;
};

class CheckBalanceScreen : public Screen
{
public:
	void show_info(Client& client) override;
};

class PutMoneyScreen : public Screen
{
public:
	PutMoneyScreen();

	void show_info(Client& client) override;
	double get_prescribed_money();
private:
	double money;
};

class GetMoneyScreen : public Screen
{
public:
	GetMoneyScreen();

	void show_info(Client& client) override;
	double get_withdrawn_money();
private:
	double money;
};

class Bankomat
{
public:
	Bankomat(const Repository& repository);

	
	void put_money(Client& client);
	void get_money(Client& client);
	void check_balance(Client& client);
private:
	Repository repository;

	bool put_pin_checker(Client& client);
	InputPinScreen input_pin_screen;
	CheckBalanceScreen check_balance_screen;
	PutMoneyScreen put_money_screen;
	GetMoneyScreen get_money_screen;

};

#endif