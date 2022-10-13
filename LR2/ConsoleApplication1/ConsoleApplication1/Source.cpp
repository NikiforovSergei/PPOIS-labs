#include "Header.h"

Card::Card()
{
	this->cvv = 0;
	this->data = "";
	this->number = 0;
}
Card::Card(const long& number, const int& cvv, const std::string& data)
{
	this->number = number;
	this->cvv = cvv;
	this->data = data;
}
long Card::get_card_number() const { return this->number; }
int Card::get_cvv() const { return this->cvv; }
std::string Card::get_data() const { return this->data; }


Account::Account()
{
	this->balance = 0;
	this->number = 0;
}
Account::Account(const long& number, const double& balance)
{
	this->number = number;
	this->balance = balance;
}
double Account::get_balance() const { return this->balance; }
long Account::get_number() const { return this->number; }
void Account::increase_balance(const double& money) { this->balance += money; }
void Account::decrease_balance(const double& money) { this->balance -= money; }



Client::Client(const int& pin_code, const Card& card, const Account& account)
{
	this->pin_code = pin_code;
	this->account = account;
	this->card = card;
}
int Client::get_pin() const { return this->pin_code; }
Card Client::get_card() const { return this->card; }
Account& Client::get_account() { return this->account; }



Repository::Repository() { this->money = 0; }
Repository::Repository(const long& money) { this->money = money; }
void Repository::get_money(const double& money) { this->money -= money; }
void Repository::put_money(const double& money) { this->money += money; }
double Repository::amount_money() const { return this->money; }



InputPinScreen::InputPinScreen() { this->pin_checker = false; }
void InputPinScreen::show_info(Client& client)
{
	int pin;
	std::cout << "Введите пин-код: ";
	try
	{
		for (int i = 0; i < ATTEMPTS; i++)
		{
			std::cin >> pin;
			if (pin == client.get_pin())
			{
				std::cout << "Доступ разрешён" << std::endl;
				this->pin_checker = true;
				return;
			}
			else
				std::cout << "Неверный пин код: " << std::endl;
		}
		throw 101;
	}
	catch (int i)
	{
		std::cout << "Ошибка №" << i << " - Ошибка доступа" << std::endl;
	}
}
bool InputPinScreen::check_pin() { return this->pin_checker; }



void CheckBalanceScreen::show_info(Client& client) { std::cout << "На счету: " << client.get_account().get_balance() << std::endl; }


PutMoneyScreen::PutMoneyScreen() { this->money = 0; }
double PutMoneyScreen::get_prescribed_money() { return this->money; }
void PutMoneyScreen::show_info(Client& client)
{
	double money;
	std::cout << "Введите сумму для пополнения: ";
	std::cin >> money;
	try {
		if (money < 0)
			throw 103;
	}
	catch (int i) { std::cout << "Ошибка №" << i << " - Ошибка ввода" << std::endl; }
	this->money = money;
	client.get_account().increase_balance(money);
}

GetMoneyScreen::GetMoneyScreen() { this->money = 0; }
double GetMoneyScreen::get_withdrawn_money() { return this->money; }
void GetMoneyScreen::show_info(Client& client)
{
	double money;
	std::cout << "Введите сумму для вывода: ";
	std::cin >> money;
	try {
		if (money < 0)
			throw 103;
	}
	catch (int i) { std::cout << "Ошибка №" << i << " - Ошибка ввода" << std::endl; }
	try {
		if (money > client.get_account().get_balance())
			throw 104;
		else
			this->money = money;
	}
	catch (int i) { std::cout << "Ошибка №" << i << " - На счете недостаточно средств" << std::endl; }
}

Bankomat::Bankomat(const Repository& repository)
{
	this->repository = repository;
}
bool Bankomat::put_pin_checker(Client& client)
{
	if (!input_pin_screen.check_pin())
	{
		input_pin_screen.show_info(client);
		return input_pin_screen.check_pin();
	}
	return true;
}
void Bankomat::put_money(Client& client)
{
	if (put_pin_checker(client))
	{
		put_money_screen.show_info(client);
		repository.put_money(put_money_screen.get_prescribed_money());
		return;
	}

}
void Bankomat::get_money(Client& client)
{
	if (put_pin_checker(client))
	{
		get_money_screen.show_info(client);
		try
		{
			if (repository.amount_money() < get_money_screen.get_withdrawn_money())
			{
				std::cout << "Текущий баланс хранилища: " << repository.amount_money() << std::endl;
				throw 102;
			}
			else
			{
				client.get_account().decrease_balance(get_money_screen.get_withdrawn_money());
				repository.get_money(get_money_screen.get_withdrawn_money());
			}
		}
		catch (int i)
		{
			std::cout << "Ошибка №" << i << " - В хранилище недостаточно средств" << std::endl;
		}
	}

}
void Bankomat::check_balance(Client& client)
{
	if (put_pin_checker(client))
		check_balance_screen.show_info(client);


}
