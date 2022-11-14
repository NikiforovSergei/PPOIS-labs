#pragma once
#include <vector>

using namespace std;

template<typename T>
class Matrix
{
private:
	vector<vector<T>> matrix;
	vector<T> node_data;
	int num_edges;


public:

	Matrix() {
		num_edges = 0;
	}

	~Matrix() {
		node_data.clear();
		matrix.clear();
	}

	Matrix(const Matrix& obj);

	void add_node(T data);
	
	void set_edge(int a, int b);

	vector<vector<T>> get_matrix();

	T get_data(int num);//vertex number

	void delete_vertex(int num);

	void delete_edge(int num1, int num2);

	bool is_vertex(int num, T data);// checks is vertex num has T data

	bool is_edge(int num1, int num2);

	int get_num_vertices();

	int get_num_edges();

	pair<int, T> get_vertex(int num);

	void operator=(const Matrix<T>& obj);

	bool operator==(const Matrix<T>& obj);

	bool operator!=(const Matrix<T>& obj);

	bool operator>=(const Matrix<T>& obj);

	bool operator<=(const Matrix<T>& obj);

	bool operator<(const Matrix<T>& obj);

	bool operator>(const Matrix<T>& obj);
	
	pair<int, T&> begin();

	pair<int, T&> end();
	
	class M_iterator_vertex {
	private:
		int vertex_pos;
		Matrix local_matrix;

	public:

		M_iterator_vertex() {
			vertex_pos = 0;
		}

		void operator=(Matrix& a) {
			local_matrix = a;
		}

		pair<int, T> & operator*() {
			pair<int, T> verteces;
			verteces.first = vertex_pos;
			verteces.second = local_matrix.node_data[vertex_pos];
			return verteces;
		}

		M_iterator_vertex &operator++() {
			vertex_pos++;
			if (vertex_pos > local_matrix.matrix.size() - 1) {
				throw"iterator outside container";
			}
			//cout << "vertex pos   " << vertex_pos << endl;
		}

		M_iterator_vertex &operator--() {
			vertex_pos--;
			if (vertex_pos < 0) {
				throw"iterator less than zero";
			}
		}
	};

	class M_iterator_edge {
	private:
		Matrix local_matrix;
		int edge_pos;
		vector<vector<int>> edges;

		void check_edges() {
			if (edges.size() != 0) {
				edges.clear();
			}
			vector<int> _vec;

			int edges_size = local_matrix.matrix.size();
			
			for (int i = 0; i < local_matrix.matrix.size(); i++)
			{
				for (int j= 0; j < edges_size; j++)
				{
					if (local_matrix.matrix[i][j] == 1) {
						_vec.push_back(i);
						_vec.push_back(j);
						cout << i << " " << j << endl;
						edges.push_back(_vec);
						_vec.clear();
					}
				}
			}

			cout <<"edges num  " << edges.size() << endl;
		}

	public:
		M_iterator_edge() {
			edge_pos = 0;
		}

		void operator=(Matrix& a) {
			local_matrix = a;
		}

		pair<int, int>& operator*() {
			this->check_edges();
			pair<int, int> edges_pair;

			edges_pair.first = edges[edge_pos][1];
			edges_pair.second = edges[edge_pos][0];
			return edges_pair;
		}

		M_iterator_edge &operator++() {
			edge_pos++;
			if (local_matrix.num_edges - 1 < edge_pos) {
				throw"iterator outside container";
			}
		}

		M_iterator_edge &operator--() {
			edge_pos--;
			if (edge_pos < 0) {
				throw"iterator less than zero";
			}
		}
	};

};








template<typename T>
inline Matrix<T>::Matrix(const Matrix& obj)
{
	this->matrix = obj.matrix;
	this->node_data = obj.node_data;
	this->num_edges = obj.num_edges;
}

template<typename T>
void Matrix<T>::add_node(T data)
{
	vector<T> add_vector;
	
	if (matrix.size() == 0) {
		add_vector.push_back(0);
		matrix.push_back(add_vector);
	}
	else {
		for (int i = 0; i < matrix[0].size(); i++)
		{
			add_vector.push_back(0);
		}

		matrix.push_back(add_vector);

		for (int i = 0; i < matrix.size(); i++)
		{
			matrix[i].push_back(0);
		}
	}
	
	node_data.push_back(data);
}

template<typename T>
inline void Matrix<T>::set_edge(int a, int b) // put numbers of vertices
{
	matrix[a][b] = 1;
	matrix[b][a] = 1;

	num_edges++;
}

template<typename T>
inline vector<vector<T>> Matrix<T>::get_matrix()
{
	return matrix;
}

template<typename T>
inline T Matrix<T>::get_data(int num)
{
	return node_data[num];
}

template<typename T>
inline void Matrix<T>::delete_vertex(int num)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix[i][num] = 0;
	}

	node_data.erase(node_data.begin() + num);

	matrix.erase(matrix.begin() + num);

	for (int i = 0; i < matrix.size(); i++) {
		matrix[i].erase(matrix[i].begin() + num);
	}
}

template<typename T>
inline void Matrix<T>::delete_edge(int num1, int num2)
{
	if (matrix[num1][num2] == 1) {
		matrix[num1][num2] = 0;
		matrix[num2][num1] = 0;
	}

	num_edges--;
}

template<typename T>
inline bool Matrix<T>::is_vertex(int num, T data)
{
	if (node_data[num] == data) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
inline bool Matrix<T>::is_edge(int num1, int num2)
{
	if (matrix[num1][num2] == 1) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
inline int Matrix<T>::get_num_vertices()
{
	return matrix.size();
}

template<typename T>
inline int Matrix<T>::get_num_edges()
{
	return num_edges;
}

template<typename T>
inline pair<int, T> Matrix<T>::get_vertex(int num)
{
	pair<int, T> a;
	a.first = num;
	a.second = node_data[num];
	return a;
}

template<typename T>
inline void Matrix<T>::operator=(const Matrix<T>& obj)
{
	this->matrix = obj.matrix;
	this->node_data = obj.node_data;
	this->num_edges = obj.num_edges;
}

template<typename T>
inline bool Matrix<T>::operator==(const Matrix<T>& obj)
{
	if (this->matrix.size() == obj.matrix.size()) {
		for (int i = 0; i < this->matrix.size(); i++)
		{
			for (int j = 0; j < this->matrix[i].size(); j++)
			{
				if (this->matrix[i][j] != obj.matrix[i][j]) {
					return false;
				}
			}
		}
	}
	else {
		return false;
	}
	
	return true;
}

template<typename T>
inline bool Matrix<T>::operator!=(const Matrix<T>& obj)
{
	if (this->matrix.size() == obj.matrix.size()) {
		for (int i = 0; i < this->matrix.size(); i++)
		{
			for (int j = 0; j < this->matrix[i].size(); j++)
			{
				if (this->matrix[i][j] != obj.matrix[i][j]) {
					return true;
				}
			}
		}
	}

	return false;
}

template<typename T>
inline bool Matrix<T>::operator>=(const Matrix<T>& obj)
{
	bool a, b;
	a = false;
	b = false;
	if (this == obj) {
		a = true;
	}
	if (this > obj) {
		b = true;
	}

	if (a == true || b == true) {
		return true;
	}

	return false;
}

template<typename T>
inline bool Matrix<T>::operator<=(const Matrix<T>& obj)
{
	bool a, b;
	a = false;
	b = false;
	if (this == obj) {
		a = true;
	}
	if (this < obj) {
		b = true;
	}

	if (a == true || b == true) {
		return true;
	}

	return false;
	return false;
}

template<typename T>
inline bool Matrix<T>::operator<(const Matrix<T>& obj)
{
	if (this->matrix.size() < obj.matrix.size()) {
		return true;
	}
	if (this->matrix.size() == obj.matrix.size()) {
		if (this->num_edges < obj.num_edges) {
			return true;
		}
	}

	return false;
}

template<typename T>
inline bool Matrix<T>::operator>(const Matrix<T>& obj)
{
	if (this->matrix.size() > obj.matrix.size()) {
		return true;
	}
	if (this->matrix.size() == obj.matrix.size()) {
		if (this->num_edges > obj.num_edges) {
			return true;
		}
	}

	return false;
}

template<typename T>
inline pair<int, T&> Matrix<T>::begin()
{
	pair<int, T&> a;
	if (matrix.size() > 0) {
		a.first = 0;
		a.second = node_data[0];
	}
	else {
		a.first = nullptr;
		a.second = nullptr;
	}
	return a;
}

template<typename T>
inline pair<int, T&> Matrix<T>::end()
{
	pair<int, T&> a;
	if (matrix.size() > 0) {
		a.first = matrix.size() - 1;
		a.second = node_data[matrix.size() - 1];
	}
	else {
		a.first = nullptr;
		a.second = nullptr;
	}
	return a;
}

