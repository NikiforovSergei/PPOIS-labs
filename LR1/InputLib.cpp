#include "InputLibHeader.h"
std::tuple<int,int, std::vector<float>>	file_input(std::string &path)
{
	std::ifstream fin(path);
	int x_size, y_size;
	float current_value;
	std::stringstream ss; 
	std::string line;
	std::vector<float> input_values;
	while (!fin.eof())
	{
		std::getline(fin,line);
		ss << line;
		while (ss >> current_value)
		{
			input_values.push_back(current_value);
		}
		ss.clear();
	}
	fin.close();
	ss.clear();
	y_size = input_values[0];
	x_size = input_values[1];
	input_values.erase(input_values.begin());
	input_values.erase(input_values.begin());
	return std::make_tuple(y_size,x_size,input_values);
}
std::tuple<int, int, std::vector<float>> console_input()
{
	std::vector<std::string> console_utility = { "Количество строк матрицы: ", "Количество столбцов матрицы: ",
		"Введите элементы матрицы:\n"};
	int x, y;
	float value;
	std::vector<float> values;
	std::cout << console_utility[0];
	std::cin >> y;
	std::cout << console_utility[1];
	std::cin >> x;
	for (int i = 0; i < x * y; ++i)
	{
		std::cin >> value;
		values.push_back(value);
	}
	return std::make_tuple(y,x,values);
}
