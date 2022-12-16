#include "Class.h"

//найти свободную ячейку
int get_free_sell(world w, int row, int column)
{

	int free_sell = MAX_SELL;

	for (int i = 0; i < MAX_SELL; i++)
	{
		if (w[row][column][i]->who() == EMPTY)
		{
			free_sell = i;
			break;
		}
	}

	return free_sell;
}

//найти номер ячейки где находиться растение
int get_plant(world w, int row, int column)
{

	int s = MAX_SELL;//если в результате поиска возвращен индекс MAX_SELL - это значит что растений в этой ячейке мира нет

	for (int i = 0; i < MAX_SELL; i++)
	{
		if (w[row][column][i]->who() == PLANTS)
		{
			s = i;// возвращает номер ячейки где находиться растение
			break;
		}
	}

	return s;
}

//найти ячейку где находиться травоядное если таких больше  1, то выбрать случайную
int get_herb_rand(world w, int row, int column)
{
	int s = MAX_SELL;//если в результате поиска возвращен индекс MAX_SELL - это значит что растений в этой ячейке мира нет
	int sarray[MAX_SELL];
	int count = 0;

	//иннициализация массива травоядных если == MAX_SELL то значит нет данных
	for (int i = 0; i < MAX_SELL; i++)
	{
		sarray[i] = MAX_SELL;
	}

	//поиск всех травоядных в этой области мира
	for (int i = 0; i < MAX_SELL; i++)
	{
		if (w[row][column][i]->who() == HERBIVOROUS)
		{
			sarray[count++] = i;// возвращает номер  ячейки где находиться травоядное
								// count подсчитывает количество травоядных в этой области мира
			break;
		}
	}

	if (count > 1)
	{
		//выбрать случайное травоядное если их больше 1
		int dice = rand() % count;
		s = sarray[dice];
	}
	else if (count == 1)
	{
		//если только одно травоядное
		s = sarray[0];
	}

	return s;
}

//найти ячейку где находиться predator если таких больше  1, то выбрать случайную
int get_pred_rand(world w, int row, int column)
{
	int s = MAX_SELL;//если в результате поиска возвращен индекс MAX_SELL - это значит что predator в этой ячейке мира нет
	int sarray[MAX_SELL];
	int count = 0;

	//иннициализация массива predator если == MAX_SELL то значит нет данных
	for (int i = 0; i < MAX_SELL; i++)
	{
		sarray[i] = MAX_SELL;
	}

	//поиск всех predator в этой области мира
	for (int i = 0; i < MAX_SELL; i++)
	{
		if (w[row][column][i]->who() == PREDATOR)
		{
			sarray[count++] = i;// возвращает номер  ячейки где находиться predator
								// count подсчитывает количество predator в этой области мира
			break;
		}
	}

	if (count > 1)
	{
		//выбрать случайное predator если их больше 1
		int dice = rand() % count;
		s = sarray[dice];
	}
	else if (count == 1)
	{
		//если только одно predator
		s = sarray[0];
	}

	return s;
}

//найти ячейку где находиться особь другого пола  если таких больше  1, то выбрать случайную
//nc- name_class tp-PREDATOR or HERB
int get_family(world w, int row, int column, char gen, int nc, int tp)
{
	int s = MAX_SELL;//если в результате поиска возвращен индекс MAX_SELL - это значит что predator в этой ячейке мира нет
	int sarray[MAX_SELL];
	int count = 0;
	char genR = 0;

	// выбор противоположного пола если в (gen)-female то выбираем male
	if (gen == 'f')
	{
		genR = 'm';
	}
	else
	{
		genR = 'f';
	}

	//иннициализация массива predator если == MAX_SELL то значит нет данных
	for (int i = 0; i < MAX_SELL; i++)
	{
		sarray[i] = MAX_SELL;
	}

	//поиск всех predator в этой области мира
	for (int i = 0; i < MAX_SELL; i++)
	{
		if (w[row][column][i]->who() == tp && w[row][column][i]->gend() == genR && w[row][column][i]->get_name_class() == nc)
		{
			sarray[count++] = i;// возвращает номер  ячейки где находиться predator
								// count подсчитывает количество predator в этой области мира
			break;
		}
	}

	if (count > 1)
	{
		//выбрать случайное predator заданного пола если их больше 1
		int dice = rand() % count;
		s = sarray[dice];
	}
	else if (count == 1)
	{
		//если только одно predator заданного пола
		s = sarray[0];
	}
	return s;
}

int str_to_int(char* data)
{
	int res = 0;
	switch (strlen(data))
	{
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

//прочитать конфигурацию из файла
int count_data_in_row(std::string& r, char* seps, int& row, int& col, int& sell, char& type, char& cl, char& sex, int& life)
{
	char* data = NULL;//Указатель на символьную строку с именем вершины
	char* next_data = NULL;//Указатель на следующую символьную строку с именем вершины
	int count_data = 0;//Счетчик количества вершин в строке
	int len_r = r.length() + 1;//Длина строки
	char* ch_r = new char[len_r];//выделение памяти под копию строки strtok_s работает только с char*
	strcpy_s(ch_r, len_r, r.c_str());//копирование string в char*
	data = strtok_s(ch_r, seps, &next_data);//Выборка названия первой вершины из строки	

	// взять значение:
	if (data != NULL)
	{
		row = str_to_int(data);
	}

	//выбираем все данные из строки
	while (data != NULL)
	{
		if (data != NULL)
		{
			data = strtok_s(NULL, seps, &next_data);//Выборка названия следующей вершины из строки
			count_data++;

			switch (count_data)
			{
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
	}

	return count_data;
}

void init_from_file(std::string path, world w)
{
	std::ifstream fin;
	std::string memory_file[100];//массив для сохранения данных из файла

	int memory_file_size = 0;//Хранит количество строк в списке смежности
	char seps[] = " \t\n";//Разделители
	int max_world_length = 3;//количество локаций по горизонтали и вертикали

	fin.open(path);

	//open file and create array 
	if (!fin.is_open())
	{
		std::cout << "error open file!!!" << std::endl;
	}
	else
	{
		std::cout << "file open!" << std::endl;

		std::string input_string;//Строка для ввода данных из файла
		int cInStr = 0;//Счетчик кол-во строк

		while (!fin.eof())
		{
			input_string = "";

			std::getline(fin, input_string);

			if (input_string.length() == 0)
			{
				break;
			}
			else
			{
				memory_file[cInStr++] = input_string;
			}
		}

		memory_file_size = cInStr;
	}

	fin.close();

	//for не с 0 потому что в 0 заголовок файла
	for (int i = 1; i < memory_file_size; i++)
	{
		int row, col, sell, life, cl_int = 0;
		char type, sex, cl;
		int c = count_data_in_row(memory_file[i], seps, row, col, sell, type, cl, sex, life);

		if (c == 7)
		{
			//set world sell
			std::cout << "set world sell " << row << "/" << col << "/" << sell << " " << type << cl << sex << life << "\n";

			delete(w[row][col][sell]);

			switch (type)
			{
			case '.':
				w[row][col][sell] = new empty(row, col, sell);
				//std::cout << ".\n";
				break;
			case 'P':
				w[row][col][sell] = new plants(row, col, sell, life);
				//std::cout << "P\n";
				break;
			case 'X':
				if (cl == 'F')
				{
					cl_int = (int)FOX;
				}
				if (cl == 'W')
				{
					cl_int = (int)WOLF;
				}
				if (cl == 'B')
				{
					cl_int = (int)BEAR;
				}
				w[row][col][sell] = new predator(row, col, sell, life, sex, 1, 0, (class_predator)cl_int);
				//std::cout << "X\n";
				break;
			case 'T':
				if (cl == 'R')
				{
					cl_int = (int)RABBIT;
				}
				if (cl == 'G')
				{
					cl_int = (int)GOAT;
				}
				if (cl == 'D')
				{
					cl_int = (int)DEER;
				}
				w[row][col][sell] = new herbivorous(row, col, sell, life, sex, 1, 0, (class_herbivorous)cl_int);
				//std::cout << "T\n";
				break;
			}
		}
		else std::cout << "error in init file in string #" << i + 1;
	}
}

living* plants::copy(world w)
{
	return new plants(row, column, sell, life, move, size);
}

living* plants::next(world w)
{
	int sum[MAX_STATES];
	int dRoll = dice_roll(4);
	int i, s;

	if (move)
	{
		//если срок жизни истек то умирает если нет то возраст растет 
		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << " (plants) " << " life-" << life << "[" << dRoll << "]";

		if (life <= 0 || size <= 0)
		{
			w[row][column][sell] = new empty(row, column, sell);

			if (life <= 0)
			{
				std::cout << " (dead) end of life ";
			}
			if (size <= 0)
			{
				std::cout << " (dead) eat other ";
			}
		}
		else if (life > 0)
		{
			// в зависимости от выпавшей кости размножаеися в соседнюю клетку
			// или остается на месте если выпадет 4 обновляет жизнь
			//увеличиваем счетчик жизни
			w[row][column][sell] = new plants(row, column, sell, life - decLifePlant, move, size);

			switch (dRoll)
			{
			case 0: // step down
				if (row < N - 1)
				{
					//если в результате поиска возвращен индекс MAX_SELL - это значит что растений в этой ячейке мира нет
					s = get_plant(w, row + 1, column);

					std::cout << " (down)->[" << row + 1 << "/" << column << "/" << s << "] ";

					if (s != MAX_SELL)
					{
						//если в соседней ячейке уже есть растение тогда сбрасываем сетчик жизни в 100
						w[row + 1][column][s] = new plants(row + 1, column, s, MAX_LIFE, move, size);
						std::cout << " (reset age) ";
					}
					else
					{
						//ищем свободную  ячейку в соседней области мира
						s = get_free_sell(w, row + 1, column);

						std::cout << " (find free sell) " << s;

						//если в соседней области мира нет растений и есть свободная ячейка то создаем там новое растение
						if (s < MAX_SELL)
						{
							//delete w[row + 1][column][free_sell]; //удаляем пустую ячейку
							w[row + 1][column][s] = new plants(row + 1, column, s, MAX_LIFE, 0);
							std::cout << " (set new plants) ";
						}
						else
						{
							//ничего не делаем если свободных ячеек нет
							std::cout << " stay all sell is fill ";
						}
					}
				}
				else
				{
					std::cout << " (down) exit ower border world";
				}
				break;
			case 1: // step up
				if (row != 0)
				{
					s = get_plant(w, row - 1, column);

					std::cout << " (up)->[" << row - 1 << "/" << column << "/" << s << "] ";

					if (s != MAX_SELL)
					{
						//в соседней ячейке сбрасываем сетчик жизни в 100
						w[row - 1][column][s] = new plants(row - 1, column, s, MAX_LIFE, move, size);
						std::cout << " (reset age) ";
					}
					else
					{
						//ищем свободную  ячейку в соседней области мира
						s = get_free_sell(w, row - 1, column);
						std::cout << " (find free sell) " << s;
						//если в соседней области мира нет растений и есть свободная ячейка то создаем там новое растение
						if (s < MAX_SELL)
						{
							//delete(w[row - 1][column][free_sell]); //удаляем пустую ячейку
							w[row - 1][column][s] = new plants(row - 1, column, s, MAX_LIFE, 0);//добавляем новое растение
							std::cout << " (set new plants) ";
						}
						else
						{
							//ничего не делаем если свободных ячеек нет
							std::cout << " stay all sell is fill ";
						}
					}
				}
				else
				{
					std::cout << " (up) exit ower border world ";
				}
				break;
			case 2: // step right
				if (column < N - 1)
				{

					s = get_plant(w, row, column + 1);

					std::cout << " (right)->[" << row << "/" << column + 1 << "/" << s << "] ";

					if (s != MAX_SELL)
					{
						//в соседней ячейке сбрасываем сетчик жизни в 0
						w[row][column + 1][s] = new plants(row, column + 1, s, MAX_LIFE, move, size);
						std::cout << " (reset age) ";
					}
					else
					{
						//ищем свободную  ячейку в соседней области мира
						s = get_free_sell(w, row, column + 1);
						std::cout << " (find free sell) " << s;
						//если в соседней области мира нет растений и есть свободная ячейка то создаем там новое растение
						if (s < MAX_SELL)
						{
							//delete w[row][column + 1][free_sell]; //удаляем пустую ячейку
							w[row][column + 1][s] = new plants(row, column + 1, s, MAX_LIFE, 0);//добавляем новое растение
							std::cout << " (set new plants) ";
						}
						else
						{
							//ничего не делаем если свободных ячеек нет
							std::cout << " stay all sell is fill ";
						}
					}
				}
				else
				{
					std::cout << " (right) exit ower border world ";
				}
				break;
			case 3: // step left
				if (column != 0)
				{
					s = get_plant(w, row, column - 1);

					std::cout << " (left)->[" << row << "/" << column - 1 << "/" << s << "] ";

					if (s != MAX_SELL)
					{
						//в соседней ячейке сбрасываем сетчик жизни в MAX_LIFE
						w[row][column - 1][s] = new plants(row, column - 1, s, MAX_LIFE, move, size);
						std::cout << " (reset age) ";
					}
					else
					{
						//ищем свободную  ячейку в соседней области мира
						s = get_free_sell(w, row, column - 1);
						std::cout << " (find free sell) " << s;
						//если в соседней области мира нет растений и есть свободная ячейка то создаем там новое растение
						if (s < MAX_SELL)
						{
							//delete w[row][column - 1][free_sell]; //удаляем пустую ячейку
							w[row][column - 1][s] = new plants(row, column - 1, s, MAX_LIFE, 0);//добавляем новое растение
							std::cout << " (set new plants) ";
						}
						else
						{
							//ничего не делаем если свободных ячеек нет
							std::cout << " stay all sell is fill ";
						}
					}
				}
				else
				{
					std::cout << "(left) exit ower border world ";
				}
				break;
			case 4: //обнуляем счетчик жизни растения (размножилось в своей ячейке)
				std::cout << "(reset)-->[" << row << "/" << column << "/" << sell << "]";
				w[row][column][sell] = new plants(row, column, sell, MAX_LIFE);
				std::cout << " (reset age) ";
				break;
			}

			//если травоядных больше одного то растение сьедают , иначе увеличиваем счетчик жизни
		}
	}
	else
	{
		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << " (plants) stop after move " << w[row][column][sell]->get_move();
	}
	//возвращаем ячейку
	return w[row][column][sell];
}

living* herbivorous::copy(world w)
{
	return new herbivorous(row, column, sell, life, gender, 1, hungry, name_class, size);
}

living* herbivorous::next(world w)
{
	int sum[MAX_STATES];
	int dRoll = dice_roll(4);//0-down 1-up 2-right 3-left 
	int s = MAX_SELL;
	char g = w[row][column][sell]->gend();
	int	nc = w[row][column][sell]->get_name_class();
	char dnc = w[row][column][sell]->designation();
	int stp = w[row][column][sell]->get_step();
	int s_parent = get_family(w, row, column, g, nc, HERBIVOROUS);
	int s_free_sell = get_free_sell(w, row, column);
	
	if (w[row][column][sell]->get_move())
	{
		sums(w, sum);

		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << dnc << " (" << g << " life-" << life << ")" << "[" << dRoll << "]";

		//проверяем травоядное на старость
		if (life <= 0 || hungry >= MAX_STEPS_HUNGRY || size <= 0)
		{
			// если закончился срок жизни
			w[row][column][sell] = (new empty(row, column, sell));
			if (life <= 0) std::cout << " (dead end life) ";
			if (hungry >= MAX_STEPS_HUNGRY) std::cout << " (dead from hungry) ";
			if (size <= 0)std::cout << " (dead) eat other ";
		}
		else
		{
			if (s_parent < MAX_SELL && s_free_sell < MAX_SELL)
			{
				std::cout << " (hungry) ";

				//если есть второй родитель и свободная ячейка то рождается новое травоядное случайного пола
				w[row][column][s_free_sell] = (new herbivorous(row, column, s_free_sell, MAX_LIFE, gender, 0, hungry));

				std::cout << " (born new life) in sell #" << s_free_sell << " ";

				w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
			}
			else if (sum[HERBIVOROUS] >= 1 && sum[PLANTS] >= 1)
			{
				// переходит в другую клетку пока не питаясь растениями
				// 4 - остается на месте
				//eat
				//если травоядных и растений больше чем 1 то они могут питаться
				std::cout << " (eat) ";

				s = get_plant(w, row, column);

				if (s < MAX_SELL)
				{
					//если есть растение то его едим
					int szPL = w[row][column][s]->get_size();
					int szHR = w[row][column][sell]->get_size();

					if (szPL > szHR)
					{
						//съедает часть растения
						//сьедает 10 процентов от собственного веса
						int szHR = int(w[row][column][sell]->get_size() / 10);

						//если вес слишком малый съедает просто 1
						if (szHR <= 0)
						{
							szHR = 1;
						}

						w[row][column][s] = (new plants(row, column, s, life, move, size - szHR));
						w[row][column][sell] = (new herbivorous(row, column, sell, life, gender));

						std::cout << " " << w[row][column][sell]->designation() << " (eat) " << szHR << " plants ";
					}
					else
					{
						//съедает все растение
						std::cout << " " << w[row][column][sell]->designation() << " (eat) full plants ";
						w[row][column][s] = (new empty(row, column, s));
						w[row][column][sell] = (new herbivorous(row, column, sell, life, gender));
					}
				}
				else
				{
					w[row][column][sell] = (new herbivorous(row, column, sell, life, gender, move, ++hungry));//сюда можно вставить обработку голода 
					std::cout << " (hungry) ";
				}
			}
			else
			{
				w[row][column][sell] = (new herbivorous(row, column, sell, life, gender, move, ++hungry));//сюда можно вставить обработку голода 
				
				std::cout << " (hungry) ";

				switch (dRoll)
				{
				case 0: //down
					if (row < N - stp)
					{
						std::cout << " (down)->[" << row + stp << "/" << column << "/" << sell << "] ";

						s = get_free_sell(w, row + stp, column);

						if (s < MAX_SELL)
						{
							//удаляем из старой локации
							w[row][column][sell] = (new empty(row, column, sell));
							//переходим в новую локацию и увеличиваем возраст
							w[row + stp][column][s] = (new herbivorous(row + stp, column, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " (GO) " << s;
						}
						else
						{
							w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " (STAY) not free sell ";
						}
					}
					else {
						w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " (STAY) over border ";
					}
					break;
				case 1: //up
					if (row != 0)
					{
						std::cout << " (up)->[" << row - stp << "/" << column << "/" << sell << "] ";

						s = get_free_sell(w, row - stp, column);

						if (s < MAX_SELL)
						{
							//удаляем из старой локации
							w[row][column][sell] = (new empty(row, column, sell));
							//переходим в новую локацию и увеличиваем возраст
							w[row - stp][column][s] = (new herbivorous(row - stp, column, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " (GO) " << s;
						}
						else
						{
							w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " (STAY) not free sell ";
						}
					}
					else
					{
						w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " (STAY) over border ";
					}
					break;
				case 2: //right
					if (column < N - stp)
					{
						std::cout << " (right)->[" << row << "/" << column + stp << "/" << sell << "] ";

						s = get_free_sell(w, row, column + stp);

						if (s < MAX_SELL)
						{
							//удаляем из старой локации
							w[row][column][sell] = (new empty(row, column, sell));
							//переходим в новую локацию и увеличиваем возраст
							w[row][column + stp][s] = (new herbivorous(row, column + stp, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " (GO) " << s;
						}
						else
						{
							w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " (STAY) not free sell ";
						}
					}
					else
					{
						w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " (STAY) over border ";
					}
					break;
				case 3: //left
					if (column != 0)
					{
						std::cout << " (left)->[" << row << "/" << column - stp << "/" << sell << "] ";
						s = get_free_sell(w, row, column - stp);
						if (s < MAX_SELL) {
							//удаляем из старой локации
							w[row][column][sell] = (new empty(row, column, sell));
							//переходим в новую локацию и увеличиваем возраст
							w[row][column - stp][s] = (new herbivorous(row, column - stp, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " (GO) " << s;
						}
						else
						{
							w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " (STAY) not free sell ";
						}
					}
					else
					{
						w[row][column][sell] = (new herbivorous(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " (STAY) over border ";
					}
					break;
				}
			}
		}
	}
	else
	{
		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << " stop after move " << w[row][column][sell]->get_move();
	}
	//возвращаем ячейку
	return w[row][column][sell];
}

living* predator::copy(world w)
{
	return new predator(row, column, sell, life, gender, 1, hungry, name_class, size);
}

living* predator::next(world w)
{
	int sum[MAX_STATES];
	int dRoll = dice_roll(4);//0-down 1-up 2-right 3-left
	int s = MAX_SELL;
	int nc = w[row][column][sell]->get_name_class();
	char g = w[row][column][sell]->gend();
	int s_parent = get_family(w, row, column, g, nc, PREDATOR);
	int s_free_sell = get_free_sell(w, row, column);
	char dnc = w[row][column][sell]->designation();
	int stp = w[row][column][sell]->get_step();

	if (w[row][column][sell]->get_move())
	{
		sums(w, sum);
		g = w[row][column][sell]->gend();
		std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << dnc << " (" << g << " life-" << life << ")" << "[" << dRoll << "] ";

		//проверяем хищника на старость
		if (life <= 0 || hungry >= MAX_STEPS_HUNGRY)
		{
			// если закончился срок жизни
			w[row][column][sell] = (new empty(row, column, sell));
			if (life <= 0) std::cout << " (dead end life) ";
			if (hungry >= MAX_STEPS_HUNGRY) std::cout << " (dead from hungry) ";
		}
		else
		{
			if (s_parent < MAX_SELL && s_free_sell < MAX_SELL)
			{
				std::cout << " (hungry) ";

				//если есть второй родитель и свободная ячейка то рождается новый хищник случайного пола
				w[row][column][s_free_sell] = (new predator(row, column, s_free_sell, MAX_LIFE, gender, 0, hungry));

				std::cout << " (born new life) in sell #" << s_free_sell;

				w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, 0, hungry));
			}
			else if (sum[HERBIVOROUS] >= 1 && sum[PREDATOR] >= 1)
			{
				// переходит в другую клетку пока не питаясь травоядными
				// 4 - остается на месте
				//eat
				//если хищников и травоядных больше чем 1 то они могут питаться
				std::cout << " (eat) ";

				// пока без учета голода по хищникам и травоядным
				s = get_herb_rand(w, row, column);
				if (s < MAX_SELL)
				{
					//если есть травоядное то его едим
					int szPL = w[row][column][s]->get_size();
					int szHR = w[row][column][sell]->get_size();

					if (szPL > szHR)
					{
						//если меньше размером то не ест
						std::cout << " " << w[row][column][sell]->designation() << " small (dont eat) " << " " << w[row][column][s]->designation();
					}
					else
					{
						//съедает все травоядное
						std::cout << " " << w[row][column][sell]->designation() << " (eat) full " << w[row][column][s]->designation();
						w[row][column][s] = (new empty(row, column, s));
						w[row][column][sell] = (new predator(row, column, sell, life, gender));

					}
				}
				else
				{
					//хищник остался голодным
					w[row][column][sell] = (new predator(row, column, sell, life, gender, move, ++hungry));//сюда можно вставить обработку голода 
					std::cout << " (hungry) ";
				}
			}
			else
			{
				w[row][column][sell] = (new predator(row, column, sell, life, gender, move, ++hungry));//сюда можно вставить обработку голода 

				std::cout << " (hungry) ";

				switch (dRoll)
				{
				case 0: //down
					if (row < N - stp)
					{
						std::cout << " (down)->[" << row + stp << "/" << column << "/" << sell << "] ";

						s = get_free_sell(w, row + stp, column);

						if (s < MAX_SELL)
						{
							//удаляем из старой локации
							w[row][column][sell] = (new empty(row, column, sell));
							//переходим в новую локацию и увеличиваем возраст
							w[row + stp][column][s] = (new predator(row + stp, column, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " (GO) " << s;
						}
						else
						{
							w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " (STAY) not free sell ";
						}
					}
					else
					{
						w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " (STAY) over border ";
					}
					break;
				case 1: //up
					if (row != 0)
					{
						std::cout << " (up)->[" << row - stp << "/" << column << "/" << sell << "] ";
						s = get_free_sell(w, row - stp, column);
						if (s < MAX_SELL) {
							//удаляем из старой локации
							w[row][column][sell] = (new empty(row, column, sell));
							//переходим в новую локацию и увеличиваем возраст
							w[row - stp][column][s] = (new predator(row - stp, column, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " (GO) " << s;
						}
						else
						{
							w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " (STAY) not free sell ";
						}
					}
					else
					{
						w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " (STAY) over border ";
					}
					break;
				case 2: //right
					if (column < N - stp)
					{
						std::cout << " (right)->[" << row << "/" << column + stp << "/" << sell << "] ";
						s = get_free_sell(w, row, column + stp);
						if (s < MAX_SELL) {
							//удаляем из старой локации
							w[row][column][sell] = (new empty(row, column, sell));
							//переходим в новую локацию и увеличиваем возраст
							w[row][column + stp][s] = (new predator(row, column + stp, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " (GO) " << s;
						}
						else {
							w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " (STAY) not free sell ";
						}
					}
					else {
						w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " (STAY) over border";
					}
					break;
				case 3: //left
					if (column != 0)
					{
						std::cout << " (left)->[" << row << "/" << column - stp << "/" << sell << "]";
						s = get_free_sell(w, row, column - stp);
						if (s < MAX_SELL) {
							//удаляем из старой локации
							w[row][column][sell] = (new empty(row, column, sell));
							//переходим в новую локацию и увеличиваем возраст
							w[row][column - stp][s] = (new predator(row, column - stp, s, life - decLifeMamale, gender, 0, hungry));
							std::cout << " (GO)" << s;
						}
						else
						{
							w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
							std::cout << " (STAY) over border";
						}
					}
					else
					{
						w[row][column][sell] = (new predator(row, column, sell, life - decLifeMamale, gender, move, hungry));
						std::cout << " (STAY) not free sell";
					}
					break;
				}
			}
		}
	}
	else std::cout << " \n[" << row << "/" << column << "/" << sell << "]->" << " stop after move " << w[row][column][sell]->get_move();
	//возвращаем ячейку
	return w[row][column][sell];
}	

living* empty::copy(world w)
{
	return new empty(row, column, sell);
}

living* empty::next(world w)
{
	return (new empty(row, column, sell));
}

void init(world w)
{
	int i, j, k;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < MAX_SELL; k++)
			{
				w[i][j][k] = new empty(i, j, k);
			}
		}
	}
}

void update(world w_new, world w_old)
{
	int i, j, k;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < MAX_SELL; k++)
			{
				w_old[i][j][k]->next(w_old);
			}
		}
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < MAX_SELL; k++)
			{
				w_new[i][j][k] = w_old[i][j][k]->copy(w_old);
			}
		}
	}
}

void dele(world w)
{
	int i, j, k;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < MAX_SELL; k++)
			{
				delete(w[i][j][k]);
			}
		}
	}
}

void eden(world w, std::string path)
{
	//иннициализация из программы
	srand(time(0));

	int i = 0, j = 0, k = 0;
	int x;
	char g = 0;

	for (int x = 0; x < N; x++)
	{
		i = rand() % N;
		j = rand() % N;
		k = get_free_sell(w, i, j);

		int dice = rand() % 2;
		if (dice)g = 'm';//male dice=1
		else g = 'f';//female dice=0
		w[i][j][k]->set_gender(g);

		delete(w[i][j][k]);
		w[i][j][k] = new predator(i, j, k, MAX_LIFE, g);

	}
	for (int x = 0; x < N; x++)
	{
		i = rand() % N;
		j = rand() % N;
		k = get_free_sell(w, i, j);

		int dice = rand() % 2;
		if (dice)g = 'm';//male dice=1
		else g = 'f';//female dice=0
		w[i][j][k]->set_gender(g);

		if (get_plant(w, i, j) == MAX_SELL) {
			delete(w[i][j][k]);
			w[i][j][k] = new herbivorous(i, j, k, MAX_LIFE, g);
		}

	}
	for (x = 0; x < N; x++)
	{
		i = rand() % N;
		j = rand() % N;
		k = get_free_sell(w, i, j);

		delete(w[i][j][k]);

		w[i][j][k] = new plants(i, j, k);

		w[i][j][k]->set_gender('.');
	}
}

void pr_state(world w)
{
	int i, j, k;

	std::cout << "\n";

	for (i = 0; i < N; i++)
	{
		std::cout << "\n";

		for (j = 0; j < N; j++)
		{
			std::cout << "(" << i << "," << j << ")[";

			for (k = 0; k < MAX_SELL; k++)
			{
				char d = w[i][j][k]->designation();
				int a = w[i][j][k]->get_age();
				char g = w[i][j][k]->gend();

				std::cout << d << g << a << " ";
			}

			std::cout << "] ";
		}
	}
}

void input()
{
	switch (_getch())
	{
	case 'd':
	{
		++cycles;
		break;
	}
	case 'x':
	{
		game = false;
		break;
	}
	}
}

int main()
{
	world odd, even;
	int i = 0;
	std::string path = "in0.txt";//путь к файлу конфигурации

	srand(time(0));

	init(odd);
	init(even);
	//иннициализация из файла
	init_from_file(path, even);
	//иннициализация из программы отключена
	//eden(even);
	while (game)
	{
		system("cls");

		if (i == 0)
		{
			std::cout << " world after init";
			pr_state(even);
			std::cout << "\n\n\n\n";
		}

		std::cout << "step #" << i << "";

		if (i % 2)
		{
			update(even, odd);
			pr_state(even);
			//pr_state(odd);
			dele(odd);
		}
		else
		{
			update(odd, even);
			pr_state(odd);
			//pr_state(even);
			dele(even);
		}
		input();
		++i;
	}
}