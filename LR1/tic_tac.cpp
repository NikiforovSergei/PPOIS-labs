//
// Created by Admin on 04.09.2022.
//

#include "tic_tac.h"

using namespace std;

//Вывод правил в начале игры
void print_rools()
{
	string rools = "\t\t===Игра крестики нолики===\n -- Игроки по очереди ставят на свободные клетки поля знаки(один всегда крестики, другой всегда нолики).\n"
		" -- Размеры игрового поля задаются игроками в начале игры.\n"
		" -- Первый, выстроивший в ряд своих фигуры по вертикали, горизонтали или диагонали, выигрывает.\n"
		" -- В качестве размера необходимо ввести целое число. Минимальный размер поля - 3x3.\n"
		" -- Чтобы поставить знак в какое-то поле необходимо ввести его номер.\n"
		" -- Программа сама определит победителя или ничью (ничья объявится, если все ходы исчерпаны).\n"
		" -- Первым ходит игрок, который ставит нолики.\n"
		" -- Очередь от одного игрока к другому переходит автоматически.\n";
	cout << rools[0] << rools[1];
	for (int i = 2; i < rools.size(); i++)
	{
		cout << rools[i];
		Sleep(6);
	}
	system("pause");
}

string play_tic_tac_toe()
{
	print_rools();
	int size;
	std::cout << "Введите размер поля:\t";
	std::cin >> size;
	while ((std::cin.fail()) || (size <= 2))
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "Введите размер поля ещё раз\t";
		std::cin >> size; std::cout << std::endl;
	}
	tic_tac tic_tac_toe(size);
	return tic_tac_toe.play();
}

//Конструктор клетки
tic_tac::cell::cell(tic_tac::cell_conditions cond)
{
	this->cell_condition = cond;
}

//Оператор присваивания cell
tic_tac::cell& tic_tac::cell::operator=(const cell& other)
{
	this->cell_condition = other.cell_condition;
	return *this;
}

//Конструктор копирования класса cell
tic_tac::cell::cell(const cell& other)
{
	this->cell_condition = other.cell_condition;
}

//Проверка пуста ли клетка
bool tic_tac::cell::is_empty()
{
	return cell_condition == Empty;
}

//Проверка пуста ли клетка (константный метод)
bool tic_tac::cell::is_empty() const
{
	return cell_condition == Empty;
}

//Проверка определяющая, можно ли поместить знак cond в клетку (константный метод)
bool tic_tac::cell::is_condition(cell_conditions cond)
{
	return cell_condition == cond;
}

//Проверка определяющая, можно ли поместить знак cond в клетку (константный метод)
bool tic_tac::cell::is_condition(cell_conditions cond) const
{
	return cell_condition == cond;
}

//Служебный метод имитирующий переход хода другому игроку (вызывается после хода другого игрока)
void tic_tac::change_turn()
{
	turn == Noughts ? turn = Crosses : turn = Noughts;
}

//Служебный метод для получения размера игрового поля
int tic_tac::size()
{
	return field.size();
}

//Перегруженный оператор для ввывода игрового поля в консоль
std::ostream& operator<<(std::ostream& out, const tic_tac& tt)
{
	for (int columns = 0; columns < tt.field.size(); columns++)
	{
		cout << " " << columns + 1;
	}
	cout << endl;

	for (int i = 0; i < tt.field.size(); i++)
	{
		cout << i + 1;
		for (int j = 0; j < tt.field.size(); j++)
		{
			if (tt[i][j].is_empty())  out << " ";
			else
			{
				if (tt[i][j].is_condition(tic_tac::cell_conditions::Noughts)) out << "O";
				else out << "X";
			}
			if (j != tt.field.size() - 1) out << "|";
		}
		out << "\n";
		if (i != tt.field.size() - 1)
		{
			out << " ";
			for (int k = 0; k < tt.field.size() - 1; k++)
			{
				out << "-+";
			}
			out << "-\n";
		}
	}
	return out;
}

//Перегруженный оператор ввода номера клетки, в которую пользователь хочет вставить знак
std::istream& operator>>(std::istream& in, tic_tac& tt)
{
	int string_number, column_number;
	cout << "Введите номер строки : \t";
	in >> string_number; cout << "Введите номер столбика:\t"; cin.clear();
	in >> column_number; cout << endl;
	tt.check_input(string_number, column_number);
	tt.use_cell(string_number, column_number);
	return in;
}

//Служебный метод записывающий крестик / нолик в ячейку выбранную игроком
void tic_tac::use_cell(int string_number, int column_number)
{
	if (turn == Noughts)
	{
		(*this)[string_number - 1][column_number - 1].cell_condition = Noughts;
	}
	else
	{
		(*this)[string_number - 1][column_number - 1].cell_condition = Crosses;
	}
}

//Служебный метод для ввода пользователем номера ячейки
//void tic_tac::input_cell_number(int& string_number, int& column_number)
//{
//	string turn_str;
//	turn == Noughts ? turn_str = "ноликов" : turn_str = "крестиков";
//	cout << "Ход " + turn_str + ". Введите номер клетки, чтобы сделать ход.\nВведите номер строки:\t";
//	cin >> string_number; cout << "Введите номер столбика:\t"; cin.clear();
//	cin >> column_number; cout << endl;
//	check_input(string_number, column_number);
//}

//Служебный метод для проверки на ошибку ввода
void tic_tac::check_input(int& string_number, int& column_number, int fail_counter, bool index_error)
{
	while ((cin.fail()) || (index_error))
	{
		index_error = false;
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Ошибка ввода!\n Введите номер строки:\t";
		cin >> string_number; cout << "Введите номер столбика:\t";
		cin >> column_number; cout << endl;

		fail_counter++;
		if (fail_counter == 6)
		{
			fail_counter = 0;
			system("cls");
			cout << (*this);
		}
	}
	try
	{
		if ((*this)[string_number - 1].at(column_number - 1).is_empty()) return;
		else
		{
			index_error = true;
			cout << "Эта клетка уже используется" << endl;
			check_input(string_number, column_number, fail_counter + 1, index_error);
		}
	}
	catch (const std::exception&)
	{
		index_error = true;
		cout << "Введите корректное значение клетки!" << endl;
		check_input(string_number, column_number, fail_counter + 1, index_error);
	}
}

//Служебный метод для проверки на выйгрыш игрока(объединяет результат проверок).
bool tic_tac::check_for_win()
{
	bool main_diagonal, secondary_diagonal, horizontal, vertical;

	thread main_diagonal_tread([&]() { main_diagonal = chech_for_main_diagonal_combination(); });
	thread secondary_daigonal_thread([&]() { secondary_diagonal = chech_for_secondary_diagonal_combination(); });
	thread horizontal_thread([&]() { horizontal = chech_for_horizontal_combination(); });
	vertical = chech_for_vertical_combination();

	main_diagonal_tread.join(); secondary_daigonal_thread.join(); horizontal_thread.join();

	return (main_diagonal || secondary_diagonal || horizontal || vertical);
}

//Служебный метод для проверки на наличие выйгрышной комбинации по горизонтали.
bool tic_tac::chech_for_horizontal_combination()
{
	for (int str = 0; str < size(); str++)
	{
		size_t counter = 0;
		for (int col = 0; col < size(); col++)
		{
			if (!(*this)[str][col].is_condition(turn)) break;
			counter++;
		}
		if (counter == size()) return true;
	}
	return false;
}


//Служебный метод для проверки на наличие выйгрышной комбинации по вертикали.
bool tic_tac::chech_for_vertical_combination()
{
	for (int col = 0; col < size(); col++)
	{
		size_t counter = 0;
		for (int str = 0; str < size(); str++)
		{
			if (!(*this)[str][col].is_condition(turn)) break;
			counter++;
		}
		if (counter == size()) return true;
	}
	return false;
}

//Служебный метод для проверки на наличие выйгрышной комбинации по диагонали (левый верхний угол -> правый нижний угол).
bool tic_tac::chech_for_main_diagonal_combination()
{
	for (int main_daigonal = 0; main_daigonal < size(); main_daigonal++)
	{
		if (!(*this)[main_daigonal][main_daigonal].is_condition(turn)) return false;
	}
	return true;
}

//Служебный метод для проверки на наличие выйгрышной комбинации по диагонали (правый верхний угол -> левый нижний угол).
bool tic_tac::chech_for_secondary_diagonal_combination()
{
	for (int secondary_daigonal = 0; secondary_daigonal < size(); secondary_daigonal++)
	{
		if (!(*this)[secondary_daigonal][(size() - 1) - secondary_daigonal].is_condition(turn)) return false;
	}
	return true;
}

//Служебный метод для вывода сообщения о выйгрыше
string tic_tac::winner_message()
{
	system("cls");
	cout << (*this);
	if (turn == Noughts) return "Нолики победили!\n\t\t===WINNER WINNER===\n\t\t===CHICKEN DINNER===";
	else return "Крестики победили!\n\t\t===WINNER WINNER===\n\t\t===CHICKEN DINNER===";
}


//Конструктор игрового поля
tic_tac::tic_tac(int size)
{
	turn = Noughts;
	if (size <= 2) throw exception("ValueError");
	field.resize(size);
	for (int i = 0; i < size; i++)
	{
		field[i].resize(size);
		for (int j = 0; j < size; j++)
		{
			field[i][j] = cell();
		}
	}
}

//Конструктор копирования игрового поля
tic_tac::tic_tac(const tic_tac& other)
{
	this->turn = other.turn;
	this->field.resize(other.field.size());
	for (int i = 0; i < other.field.size(); i++)
	{
		this->field[i].resize(other.field[i].size());
		for (int j = 0; j < other.field[i].size(); j++)
		{
			(*this)[i][j] = other[i][j];
		}
	}
}

//Индексация поля (т.к. поле представлено матрицей индексация вернёт вектор, соответсвующий строке по указанному индексу в матрице)
std::vector<tic_tac::cell>& tic_tac::operator[](int index)
{
	if ((index < 0) || (index >= size()))
	{
		throw exception("IndexError");
	}
	return field[index];
}

//Индексация поля {константный метод} (т.к. поле представлено матрицей индексация вернёт вектор, соответсвующий строке по указанному индексу в матрице)
std::vector<tic_tac::cell> tic_tac::operator[](int index) const
{
	if ((index < 0) || (index >= field.size()))
	{
		throw exception("IndexError");
	}
	return field[index];
}

//Непосредственно игровой процесс с очерёдностью хода (начинают нолики (Noughts))
string tic_tac::play()
{
	for (int move = 0; move < size() * size(); move++)
	{
		system("cls");
		int string_number, column_number;
		cout << *this;

		string turn_str;
		turn == Noughts ? turn_str = "ноликов" : turn_str = "крестиков";
		cout << "Ход " + turn_str + ". Введите номер клетки, чтобы сделать ход.\n";
		cin >> *this;

		if (move + 1 >= size() * 2 - 1) // move + 1 делает количество ходов похожим на человеческий счёт
		{
			if (check_for_win())
			{
				system("cls");
				cout << *this;
				return winner_message();
			}
		}
		change_turn();
	}

	system("cls");
	cout << *this;
	return "\t\t===Ничья. В этот раз у нас нет победителя.===\n\n\n";
}

//Деструктор
//tic_tac::~tic_tac()
//{
//	field.clear();
//}