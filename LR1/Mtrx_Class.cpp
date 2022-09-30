#include <iomanip>
#include "MtrxHeader.h"
float Mtrx::determinant_utility(vector<vector<float>>& mtrx, int mtrx_size) {
	float determinant = 0;
	if (mtrx_size == 1) {
		return mtrx[0][0];
	}
	if (mtrx_size == 2) {
		return (mtrx[0][0] * mtrx[1][1]) - (mtrx[0][1] * mtrx[1][0]);
	}
	vector<vector<float>> temp(mtrx_size, vector<float>(mtrx_size));
	int sign = 1;
	for (int i = 0; i < mtrx_size; i++) {
		subMatrix(mtrx, temp, 0, i, mtrx_size);
		determinant += sign * mtrx[0][i] * determinant_utility(temp, mtrx_size - 1);
		sign = -sign;
	}
	return determinant;
}

void Mtrx::subMatrix(vector<vector<float>>& mtrx, vector<vector<float>>& temp, int p, int q, int n) {
	int i = 0, j = 0;
	//  Заполнение субматрицы
	for (int row = 0; row < n; ++row) {
		for (int col = 0; col < n; ++col) {
			//пропуск если текущая строка или столбец не соответствует текущему
			//элемент строка и столбец
			if (row != p && col != q) {
				temp[i][j++] = mtrx[row][col];
				if (j == n - 1) {
					j = 0;
					++i;
				}
			}
		}
	}
}

void Mtrx::init(const vector<float>& input_values, const int& size_y, const int& size_x)
{
	vector<float> tmp_vector;
	tmp_vector.resize(size_x);
	for (size_t y = 0; y < size_y; ++y)
		mtrx.push_back(tmp_vector);
	int current_index = 0;
	for (size_t y = 0; y < size_y; ++y)
		for (size_t x = 0; x < size_x; ++x)
		{
			mtrx[y][x] = input_values[current_index];
			current_index++;
		}
	return;
}

void Mtrx::clear_current_mtrx()
{
	mtrx.clear();
}

void Mtrx::print_mtrx()
{
	for (int y = 0; y < mtrx.size(); ++y)
	{
		for (int x = 0; x < mtrx[y].size(); ++x)
		{
			std::cout << std::left<<std::setw(15)<<mtrx[y][x] << std::setw(15);
		}
		std::cout << std::endl;
	}
}

int Mtrx::get_y_size()
{
	return mtrx.size();
}

int Mtrx::get_x_size()
{
	return mtrx[0].size();
}

float Mtrx::get_elm_by_index(int x_index, int y_index)
{
	return mtrx[y_index][x_index];
}

void Mtrx::set_elm_by_index(int& x_index, int& y_index, float& elm)
{
	mtrx[y_index][x_index] = elm;
	return;
}

vector<vector<float>> Mtrx::get_current_mtrx()
{
	return mtrx;
}

vector<float> Mtrx::get_line_by_index(int y_index)
{
	return mtrx[y_index];
}

vector<float> Mtrx::get_column_by_index(int x_index)
{
	vector<float> column;
	for (int y = 0; y < get_y_size(); ++y)
	{
		column.push_back(mtrx[y][x_index]);
	}
	return column;
}
//mtrx sum+
const Mtrx Mtrx::operator+(Mtrx& right)
{
	Mtrx addition_res;
	vector<float> result_values;
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			result_values.push_back(this->get_elm_by_index(x, y) + right.get_elm_by_index(x, y));
		}
	addition_res.init(result_values, this->get_x_size(), right.get_y_size());
	return addition_res;
}
//mtrx sum+=
const void Mtrx::operator+=(Mtrx& right)
{
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			float set_elm = this->get_elm_by_index(x, y) + right.get_elm_by_index(x, y);
			this->set_elm_by_index(x, y, set_elm);
		}
	return;
}
//mtrx difference-
const Mtrx Mtrx::operator-(Mtrx& right)
{
	Mtrx difference_res;
	vector<float> result_values;
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			result_values.push_back(this->get_elm_by_index(x, y) - right.get_elm_by_index(x, y));
		}
	difference_res.init(result_values, this->get_x_size(), right.get_y_size());
	return difference_res;
}
//mtrx difference-=
const void Mtrx::operator-=(Mtrx& right)
{
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			float set_elm = this->get_elm_by_index(x, y) - right.get_elm_by_index(x, y);
			this->set_elm_by_index(x, y, set_elm);
		}
	return;
}
//mtrx sum+(value)
const Mtrx Mtrx::operator+(float addition_value)
{
	Mtrx addition_res;
	vector<float> result_values;
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			result_values.push_back(this->get_elm_by_index(x, y) + addition_value);
		}
	addition_res.init(result_values, this->get_x_size(), this->get_y_size());
	return addition_res;
}
//mtrx sum+=(value)
const void Mtrx::operator+=(float addition_value)
{
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			float set_elm = this->get_elm_by_index(x, y) + addition_value;
			this->set_elm_by_index(x, y, set_elm);
		}
	return;
}
//mtrx difference-(value)
const Mtrx Mtrx::operator-(float difference_value)
{
	Mtrx difference_res;
	vector<float> result_values;
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			result_values.push_back(this->get_elm_by_index(x, y) - difference_value);
		}
	difference_res.init(result_values, this->get_x_size(), this->get_y_size());
	return difference_res;
}
//mtrx difference-=(value)
const void Mtrx::operator-=(float addition_value)
{
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			float set_elm = this->get_elm_by_index(x, y) - addition_value;
			this->set_elm_by_index(x, y, set_elm);
		}
	return;
}
//check mtrx rows and columns(possibility for multiplying)
bool Mtrx::check_multiplication_possibility(Mtrx& right)
{
	if (this->get_y_size() == right.get_x_size())
		return true;
	else
		return false;
}
//mtrx multiplication*
const Mtrx Mtrx::operator*(Mtrx& right)
{
	Mtrx multiplication_res;
	float tmp_res = 0;
	vector<float> result_values;
	vector<vector<float>> tmp_left_mtrx;
	vector<vector<float>> tmp_right_mtrx;
	for (int y = 0; y < this->get_y_size(); ++y)
		tmp_left_mtrx.push_back(this->get_line_by_index(y));
	for (int x = 0; x < right.get_x_size(); ++x)
		tmp_right_mtrx.push_back(right.get_column_by_index(x));
	for (int i = 0; i < tmp_left_mtrx.size(); ++i)
	{
		for (int j = 0; j < tmp_right_mtrx.size(); ++j)
		{
			tmp_res = 0;
			for (int z = 0; z < tmp_right_mtrx[j].size(); ++z)
			{
				tmp_res += tmp_left_mtrx[i][z] * tmp_right_mtrx[j][z];
			}
			result_values.push_back(tmp_res);
		}
	}
	multiplication_res.init(result_values, this->get_y_size(), right.get_x_size());
	return multiplication_res;
}
//mtrx multiplication*(value)
const Mtrx Mtrx::operator*(float multiplication_value)
{
	Mtrx multiplication_res;
	vector<float> result_values;
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			result_values.push_back(this->get_elm_by_index(x, y) * multiplication_value);
		}
	multiplication_res.init(result_values, this->get_x_size(), this->get_y_size());
	return multiplication_res;
}
//mtrx multiplication*=(value)
const void Mtrx::operator*=(float multiplication_value)
{
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			float set_elm = this->get_elm_by_index(x, y) * multiplication_value;
			this->set_elm_by_index(x, y, set_elm);
		}
	return;
}
//mtrx division/(value)
const Mtrx Mtrx::operator/(float division_value)
{
	Mtrx division_res;
	vector<float> result_values;
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			result_values.push_back(this->get_elm_by_index(x, y) / division_value);
		}
	division_res.init(result_values, this->get_x_size(), this->get_y_size());
	return division_res;
}
//mtrx multiplication*=(value)
const void Mtrx::operator/=(float division_value)
{
	for (int y = 0; y < this->get_y_size(); ++y)
		for (int x = 0; x < this->get_x_size(); ++x)
		{
			float set_elm = this->get_elm_by_index(x, y) / division_value;
			this->set_elm_by_index(x, y, set_elm);
		}
	return;
}
//mtrx involution^
const Mtrx Mtrx::operator^(int involution_value)
{
	Mtrx res_mtrx;
	Mtrx tmp_mtrx = *this;
	for (int i = 1; i < involution_value; ++i)
	{
		res_mtrx = tmp_mtrx * (*this);
		tmp_mtrx = res_mtrx;
	}
	return res_mtrx;
}
//mtrx involution^=
const void Mtrx::operator^=(int involution_value)
{
	Mtrx res_mtrx;
	Mtrx tmp_mtrx = *this;
	for (int i = 1; i < involution_value; ++i)
	{
		res_mtrx = tmp_mtrx * (*this);
		tmp_mtrx = res_mtrx;
	}
	*this = res_mtrx;
}

float Mtrx::determinant()
{
	vector<vector<float>> mtrx = this->get_current_mtrx();
	float determinant = determinant_utility(mtrx, mtrx.size());
	return determinant;
}

float Mtrx::M_normal_mtrx()
{
	vector<float> values;
	for (int i = 0; i < this->get_y_size(); ++i)
	{
		float value = 0;
		for (auto& s : this->get_line_by_index(i))
		{
			value += s;
			++s;
		}
		values.push_back(value);
	}
	float M_norm = values[0];
	for (int i = 1; i < values.size(); ++i)
		if (M_norm < values[i])
			M_norm = values[i];
	return M_norm;
}

float Mtrx::L_normal_mtrx()
{
	vector<float> values;
	for (int i = 0; i < this->get_x_size(); ++i)
	{
		float value = 0;
		for (auto& s : this->get_column_by_index(i))
		{
			value += s;
			++s;
		}
		values.push_back(value);
	}
	float L_norm = values[0];
	for (int i = 1; i < values.size(); ++i)
		if (L_norm < values[i])
			L_norm = values[i];
	return L_norm;
}

float Mtrx::K_normal_mtrx()
{
	vector<float> values;
	for (int i = 0; i < this->get_y_size(); ++i)
	{
		float value = 0;
		for (auto& s : this->get_line_by_index(i))
		{
			value += pow(s, 2.0);
			++s;
		}
		values.push_back(value);
	}
	float K_norm = 0;
	for (int i = 0; i < values.size(); ++i)
		K_norm += values[i];
	return sqrt(K_norm);
}
