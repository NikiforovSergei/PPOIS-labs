#pragma once

class IBankCard
{
public:
	virtual bool GetUsing() = 0;
	virtual void SetUse(bool inserted) = 0;
	virtual int GetCardNumber() = 0;
};