#include "ATMHeader.h"
#include <limits>
#include <ios>
//////////////////////////////////BANK//////////////////////////

void Bank::buildBankBase()
{
	ifstream getBankBase("BankBase.txt");
	string in;
	while (getline(getBankBase, in))
	{
		stringstream info(in);
		string fo;
		client new_client;
		card new_card;
		account new_acc;
		int score = 0;
		while (getline(info, fo, ' '))
		{
			if (!score)
				new_client.setFIO(fo);
			if (score == 1) { // ñ÷åò
				int num[16];
				for (int i = 0; i < 16; i++)
					num[i] = fo[i] - '0';
				new_acc.setAccountsNumber(num);
			}
			if (score == 2) {//êàðòà
				int num[16];
				for (int i = 0; i < 16; i++)
					num[i] = fo[i] - '0';
				new_card.setCardsNumber(num);
			}
			if (score == 3) {
				int num[4];
				for (int i = 0; i < 4; i++)
					num[i] = fo[i] - '0';
				PIN pin;
				pin.setPIN(num);
				new_card.setCardsPIN(pin);
			}
			if (score == 4) {
				new_acc.setAccountsSum(stoi(fo));

				new_card.setCardsAccount(new_acc);
				new_client.setClientsCard(new_card);
				this->client_info.push_back(new_client);
			}
			score++;
		}
		info.clear();
	}
	getBankBase.close();
}
Bank::Bank(session & sss)
{
	this->buildBankBase();
	sss.setUserBank(this);
}


void Bank::addSessionsHistory(session& sss)
{
	string acc_num_str = "";
	account acc = sss.getAcc(); const int* acc_num = acc.getAccountsNumber();
	for (int i = 0; i < 16; i++)
		acc_num_str += acc_num[i] + '0';
	sss.addUserHistory(acc_num_str);
	this->sessions_history.insert(sessions_history.begin(), sss.getUserHistory());
};

void Bank::setClientInfo(session& sss, char flag)
{
	account acc = sss.getAcc();

	for (int i = 0; i < this->client_info.size(); i++)
	{
		client j = this->client_info[i];
		card cl_card = j.getClientsCard(); account cl_acc = cl_card.getCardsAccount();
		for (int k = 0; k < 16; k++)
		{
			if (cl_acc.getAccountsNumber()[k] == acc.getAccountsNumber()[k])
			{
				if (k == 15)
				{
					switch(flag)
					{
					case 'a':
						cl_acc.setAccountsSum(acc.getAccountsSum());	
						cl_card.setCardsAccount(cl_acc); break;
					case 'p':
						cl_card.setCardsPIN(sss.getUserPIN()); break;

					}

					j.setClientsCard(cl_card);

					this->client_info.erase(this->client_info.begin()+i);
					this->client_info.push_back(j);


				}
			}
			else
				k = 16;
		}
	}

};

const vector <client> Bank::getClientHistory()
{
	return this->client_info;
};
const vector<vector <string>> Bank::getWholeHistory()
{
	return this->sessions_history;
};

////////////////////////////////CARD//////////////////////////////

card::card() {};
card::card(session & sss, string cardname)
{
	this->readCard(sss, cardname);
}

void card::setCardsAccount(account account)
{
	this->cards_account = account;
};
void card::setCardsNumber(int* num)
{
	for (int i = 0; i < 16; i++)
		this->cards_number[i] = num[i];
};
void card::setCardsPIN(PIN pin)
{
	this->cards_pin = pin;
};

const account card::getCardsAccount()
{
	return this->cards_account;
};
const int* card::getCardsNumber()
{
	return this->cards_number;
};
const PIN card::getCardsPIN()
{
	return this->cards_pin;
};
void card::readCard(session & sss, string cardname)
{
	ifstream getCard(cardname);
	string in;
	while (getline(getCard, in))
	{
		stringstream info(in);
		string fo;
		client new_client;
		card new_card;
		int score = 0;
		while (getline(info, fo, ' '))
		{
			if (!score)
				new_client.setFIO(fo);
			if (score == 1) {//êàðòà
				int num[16];
				for (int i = 0; i < 16; i++)
					num[i] = fo[i] - '0';
				this->setCardsNumber(num);
			}
			score++;
		}
		new_client.setClientsCard(*this);
		sss.setUser(new_client);
		sss.setUserCard(*this);
	}
};

/// ////////////////////////////PIN/////////////////////////////////


void PIN::setPIN(int* pin)
{
	for (int i = 0; i < 4; i++)
		this->pin[i] = pin[i];
};
const int* PIN::getPIN()
{
	return this->pin;
};

bool PIN::isEqual(const PIN& pin2)
{
	for (int i = 0; i< 4; i++)
	{
		if (this->pin[i] == pin2.pin[i])
		{
			if (i == 3)
				return 1;
		}
		else return 0;
	}
	
};


///////////////////////////ACCOUNT//////////////////////////////////////


void account::setAccountsNumber(int* num)
{
	for (int i = 0; i < 16; i++)
		this->accounts_number[i] = num[i];
};
void account::setAccountsSum(double sum)
{
	this->sum = sum;
};
void account::changeAccountsSum(double sum)
{

	this->sum += sum;
};

const double account::getAccountsSum()
{
	return this->sum;
};
const int* account::getAccountsNumber()
{
	return this->accounts_number;
};


/// ///////////////////////////CLIENT/////////////////////////////

void client::setClientsCard(card card)
{
	this->clients_card = card;
}
void client::setFIO(string fio)
{
	this->FIO = fio;
};

const string client::getFIO()
{
	return this->FIO;
};
const card client::getClientsCard()
{
	return this->clients_card;
};

//bool operator == (client a, client b) {
//	string fio_a = a.FIO; string fio_b = b.FIO;
//	card card_a = a.clients_card, card_b = b.clients_card; 
//	int num_a[16], num_b[16];
//	*num_a = *card_a.getCardsNumber(), *num_b = *card_b.getCardsNumber();
//
//
//	return 0;
//};

//////////////////////////SESSION//////////////////////////////////

void session::clear()
{
	client n;this->user = n;
	account a = {}; this->userAcc = a;
	card c; this->userCard = c;
	vector <string> v; this->user_history = v;
	PIN p; this->userPIN = p;
};

void session::setUser(client& user)
{
	this->user = user;
};
void session::setAcc(account &acc)
{
	this->userAcc = acc;
};
void session::setUserPIN(PIN &pin)
{
	this->userPIN = pin;
};
void session::setUserCard(card& card)
{
	this->userCard = card;
};
void session::setUserBank(Bank *bank)
{
	this->userBank = bank;
};
void session::addUserHistory(string hist)
{
	this->user_history.insert(user_history.begin(),hist);
};

const client session::getUser()
{
	return this->user;
};
const account session::getAcc()
{
	return this->userAcc;
};
const PIN session::getUserPIN()
{
	return this->userPIN;
};
const card session::getUserCard()
{
	return this->userCard;
};
Bank* session::getUserBank()
{
	return this->userBank;
};
const vector<string> session::getUserHistory()
{
	return this->user_history;
};

void session::checkUserInBank()
{
	bool ifExist = 0;
	for (client i : this->userBank->getClientHistory())
		if (i.getFIO() == this->user.getFIO())
		{
			card current = i.getClientsCard();
			const int* curr_num = current.getCardsNumber();
			for (int j = 0; j < 16; j++)
				if (curr_num[j] == this->userCard.getCardsNumber()[j])
				{
					if (j == 15)
					{
						ifExist++;
						account temp = current.getCardsAccount();
						this->setAcc(temp);
						this->userCard.setCardsPIN(current.getCardsPIN());
						this->user.setClientsCard(current);
						this->setUserCard(current);
						this->userPIN = current.getCardsPIN();
					}
				}
				else j = 16; ////////////////////////////////проверить на карточке, которой нет в базе
		}
	if (!ifExist)
	{
		system("cls");
		cout << "This card isn't maintained by the bank\n;"; ///////искл!
	}
};

bool session::askPIN()
{
	Sleep(400); system("cls");
	PIN pin; string str_pin = ""; int int_pin[4];
	while (pin.PIN_attempt != 3)
	{
		pin.PIN_attempt++;
		cout << "Please, insert PIN...\n";
		insertPIN(pin, str_pin, int_pin);
		if (this->userPIN.isEqual(pin))
			return 1;
		else {
			cout << "PIN is incorrect.\nTry again, please\n"; 
			Sleep(2000); system("cls");
		}
	}
	return 0;
};
void session::insertPIN(PIN & pin, string & str_pin, int * int_pin)
{
	str_pin = "";
	cin >> str_pin;
	if (str_pin.size() != 4)
	{
		str_pin = "0000"; //добавить ииииискккл чтоб не было реального искл, потому что оно тут есть!
		return;
	}
		
	for (int i = 0; i < 4; i++)
		int_pin[i] = str_pin[i]-'0';
	pin.setPIN(int_pin);
	
}
//////////////////////////////CM///////////////////////////////


const void cm::showBalanceOnScreen(session& sss)
{
	account temp = sss.getAcc();
	cout << temp.getAccountsSum();
	
	sss.addUserHistory("Checking the balance of the card by showing on the sreen.\n");
};

const void cm::printGeneralInfo(ofstream& file, session &sss)
{
	client user = sss.getUser();
	card users_card = user.getClientsCard();
	account cards_acc = users_card.getCardsAccount(); const int* acc = cards_acc.getAccountsNumber();
	string str_num = "";

	file << "Client: " << user.getFIO() << endl;

	for (int i = 0; i < 16; i++)
		str_num += acc[i] + '0';

	file << "Account: " << str_num << endl;

	str_num = "";
	const int* cards_num = users_card.getCardsNumber();
	for (int i = 0; i < 16; i++)
		str_num += cards_num[i] + '0';

	file << "Card: " << str_num << endl;
};

const void cm::printBalanceInFile(session& sss)
{
	ofstream file("chequeB.txt");

	this->printGeneralInfo(file, sss);
	client user = sss.getUser();
	card users_card = user.getClientsCard();
	account cards_acc = users_card.getCardsAccount();
	file << "Current sum: " << cards_acc.getAccountsSum();

	file.close();
	sss.addUserHistory("Checking the balance of the card by printing the cheque.\n");
};

const void cm::getExtract(session& sss)
{
	/////на экране с выпиской написать о ее стоимости (0,35)
	ofstream file("extract.txt");

	this->printGeneralInfo(file, sss);
	Bank a = *sss.getUserBank();

	file << "Account extract will be charged a fee of 0.35BYN\n";

	account cur_acc = sss.getAcc(); const int* acc_num = cur_acc.getAccountsNumber();
	cur_acc.changeAccountsSum(-0.35); sss.setAcc(cur_acc);

	for (string i : sss.getUserHistory())
		file << i;

	for (vector <string> i : a.getWholeHistory())
	{
		string i_acc_num = i.front();
		for (int j = 0; j < 16; j++)
			if (acc_num[j] != (i_acc_num[j] - '0'))
				j = 16;
		else {
				if(j == 15)
					for (string k : i)
						if (k.back() == '\n')
							file << k;
		}
			
	}

	file << "\nRemaining balance: " << cur_acc.getAccountsSum() << " BYN\n";

	file.close();
	sss.addUserHistory("Getting the extract: -0.35BYN\n");
};

const void cm::printCheque(session& sss, double how_many, char flag)
{
	ofstream cheque;
	switch(flag)
	{
	case 'w':
		cheque.open("chequeW.txt"); break;
	case 'm':
		cheque.open("chequeMB.txt"); break;
	case 't':
		cheque.open("chequeTR.txt"); break;
	case 'p':
		cheque.open("chequePIN.txt"); break;
	}

	this->printGeneralInfo(cheque, sss);

	string sum_str = to_string(how_many), fee_str = to_string(0.015*how_many); 
	string hist; account temp = sss.getAcc(); 
	
	sum_str.resize(6), fee_str.resize(4);
	switch(flag)
	{
	case 'w':
		hist = "Withdrawing  money: -" + sum_str + "BYN \n"; break;
	case 'm':

		hist = "Mobile phone service: -" + sum_str + "BYN \n"; break;
	case 't':
		hist = "Money transfer: -" + sum_str + "BYN \n\tFee: -" + fee_str + "BYN\n"; break;
	case 'p':
		hist = "PIN change: -1.5BYN\n"; break;
	}

	cheque << hist << "\nRemaining balance: " << temp.getAccountsSum() << "BYN \n";
	cheque.close();
};
const void cm::Q_PrintCheque(double how_many, session& sss, char flag)
{
	cout << "Do you want to print a cheque?\n1.Yes\t\t2.No";
	int n = 0; 

	while (n == 0) {
		while (_kbhit()) {
			char ch = _getch();
			if (ch == 0x31 || ch == 0x61)
			{
				Sleep(500);
				this->printCheque(sss, how_many, flag); n++;
				break;
			}
			if (ch == 0x32 || ch == 0x62)
			{
				Sleep(500); n++;
				break;
			}
		}
	}

	//
};

const void cm::getCash(session& sss)
{	
	Sleep(2000); system("cls");
	cout << "Choose the sum you want to obtain: \n1.5 \t" << "5.100\n"
		<< "2.10\t" << "6.200\n"
		<< "3.20\t" << "7.500\n"
		<< "4.50\t" << "8. Other\n";

	int how_many = 0, n = 0; string trash;
	
	
	while (n == 0) {	
		while (_kbhit()){
			char ch = _getch();
			if (ch == 0x31 || ch == 0x61)
			{
				Sleep(500);
				how_many = 5; n++;		 n++;	break;
			}
			if (ch == 0x32 || ch == 0x62)
			{
				Sleep(500);
				how_many = 10;		 n++;	break;
			}
			if (ch == 0x33 || ch == 0x63)
			{
				Sleep(500);
				how_many = 20;	 n++;		break;
			}
			if (ch == 0x34 || ch == 0x64)
			{
				Sleep(500);
				how_many = 50;		 n++;	break;
			}
			if (ch == 0x35 || ch == 0x65)
			{
				Sleep(500);
				how_many = 100;	 n++;		break;
			}
			if (ch == 0x36 || ch == 0x66)
			{
				Sleep(500);
				how_many = 200;		 n++;	break;
			}
			if (ch == 0x37 || ch == 0x67)
			{
				Sleep(500);
				how_many = 500;  n++;
				break;
			}
			if (ch == 0x38 || ch == 0x68)//if (GetKeyState(0x38) || GetKeyState(0x68)) ///другая сумма
			{
				Sleep(500); system("cls"); //how_many = _getch();
				cout << "Insert the sum you want to obtain: \n";

				cin >> how_many; n++;
				break;
			}
		}
	}

	if (how_many % 5)
	{
		Sleep(2000); system("cls");
		cout << "Incorrect sum. Try again.\n";
		getCash(sss);
		return;
	}

	account temp = sss.getAcc(); double sum = temp.getAccountsSum();

	
	if (sum < how_many)
	{
		Sleep(2000); system("cls");
		cout << "Insufficient funds. Try again.\n";
		getCash(sss);
		return;
	}

	temp.changeAccountsSum(-how_many);sss.setAcc(temp); 
	card ctemp = sss.getUserCard(); ctemp.setCardsAccount(temp); sss.setUserCard(ctemp);
	
	Bank* a = sss.getUserBank(); a->setClientInfo(sss, 'a');
	
	Q_PrintCheque(how_many, sss, 'w');

	string sum_str = to_string(how_many);
	string hist = "Withdrawing  money: -" + sum_str + "BYN \n";
	sss.addUserHistory(hist);

};

const void cm::InputPhoneNumber(string& number)
{
	Sleep(2000); system("cls");
	cout << "Input a phone number: \n"; 

	string NPhone; NPhone = _getch();
	cin >> NPhone; number = NPhone;

	if (!(NPhone[0] == '+' && NPhone[1] == '3' && NPhone[2] == '7' && NPhone[3] == '5' 
		&& ((NPhone[4] == '3' && NPhone[5] == '3') || (NPhone[4] == '2' && NPhone[5] == '9') \
			|| (NPhone[4] == '4' && NPhone[5] == '4') || (NPhone[4] == '2' && NPhone[5] == '5')) 
		&& (NPhone.size() == 13)))
	{
		Sleep(2000); system("cls");
		cout << "Incorrect phone number. Try again. \n";

	    return InputPhoneNumber(number);
	}


};
const void cm::MobileCommunications(session& sss)
{
	string number;
	InputPhoneNumber(number);

	Sleep(1500); system("cls");
	cout << "Input the sum you want to put into the phone account: \n";
	double sum; //sum = _getch();
	cin >> sum;
	
	account temp = sss.getAcc();

	Sleep(1500); system("cls");
	cout << "Is it correct?\n\nPhone number: " << number << "\nSum: " << sum; 	
	
	string trash;
	int n = 0;
	
	while (n == 0) {
		while (_kbhit()) {
				char ch = _getch();
			if (ch == 0x31 || ch == 0x61) //норм
			{
				Sleep(500);
				n++;
				break;
			}
			else if (ch == 0x32 || ch == 0x62) //не норм
			{
				Sleep(500);

				return MobileCommunications(sss); //////периодически падает сюда
				n++;
				break;
			}
		}
	}
  
	Sleep(200); system("cls");

	if (sum > temp.getAccountsSum())
	{
		Sleep(2000); system("cls");
		cout << "Incorrect sum. Try again. \n";
		return MobileCommunications(sss);
	}

	temp.changeAccountsSum(-sum); card ctemp = sss.getUserCard();
	ctemp.setCardsAccount(temp); sss.setAcc(temp); sss.setUserCard(ctemp);

	Q_PrintCheque(sum, sss, 'm');

	string sum_str = to_string(sum);sum_str.resize(6);
	string hist = "Mobile phone service: -" + sum_str + "BYN \n";
	sss.addUserHistory(hist);
};

const bool session::checkAccInBank(account& acc, double sum, Bank & bank)
{
	session for_another_acc;
	for_another_acc.userBank = this->userBank;
	for_another_acc.userAcc = acc;


	bool ifExist = 0;
	for (client i : this->userBank->getClientHistory())
	{
		card cl_card = i.getClientsCard(); account cl_acc = cl_card.getCardsAccount(); string transferer_acc_num = "";
		for (int k = 0; k < 16; k++)
		{
			if (cl_acc.getAccountsNumber()[k] == acc.getAccountsNumber()[k])
			{
				transferer_acc_num += this->userAcc.getAccountsNumber()[k] + '0';
				if (k == 15)
				{
					ifExist++;
					cl_acc.changeAccountsSum(sum);
					cl_card.setCardsAccount(cl_acc);
					for_another_acc.userAcc = cl_acc;
					for_another_acc.userCard = cl_card;
					bank.setClientInfo(for_another_acc, 'a');

					string sum_str = to_string(sum); sum_str.resize(6);
					string hist = "Transfer: +" + sum_str + "BYN \n\tTransferer: " + transferer_acc_num + "\n";
					for_another_acc.addUserHistory(hist);
					bank.addSessionsHistory(for_another_acc );
				}
			}
			else k = 16; ////////////////////////////////проверить на карточке, которой нет в базе
		}
		
	}
	if (!ifExist)
	{
		system("cls");
		cout << "This card isn't maintained by the bank\nOperation failed\n"; ///////искл!
		return false;
	}
	else return true;

};
const void cm::TransferOfFunds(session& sss)
{
	Sleep(200); system("cls");

	cout << "Money transfer will be charged a fee of 1.5%\n";

	cout << "Input the number of transferee account: \n";

	string num_str; int num[16]; string string_num = "";
	cin >> num_str;

	for (int i = 0; i < 16; i++)
	{
		num[i] = num_str[i] - '0';
		string_num += num_str[i];
	}
	
	account transferee;
	transferee.setAccountsNumber(num);

	Sleep(200); system("cls");
	cout << "Input the sum you want to transfer:\n"; double sum;
	cin >> sum;

	if (sss.checkAccInBank(transferee, sum, *sss.getUserBank()))
	{
		account main_acc = sss.getAcc(); main_acc.changeAccountsSum(-(sum*1.015)); card main_card = sss.getUserCard();
		main_card.setCardsAccount(main_acc);
		sss.setAcc(main_acc); sss.setUserCard(main_card);

		string sum_str = to_string(sum), fee_str = to_string(sum * 0.015); sum_str.resize(6); fee_str.resize(4);
		string hist = "Transfere: -" + sum_str + "BYN \n\tFee: -" + fee_str + "BYN\n\t" + "Transferee: " + string_num + "\n";
		sss.addUserHistory(hist);

		Q_PrintCheque(sum, sss, 't');
	}
	
};

const PIN cm::InputPIN()
{
	Sleep(200); system("cls");
	string pin_str;
	cout << "Input new PIN:\n";
	cin >> pin_str; PIN userpin; int pin_num[4];
	for (int i = 0; i < 4; i++)
	{
		pin_num[i] = pin_str[i] - '0';

	}
	userpin.setPIN(pin_num);
	return userpin;

}
const void cm::ChangePIN(session& sss)
{
	Sleep(200); system("cls");

	cout << "PIN changing will be charged a fee of 1.5BYN\n";

	PIN currentPIN = sss.getUserPIN(), newPIN;
	if (sss.askPIN())
	{
		bool same = true;
		while (same) {

			newPIN = InputPIN();
			if (currentPIN.isEqual(newPIN)) /////*?????????????????????????????????????
			{
				Sleep(200); system("cls");
				cout << "PINs are equal. Try again.\n"; Sleep(400);
			}
			else {
				same = false;
			}
		}

		Sleep(200); system("cls");
		cout << "Are you sure?\n";

		int n = 0;

		while (n == 0) {
			while (_kbhit()) {
				char ch = _getch();
				if (ch == 0x31 || ch == 0x61) //норм
				{
					Sleep(500);
					n++;
					break;
				}
				else if (ch == 0x32 || ch == 0x62) //не норм
				{
					Sleep(500);

					return ChangePIN(sss); //////периодически падает сюда
					n++;
					break;
				}
			}
		}


		account acc = sss.getAcc(); acc.changeAccountsSum(-1.5); card card = sss.getUserCard(); card.setCardsAccount(acc);  card.setCardsPIN(newPIN); 
		sss.setAcc(acc); sss.setUserCard(card); sss.setUserPIN(newPIN);

		string 	hist = "PIN change: -1.5BYN\n";
		sss.addUserHistory(hist);

		Bank *a = sss.getUserBank();
		a->setClientInfo(sss, 'p');
				
		Q_PrintCheque(1.5, sss, 'p');
	}
};