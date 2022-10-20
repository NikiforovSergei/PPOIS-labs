#include "ATMHeader.h"
#include "ScreenHeader.h"


////////////////////////////////SCREEN////////////////////////////////////////////////////////////////
screen::screen(session* sss, cm* cmb)
{
	ssss = sss;
	cmbb = cmb;
};

void screen::continue_session(screen* pr_screen)
{
	Sleep(400); system("cls");
	cout << "Do you want to continue?\n1.Yes\t\t\t2.No";

	int n = 0;
	while (n == 0) {
		while (_kbhit()) {
			char ch = _getch();
			if (ch == 0x31 || ch == 0x61)
			{
				Sleep(500);
				return pr_screen->work();
				n++;	break;
			}
			if (ch == 0x32 || ch == 0x62)
			{
				Sleep(500);
				pr_screen->s_is_on = false;
				n++;	break;
			}
		}
	}
};
////////////////////////////////START SCREEN////////////////////////////////////////////////////////////////
void start_screen::read_card()
{
	Sleep(400); system("cls");
	cout << "Please, insert the card...\n";

	string card_name;
	cin >> card_name;

	card(*this->ssss, card_name);
	(*ssss).checkUserInBank();

	account acc = (*ssss).getAcc();
	if (!acc.getAccountsNumber()[0])
		this->is_on = false;
};

start_screen::start_screen(session* sss, cm* cmb) : screen(sss, cmb) { };


void start_screen::work()
{

	if ((*(this->ssss)).askPIN())
	{
		Sleep(400); system("cls");
		cout << "\t\t...Choose the operation...\n1.Check the current balance" << "\t4.Mobile communication service\n"
			<< "2.Get the extract          " << "\t5.Money Transfer\n"
			<< "3.Get cash                 " << "\t6.Change the PIN\n";
											  
		int n = 0;
		while (n == 0) {
			while (_kbhit()) {
				char ch = _getch();

				if (ch == 0x31 || ch == 0x61)
				{
					Sleep(500);
					balance_screen s1(ssss, cmbb, this);
					s1.work();
					if (!s_is_on)
					{
						this->is_on = false;
						return;
					}
					n++;	break;
				}
				if (ch == 0x32 || ch == 0x62)
				{
					Sleep(500);
					extract_screen s1(ssss, cmbb, this);
					s1.work();
					if (!s_is_on)
					{
						this->is_on = false;
						return;
					}
				    n++;	break;
				}
				if (ch == 0x33 || ch == 0x63)
				{
					Sleep(500);
					cash_screen s1(ssss, cmbb, this);
					s1.work();
					if (!s_is_on)
					{
						this->is_on = false;
						return;
					}
					n++;		break;
				}
				if (ch == 0x34 || ch == 0x64)
				{
					Sleep(500);

					mobile_screen s1(ssss, cmbb, this);
					s1.work();

					if (!s_is_on)
					{
						this->is_on = false;
						return;
					}

					n++;
					break;
				}
				if (ch == 0x35 || ch == 0x65)
				{
					Sleep(500);

					transfer_screen s1(ssss, cmbb, this);
					s1.work();

					if (!s_is_on)
					{
						this->is_on = false;
						return;
					}

					n++;
					break;
				}
				if (ch == 0x36 || ch == 0x66)
				{
					Sleep(500);

					change_screen s1(ssss, cmbb, this);
					s1.work();

					if (!s_is_on)
					{
						this->is_on = false;
						return;
					}

					n++;
					break;
				}


				if (ch == 0x37 || ch == 0x67)
				{
					Sleep(500);	
					this->is_on = false;

					n++;	break;
				}

				if (ch == VK_ESCAPE)
				{
					Sleep(500);	
					exit(0);
					n++;	break;
				}
			}
		}


	}
};


///////////////////////////////CASH SCREEN////////////////////////////////////////////////////////////////////////////////////
cash_screen::cash_screen(session* sss, cm* cmb, screen* scr) : screen(sss, cmb) { this->pr_screen = scr; };

void cash_screen::work()
{	
	if ((*(this->ssss)).askPIN())
	{
		(*(this->cmbb)).getCash((*(this->ssss)));
	}

	continue_session(this->pr_screen);
};

////////////////////////////BALANCE SCREEN///////////////////////////////////////////////////////
balance_screen::balance_screen(session* sss, cm* cmb, screen* scr) : screen(sss, cmb) {	this->pr_screen = scr;};


void balance_screen::work()
{

		Sleep(400); system("cls");

		(*(this->cmbb)).showBalanceOnScreen((*(this->ssss)));	

		

		cout << "\nDo you want to print the balance on paper?\n1.Yes\t\t\t2.No";
		int n = 0;
		while (n == 0) {
			while (_kbhit()) {
				char ch = _getch();
				if (ch == 0x31 || ch == 0x61)
				{
					Sleep(500);
					(*(this->cmbb)).printBalanceInFile((*(this->ssss)));
					n++;	break;
				}
				if (ch == 0x32 || ch == 0x62)
				{
					Sleep(500);
					n++;	break;
				}
			}
		}
		continue_session(this->pr_screen);
		
};

////////////////////////////EXTRACT SCREEN///////////////////////////////////////////////////////
extract_screen::extract_screen(session* sss, cm* cmb, screen* scr) : screen(sss,cmb) { this->pr_screen = scr; };

void extract_screen::work()
{
	(*(this->cmbb)).getExtract((*(this->ssss)));
	continue_session(this->pr_screen);
};

////////////////////////////MOBILE COMMUNICATION SERVICE SCREEN///////////////////////////////////////////////////////
mobile_screen::mobile_screen(session* sss, cm* cmb, screen* scr) : screen(sss, cmb) { this->pr_screen = scr; };

void mobile_screen::work()
{
	Sleep(400);
	system("cls");

	(*(this->cmbb)).MobileCommunications((*(this->ssss)));
	continue_session(this->pr_screen);
};

////////////////////////////MONEY TRANSFER SCREEN///////////////////////////////////////////////////////
transfer_screen::transfer_screen(session* sss, cm* cmb, screen* scr) : screen(sss, cmb) { this->pr_screen = scr; };

void transfer_screen::work()
{
	Sleep(400);
	system("cls");

	(*(this->cmbb)).TransferOfFunds((*(this->ssss)));
	continue_session(this->pr_screen);
};

////////////////////////////CHANGE PIN SCREEN///////////////////////////////////////////////////////
change_screen::change_screen(session* sss, cm* cmb, screen* scr) : screen(sss, cmb) { this->pr_screen = scr; };

void change_screen::work()
{
	Sleep(400);
	system("cls");

	(*(this->cmbb)).ChangePIN((*(this->ssss)));
	continue_session(this->pr_screen);
};