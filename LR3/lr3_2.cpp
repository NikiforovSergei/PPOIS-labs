#include <iostream>
#include <vector>
#include "Matrix.h"
using namespace std;

int main()
{
	vector<vector<int>> vec;
	Matrix<int> a;
	/*add nodes with data 5 8 9*/
	a.add_node(5);
	a.add_node(8);
	a.add_node(9);

	/*set edges between 0 2 & 2 1*/
	a.set_edge(0, 2);
	a.set_edge(2, 1);

	/*print matrix*/
	vec = a.get_matrix();
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}

	/*print data from vertex number 0*/
	cout << a.get_data(0) << endl;
	
	/*delete edge between 0 2 */
	a.delete_edge(0, 2);

	/*print matrix*/
	vec = a.get_matrix();
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	/*let's return the edge 0 2 and delete vertex 0*/
	a.set_edge(0, 2);

	a.delete_vertex(0);

	/*print matrix*/
	vec = a.get_matrix();
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << a.get_data(0) << endl;

	cout << "comparison\n";
	Matrix<int> d, c;
	d.add_node(5);
	d.add_node(8);
	d.add_node(9);
	d.set_edge(0, 1);

	vec = d.get_matrix();
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	c.add_node(5);
	c.add_node(8);
	c.add_node(9);
	c.set_edge(0, 1);

	vec = c.get_matrix();
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	bool t = (d == c);
	cout << t << endl;
	t = d == a;
	cout << t << endl;
	t = (d != a);
	cout << t << endl;
	t = (d > a);
	cout << t << endl;
	t = (d < a);
	cout << t << endl;
	
	cout << "\n iterator vertex\n";
	Matrix<int>::M_iterator_vertex it;

	it = c;
	pair<int, int> dfas = *it;
	cout << dfas.first << " " << dfas.second << endl;

	cout << "number el 0  " << c.get_data(0) << endl;

	cout << "it++\n";
	++it;

	dfas = *it;
	cout << dfas.first << " " << dfas.second << endl;

	cout << "number el 0  " << c.get_data(1) << endl << endl;

	cout << "\n iterator edge \n";
	Matrix<int>::M_iterator_edge it1;

	it1 = c;

	pair<int, int> edges_ = *it1;

	cout << "vertex from " << edges_.first << "		vertex to " << edges_.second << endl;

	++it1;
	edges_ = *it1;
	cout << "vertex from " << edges_.first << "		vertex to " << edges_.second << endl;

}