#include "bankomat.h"

class start_screen;
class cash_screen;
class screen;
class balance_screen;


//////////////////////////////////// SCREEN////////////////////////////////////////////////////////////////

class screen
{
protected:
	session* ssss;
	cm* cmbb;
public:
	screen(session* sss, cm* cmb);
	virtual void work() {};
	bool s_is_on = true;
	void continue_session(screen* pr_screen);
};

///////////////////////////////START SCREEN///////////////////////////////////////////////////////
class start_screen : public screen
{
public:
	bool is_on = true;

	void work();

	void read_card();


	start_screen(session* sss, cm* cmb);


};

///////////////////////////////CASH SCREEN////////////////////////////////////////////////////////////////////////////////////
class cash_screen : public screen
{
public:
	screen* pr_screen;
	cash_screen(session* sss, cm* cmb, screen* scr);


	void work();
};

////////////////////////////BALANCE SCREEN///////////////////////////////////////////////////////
class balance_screen : public screen
{
public:
	screen* pr_screen;

	balance_screen(session* sss, cm* cmb, screen* scr);

	void work();
};

////////////////////////////EXTRACT SCREEN///////////////////////////////////////////////////////
class extract_screen : public screen
{
public:
	screen* pr_screen;
	extract_screen(session* sss, cm* cmb, screen* scr);

	void work();
};

///////////////////////////MOBILE COMMUNICATION SERVICE SCREEN///////////////////////////////////////////////////////
class mobile_screen : public screen
{
public:
	screen* pr_screen;
	mobile_screen(session* sss, cm* cmb, screen* scr);

	void work();
};

////////////////////////////MONEY TRANSFER SCREEN///////////////////////////////////////////////////////
class transfer_screen : public screen
{
public:
	screen* pr_screen;
	transfer_screen(session* sss, cm* cmb, screen* scr);

	void work();
};

////////////////////////////MONEY TRANSFER SCREEN///////////////////////////////////////////////////////
class change_screen : public screen
{
public:
	screen* pr_screen;
	change_screen(session* sss, cm* cmb, screen* scr);

	void work();
};