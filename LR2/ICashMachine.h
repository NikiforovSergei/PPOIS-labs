#pragma once
#include "IBank.h"
#include "IBankCard.h"

class ICashMachine
{
public:
	virtual void InsertCard(IBankCard& card, IBank& DataOfCar) = 0;
	virtual void CashByCode(IBank& DataOfCard) = 0;
	virtual void TransferOfFunds(IBank& DataOfCard) = 0;
	virtual void CashWithdrawal(IBank& DataOfCard) = 0;
	virtual void AmountOfMoney(IBank& DataOfCard) = 0;
	virtual void ReturnCard(IBankCard& card) = 0;
};
