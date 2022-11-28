#pragma once

class IBank
{
public:
	void virtual WriteOffMoney(int amount) = 0;
	void virtual CreditMoney(int amount) = 0;

	int virtual MoneyInAccount() = 0;
	bool virtual CheckPIN(int PIN) = 0;

	void virtual SayPIN() = 0;

	bool virtual FindCheck(int CardNumber) = 0;
};
