#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <new>


#define N					3
#define decLifePlant		10
#define decLifeMamale		20
#define MAX_LIFE			100
#define MAX_STEPS_HUNGRY	3
#define MAX_SELL			4

int cycles = 20;
bool is_running = true;

enum class_predator {
	FOX,
	WOLF,
	BEAR,
	MAX_CLASS_PREDATOR
};

enum class_herbivorous {
	RABBIT,
	GOAT,
	DEER,
	MAX_CLASS_HERBIVOROUS
};

enum state {
	EMPTY,
	PLANTS,
	HERBIVOROUS,
	PREDATOR,
	MAX_STATES
};

class living;
typedef living* world[N][N][MAX_SELL];

class living {

public:

	virtual state who() = 0;
	virtual living* next(world w) = 0;
	virtual living* copy(world w) = 0;
	virtual char designation() = 0;
	virtual int get_age() = 0;
	virtual int get_move() = 0;
	virtual int get_hungry() = 0;
	virtual int get_size() = 0;
	virtual int get_step() = 0;
	virtual int get_name_class() = 0;
	virtual char gend() = 0;
	char set_gender(char g);
	char gender; //f-female , m-male

protected:

	int row, column, sell;
	void sums(world w, int sm[]);
	int dice_roll(int range);

};

void living::sums(world w, int sm[]) {
	//подсчет количества видов существ в ячейке
	sm[EMPTY] = sm[PLANTS] = sm[HERBIVOROUS] = sm[PREDATOR] = 0;

	for (int k = 0; k < MAX_SELL; k++)
		sm[w[row][column][k]->who()]++;

}

int living::dice_roll(int range) {

	int diceValue = 0;

	diceValue = rand() % range;

	return diceValue;
}

char living::set_gender(char g) {

	gender = g;
	return gender;

}

class predator : public living {

public:

	predator(int r, int c, int s, int a = MAX_LIFE, char g = '.', int m = 1, int h = 0, class_predator name = FOX, int sz = 10)
		:life(a), gender(g), move(m), hungry(h), name_class(name), size(10) {

		row = r; column = c; sell = s;
		switch (name_class) {
		case FOX:
			size = 10;
			step = 1;
			break;
		case WOLF:
			size = 50;
			step = 1;
			break;
		case BEAR:
			size = 200;
			step = 1;
			break;
		}

	}

	state who() override {

		return PREDATOR;

	}

	char designation() override {

		char n = '?';
		switch (name_class)
		{
		case FOX:
			n = 'F';
			break;
		case WOLF:
			n = 'W';
			break;
		case BEAR:
			n = 'B';
			break;
		}
		return n;

	}

	int get_age() override {
		return life;
	}

	int get_move() override {
		return move;
	}

	int get_hungry() override {
		return hungry;
	}

	char gend() override {
		return gender;
	}

	int get_size()override {
		return size;
	}

	int get_step() override {
		return step;
	}

	int get_name_class() override {
		return name_class;
	}

	living* next(world w)override;

	living* copy(world w)override;

protected:

	char gender;
	int life, size, move;
	int hungry, step;
	class_predator name_class;

};

class herbivorous : public living {

public:

	herbivorous(int r, int c, int s, int a = MAX_LIFE, char g = '.', int m = 1, int h = 0, class_herbivorous name = RABBIT, int sz = 2)
		:life(a), gender(g), move(m), hungry(h), name_class(name), size(sz) {

		row = r; column = c; sell = s;
		switch (name_class) {
		case RABBIT:
			size = 2;
			step = 1;
			break;
		case GOAT:
			size = 20;
			step = 1;
			break;
		case DEER:
			size = 200;
			step = 1;
			break;
		}
	}

	state who() override {
		return HERBIVOROUS;
	}

	int get_age() override {
		return life;
	}

	int get_move() override {
		return move;
	}

	int get_hungry() override {
		return hungry;
	}

	char designation() override {

		char n = '?';

		switch (name_class) {
		case RABBIT:
			n = 'R';
			break;
		case GOAT:
			n = 'G';
			break;
		case DEER:
			n = 'D';
			break;
		}

		return n;

	}

	char gend() override {
		return gender;
	}

	int get_size() override {
		return size;
	}

	int get_step() override {
		return step;
	}

	int get_name_class() override {
		return name_class;
	};

	living* next(world w)override;

	living* copy(world w)override;

protected:

	char gender;
	int life, size, move;
	int hungry, step;
	class_herbivorous name_class;

};

class plants : public living {

public:

	plants(int r, int c, int s, int a = MAX_LIFE, int m = 1, int sz = 20)
		:life(a), move(m), size(sz) {
		row = r; column = c; sell = s;  gender = '.';
	}

	state who() override {
		return PLANTS;
	}

	int get_age() override {
		return life;
	}

	int get_move() override {
		return move;
	}

	char designation() override {
		return 'P';
	}

	char gend() override {
		return gender;
	}

	int get_hungry() override {
		return 0;
	}

	int get_size() override {
		return size;
	}

	int get_step() override {
		return 0;
	}

	int get_name_class() override {
		return 0;
	};

	living* next(world w)override;
	living* copy(world w)override;

protected:

	int life, move, size;

};

class empty : public living {

public:

	empty(int r, int c, int s) {
		row = r; column = c; sell = s; gender = '.';
	}

	state who() override {
		return EMPTY;
	}

	char designation() override {
		return '.';
	}

	int get_age() override {
		return 0;
	}

	int get_move() override {
		return 1;
	}

	char gend() override {
		return gender;
	}

	int get_hungry() override {
		return 0;
	}

	int get_size() override {
		return 0;
	}

	int get_step() override {
		return 0;
	}

	int get_name_class() override {
		return 0;
	};

	living* next(world w)override;
	living* copy(world w)override;

};

int get_free_cell(world w, int row, int column) {

	int free_sell = MAX_SELL;

	for (int i = 0; i < MAX_SELL; i++)
		if (w[row][column][i]->who() == EMPTY) {
			free_sell = i;
			break;
		}

	return free_sell;

}

int get_plant(world w, int row, int column) {

	int s = MAX_SELL;

	for (int i = 0; i < MAX_SELL; i++)
		if (w[row][column][i]->who() == PLANTS) {
			s = i;
			break;
		}

	return s;
}

int get_herb_rand(world w, int row, int column) {

	int s = MAX_SELL;
	int sarray[MAX_SELL];
	int count = 0;

	for (int i = 0; i < MAX_SELL; i++)
		sarray[i] = MAX_SELL;

	for (int i = 0; i < MAX_SELL; i++)
		if (w[row][column][i]->who() == HERBIVOROUS) {

			sarray[count++] = i;
			break;

		}

	if (count > 1) {

		int dice = rand() % count;
		s = sarray[dice];

	}
	else if (count == 1)
		s = sarray[0];

	return s;

}

int get_pred_rand(world w, int row, int column) {

	int s = MAX_SELL;
	int sarray[MAX_SELL];
	int count = 0;

	for (int i = 0; i < MAX_SELL; i++)
		sarray[i] = MAX_SELL;

	for (int i = 0; i < MAX_SELL; i++)
		if (w[row][column][i]->who() == PREDATOR) {
			sarray[count++] = i;
			break;
		}

	if (count > 1) {

		int dice = rand() % count;
		s = sarray[dice];

	}
	else if (count == 1)
		s = sarray[0];

	return s;

}

int get_family(world w, int row, int column, char gen, int nc, int tp) {

	int s = MAX_SELL;
	int sarray[MAX_SELL];
	int count = 0;
	char genR = 0;

	if (gen == 'f')
		genR = 'm';
	else
		genR = 'f';

	for (int i = 0; i < MAX_SELL; i++)
		sarray[i] = MAX_SELL;

	for (int i = 0; i < MAX_SELL; i++)
		if (w[row][column][i]->who() == tp && w[row][column][i]->gend() == genR && w[row][column][i]->get_name_class() == nc) {
			sarray[count++] = i;
			break;
		}

	if (count > 1) {

		int dice = rand() % count;
		s = sarray[dice];

	}
	else if (count == 1)
		s = sarray[0];

	return s;

}

int str_to_int(char* data) {

	int res = 0;

	switch (strlen(data)) {
	case 1:
		res = *data - '0';
		break;
	case 2:
		res = ((data[0] - '0') * 10) + (data[1] - '0');
		break;
	case 3:
		res = ((data[0] - '0') * 100) + ((data[1] - '0') * 10) + (data[2] - '0');
		break;
	}

	return res;

}

int count_data_in_row(std::string& r, char* seps, int& row, int& col, int& sell, char& type, char& cl, char& sex, int& life) {

	char* data = NULL;
	char* next_data = NULL;
	int count_data = 0;
	int len_r = r.length() + 1;
	char* ch_r = new char[len_r];
	strcpy_s(ch_r, len_r, r.c_str());
	data = strtok_s(ch_r, seps, &next_data);

	if (data != NULL)
		row = str_to_int(data);

	while (data != NULL)
		if (data != NULL) {

			data = strtok_s(NULL, seps, &next_data);
			count_data++;

			switch (count_data) {
			case 1:
				col = str_to_int(data);
				break;
			case 2:
				sell = str_to_int(data);
				break;
			case 3:
				type = *data;
				break;
			case 4:
				cl = *data;
				break;
			case 5:
				sex = *data;
				break;
			case 6:
				life = str_to_int(data);
				break;
			}
		}

	return count_data;

}

void get_world_from_file(std::string path, world w) {

	std::ifstream fin;
	std::string memory_file[100];

	int memory_file_size = 0;
	char seps[] = " \t\n";
	int max_world_length = 3;

	fin.open(path);

	if (!fin.is_open())
		std::cout << "Error opening file!" << std::endl;
	else {

		std::string input_string;
		int cInStr = 0;

		while (!fin.eof()) {

			input_string = "";

			std::getline(fin, input_string);

			if (input_string.length() == 0)
				break;
			else
				memory_file[cInStr++] = input_string;

		}

		memory_file_size = cInStr;

	}

	fin.close();

	for (int i = 1; i < memory_file_size; i++) {

		int row, col, sell, life, cl_int = 0;
		char type, sex, cl;

		int c = count_data_in_row(memory_file[i], seps, row, col, sell, type, cl, sex, life);

		if (c == 7) {

			std::cout << "set world sell " << row << "/" << col << "/" << sell << " " << type << cl << sex << life << "\n";

			delete(w[row][col][sell]);

			switch (type) {
			case '.':
				w[row][col][sell] = new empty(row, col, sell);
				break;
			case 'P':
				w[row][col][sell] = new plants(row, col, sell, life);
				break;
			case 'X':
				if (cl == 'F')
					cl_int = (int)FOX;
				else if (cl == 'W')
					cl_int = (int)WOLF;
				else if (cl == 'B')
					cl_int = (int)BEAR;

				w[row][col][sell] = new predator(row, col, sell, life, sex, 1, 0, (class_predator)cl_int);
				break;
			case 'T':
				if (cl == 'R')
					cl_int = (int)RABBIT;
				else if (cl == 'G')
					cl_int = (int)GOAT;
				else if (cl == 'D')
					cl_int = (int)DEER;

				w[row][col][sell] = new herbivorous(row, col, sell, life, sex, 1, 0, (class_herbivorous)cl_int);
				break;
			}
		}

		else std::cout << "Error initializing file on string " << i + 1 << '\n';

	}
}

living* plants::copy(world w) {
	return new plants(row, column, sell, life, move, size);
}

living* plants::next(world w) {

	int sum[MAX_STATES];
	int dRoll = dice_roll(4);
	int i, s;

	if (move) {

		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << " (plants) " << " life-" << life << "[" << dRoll << "]";

		if (life <= 0 || size <= 0) {

			w[row][column][sell] = new empty(row, column, sell);

			if (life <= 0)
				std::cout << " (dead) end of life ";
			if (size <= 0)
				std::cout << " (was eaten) ";

		}
		else if (life > 0) {

			w[row][column][sell] = new plants(row, column, sell, life - decLifePlant, move, size);

			switch (dRoll) {

			case 0:
				if (row < N - 1) {

					s = get_plant(w, row + 1, column);

					std::cout << " (down)->[" << row + 1 << "/" << column << "/" << s << "] ";

					if (s != MAX_SELL) {
						w[row + 1][column][s] = new plants(row + 1, column, s, MAX_LIFE, move, size);
						std::cout << " (reset age) ";
					}
					else {

						s = get_free_cell(w, row + 1, column);

						std::cout << " (find free sell) " << s;

						if (s < MAX_SELL) {

							w[row + 1][column][s] = new plants(row + 1, column, s, MAX_LIFE, 0);
							std::cout << " (set new plants) ";

						}
						else
							std::cout << " stay all sell is fill ";

					}
				}
				else
					std::cout << " (down) exit ower border world";

				break;
			case 1:
				if (row != 0) {

					s = get_plant(w, row - 1, column);

					std::cout << " (up)->[" << row - 1 << "/" << column << "/" << s << "] ";

					if (s != MAX_SELL) {

						w[row - 1][column][s] = new plants(row - 1, column, s, MAX_LIFE, move, size);
						std::cout << " (reset age) ";

					}
					else {

						s = get_free_cell(w, row - 1, column);
						std::cout << " (find free sell) " << s;

						if (s < MAX_SELL) {

							w[row - 1][column][s] = new plants(row - 1, column, s, MAX_LIFE, 0);//добавляем новое растение
							std::cout << " (set new plants) ";

						}
						else
							std::cout << " stay all sell is fill ";

					}
				}
				else
					std::cout << " (up) exit ower border world ";

				break;
			case 2:

				if (column < N - 1) {

					s = get_plant(w, row, column + 1);

					std::cout << " (right)->[" << row << "/" << column + 1 << "/" << s << "] ";

					if (s != MAX_SELL) {

						w[row][column + 1][s] = new plants(row, column + 1, s, MAX_LIFE, move, size);
						std::cout << " (reset age) ";

					}
					else {

						s = get_free_cell(w, row, column + 1);
						std::cout << " (find free sell) " << s;

						if (s < MAX_SELL) {

							w[row][column + 1][s] = new plants(row, column + 1, s, MAX_LIFE, 0);//добавляем новое растение
							std::cout << " (set new plants) ";

						}
						else
							std::cout << " stay all sell is fill ";

					}
				}
				else
					std::cout << " (right) exit ower border world ";

				break;
			case 3:

				if (column != 0) {

					s = get_plant(w, row, column - 1);

					std::cout << " (left)->[" << row << "/" << column - 1 << "/" << s << "] ";

					if (s != MAX_SELL) {

						w[row][column - 1][s] = new plants(row, column - 1, s, MAX_LIFE, move, size);
						std::cout << " (reset age) ";

					}
					else {

						s = get_free_cell(w, row, column - 1);
						std::cout << " (find free sell) " << s;

						if (s < MAX_SELL) {

							w[row][column - 1][s] = new plants(row, column - 1, s, MAX_LIFE, 0);
							std::cout << " (set new plants) ";

						}
						else
							std::cout << " stay all sell is fill ";

					}
				}
				else
					std::cout << "(left) exit ower border world ";

				break;
			case 4:

				std::cout << "(reset)-->[" << row << "/" << column << "/" << sell << "]";

				w[row][column][sell] = new plants(row, column, sell, MAX_LIFE);

				std::cout << " (reset age) ";

				break;
			}

		}
	}
	else
		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << " (plants) stop after move " << w[row][column][sell]->get_move();

	return w[row][column][sell];
}

living* herbivorous::copy(world w) {
	return new herbivorous(row, column, sell, life, gender, 1, hungry, name_class, size);
}

living* herbivorous::next(world w) {

	int sum[MAX_STATES];
	int dRoll = dice_roll(4);
	int s = MAX_SELL;
	char g = w[row][column][sell]->gend();
	int	nc = w[row][column][sell]->get_name_class();
	char dnc = w[row][column][sell]->designation();
	int stp = w[row][column][sell]->get_step();
	int s_parent = get_family(w, row, column, g, nc, HERBIVOROUS);
	int s_free_sell = get_free_cell(w, row, column);

	if (w[row][column][sell]->get_move()) {

		sums(w, sum);

		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << dnc << " (" << g << " life-" << life << ")" << "[" << dRoll << "]";

		if (life <= 0 || hungry >= MAX_STEPS_HUNGRY || size <= 0) {

			w[row][column][sell] = (new empty(row, column, sell));

			if (life <= 0)
				std::cout << " (was killed) ";
			if (hungry >= MAX_STEPS_HUNGRY)
				std::cout << " (starved to death)  ";
			if (size <= 0)
				std::cout << " (was eaten) ";

		}
		else {

			if (s_parent < MAX_SELL && s_free_sell < MAX_SELL) {

				std::cout << " (is starving) ";

				w[row][column][s_free_sell] = (new herbivorous(row, column, s_free_sell, MAX_LIFE, gender, 0, hungry));

				std::cout << " (made new creature) in cell " << s_free_sell << " ";

				w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));

			}
			else if (sum[HERBIVOROUS] >= 1 && sum[PLANTS] >= 1) {

				std::cout << " (is eating) ";

				s = get_plant(w, row, column);

				if (s < MAX_SELL) {

					int szPL = w[row][column][s]->get_size();
					int szHR = w[row][column][sell]->get_size();

					if (szPL > szHR) {

						int szHR = int(w[row][column][sell]->get_size() / 10);

						if (szHR <= 0)
							szHR = 1;

						w[row][column][s] = (new plants(row, column, s, life, move, size - szHR));
						w[row][column][sell] = (new herbivorous(row, column, sell, life, gender));

						std::cout << " " << w[row][column][sell]->designation() << " (is eating) " << szHR << " plants ";

					}
					else {

						std::cout << " " << w[row][column][sell]->designation() << " (eat) full plants ";

						w[row][column][s] = (new empty(row, column, s));
						w[row][column][sell] = (new herbivorous(row, column, sell, life, gender));

					}
				}
				else {

					w[row][column][sell] = (new herbivorous(row, column, sell, life, gender, move, ++hungry));
					std::cout << " (is starving) ";

				}
			}
			else {

				w[row][column][sell] = (new herbivorous(row, column, sell, life, gender, move, ++hungry));

				std::cout << " (is starving) ";

				switch (dRoll) {
				case 0:
					if (row < N - stp) {

						std::cout << " (down)->[" << row + stp << "/" << column << "/" << sell << "] ";

						s = get_free_cell(w, row + stp, column);

						if (s < MAX_SELL) {

							w[row][column][sell] = (new empty(row, column, sell));
							w[row + stp][column][s] = (new herbivorous(row + stp, column, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " changed it's position ";

						}
						else {

							w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " stayed because destination cell was full";

						}
					}
					else {

						w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " slammed into world border";

					}
					break;
				case 1:
					if (row != 0) {

						std::cout << " (up)->[" << row - stp << "/" << column << "/" << sell << "] ";

						s = get_free_cell(w, row - stp, column);

						if (s < MAX_SELL) {

							w[row][column][sell] = (new empty(row, column, sell));
							w[row - stp][column][s] = (new herbivorous(row - stp, column, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " changed it's position ";

						}
						else {

							w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " stayed because destination cell was full";

						}
					}
					else {

						w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " slammed into world border";

					}

					break;
				case 2:
					if (column < N - stp) {

						std::cout << " (right)->[" << row << "/" << column + stp << "/" << sell << "] ";

						s = get_free_cell(w, row, column + stp);

						if (s < MAX_SELL) {

							w[row][column][sell] = (new empty(row, column, sell));
							w[row][column + stp][s] = (new herbivorous(row, column + stp, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " changed it's position ";

						}
						else {

							w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " stayed because destination cell was full";

						}
					}
					else {

						w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " slammed into world border";

					}

					break;
				case 3:
					if (column != 0) {

						std::cout << " (left)->[" << row << "/" << column - stp << "/" << sell << "] ";

						s = get_free_cell(w, row, column - stp);

						if (s < MAX_SELL) {

							w[row][column][sell] = (new empty(row, column, sell));
							w[row][column - stp][s] = (new herbivorous(row, column - stp, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " changed it's position ";

						}
						else {

							w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " stayed because destination cell was full";

						}
					}
					else {

						w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " slammed into world border";

					}

					break;
				}
			}
		}
	}
	else
		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << " has already made it's turn";

	return w[row][column][sell];
}

living* predator::copy(world w) {
	return new predator(row, column, sell, life, gender, 1, hungry, name_class, size);
}

living* predator::next(world w) {

	int sum[MAX_STATES];
	int dRoll = dice_roll(4);
	int s = MAX_SELL;
	int nc = w[row][column][sell]->get_name_class();
	char g = w[row][column][sell]->gend();
	int s_parent = get_family(w, row, column, g, nc, PREDATOR);
	int s_free_sell = get_free_cell(w, row, column);
	char dnc = w[row][column][sell]->designation();
	int stp = w[row][column][sell]->get_step();

	if (w[row][column][sell]->get_move()) {

		sums(w, sum);

		g = w[row][column][sell]->gend();

		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << dnc << " (" << g << " life-" << life << ")" << "[" << dRoll << "] ";

		if (life <= 0 || hungry >= MAX_STEPS_HUNGRY) {

			w[row][column][sell] = (new empty(row, column, sell));
			if (life <= 0)
				std::cout << " (was killed) ";
			if (hungry >= MAX_STEPS_HUNGRY)
				std::cout << " (starved to death)  ";

		}
		else {

			if (s_parent < MAX_SELL && s_free_sell < MAX_SELL) {

				std::cout << " (is starving) ";

				w[row][column][s_free_sell] = (new predator(row, column, s_free_sell, MAX_LIFE, gender, 0, hungry));

				std::cout << " (made new creature) in cell " << s_free_sell;

				w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, 0, hungry));

			}
			else if (sum[HERBIVOROUS] >= 1 && sum[PREDATOR] >= 1) {

				std::cout << " (is eating) ";

				s = get_herb_rand(w, row, column);

				if (s < MAX_SELL) {

					int szPL = w[row][column][s]->get_size();
					int szHR = w[row][column][sell]->get_size();

					if (szPL > szHR)
						std::cout << " " << w[row][column][sell]->designation() << " small (dont eat) " << " " << w[row][column][s]->designation();
					else {

						std::cout << " " << w[row][column][sell]->designation() << " (eat) full " << w[row][column][s]->designation();
						w[row][column][s] = (new empty(row, column, s));
						w[row][column][sell] = (new predator(row, column, sell, life, gender));

					}

				}
				else {

					w[row][column][sell] = (new predator(row, column, sell, life, gender, move, ++hungry));//сюда можно вставить обработку голода 
					std::cout << " (is starving) ";

				}
			}
			else {

				w[row][column][sell] = (new predator(row, column, sell, life, gender, move, ++hungry));//сюда можно вставить обработку голода 

				std::cout << " (is starving) ";

				switch (dRoll) {

				case 0:
					if (row < N - stp) {

						std::cout << " (down)->[" << row + stp << "/" << column << "/" << sell << "] ";

						s = get_free_cell(w, row + stp, column);

						if (s < MAX_SELL) {

							w[row][column][sell] = (new empty(row, column, sell));
							w[row + stp][column][s] = (new predator(row + stp, column, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " changed it's position ";

						}
						else {

							w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " stayed because destination cell was full";

						}
					}
					else {

						w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " slammed into world border";

					}
					break;
				case 1:
					if (row != 0) {

						std::cout << " (up)->[" << row - stp << "/" << column << "/" << sell << "] ";

						s = get_free_cell(w, row - stp, column);

						if (s < MAX_SELL) {

							w[row][column][sell] = (new empty(row, column, sell));
							w[row - stp][column][s] = (new predator(row - stp, column, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " changed it's position ";

						}
						else {

							w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " stayed because destination cell was full";

						}
					}
					else {

						w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " slammed into world border";

					}
					break;
				case 2:
					if (column < N - stp) {

						std::cout << " (right)->[" << row << "/" << column + stp << "/" << sell << "] ";

						s = get_free_cell(w, row, column + stp);

						if (s < MAX_SELL) {

							w[row][column][sell] = (new empty(row, column, sell));
							w[row][column + stp][s] = (new predator(row, column + stp, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " changed it's position ";

						}
						else {

							w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " stayed because destination cell was full";

						}
					}
					else {

						w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " slammed into world border";

					}
					break;
				case 3:
					if (column != 0) {

						std::cout << " (left)->[" << row << "/" << column - stp << "/" << sell << "]";

						s = get_free_cell(w, row, column - stp);

						if (s < MAX_SELL) {

							w[row][column][sell] = (new empty(row, column, sell));
							w[row][column - stp][s] = (new predator(row, column - stp, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " changed it's position ";

						}
						else {

							w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " slammed into world border";

						}
					}
					else {

						w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " stayed because destination cell was full";

					}

					break;
				}
			}
		}
	}
	else
		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << " has already made it's turn" << w[row][column][sell]->get_move();

	return w[row][column][sell];

}

living* empty::copy(world w) {
	return new empty(row, column, sell);
}

living* empty::next(world w) {
	return (new empty(row, column, sell));
}

void init(world w) {

	int i, j, k;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = 0; k < MAX_SELL; k++)
				w[i][j][k] = new empty(i, j, k);

}

void update(world w_new, world w_old) {

	int i, j, k;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = 0; k < MAX_SELL; k++)
				w_old[i][j][k]->next(w_old);

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = 0; k < MAX_SELL; k++)
				w_new[i][j][k] = w_old[i][j][k]->copy(w_old);

}

void dele(world w) {

	int i, j, k;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = 0; k < MAX_SELL; k++)
				delete(w[i][j][k]);

}

void get_debug_info(world w) {

	int i, j, k;

	std::cout << "\n";

	for (i = 0; i < N; i++) {

		std::cout << "\n";

		for (j = 0; j < N; j++) {

			std::cout << "[" << i << "," << j << "][";

			for (k = 0; k < MAX_SELL; k++) {

				char d = w[i][j][k]->designation();
				int a = w[i][j][k]->get_age();
				char g = w[i][j][k]->gend();

				std::cout << d << g << a << " ";

			}

			std::cout << "] ";
		}

	}
}

void input() {

	switch (_getch()) {
	case 'd':
		++cycles;
		break;

	case 'x':
		is_running = false;
		break;

	}
}

int main() {

	world odd, even;

	int i = 0;

	std::string path = "config.txt";

	srand(time(0));

	init(odd);
	init(even);
	get_world_from_file(path, even);

	while (is_running) {

		system("cls");

		if (i == 0)	{

			std::cout << " world after init";
			get_debug_info(even);
			std::cout << "\n\n\n\n";

		}

		std::cout << "step " << i << "";

		if (i % 2) {
			update(even, odd);
			get_debug_info(even);
			//get_debug_info(odd);
		}
		else {
			update(odd, even);
			get_debug_info(odd);
			//get_debug_info(even);
		}

		input();
		++i;
	}
}