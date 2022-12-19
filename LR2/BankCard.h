#pragma once
#include "IBankCard.h"

class BankCard : public IBankCard
{
private:
	bool IUsing;
	int CardNumber;

public:
	BankCard(int CardNumber = 0)
	{
		this->CardNumber = CardNumber;
		IUsing = false;
	}

	void SetUse(bool inserted) override;
	bool GetUsing() override;
	int GetCardNumber() override;
};

inline void BankCard::SetUse(bool inserted)
{
	IUsing = inserted;
}

inline bool BankCard::GetUsing()
{
	return IUsing;
}

inline int BankCard::GetCardNumber()
{
	return CardNumber;
}