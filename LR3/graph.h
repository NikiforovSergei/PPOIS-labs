#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

template <typename type, typename A = std::allocator<type>>
class graph
{
private:

	struct tail
	{
		type key;
		tail* next_leader;
		tail* next_tail;
	};

	struct leader
	{
		type key;
		leader* next;
		tail* list;
	};

	leader* begin;
	int vertex_counter;
	int edges_counter;
	void print_edges(leader* vertex);
	leader* find_end();
	void delete_spisok(tail* value);
	void delete_tail(type value);
	

public:
	typedef std::pair<leader*, tail*> pair;
	class iterator_node;
	class iterator_edge;
	graph();
	graph(const graph& other);
	~graph();

	graph& operator=(const graph& other);
	bool operator ==(const graph& other);
	bool operator !=(const graph& other);
	bool operator >=(const graph& other);
	bool operator <=(const graph& other);
	bool operator >(const graph& other);
	bool operator <(const graph& other);

	bool add_vertex(type value);
	bool add_edge(type first, type second);
	void print();
	int get_vertex_counter();
	int get_edges_counter();
	int get_vertex_degree(type vertex);
	bool find_edge(type first, type second);
	bool delete_edge(type first, type second);
	bool delete_vertex(type first);
	bool empty();
	void clear(leader* value);
	leader* finder(type value);
	leader& operator [](const int& n);

	leader* get_begin();
	leader* get_end();	

	iterator_node Begin() { return get_begin(); }
	iterator_node End() { return get_end(); }
	
	iterator_edge eBegin(iterator_node& x)
	{ 
		return x.temp->list;
	}
	iterator_edge eEnd() 
	{ 
		return nullptr;
	}

	class iterator_node
	{
	public:
		leader* temp;
		iterator_node(leader* value) :temp(value)
		{}
		leader& operator++(int) { return *(temp = temp->next); }
		leader& operator++()
		{
			leader* t = temp;
			temp = temp->next;
			return *t;
		}
		bool operator !=(const iterator_node& it) { return temp != it.temp; }
		leader& operator*() { return *temp; }
	};
	
	class iterator_edge
	{
		tail* ttemp;
	public:
		iterator_edge(tail* value) :ttemp(value)
		{}
		tail& operator++(int) { return *(ttemp=ttemp->next_tail); }
		tail& operator++()
		{
			pair t = ttemp;
			ttemp=ttemp->next_tail;
			return *t;
		}
		bool operator !=(const iterator_edge& it) { return ttemp != it.ttemp; }
		tail& operator*(){ return *ttemp; }
	};
};

template<typename type,typename A>
inline graph<type,A>::graph()
{
	begin = nullptr;
	vertex_counter = 0;
	edges_counter = 0;
}

template<typename type, typename A>
inline graph<type,A>::graph(const graph<type,A>& other)
{
	leader* temp = other.begin;
	while (temp)
	{
		this->add_vertex(temp->key);		
		temp = temp->next;
	}
	
	temp = other.begin;
	while (temp)
	{
		tail* ttemp = temp->list;
		while (ttemp)
		{
			this->add_edge(temp->key, ttemp->key);
			ttemp = ttemp->next_tail;
		}
		temp = temp->next;
	}
}

template<typename type, typename A>
inline graph<type,A>::~graph()
{
	clear(get_begin());
}

template<typename type, typename A>
inline bool graph<type,A>::add_vertex(type value)
{
	if (vertex_counter)
	{
		if (!finder(value))
		{
			leader* temp = find_end();
			temp->next = new leader();
			temp = temp->next;
			temp->key = value;
			temp->next = nullptr;
			temp->list = nullptr;
			vertex_counter++;
			return 1;
		}
		std::cout << "Vertex has been added before\n";
		return 0;
	}
	else
	{
		begin = new leader();
		begin->next = nullptr;
		begin->list = nullptr;
		begin->key = value;
		vertex_counter++;
		return 1;
	}
	return 0;
}

template<typename type, typename A>
inline bool graph<type,A>::add_edge(type first, type second)
{
	if (finder(first) && finder(second))
	{
		if (find_edge(first, second)) return 0;
		if (first == second) return 0;

		leader* temp = finder(first);
		if (temp->list)
		{
			tail* ttemp = temp->list;

			while (ttemp->next_tail != nullptr)
				ttemp = ttemp->next_tail;

			ttemp->next_tail = new tail();
			ttemp = ttemp->next_tail;
			ttemp->next_tail = nullptr;
			ttemp->next_leader = finder(second)->list;
			ttemp->key = second;
		}
		else
		{
			temp->list = new tail();
			tail* ttemp = temp->list;
			ttemp->next_tail = nullptr;
			ttemp->next_leader = (finder(second))->list;
			ttemp->key = second;
		}
		edges_counter++;
		return 1;
	}
	else
	{
		std::cout << "there's no vertex such yours\n";
		return 0;
	}
}

template<typename type, typename A>
inline void graph<type,A>::print_edges(leader *vertex)
{
	tail* ttemp = vertex->list;
	while (ttemp != nullptr)
	{
		std::cout << "\t" << ttemp->key;
		ttemp = ttemp->next_tail;
	}
	std::cout << std::endl;
}

template<typename type, typename A>
inline void graph<type,A>::print()
{
	leader* temp = begin;
	while (temp != nullptr)
	{
		std::cout << temp->key <<"\n";
		print_edges(temp);
		temp = temp->next;
	}
	
}

template<typename type, typename A>
int graph<type,A>::get_vertex_counter()
{
	return vertex_counter;
}

template<typename type, typename A>
inline int graph<type,A>::get_edges_counter()
{
	return edges_counter;
}

template<typename type, typename A>
inline int graph<type,A>::get_vertex_degree(type vertex)
{
	leader* temp = finder(vertex);
	if (temp)
	{
		tail* ttemp = temp->list;
		int counter = 0;
		while (ttemp)
		{
			ttemp = ttemp->next_tail;
			counter++;
		}
		return counter;
	}
	else
		std::cout << "There's no vertex";
}

template<typename type, typename A>
inline bool graph<type,A>::find_edge(type first, type second)
{
	if (finder(first) && finder(second))
	{
		tail* ttemp  = finder(first)->list;
		while (ttemp)
		{
			if (ttemp->key == second)
				return 1;
			ttemp = ttemp->next_tail;
		}
	}
	return 0;
}

template<typename type, typename A>
inline bool graph<type,A>::delete_edge(type first, type second)
{
	if (finder(first) && finder(second))
	{
		leader* temp = finder(first);
		tail* ttemp = temp->list;
		while (ttemp)
		{
			if (ttemp->key == second)
			{
				if (ttemp == temp->list)
				{
					temp->list = temp->list->next_tail;
					delete ttemp;
					edges_counter--;
					return 1;
				}
				if (ttemp->next_tail == nullptr)
				{
					tail* prev = temp->list;
					while (prev->next_tail != ttemp)
						prev = prev->next_tail;
					prev->next_tail = nullptr;
					delete ttemp;
					edges_counter--;
					return 1;
				}
				else
				{
					tail* prev = temp->list;
					while (prev->next_tail->key != second)
						prev = prev->next_tail;
					prev->next_tail = prev->next_tail->next_tail;
					delete ttemp;
					edges_counter--;
					return 1;
				}
			}
			ttemp = ttemp->next_tail;
		}
	}
	return 0;
}

template<typename type, typename A>
inline bool graph<type,A>::delete_vertex(type first)
{
	leader* temp = finder(first);
	if (temp)
	{
		if (temp == begin)
		{
			delete_tail(first);
			delete_spisok(temp->list);
			begin = begin->next;
			delete temp;
			vertex_counter--;
			return 1;
		}
		if (temp->next == nullptr)
		{
			delete_tail(first);
			delete_spisok(temp->list);
			leader* prev = begin;
			while (prev->next != temp)
				prev = prev->next;
			prev->next = nullptr;
			delete temp;
			vertex_counter--;
			return 1;
		}
		else
		{
			delete_tail(first);
			delete_spisok(temp->list);
			leader* prev = begin;
			while (prev->next != temp)
				prev = prev->next;
			prev->next = prev->next->next;
			delete temp;
			vertex_counter--;
			return 1;
		}
		
	}
	return 0;
}

template<typename type, typename A>
inline bool graph<type,A>::empty()
{
	if (this->begin)
	{
		std::cout << "Not empty\n";
		return 1;
	}
	else
		std::cout <<"Empty\n";
	return 0;
}

template<typename type,  typename A>
inline void graph<type,A>::clear(leader* value)
{
	while (value != nullptr)
	{
		clear(value->next);
		delete_vertex(value->key);
		return;
	}
}

template<typename type, typename A>
inline typename graph<type, A>::leader& graph<type, A>::operator[](const int& n)
{
	if (n <= vertex_counter && n > 0)
	{
		leader* temp = begin;
		for (int i = 0; temp != nullptr; i++, temp = temp->next)
		{
			if (i == n) return *temp;
		}
	}
}

template<typename type, typename A>
inline  typename graph<type,A>::leader* graph<type,A>::get_begin()
{
	return begin;
}

template<typename type, typename A>
inline void graph<type,A>::delete_spisok(tail* value)
{
	while (value != nullptr)
	{
		delete_spisok(value->next_tail);
		edges_counter--;
		delete value;
		return;
	}
}

template<typename type, typename A>
inline void graph<type,A>::delete_tail(type value)
{
	if (finder(value))
	{
		leader* temp = begin;
		while (temp)
		{
			tail* ttemp = temp->list;
			while (ttemp)
			{
				if (ttemp->key == value)
				{
					if (ttemp == temp->list)
					{
						temp->list = ttemp->next_tail;
						delete ttemp;
						break;
					}
					if (ttemp->next_tail == nullptr)
					{
						tail* prev = temp->list;
						while (prev->next_tail != ttemp)
							prev = prev->next_tail;
						prev->next_tail = nullptr;
						delete ttemp;
						break;
					}
					else
					{
						tail* prev = temp->list;
						while (prev->next_tail->key != value)
							prev = prev->next_tail;
						prev->next_tail = prev->next_tail->next_tail;
						delete ttemp;
						break;
					}
				}
				ttemp = ttemp->next_tail;
			}
			temp = temp->next;
		}
	}
	return;
}

template<typename type, typename A>
inline typename graph<type, A>::leader* graph<type, A>::finder(type value)
{
	if (begin)
	{
		leader* temp = begin;
		while (temp->key != value)
		{
			temp = temp->next;
			if (temp == nullptr) return nullptr;
		}
		return temp;
	}
	return nullptr;
}

template<typename type, typename A>
inline typename graph<type,A>::leader* graph<type,A>::find_end()
{
	leader* temp = begin;
	while (temp->next != nullptr) temp = temp->next;
	return temp;
}

template<typename type, typename A>
inline typename graph<type,A>::leader* graph<type,A>::get_end()
{
	leader* temp = begin;
	while (temp) 
		temp = temp->next;
	return temp;
}

template<typename type, typename A>
inline typename graph<type,A>& graph<type,A>::operator =(const graph<type,A> &other)
{
	if (this->begin != nullptr)
		this->clear(this->begin);

	leader* temp = other.begin;

	while (temp)
	{
		this->add_vertex(temp->key);
		temp = temp->next;
	}

	temp = other.begin;

	while (temp)
	{
		tail* ttemp = temp->list;
		while (ttemp)
		{
			this->add_edge(temp->key, ttemp->key);
			ttemp = ttemp->next_tail;
		}
		temp = temp->next;
	}
	return *this;
}

template<typename type, typename A>
inline bool graph<type,A>::operator ==(const graph<type,A>& other)
{
	leader* temp_this = this->begin;
	leader* temp_other = other.begin;
	while (temp_this && temp_other)
	{
		if (temp_this->key != temp_other->key)
			return false;
		tail* ttemp_this = temp_this->list;
		tail* ttemp_other = temp_other->list;
		while (ttemp_this && ttemp_other)
		{
			if (ttemp_this->key != ttemp_other->key)
				return false;
			ttemp_this = ttemp_this->next_tail;
			ttemp_other = ttemp_other->next_tail;
		}
		temp_this = temp_this->next;
		temp_other = temp_other->next;
	}
	return true;
}

template<typename type, typename A>
inline bool graph<type,A>::operator !=(const graph& other)
{
	return !operator==(other);
}

template<typename type, typename A>
inline bool graph<type,A>::operator >=(const graph& other)
{
	return this->vertex_counter > other.vertex_counter || operator==(other);
}

template<typename type, typename A>
inline bool graph<type,A>::operator <=(const graph& other)
{
	return this->vertex_counter < other.vertex_counter || operator==(other);
}

template<typename type, typename A>
inline bool graph<type,A>::operator >(const graph& other)
{
	return this->vertex_counter > other.vertex_counter;
}

template<typename type, typename A>
inline bool graph<type,A>::operator <(const graph& other)
{
	return this->vertex_counter < other.vertex_counter;
}


#endif 

