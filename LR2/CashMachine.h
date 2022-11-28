#pragma once 
#include "IBank.h"
#include "ICashMachine.h"

class BelarusBank : public ICashMachine
{
private:
	int CardNumber = 0;

public:
	void InsertCard(IBankCard& card, IBank& DataOfCard) override;
	void CashByCode(IBank& DataOfCard) override;
	void TransferOfFunds(IBank& DataOfCard) override;
	void CashWithdrawal(IBank& DataOfCard) override;
	void AmountOfMoney(IBank& DataOfCard) override;
	void ReturnCard(IBankCard& card) override;
};


inline void BelarusBank::InsertCard(IBankCard& card, IBank& DataOfCard)
{
	CardNumber = card.GetCardNumber();
	DataOfCard.FindCheck(CardNumber);
	int PIN;
	std::cout << "Write your PIN ";
	std::cin >> PIN;
	if (DataOfCard.CheckPIN(PIN))
	{
		card.SetUse(true);
	}
	else
	{
		std::cout << "Incorrect PIN ";
	}
}

inline void BelarusBank::CashByCode(IBank& DataOfCard)
{
	int PIN;
	int AmountOfMoney = 0;
	std::cout << "Write your PIN from SMS (752789) ";
	std::cin >> PIN;
	if (752789 == PIN)
	{
		std::cout << "Write necessary value of money ";
		std::cin >> AmountOfMoney;

		if (DataOfCard.MoneyInAccount() - AmountOfMoney >= 0)
		{
			DataOfCard.WriteOffMoney(AmountOfMoney);
		}
		else
		{
			std::cout << "Error! You can't take that value of money" << std::endl;
		}
	}
	else
	{
		std::cout << "PIN not right";
	}
}

inline void BelarusBank::TransferOfFunds(IBank& DataOfCard)
{
	int CardNumber = 0;
	int AmountOfMoney = 0;

	std::cout << "Write the number of another card ";
	std::cin >> CardNumber;

	if (DataOfCard.FindCheck(CardNumber))
	{
		std::cout << "Write necessary value of money ";
		std::cin >> AmountOfMoney;

		DataOfCard.CreditMoney(AmountOfMoney);
		DataOfCard.FindCheck(this->CardNumber);

		if (DataOfCard.MoneyInAccount() - AmountOfMoney >= 0)
		{
			DataOfCard.WriteOffMoney(AmountOfMoney);
		}
		else
		{
			std::cout << "Error! You can't send that value of money" << std::endl;
			DataOfCard.FindCheck(CardNumber);
			DataOfCard.WriteOffMoney(AmountOfMoney);
			DataOfCard.FindCheck(this->CardNumber);
		}
	}
}

inline void BelarusBank::CashWithdrawal(IBank& DataOfCard)
{
	int PIN;
	int AmountOfMoney;

	std::cout << "Write your PIN ";
	std::cin >> PIN;

	if (DataOfCard.CheckPIN(PIN))
	{
		std::cout << "Write necessary value of money ";
		std::cin >> AmountOfMoney;

		if (DataOfCard.MoneyInAccount() - AmountOfMoney >= 0)
		{
			DataOfCard.WriteOffMoney(AmountOfMoney);
		}
		else
		{
			std::cout << "Error! You can't take that value of money";
		}
	}
	else
	{
		std::cout << "PIN not right";
	}
}

inline void BelarusBank::AmountOfMoney(IBank& DataOfCard)
{
	std::cout << "Money " << DataOfCard.MoneyInAccount();
}

inline void BelarusBank::ReturnCard(IBankCard& card)
{
	card.SetUse(false);
	CardNumber = 0;
}