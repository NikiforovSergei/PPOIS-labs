#pragma once
#include <fstream>
#include "IBank.h"

class Bank : public IBank
{
private:
	int ÑardDatas[6];
	int IndexOfPIN = 0;
	int IndexOfCheck = 0;

public:
	Bank()
	{
		std::ifstream fs;
		int iteration = 0;
		int currentData = 0;
		fs.open("BankData.txt", std::ios::in);

		while (fs)
		{
			fs >> currentData;
			ÑardDatas[iteration] = currentData;
			iteration++;
		}

		fs.close();
	}

	~Bank()
	{
		std::ofstream fs;
		int iteration = 0;
		int currentData = 0;
		fs.open("BankData.txt", std::ios::out);

		for (int data : this->ÑardDatas)
		{
			fs << data << " ";
		}

		fs.close();
	}

	void WriteOffMoney(int amount) override;
	void CreditMoney(int amount) override;
	int MoneyInAccount() override;
	bool CheckPIN(int PIN) override;
	void SayPIN() override;
	bool FindCheck(int CardNumber) override;
};

inline void Bank::WriteOffMoney(int amount)
{
	if (ÑardDatas[IndexOfCheck] - amount >= 0)
	{
		ÑardDatas[IndexOfCheck] = ÑardDatas[IndexOfCheck] - amount;
		std::cout << "Ok";
	}
	else
	{
		std::cout << "Failed operation";
	}
}

inline void Bank::CreditMoney(int amount)
{
	ÑardDatas[IndexOfCheck] = ÑardDatas[IndexOfCheck] + amount;
}

inline int Bank::MoneyInAccount()
{
	return ÑardDatas[IndexOfCheck];
}

inline bool Bank::CheckPIN(int PIN)
{

	if (ÑardDatas[IndexOfPIN] == PIN)
	{
		return true;
	}
	return false;
}

inline void Bank::SayPIN()
{
	std::cout << "Your PIN is " << ÑardDatas[IndexOfPIN];
}

inline bool Bank::FindCheck(int CardNumber)
{
	int iterations = 0;
	for (int CardNumbers : this->ÑardDatas)
	{
		if (CardNumbers == CardNumber)
		{
			IndexOfPIN = ++iterations;
			IndexOfCheck = ++iterations;
			return true;
		}
		iterations++;
	}
	std::cout << "Check not found";
	return false;
}