#include "bankomat.h"

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
	std::cout << "Введите пин код: ";
	for (int i = 0; i < ATTEMPTS; i++)
	{
		std::cin >> pin;
		if (pin == client.get_pin())
		{
			std::cout << "Успешно" << std::endl;
			this->pin_checker = true;
			return;
		}
		else
			std::cout << "Повторите попытку: " << std::endl;
	}
	throw std::invalid_argument("Неверное значение");
}
bool InputPinScreen::check_pin() { return this->pin_checker; }



void CheckBalanceScreen::show_info(Client& client) { std::cout << "Ваш баланс: " << client.get_account().get_balance() << std::endl; }


PutMoneyScreen::PutMoneyScreen() { this->money = 0; }
double PutMoneyScreen::get_prescribed_money() { return this->money; }
void PutMoneyScreen::show_info(Client& client)
{
	double money;
	std::cout << "Введите сумму, которую хотите положить: ";
	std::cin >> money;
	if (money < 0)
		throw std::invalid_argument("Неверное значение");
	this->money = money;
	client.get_account().increase_balance(money);
}

GetMoneyScreen::GetMoneyScreen() { this->money = 0; }
double GetMoneyScreen::get_withdrawn_money() { return this->money; }
void GetMoneyScreen::show_info(Client& client)
{
	double money;
	std::cout << "Введите сумму, которую хотите снять: ";
	std::cin >> money;
	if (money < 0)
		throw std::invalid_argument("Неверное значение");
	if (money > client.get_account().get_balance())
		throw std::invalid_argument("Неверное значние");
	else
		this->money = money;
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
		if (repository.amount_money() < get_money_screen.get_withdrawn_money())
		{
			std::cout << "Ваш баланс: " << repository.amount_money() << std::endl;
			throw std::invalid_argument("Неверное значение");
		}
		else
		{
			client.get_account().decrease_balance(get_money_screen.get_withdrawn_money());
			repository.get_money(get_money_screen.get_withdrawn_money());
		}

	}

}
void Bankomat::check_balance(Client& client)
{
	if (put_pin_checker(client))
		check_balance_screen.show_info(client);


}

void Bankomat::cc(Client& client)
{
	if (put_pin_checker(client)) {
		Card card;
		std::cout << client.get_card().get_card_number() << std::endl;
		std::cout << client.get_card().get_data() << std::endl;
		std::cout << client.get_card().get_cvv() << std::endl;
	}
}
