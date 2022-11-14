#pragma once

#ifndef _ADJECENCY_LIST_
#define _ADJECENCY_LIST_

#include <vector>
#include <iostream>
#include <string>

template<typename T>
class adjecency_list;

template<typename T>
class vertex;


template<typename T>
std::ostream& operator<< (std::ostream& ost, const adjecency_list<T>& graph);

template<typename T>
std::ostream& operator<<(std::ostream& ost, const vertex<T>& vert);


template<typename T>
class vertex
{
private:
	friend std::ostream& operator<< <T>(std::ostream& ost, const vertex<T>& vert);
	friend class adjecency_list<T>;

	//Итератор для перебора смежных вершин
	template<typename Iter>
	class AdjecentVertexIterator
	{
	public:
		typedef Iter iterator_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;
		typedef ptrdiff_t difference_type;

		pointer _VertPtr;

	protected:
		friend class vertex;
		friend class adjecency_list<T>;
		int vector_length;
		int position;
		pointer* vert;

	private:
		AdjecentVertexIterator(Iter** ptr, int position, int vector_length) : vert(ptr), position(position), vector_length(vector_length), _VertPtr(*ptr) {}

	public:
		AdjecentVertexIterator(const AdjecentVertexIterator& other) : vert(other.vert), position(other.position), vector_length(other.vector_length), _VertPtr(*(other.vert)) {}

		AdjecentVertexIterator& operator= (const  AdjecentVertexIterator& other)
		{
			vert = other.vert;
			position = other.position;
			vector_length = other.vector_length;
			_VertPtr = *vert;
			return *this;
		}

		bool operator == (const AdjecentVertexIterator& other) { return vert == other.vert; }

		bool operator != (const AdjecentVertexIterator& other) { return vert != other.vert; }

		typename AdjecentVertexIterator::reference operator*() const { return *(*vert); }

		virtual AdjecentVertexIterator& operator++()
		{
			if (position == vector_length) throw std::exception("can't increment iterator past end");
			++vert;
			_VertPtr = *vert;
			++position;

			return *this;
		}

		virtual AdjecentVertexIterator& operator++(int)
		{
			if (position == vector_length) throw std::exception("can't increment iterator past end");
			AdjecentVertexIterator temp = *this;
			++vert;
			_VertPtr = *vert;
			++position;

			return temp;
		}

		virtual AdjecentVertexIterator& operator--()
		{
			if (position == 0) throw std::exception("can't dencrement iterator before begin");
			--vert;
			_VertPtr = *vert;
			--position;

			return *this;
		}

		virtual AdjecentVertexIterator& operator--(int)
		{
			if (position == 0) throw std::exception("can't dencrement iterator before begin");
			AdjecentVertexIterator temp = *this;
			--vert;
			_VertPtr = *vert;
			--position;

			return temp;
		}
	};

	//Reverse итератор для перебора смежных вершин
	template<typename Iter>
	class AdjecentVertexReverseIterator : public AdjecentVertexIterator<Iter>
	{
	private:
		friend class vertex;

		AdjecentVertexReverseIterator(Iter** ptr, int position, int vector_length) : AdjecentVertexIterator<Iter>(ptr, position, vector_length) {}

	public:
		AdjecentVertexReverseIterator(const AdjecentVertexIterator<Iter>& other) : AdjecentVertexIterator<Iter>(other) {}

		AdjecentVertexReverseIterator& operator= (const AdjecentVertexIterator<Iter>& other)
		{
			this->vert = other.vert;
			this->_VertPtr = *(this->vert);
			this->position = other.position;
			this->vector_length = other.vector_length;
			return *this;
		}

		virtual AdjecentVertexReverseIterator& operator++() override
		{
			if (this->position == 0) throw std::exception("can't increment reverse iterator before begin");
			--this->vert;
			this->_VertPtr = *(this->vert);
			--this->position;

			return *this;
		}

		virtual AdjecentVertexReverseIterator& operator++(int) override
		{
			if (this->position == 0) throw std::exception("can't increment reverse iterator befor begin");
			AdjecentVertexReverseIterator temp = *this;
			--this->vert;
			this->_VertPtr = *(this->vert);
			--this->position;

			return temp;
		}

		virtual AdjecentVertexReverseIterator& operator--() override
		{
			if (this->position == this->vector_length) throw std::exception("can't dencrement reverse iterator past end");
			++this->vert;
			this->_VertPtr = *(this->vert);
			++this->position;

			return *this;
		}

		AdjecentVertexReverseIterator& operator--(int) override
		{
			if (this->position == this->vector_length) throw std::exception("can't dencrement reverse iterator past end");
			AdjecentVertexReverseIterator temp = *this;
			++this->vert;
			this->_VertPtr = *(this->vert);
			++this->position;

			return temp;
		}
	};

	//Итератор для перебора инцидентных вершине рёбер
	template<typename Iter>
	class IncidentalEdgeIterator
	{
	public:
		typedef Iter iterator_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef std::pair<Iter, Iter> reference;
		typedef iterator_type* pointer;
		typedef ptrdiff_t difference_type;

		pointer _FirstVertexPtr;
		pointer _SecondVertexPtr;

	protected:
		friend class vertex;
		int position;
		int vector_length;
		pointer* second_vert;

		IncidentalEdgeIterator(pointer _FirstVertexPtr, pointer* second_vert, int position, int vector_length) :
			_FirstVertexPtr(_FirstVertexPtr), _SecondVertexPtr(*second_vert), second_vert(second_vert), position(position), vector_length(vector_length) {}

	public:
		IncidentalEdgeIterator(const IncidentalEdgeIterator& other) :
			_FirstVertexPtr(other._FirstVertexPtr), second_vert(other.second_vert), _SecondVertexPtr(*(other.second_vert)), position(other.position), vector_length(other.vector_length) {}

		IncidentalEdgeIterator& operator=(const IncidentalEdgeIterator& other)
		{
			_FirstVertexPtr = other._FirstVertexPtr;
			second_vert = other.second_vert;
			_SecondVertexPtr = *second_vert;
			position = other.position;
			vector_length = other.vector_length;
			return *this;
		}

		bool operator == (const IncidentalEdgeIterator& other) { return second_vert == other.second_vert; }

		bool operator != (const IncidentalEdgeIterator& other) { return second_vert != other.second_vert; }

		typename IncidentalEdgeIterator::reference operator* () const { return std::pair<Iter, Iter>(*_FirstVertexPtr, *_SecondVertexPtr); }

		virtual IncidentalEdgeIterator& operator++()
		{
			if (position == vector_length) throw std::exception("can't increment iterator past end");
			++second_vert;
			_SecondVertexPtr = *second_vert;
			++position;


			return *this;
		}

		virtual IncidentalEdgeIterator& operator++(int)
		{
			if (position == vector_length) throw std::exception("can't increment iterator past end");
			IncidentalEdgeIterator temp = *this;
			++second_vert;
			_SecondVertexPtr = *second_vert;
			++position;

			return temp;
		}

		virtual IncidentalEdgeIterator& operator--()
		{
			if (position == 0) throw std::exception("can't dencrement iterator before begin");
			--second_vert;
			_SecondVertexPtr = *second_vert;
			--position;

			return *this;
		}

		virtual IncidentalEdgeIterator& operator--(int)
		{
			if (position == 0) throw std::exception("can't dencrement iterator before begin");
			IncidentalEdgeIterator temp = *this;
			--second_vert;
			_SecondVertexPtr = *second_vert;
			--position;

			return temp;
		}
	};

	//Reverse итератор для перебора инцидентных вершине рёбер
	template<typename Iter>
	class IncidentalEdgeReverseIterator : public IncidentalEdgeIterator<Iter>
	{
	private:
		friend class vertex;

		IncidentalEdgeReverseIterator(Iter* _FirstVertexPtr, Iter** second_vert, int position, int vector_length) : IncidentalEdgeIterator<Iter>(_FirstVertexPtr, second_vert, position, vector_length)
		{}

	public:
		IncidentalEdgeReverseIterator(const IncidentalEdgeIterator<Iter>& other) : IncidentalEdgeIterator<Iter>(other)
		{}

		IncidentalEdgeReverseIterator& operator= (const IncidentalEdgeIterator<Iter>& other)
		{
			this->second_vert = other.second_vert;
			this->_FirstVertexPtr = other._FirstVertexPtr;
			this->_SecondVertPtr = *(this->second_vert);
			this->position = other.position;
			this->vector_length = other.vector_length;
			return *this;
		}

		virtual IncidentalEdgeReverseIterator& operator++() override
		{
			if (this->position == 0) throw std::exception("can't increment reverse iterator before begin");
			--this->second_vert;
			this->_SecondVertexPtr = *(this->second_vert);
			--this->position;

			return *this;
		}

		virtual IncidentalEdgeReverseIterator& operator++(int) override
		{
			if (this->position == 0) throw std::exception("can't increment reverse iterator befor begin");
			IncidentalEdgeReverseIterator temp = *this;
			--this->second_vert;
			this->_SecondVertexPtr = *(this->second_vert);
			--this->position;

			return temp;
		}

		virtual IncidentalEdgeReverseIterator& operator--() override
		{
			if (this->position == this->vector_length) throw std::exception("can't dencrement reverse iterator past end");
			++this->second_vert;
			this->_SecondVertexPtr = *(this->second_vert);
			++this->position;

			return *this;
		}

		virtual IncidentalEdgeReverseIterator& operator--(int) override
		{
			if (this->position == this->vector_length) throw std::exception("can't dencrement reverse iterator past end");
			IncidentalEdgeReverseIterator temp = *this;
			++this->seccond_vert;
			this->_SecondVertexPtr = *(this->second_vert);
			++this->position;

			return temp;
		}
	};

	T name;
	std::vector<vertex<T>*> adjecent_vertexes;

public:

	//Итератор для перебора смежных вершин
	typedef AdjecentVertexIterator<vertex<T>> iterator_adjvert;
	typedef AdjecentVertexIterator<const vertex<T>> const_iterator_adjvert;

	//Reverse итератор для перебора смежных вершин
	typedef AdjecentVertexReverseIterator<vertex<T>> reverse_iterator_adjvert;
	typedef AdjecentVertexReverseIterator<const vertex<T>> const_reverse_iterator_adjvert;

	//Итератор для перебора инцидентных рёбер
	typedef IncidentalEdgeIterator<vertex<T>> iterator_incedge;
	typedef IncidentalEdgeIterator<const vertex<T>> const_iterator_incedge;

	//Reverse итератор для перебора инцидентных рёбер
	typedef IncidentalEdgeReverseIterator<vertex<T>> reverse_iterator_incedge;
	typedef IncidentalEdgeReverseIterator<const vertex<T>> const_reverse_iterator_incedge;


	vertex();
	vertex(const T& name);
	vertex(T&& name);

	vertex(const vertex<T>& other);
	vertex<T>& operator=(const vertex<T>& other);


	void push_vertex(vertex<T>* adjecent_vertex);
	void push_vertex(iterator_adjvert& adjecent_vertex_iterator);

	void erase(vertex<T>* adjecent_vertex);
	void erase(iterator_adjvert& adjecent_vertex_iterator);

	bool operator==(const vertex<T>& other);
	bool operator!=(const vertex<T>& other);

	bool operator > (const vertex<T>& other);
	bool operator >= (const vertex<T>& other);

	bool operator < (const vertex<T>& other);
	bool operator <= (const vertex<T>& other);

	int degree();
	int degree() const;

	const T& get_name();
	const T& get_name() const;


	//Итератор для перебора смежных вершин
	iterator_adjvert begin();
	iterator_adjvert end();

	const_iterator_adjvert begin() const;
	const_iterator_adjvert end() const;

	//Reverse итератор для перебора смежных вершин
	reverse_iterator_adjvert rbegin();
	reverse_iterator_adjvert rend();

	const_reverse_iterator_adjvert rbegin() const;
	const_reverse_iterator_adjvert rend() const;


	//Итератор для перебора инцидентных рёбер
	iterator_incedge incedge_begin();
	iterator_incedge incedge_end();

	const_iterator_incedge incedge_begin() const;
	const_iterator_incedge incedge_end() const;

	//Reverse итератор для перебора смежных вершин
	reverse_iterator_incedge incedge_rbegin();
	reverse_iterator_incedge incedge_rend();

	const_reverse_iterator_incedge incedge_rbegin() const;
	const_reverse_iterator_incedge incedge_rend() const;

};


template<typename T>
std::ostream& operator<< <T>(std::ostream& ost, const vertex<T>& vert)
{
	ost << vert.name;
	return ost;
}

template<typename T>
vertex<T>::vertex() {}

template<typename T>
vertex<T>::vertex(T&& name)
{
	this->name = name;
}

template<typename T>
vertex<T>::vertex(const T& name)
{
	this->name = name;
}

template<typename T>
vertex<T>::vertex(const vertex<T>& other)
{
	this->name = other.name;
	this->adjecent_vertexes = other.adjecent_vertexes;
}

template<typename T>
vertex<T>& vertex<T>::operator=(const vertex<T>& other)
{
	name = other.name;
	adjecent_vertexes = other.adjecent_vertexes;
	return *this;
}

template<typename T>
void vertex<T>::push_vertex(vertex<T>* adjecent_vertex)
{
	if (std::find(adjecent_vertexes.begin(), adjecent_vertexes.end(), adjecent_vertex) == adjecent_vertexes.end())
	{
		if (adjecent_vertex->name != name)
		{
			adjecent_vertexes.push_back(adjecent_vertex);
			adjecent_vertex->adjecent_vertexes.push_back(this);
		}
		else adjecent_vertexes.push_back(adjecent_vertex);
	}
	else { throw std::exception("You try to make the second edge between two vertexes."); }
}

template<typename T>
void vertex<T>::push_vertex(iterator_adjvert& adjecent_vertex_iterator)
{
	try { ++adjecent_vertex_iterator; }
	catch (std::exception& ex) { throw std::exception("you can't push end iterator"); }
	--adjecent_vertex_iterator;
	push_vertex(adjecent_vertex_iterator._VertPtr);
}

template<typename T>
void vertex<T>::erase(vertex<T>* adjecent_vertex)
{
	auto iter = std::find_if(adjecent_vertexes.begin(), adjecent_vertexes.end(), [adjecent_vertex](vertex<T>* vert_ptr) {return adjecent_vertex->get_name() == vert_ptr->get_name(); });
	if (iter != adjecent_vertexes.end())
	{
		if (adjecent_vertex->name != name)
		{
			(*iter)->adjecent_vertexes.erase(std::find_if((*iter)->adjecent_vertexes.begin(), (*iter)->adjecent_vertexes.end(), [this, &iter](vertex<T>* vert_ptr) { return this->get_name() == vert_ptr->get_name(); }));
			adjecent_vertexes.erase(iter);
		}
		else adjecent_vertexes.erase(std::find(adjecent_vertexes.begin(), adjecent_vertexes.end(), adjecent_vertex));
	}
	else { throw std::exception("You try to erase non-existent vertex"); }
}

template<typename T>
void vertex<T>::erase(iterator_adjvert& adjecent_vertex_iterator)
{
	try { ++adjecent_vertex_iterator; }
	catch (std::exception& ex) { throw std::exception("you can't push end iterator"); }
	--adjecent_vertex_iterator;
	erase(adjecent_vertex_iterator._VertPtr);
}

template<typename T>
bool vertex<T>::operator==(const vertex<T>& other) 
{
	if ((name != other.name) || (degree() != other.degree())) return false;
	for (int i = 0; i < adjecent_vertexes.size(); i++)
	{
		if (std::find(other.adjecent_vertexes.begin(), other.adjecent_vertexes.end(), adjecent_vertexes[i]) == other.adjecent_vertexes.end()) return false;
	}
	return true;
}

template<typename T>
bool vertex<T>::operator!=(const vertex<T>& other) { return !(*this == other); }

template<typename T>
bool vertex<T>::operator>(const vertex<T>& other) { return name > other.name; }

template<typename T>
bool vertex<T>::operator<(const vertex<T>& other) { return name < other.name; }

template<typename T>
bool vertex<T>::operator>=(const vertex<T>& other) { return name >= other.name; }

template<typename T>
bool vertex<T>::operator<=(const vertex<T>& other) { return name <= other.name; }

template<typename T>
int vertex<T>::degree() { return adjecent_vertexes.size(); }
template<typename T>
int vertex<T>::degree() const { return adjecent_vertexes.size(); }

template<typename T>
typename const T& vertex<T>::get_name() { return name; }

template<typename T>
typename const T& vertex<T>::get_name() const { return name; }

//Итератор для перебора смежных вершин
template<typename T>
typename vertex<T>::iterator_adjvert vertex<T>::begin() { return iterator_adjvert(adjecent_vertexes.begin()._Ptr, 0, adjecent_vertexes.size()); }

template<typename T>
typename vertex<T>::const_iterator_adjvert vertex<T>::begin() const { return const_iterator_adjvert(adjecent_vertexes.begin()._Ptr, 0, adjecent_vertexes.size()); }

template<typename T>
typename vertex<T>::iterator_adjvert vertex<T>::end() { return iterator_adjvert(adjecent_vertexes.end()._Ptr, adjecent_vertexes.size(), adjecent_vertexes.size()); }

template<typename T>
typename vertex<T>::const_iterator_adjvert vertex<T>::end() const { return const_iterator_adjvert(adjecent_vertexes.end()._Ptr, adjecent_vertexes.size(), adjecent_vertexes.size()); }

//Reverse итератор для перебора смежных вершин
template<typename T>
typename vertex<T>::reverse_iterator_adjvert vertex<T>::rbegin() { return reverse_iterator_adjvert(adjecent_vertexes.end()._Ptr - 1, adjecent_vertexes.size(), adjecent_vertexes.size()); }

template<typename T>
typename vertex<T>::const_reverse_iterator_adjvert vertex<T>::rbegin() const { return const_reverse_iterator_adjvert(adjecent_vertexes.end()._Ptr - 1, adjecent_vertexes.size(), adjecent_vertexes.size()); }

template<typename T>
typename vertex<T>::reverse_iterator_adjvert vertex<T>::rend() { return reverse_iterator_adjvert(adjecent_vertexes.begin()._Ptr - 1, 0, adjecent_vertexes.size()); }

template<typename T>
typename vertex<T>::const_reverse_iterator_adjvert vertex<T>::rend() const { return const_reverse_iterator_adjvert(adjecent_vertexes.begin()._Ptr - 1, 0, adjecent_vertexes.size()); }

//Итератор для перебора смежных вершин
template<typename T>
typename vertex<T>::iterator_incedge vertex<T>::incedge_begin() { return iterator_incedge(this, adjecent_vertexes.begin()._Ptr, 0, adjecent_vertexes.size()); }

template<typename T>
typename vertex<T>::const_iterator_incedge vertex<T>::incedge_begin() const { return iterator_incedge(this, adjecent_vertexes.begin()._Ptr, 0, adjecent_vertexes.size()); }

template<typename T>
typename vertex<T>::iterator_incedge vertex<T>::incedge_end() { return iterator_incedge(this, adjecent_vertexes.end()._Ptr, adjecent_vertexes.size(), adjecent_vertexes.size()); }

template<typename T>
typename vertex<T>::const_iterator_incedge vertex<T>::incedge_end() const { return iterator_incedge(this, adjecent_vertexes.end()._Ptr, adjecent_vertexes.size(), adjecent_vertexes.size()); }

//Reverse итератор для перебора смежных вершин
template<typename T>
typename vertex<T>::reverse_iterator_incedge vertex<T>::incedge_rbegin()
{
	return reverse_iterator_incedge(this, adjecent_vertexes.end()._Ptr - 1, adjecent_vertexes.size(), adjecent_vertexes.size());
}

template<typename T>
typename vertex<T>::const_reverse_iterator_incedge vertex<T>::incedge_rbegin() const
{
	return const_reverse_iterator_incedge(this, adjecent_vertexes.end()._Ptr - 1, adjecent_vertexes.size(), adjecent_vertexes.size());
}

template<typename T>
typename vertex<T>::reverse_iterator_incedge vertex<T>::incedge_rend()
{
	return reverse_iterator_incedge(this, adjecent_vertexes.begin()._Ptr - 1, 0, adjecent_vertexes.size());
}

template<typename T>
typename vertex<T>::const_reverse_iterator_incedge vertex<T>::incedge_rend() const
{
	return const_reverse_iterator_incedge(this, adjecent_vertexes.begin()._Ptr - 1, 0, adjecent_vertexes.size());
}


//###############################################################################################
//###############################################################################################
//Adjecency List
//###############################################################################################
//###############################################################################################


template<typename T>
class adjecency_list
{
private:
	friend std::ostream& operator<< <T>(std::ostream& ost, const adjecency_list<T>& graph);
	friend class vertex<T>;

	std::vector<vertex<T>> vertexes;

	void change_pointers_by_name(vertex<T>* new_ptr);

	bool _name_is_unique(T&& name);
	bool _name_is_unique(const T& name);

	void erase(vertex<T>* vertex_ptr);
	void erase_edge(vertex<T>* first_vertex_ptr, vertex<T>* second_vertex_ptr);

	//Итератор для перебора вершин
	template<typename Iter>
	class VertexIterator
	{
	public:
		typedef Iter iterator_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;
		typedef ptrdiff_t difference_type;

		pointer _VertPtr;

	protected:
		friend class adjecency_list;
		int vector_length;
		int position;


	private:
		VertexIterator(Iter* _VertPtr, int position, int vector_length) : _VertPtr(_VertPtr), position(position), vector_length(vector_length){}

	public:
		VertexIterator(const VertexIterator& other) : _VertPtr(other._VertPtr), position(other.position), vector_length(other.vector_length) {}

		VertexIterator& operator= (const  VertexIterator& other)
		{
			_VertPtr = other._VertPtr;
			position = other.position;
			vector_length = other.vector_length;
			return *this;
		}

		bool operator == (const VertexIterator& other) { return _VertPtr == other._VertPtr; }

		bool operator != (const VertexIterator& other) { return _VertPtr != other._VertPtr; }

		typename VertexIterator::reference operator*() const { return *_VertPtr; }

		virtual VertexIterator& operator++()
		{
			if (position == vector_length) throw std::exception("can't increment iterator past end");
			++_VertPtr;
			++position;

			return *this;
		}

		virtual VertexIterator& operator++(int)
		{
			if (position == vector_length) throw std::exception("can't increment iterator past end");
			VertexIterator temp = *this;
			++_VertPtr;
			++position;

			return temp;
		}

		virtual VertexIterator& operator--()
		{
			if (position == 0) throw std::exception("can't dencrement iterator before begin");
			--_VertPtr;
			--position;

			return *this;
		}

		virtual VertexIterator& operator--(int)
		{
			if (position == 0) throw std::exception("can't dencrement iterator before begin");
			VertexIterator temp = *this;
			--_VertPtr;
			--position;

			return temp;
		}
	};


	//Reverse итератор для перебора вершин
	template<typename Iter>
	class ReverseVertexIterator : public VertexIterator<Iter>
	{
	public:
		typedef Iter iterator_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;
		typedef ptrdiff_t difference_type;

	private:
		friend class adjecency_list;

		ReverseVertexIterator(Iter* _VertPtr, int position, int vector_length) : VertexIterator<Iter>(_VertPtr, position, vector_length) {}

	public:
		ReverseVertexIterator(const VertexIterator<Iter>& other) : VertexIterator<Iter>(other) {}

		ReverseVertexIterator& operator= (const VertexIterator& other)
		{
			this->_VertPtr = other._VertPtr;
			this->position = other.position;
			this->vector_length = other.vector_length;
			return *this;
		}

		virtual ReverseVertexIterator& operator++() override
		{
			if (this->position == 0) throw std::exception("can't increment reverse iterator before begin");
			--this->_VertPtr;
			--this->position;

			return *this;
		}

		virtual ReverseVertexIterator& operator++(int) override
		{
			if (this->position == 0) throw std::exception("can't increment reverse iterator before begin");
			ReverseVertexIterator temp = *this;
			--this->_VertPtr;
			--this->position;

			return temp;
		}

		virtual ReverseVertexIterator& operator--() override
		{
			if (this->position == this->vector_length) throw std::exception("can't dencrement reverse iterator past end");
			++this->_VertPtr;
			++this->position;

			return *this;
		}

		virtual ReverseVertexIterator& operator--(int) override
		{
			if (this->position == this->vector_length) throw std::exception("can't dencrement reverse iterator past end");
			ReverseVertexIterator temp = *this;
			++this->_VertPtr;
			++this->position;

			return temp;
		}
	};


	//Итератор для перебора рёбер
	template<typename Iter>
	class EdjeIterator
	{
	public:
		typedef Iter iterator_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef std::pair<Iter, Iter> reference;
		typedef iterator_type* pointer;
		typedef ptrdiff_t difference_type;

		pointer _FirstVertexPtr;
		pointer _SecondVertexPtr;

	protected:
		friend class adjecency_list;
		int position;
		int edje_amount;
		int incedje_position;
		pointer* second_vert;

		EdjeIterator(pointer _FirsrtVertexPtr, pointer* second_vert, int position, int edje_amount, int incedje_position)
		{
			this->_FirstVertexPtr = _FirsrtVertexPtr;
			if (second_vert) this->_SecondVertexPtr = *second_vert;
			this->second_vert = second_vert;
			this->position = position;
			this->edje_amount = edje_amount;
			this->incedje_position = incedje_position;
		}

	public:

		EdjeIterator(const EdjeIterator& other)
		{
			this->_FirstVertexPtr = other._FirstVertexPtr;
			this->_SecondVertexPtr = other._SecondVertexPtr;
			this->second_vert = other.second_vert;
			this->position = other.position;
			this->edje_amount = other.edje_amount;
			this->incedje_position = other.incedje_position;
		}

		EdjeIterator& operator=(const EdjeIterator& other)
		{
			this->_FirstVertexPtr = other._FirstVertexPtr;
			this->_SecondVertexPtr = other._SecondVertexPtr;
			this->second_vert = other.second_vert;
			this->position = other.position;
			this->edje_amount = other.edje_amount;
			this->incedje_position = other.incedje_position;
			return *this;
		}

		bool operator == (const EdjeIterator& other) { return ((second_vert == other.second_vert) && (_FirstVertexPtr == other._FirstVertexPtr)); }

		bool operator != (const EdjeIterator& other) { return !(*this == other); }

		typename EdjeIterator::reference operator* () const { return std::pair<Iter, Iter>(*_FirstVertexPtr, *_SecondVertexPtr); }

		virtual EdjeIterator& operator++()
		{
			if (position == edje_amount) throw std::exception("can't increment iterator past end");
			if (position == edje_amount - 1)
			{
				++second_vert;
				_SecondVertexPtr = *second_vert;
				++position;
				++incedje_position;
			}
			else
			{
				if (incedje_position < _FirstVertexPtr->degree() - 1)
				{
					++second_vert;
					_SecondVertexPtr = *second_vert;
					++position;
					++incedje_position;
				}
				else
				{
					++_FirstVertexPtr;
					second_vert = _FirstVertexPtr->begin().vert;
					_SecondVertexPtr = *second_vert;
					++position;
					incedje_position = 0;
				}
			}
			return *this;
		}

		virtual EdjeIterator& operator++(int)
		{
			if (position == edje_amount) throw std::exception("can't increment iterator past end");
			EdjeIterator temp = *this;
			if (position == edje_amount - 1)
			{
				++second_vert;
				_SecondVertexPtr = *second_vert;
				++position;
				++incedje_position;
			}
			else
			{
				if (incedje_position < _FirstVertexPtr->degree() - 1)
				{
					++second_vert;
					_SecondVertexPtr = *second_vert;
					++position;
					++incedje_position;
				}
				else
				{
					++_FirstVertexPtr;
					second_vert = _FirstVertexPtr->begin().vert;
					_SecondVertexPtr = *second_vert;
					++position;
					incedje_position = 0;
				}
			}
			return temp;
		}

		virtual EdjeIterator& operator--()
		{
			if (position == 0) throw std::exception("can't dencrement iterator before begin");
			if (incedje_position != 0)
			{
				--second_vert;
				_SecondVertexPtr = *second_vert;
				--position;
				--incedje_position;
			}
			else
			{
				--_FirstVertexPtr;
				second_vert = _FirstVertexPtr->end().vert - 1;
				_SecondVertexPtr = *second_vert;
				--position;
				incedje_position = _FirstVertexPtr->degree() - 1;
			}
			return *this;
		}

		virtual EdjeIterator& operator--(int)
		{
			if (position == 0) throw std::exception("can't dencrement iterator before begin");
			EdjeIterator temp = *this;
			if (incedje_position != 0)
			{
				--second_vert;
				_SecondVertexPtr = *second_vert;
				--position;
				--incedje_position;
			}
			else
			{
				--_FirstVertexPtr;
				second_vert = _FirstVertexPtr->end().vert - 1;
				_SecondVertexPtr = *second_vert;
				--position;
				incedje_position = _FirstVertexPtr->degree() - 1;
			}

			return temp;
		}
	};


	//Reverse итератор для перебора рёбер
	template<typename Iter>
	class EdjeReverseIterator : public EdjeIterator<Iter>
	{
	public:
		typedef Iter iterator_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef std::pair<Iter, Iter> reference;
		typedef iterator_type* pointer;
		typedef ptrdiff_t difference_type;

	private:
		friend class adjecency_list;

		EdjeReverseIterator(pointer _FirstVertexPtr, pointer* second_vert, int position, int edje_amount, int incedje_position)
			:EdjeIterator<Iter>(_FirstVertexPtr, second_vert, position, edje_amount, incedje_position) {}

	public:

		EdjeReverseIterator(const EdjeIterator& other) : EdjeIterator<Iter>(other) {}

		EdjeReverseIterator& operator=(const EdjeIterator& other)
		{
			this->_FirstVertexPtr = other._FirstVertexPtr;
			this->second_vert = other.second_vert;
			this->_SecondVertexPtr = *(this->second_vert);
			this->position = other.position;
			this->edje_amount = other.edje_amount;
			this->incedje_position = other.incedje_position;
			return *this;
		}

		virtual EdjeReverseIterator& operator++()
		{
			if (this->position == 0) throw std::exception("can't increment reverse iterator before begin");
			if (this->position == 1)
			{
				--this->second_vert;
				this->_SecondVertexPtr = *this->second_vert;
				--this->position;
				--this->incedje_position;
			}
			else
			{
				if (this->incedje_position > 0)
				{
					--this->second_vert;
					this->_SecondVertexPtr = *this->second_vert;
					--this->position;
					--this->incedje_position;
				}
				else
				{
					--this->_FirstVertexPtr;
					this->second_vert = this->_FirstVertexPtr->end().vert - 1;
					this->_SecondVertexPtr = *this->second_vert;
					--this->position;
					this->incedje_position = this->_FirstVertexPtr->degree() - 1;
				}
				return *this;
			}
		}

		virtual EdjeReverseIterator& operator++(int)
		{
			if (this->position == 0) throw std::exception("can't increment reverse iterator before begin");
			EdjeReverseIterator& temp = *this;
			if (this->position == 1)
			{
				--this->second_vert;
				this->_SecondVertexPtr = *this->second_vert;
				--this->position;
				--this->incedje_position;
			}
			else
			{
				if (this->incedje_position > 0)
				{
					--this->second_vert;
					this->_SecondVertexPtr = *this->second_vert;
					--this->position;
					--this->incedje_position;
				}
				else
				{
					--this->_FirstVertexPtr;
					this->second_vert = this->_FirstVertexPtr->end().vert - 1;
					this->_SecondVertexPtr = *this->second_vert;
					--this->position;
					this->incedje_position = this->_FirstVertexPtr->degree() - 1;
				}
				return temp;
			}
		}

		virtual EdjeReverseIterator& operator--()
		{
			if (this->position == this->edje_amount) throw std::exception("can't dencrement reverse iterator past end");
			if (this->incedje_position < this-> _FirstVertexPtr->degree() - 1)
			{
				++this->second_vert;
				this->_SecondVertexPtr = *this->second_vert;
				++this->position;
				++this->incedje_position;
			}
			else
			{
				++this->_FirstVertexPtr;
				this->second_vert = this->_FirstVertexPtr->begin().vert;
				this->_SecondVertexPtr = *this->second_vert;
				++this->position;
				this->incedje_position = 0;
			}
			return *this;
		}

		virtual EdjeReverseIterator& operator--(int)
		{
			if (this->position == this->edje_amount) throw std::exception("can't dencrement reverse iterator past end");
			EdjeReverseIterator temp = *this;
			if (this->incedje_position < this->_FirstVertexPtr->degree() - 1)
			{
				++this->second_vert;
				this->_SecondVertexPtr = *this->second_vert;
				++this->position;
				++this->incedje_position;
			}
			else
			{
				++this->_FirstVertexPtr;
				this->second_vert = this->_FirstVertexPtr->begin().vert;
				this->_SecondVertexPtr = *this->second_vert;
				++this->position;
				this->incedje_position = 0;
			}
			return temp;
		}
	};
	
public:
	//Итератор для перебора вершин
	typedef VertexIterator<vertex<T>> vert_iterator;
	typedef VertexIterator<const vertex<T>> const_vert_iterator;

	//Reverse итератор для перебора вершин
	typedef ReverseVertexIterator<vertex<T>> reverse_vert_iterator;
	typedef ReverseVertexIterator<const vertex<T>> const_reverse_vert_iterator;

	//Итератор для перебора рёбер
	typedef EdjeIterator<vertex<T>> edje_iterator;
	typedef EdjeIterator<const vertex<T>> const_edje_iterator;

	//Reverse итератор для перебора рёбер
	typedef EdjeReverseIterator<vertex<T>> edje_reverse_iterator;
	typedef EdjeReverseIterator<const vertex<T>> const_edje_reverse_iterator;


	adjecency_list();

	adjecency_list(const adjecency_list& other);
	adjecency_list& operator= (const adjecency_list& other);

	~adjecency_list();
	void clear();

	bool operator==(const adjecency_list& other);
	bool operator!=(const adjecency_list& other);

	bool operator>(const adjecency_list& other);
	bool operator>=(const adjecency_list& other);

	bool operator<(const adjecency_list& other);
	bool operator<=(const adjecency_list& other);

	bool empty();

	size_t vertex_amount();
	size_t vertex_amount() const;

	size_t edje_amount();
	size_t edje_amount() const;

	void push_vertex(T&& vertex_name);
	void push_vertex(const T& vertex_name);
	void push_vertex(vertex<T>&& vert);
	void push_vertex(const vertex<T>& vert);
	
	//Поиск вершины по имени
	vert_iterator find(const T& name);
	vert_iterator find(T&& name);

	//Поиск ребра по имени двух вершин
	edje_iterator find_edje(const T& first_name, const T& second_name);
	edje_iterator find_edje(const T& first_name, T&& second_name);
	edje_iterator find_edje(T&& first_name, const T& second_name);
	edje_iterator find_edje(T&& first_name, T&& second_name);

	//Поиск ребра по двум вершинам
	edje_iterator find_edje(const vertex<T>& first_vertex, const vertex<T>& second_vertex);
	edje_iterator find_edje(const vertex<T>& first_vertex, vertex<T>&& second_vertex);
	edje_iterator find_edje(vertex<T>&& first_vertex, const vertex<T>& second_vertex);
	edje_iterator find_edje(vertex<T>&& first_vertex, vertex<T>&& second_vertex);

	//Поиск ребра по двум указателям на вершины
	edje_iterator find_edje(vertex<T>* first_vertex_ptr, vertex<T>* second_vertex_ptr);

	//Поиск ребра по двум итераторам на рёбра
	edje_iterator find_edje(vert_iterator& first_vertex_it, vert_iterator& second_vertex_it);
	edje_iterator find_edje(vert_iterator& first_vertex_it, typename vertex<T>::iterator_adjvert& second_vertex_it);
	edje_iterator find_edje(typename vertex<T>::iterator_adjvert& first_vertex_it, vert_iterator& second_vertex_it);
	edje_iterator find_edje(typename vertex<T>::iterator_adjvert& first_vertex_it, typename vertex<T>::iterator_adjvert& second_vertex_it);

	//Cтепень вершины по итератору
	int degree(vert_iterator& iter);
	int degree(typename vertex<T>::iterator_adjvert& iter);

	//Создание ребра по именам вершин
	void make_edje(const T& first_name, const T& second_name);
	void make_edje(const T& first_name, T&& second_name);
	void make_edje(T&& first_name, const T& second_name);
	void make_edje(T&& first_name, T&& second_name);

	//Создание ребра по двум вершинам
	void make_edje(const vertex<T>& first_vertex, const vertex<T>& second_vertex);
	void make_edje(const vertex<T>& first_vertex, vertex<T>&& second_vertex);
	void make_edje(vertex<T>&& first_vertex, const vertex<T>& second_vertex);
	void make_edje(vertex<T>&& first_vertex, vertex<T>&& second_vertex);

	//Создание ребра по указателям на вершины
	void make_edje(vertex<T>* first_vertex, vertex<T>* second_vertex);

	//Создание ребра по итераторам на вершины
	void make_edje(vert_iterator& first_vertex_it, vert_iterator& second_vertex_it);
	void make_edje(vert_iterator& first_vertex_it, typename vertex<T>::iterator_adjvert& second_vertex_it);
	void make_edje(typename vertex<T>::iterator_adjvert& first_vertex_it, vert_iterator& second_vertex_it);
	void make_edje(typename vertex<T>::iterator_adjvert& first_vertex_it, typename vertex<T>::iterator_adjvert& second_vertex_it);

	//Удаление вершины по итератору
	void erase(vert_iterator& vertex_it);
	void erase(typename vertex<T>::iterator_adjvert& vertex_it);

	//Удаление ребра по итератору на ребро
	void erase_edge(edje_iterator& edge_it);
	void erase_edge(typename vertex<T>::iterator_incedge& edge_it);

	//Итератор для перебора смежных вершин
	vert_iterator begin();
	vert_iterator end();

	const_vert_iterator begin() const;
	const_vert_iterator end() const;

	//Reverse итератор для перебора вершин
	reverse_vert_iterator rbegin();
	reverse_vert_iterator  rend();

	const_reverse_vert_iterator rbegin() const;
	const_reverse_vert_iterator rend() const;

	//Итератор для перебора рёбер
	edje_iterator edje_begin();
	edje_iterator edje_end();

	const_edje_iterator edje_begin() const;
	const_edje_iterator edje_end() const;

	//Reverse итератор для перебора рёбер
	edje_reverse_iterator edje_rbegin();
	edje_reverse_iterator edje_rend();

	const_edje_reverse_iterator edje_rbegin() const;
	const_edje_reverse_iterator edje_rend() const;
};

template <typename T>
void adjecency_list<T>::change_pointers_by_name(vertex<T>* new_ptr)
{
	for (int i = 0; i < vertexes.size(); i++)
	{
		for (int j = 0; j < vertexes[i].degree(); j++)
		{
			if (new_ptr->get_name() == vertexes[i].adjecent_vertexes[j]->get_name())
			{ vertexes[i].adjecent_vertexes[j]->adjecent_vertexes = new_ptr->adjecent_vertexes; }
		}
	}
}

template<typename T>
std::ostream& operator<<<T>(std::ostream& ost, const adjecency_list<T>& graph)
{
	for (auto it_v : graph)
	{
		ost << it_v << ": ";
		if (it_v.degree() > 0)
		{
			for(auto it_adjv : it_v)
			{
				ost << it_adjv << "\t";
			}
		}
		else ost << "no adjecent vertexes";
		ost << std::endl;
	}
	return ost;
}


template<typename T>
bool adjecency_list<T>::_name_is_unique(const T& name)
{
	return (std::find_if(vertexes.begin(), vertexes.end(), [&name](vertex<T>& name_to_check) { return name_to_check.get_name() == name; }) == vertexes.end());
}

template<typename T>
bool adjecency_list<T>::_name_is_unique(T&& name)
{
	return (std::find_if(vertexes.begin(), vertexes.end(), [&name](T& name_to_check) { return name_to_check.get_name() == name; }) == vertexes.end());
}


template<typename T>
adjecency_list<T>::adjecency_list() {}

template<typename T>
adjecency_list<T>::adjecency_list(const adjecency_list& other) : vertexes(other.vertexes){}

template<typename T>
adjecency_list<T>& adjecency_list<T>::operator=(const adjecency_list& other)
{
	vertexes = other.vertexes;
	return *this;
}

template<typename T>
adjecency_list<T>::~adjecency_list() { clear(); }

template<typename T>
void adjecency_list<T>::clear() { vertexes.clear(); }


template<typename T>
bool adjecency_list<T>::operator==(const adjecency_list& other)
{
	if ((vertex_amount() != other.vertex_amount()) || (edje_amount() != other.edje_amount())) return false;
	for (int i = 0; i < vertexes.size(); i++)
	{
		if (vertexes[i] != other.vertexes[i]) return false;
	}
	return true;
}

template<typename T>
bool adjecency_list<T>::operator!=(const adjecency_list& other) { return !(*this == other); }


template<typename T>
bool adjecency_list<T>::operator>(const adjecency_list& other)
{
	if (vertex_amount() == other.vertex_amount()) return edje_amount() > other.edje_amount();
	else return vertex_amount() > other.vertex_amount();
}

template<typename T>
bool adjecency_list<T>::operator>=(const adjecency_list& other) { return ((*this == other) || (*this > other)); }


template<typename T>
bool adjecency_list<T>::operator<(const adjecency_list& other)
{
	if (vertex_amount() == other.vertex_amount()) return edje_amount() < other.edje_amount();
	else return vertex_amount() < other.vertex_amount();
}

template<typename T>
bool adjecency_list<T>::operator<=(const adjecency_list& other) { return ((*this == other) || (*this < other)); }

template <typename T>
bool adjecency_list<T>::empty()
{
	(vertexes.size() > 0) ? false : true;
}


template<typename T>
size_t adjecency_list<T>::vertex_amount() { return vertexes.size(); }

template<typename T>
size_t adjecency_list<T>::vertex_amount() const { return vertexes.size(); }


template<typename T>
size_t adjecency_list<T>::edje_amount()
{
	size_t edje_counter = 0;
	for (int i = 0; i < vertexes.size(); i++) { edje_counter += vertexes[i].degree(); }
	return edje_counter;
}

template<typename T>
size_t adjecency_list<T>::edje_amount() const
{
	size_t edje_counter = 0;
	for (int i = 0; i < vertexes.size(); i++) { edje_counter += vertexes[i].degree(); }
	return edje_counter;
}


//Добавление вершины
template<typename T>
void adjecency_list<T>::push_vertex(T&& vertex_name)
{
	if (_name_is_unique(vertex_name))
	{
		vertexes.push_back(vertex<T>(vertex_name));
	}
	else throw std::exception("name of vertex must be unique in graph");
}

template<typename T>
void adjecency_list<T>::push_vertex(const T& vertex_name)
{
	if (_name_is_unique(vertex_name))
	{
		vertexes.push_back(vertex<T>(vertex_name));
	}
	else throw std::exception("name of vertex must be unique in graph");
}


template<typename T>
void adjecency_list<T>::push_vertex(vertex<T>&& vert)
{
	if (_name_is_unique(vert.get_name()))
	{
		vertexes.push_back(vert);
	}
	else throw std::exception("name of vertex must be unique in graph");
}

template<typename T>
void adjecency_list<T>::push_vertex(const vertex<T>& vert)
{
	if (_name_is_unique(vert.get_name()))
	{
		vertexes.push_back(vert);
	}
	else throw std::exception("name of vertex must be unique in graph");
}


//Поиск вершины по имени
template<typename T>
typename adjecency_list<T>::vert_iterator adjecency_list<T>::find(const T& name) { return std::find_if(begin(), end(), [&name](vertex<T> vertex_) { return vertex_.get_name() == name; }); }

template<typename T>
typename adjecency_list<T>::vert_iterator adjecency_list<T>::find(T&& name) { return std::find_if(begin(), end(), [&name](vertex<T> vertex_) { return vertex_.get_name() == name; }); }

//Поиск ребра по имени двух вершин
template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(const T& first_name, const T& second_name) 
{
	if ((find(first_name) == end()) || (find(second_name) == end())) return edje_end();
	auto edje_iter = edje_begin();
	for (edje_iter; edje_iter != edje_end(); ++edje_iter)
	{
		if (edje_iter._FirstVertexPtr->get_name() == first_name && edje_iter._SecondVertexPtr->get_name() == second_name) break;
	}
	return edje_iter;
}

template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(const T& first_name, T&& second_name)
{
	if ((find(first_name) == end()) || (find(second_name) == end())) return edje_end();
	auto edje_iter = edje_begin();
	for (edje_iter; edje_iter != edje_end(); ++edje_iter)
	{
		if (edje_iter._FirstVertexPtr->get_name() == first_name && edje_iter._SecondVertexPtr->get_name() == second_name) break;
	}
	return edje_iter;
}

template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(T&& first_name, const T& second_name)
{
	if ((find(first_name) == end()) || (find(second_name) == end())) return edje_end();
	auto edje_iter = edje_begin();
	for (edje_iter; edje_iter != edje_end(); ++edje_iter)
	{
		if (edje_iter._FirstVertexPtr->get_name() == first_name && edje_iter._SecondVertexPtr->get_name() == second_name) break;
	}
	return edje_iter;
}

template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(T&& first_name, T&& second_name)
{
	if ((find(first_name) == end()) || (find(second_name) == end())) return edje_end();
	auto edje_iter = edje_begin();
	for (edje_iter; edje_iter != edje_end(); ++edje_iter)
	{
		if (edje_iter._FirstVertexPtr->get_name() == first_name && edje_iter._SecondVertexPtr->get_name() == second_name) break;
	}
	return edje_iter;
}

//Поиск ребра по двум вершинам
template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(const vertex<T>& first_vertex, const vertex<T>& second_vertex)
{
	if ((find(first_vertex.get_name()) == end()) || (find(second_vertex.get_name()) == end())) return edje_end();
	return find_edje(first_vertex.get_name(), second_vertex.get_name());
}

template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(const vertex<T>& first_vertex, vertex<T>&& second_vertex)
{
	if ((find(first_vertex.get_name()) == end()) || (find(second_vertex.get_name()) == end())) return edje_end();
	return find_edje(first_vertex.get_name(), second_vertex.get_name());
}

template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(vertex<T>&& first_vertex, const vertex<T>& second_vertex)
{
	if ((find(first_vertex.get_name()) == end()) || (find(second_vertex.get_name()) == end())) return edje_end();
	return find_edje(first_vertex.get_name(), second_vertex.get_name());
}

template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(vertex<T>&& first_vertex, vertex<T>&& second_vertex)
{
	if ((find(first_vertex.get_name()) == end()) || (find(second_vertex.get_name()) == end())) return edje_end();
	return find_edje(first_vertex.get_name(), second_vertex.get_name());
}

//Поиск ребра по двум указателям на вершины
template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(vertex<T>* first_vertex_ptr, vertex<T>* second_vertex_ptr)
{
	if ((find(first_vertex_ptr->get_name()) == end()) || (find(second_vertex_ptr->get_name()) == end())) return edje_end();
	return find_edje(first_vertex_ptr->get_name(), second_vertex_ptr->get_name());
}

//Поиск ребра по двум итераторам на вершины
template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(vert_iterator& first_vertex_it, vert_iterator& second_vertex_it) 
{
	return find_edje(first_vertex_it._VertPtr, second_vertex_it._VertPtr); 
}

template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(vert_iterator& first_vertex_it, typename vertex<T>::iterator_adjvert& second_vertex_it)
{
	return find_edje(first_vertex_it._VertPtr, second_vertex_it._VertPtr);
}

template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(typename vertex<T>::iterator_adjvert& first_vertex_it, vert_iterator& second_vertex_it)
{
	return find_edje(first_vertex_it._VertPtr, second_vertex_it._VertPtr);
}

template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::find_edje(typename vertex<T>::iterator_adjvert& first_vertex_it, typename vertex<T>::iterator_adjvert& second_vertex_it)
{
	return find_edje(first_vertex_it._VertPtr, second_vertex_it._VertPtr);
}

template<typename T>
int adjecency_list<T>::degree(vert_iterator& iter) { return (*iter).degree(); }

template<typename T>
int adjecency_list<T>::degree(typename vertex<T>::iterator_adjvert& iter) { return (*iter).degree(); }

//Добавление ребра по именам двух вершин
template<typename T>
void adjecency_list<T>::make_edje(const T& first_name, const T& second_name)
{
	if (find_edje(first_name, second_name) != edje_end()) throw std::exception("You try to make the second edge between two vertexes.");
	if (find(first_name) == end()) push_vertex(first_name);
	if (find(second_name) == end()) push_vertex(second_name);
	auto first_it = find(first_name);
	first_it._VertPtr->push_vertex(find(second_name)._VertPtr);
}

template<typename T>
void adjecency_list<T>::make_edje(const T& first_name,T&& second_name)
{
	if (find_edje(first_name, second_name) != edje_end()) throw std::exception("You try to make the second edge between two vertexes.");
	if (find(first_name) == end()) push_vertex(first_name);
	if (find(second_name) == end()) push_vertex(second_name);
	auto first_it = find(first_name);
	first_it._VertPtr->push_vertex(find(second_name)._VertPtr);
}

template<typename T>
void adjecency_list<T>::make_edje(T&& first_name, const T& second_name)
{
	if (find_edje(first_name, second_name) != edje_end()) throw std::exception("You try to make the second edge between two vertexes.");
	if (find(first_name) == end()) push_vertex(first_name);
	if (find(second_name) == end()) push_vertex(second_name);
	auto first_it = find(first_name);
	first_it._VertPtr->push_vertex(find(second_name)._VertPtr);
}

template<typename T>
void adjecency_list<T>::make_edje(T&& first_name, T&& second_name)
{
	if (find_edje(first_name, second_name) != edje_end()) throw std::exception("You try to make the second edge between two vertexes.");
	if (find(first_name) == end()) push_vertex(first_name);
	if (find(second_name) == end()) push_vertex(second_name);
	auto first_it = find(first_name);
	first_it._VertPtr->push_vertex(find(second_name)._VertPtr);
}

//Создание ребра по двум вершинам
template<typename T>
void adjecency_list<T>::make_edje(const vertex<T>& first_vertex, const vertex<T>& second_vertex)
{
	if(find_edje(first_vertex, second_vertex) != edje_end()) throw std::exception("You try to make the second edge between two vertexes.");
	auto first_vertex_iterator = std::find(begin(), end(), first_vertex);
	if (first_vertex_iterator == end()) throw std::exception("First vertexe don't exist in graph");
	auto second_vertex_iterator = std::find(begin(), end(), second_vertex);
	if (second_vertex_iterator == end()) throw std::exception("Second vertexe don't exist in graph");

	first_vertex_iterator._VertPtr->push_vertex(second_vertex_iterator._VertPtr);
	
	change_pointers_by_name(first_vertex_iterator._VertPtr);
	change_pointers_by_name(second_vertex_iterator._VertPtr);
}

template<typename T>
void adjecency_list<T>::make_edje(const vertex<T>& first_vertex, vertex<T>&& second_vertex)
{
	if (find_edje(first_vertex, second_vertex) != edje_end()) throw std::exception("You try to make the second edge between two vertexes.");
	auto first_vertex_iterator = std::find(begin(), end(), first_vertex);
	if (first_vertex_iterator == end()) throw std::exception("First vertexe don't exist in graph");
	auto second_vertex_iterator = std::find(begin(), end(), second_vertex);
	if (second_vertex_iterator == end()) throw std::exception("Second vertexe don't exist in graph");

	first_vertex_iterator._VertPtr->push_vertex(second_vertex_iterator._VertPtr);

	change_pointers_by_name(first_vertex_iterator._VertPtr);
	change_pointers_by_name(second_vertex_iterator._VertPtr);
}

template<typename T>
void adjecency_list<T>::make_edje(vertex<T>&& first_vertex, const vertex<T>& second_vertex)
{
	if (find_edje(first_vertex, second_vertex) != edje_end()) throw std::exception("You try to make the second edge between two vertexes.");
	auto first_vertex_iterator = std::find(begin(), end(), first_vertex);
	if (first_vertex_iterator == end()) throw std::exception("First vertexe don't exist in graph");
	auto second_vertex_iterator = std::find(begin(), end(), second_vertex);
	if (second_vertex_iterator == end()) throw std::exception("Second vertexe don't exist in graph");

	first_vertex_iterator._VertPtr->push_vertex(second_vertex_iterator._VertPtr);

	change_pointers_by_name(first_vertex_iterator._VertPtr);
	change_pointers_by_name(second_vertex_iterator._VertPtr);
}

template<typename T>
void adjecency_list<T>::make_edje(vertex<T>&& first_vertex, vertex<T>&& second_vertex)
{
	if (find_edje(first_vertex, second_vertex) != edje_end()) throw std::exception("You try to make the second edge between two vertexes.");
	auto first_vertex_iterator = std::find(begin(), end(), first_vertex);
	if (first_vertex_iterator == end()) throw std::exception("First vertexe don't exist in graph");
	auto second_vertex_iterator = std::find(begin(), end(), second_vertex);
	if (second_vertex_iterator == end()) throw std::exception("Second vertexe don't exist in graph");

	first_vertex_iterator._VertPtr->push_vertex(second_vertex_iterator._VertPtr);

	change_pointers_by_name(first_vertex_iterator._VertPtr);
	change_pointers_by_name(second_vertex_iterator._VertPtr);
}

//Создание ребра по двум указателям на вершины
template<typename T>
void adjecency_list<T>::make_edje(vertex<T>* first_vertex, vertex<T>* second_vertex)
{
	if (find_edje(first_vertex, second_vertex) != edje_end()) throw std::exception("You try to make the second edge between two vertexes.");
	auto first_vertex_iterator = std::find(begin(), end(), *first_vertex);
	if (first_vertex_iterator == end()) throw std::exception("First vertexe don't exist in graph");
	auto second_vertex_iterator = std::find(begin(), end(), *second_vertex);
	if (second_vertex_iterator == end()) throw std::exception("Second vertexe don't exist in graph");

	first_vertex_iterator._VertPtr->push_vertex(second_vertex_iterator._VertPtr);

	change_pointers_by_name(first_vertex_iterator._VertPtr);
	change_pointers_by_name(second_vertex_iterator._VertPtr);
}

//Создание ребра по итераторам на вершины
template<typename T>
void adjecency_list<T>::make_edje(vert_iterator& first_vertex_it, vert_iterator& second_vertex_it) { make_edje(first_vertex_it._VertPtr, second_vertex_it._VertPtr); }

template<typename T>
void adjecency_list<T>::make_edje(vert_iterator& first_vertex_it, typename vertex<T>::iterator_adjvert& second_vertex_it) { make_edje(first_vertex_it._VertPtr, second_vertex_it._VertPtr); }

template<typename T>
void adjecency_list<T>::make_edje(typename vertex<T>::iterator_adjvert& first_vertex_it, vert_iterator& second_vertex_it) { make_edje(first_vertex_it._VertPtr, second_vertex_it._VertPtr); }

template<typename T>
void adjecency_list<T>::make_edje(typename vertex<T>::iterator_adjvert& first_vertex_it, typename vertex<T>::iterator_adjvert& second_vertex_it) { make_edje(first_vertex_it._VertPtr, second_vertex_it._VertPtr); }

//Удаление вершины по указателю
template<typename T>
void adjecency_list<T>::erase(vertex<T>* vertex_ptr)
{
	const T& name_to_delete = vertex_ptr->get_name();
	auto iter = std::find(vertexes.begin(), vertexes.end(), *vertex_ptr);
	std::vector<vertex<T>*>* to_change = new std::vector<vertex<T>*>();
	int size = vertex_ptr->degree();
	for (int i = 0; i < vertex_ptr->degree(); i++)
	{
		iter._Ptr->adjecent_vertexes[i]->erase(iter._Ptr);
		vertex<T>* temp = new vertex<T>(*std::move(iter._Ptr->adjecent_vertexes[i]));
		to_change->push_back(temp);
	}
	/*for (int i = 0; i < vertexes.size(); i++)
	{
		if (vertexes[i].get_name() == name_to_delete)
		{
			for (int j = 0; j < vertexes[i].degree(); j++)
			{
				vertexes[i].adjecent_vertexes[j] = nullptr;
			}
			break;
		}
	}
	vertexes.erase(std::find_if(vertexes.begin(), vertexes.end(), [&name_to_delete](vertex<T> v) { return v.get_name() == name_to_delete; }));*/

	int j = 0;
	std::vector<vertex<T>>* new_vertexes = new std::vector<vertex<T>>(vertexes.size() - 1);
	for (int i = 0; i < vertexes.size(); i++, j++)
	{
		if (vertexes[i].get_name() != name_to_delete) new_vertexes->operator[](j) = vertexes[i];
		else j--;
	}
	vertexes.swap(*new_vertexes);
	//vertexes.resize(vertexes.size() - 1);
	//vertexes = new_vertexes;

	for (int i = 0; i < to_change->size(); i++)
	{
		for (int j = 0; j < vertexes.size(); j++)
		{
			if (to_change->operator[](i)->get_name() == vertexes[j].get_name()) vertexes[j] = *std::move((to_change->operator[](i)));
		}
	}
	for (int i = 0; i < to_change->size(); i++) change_pointers_by_name(std::move(to_change->operator[](i)));
	new_vertexes = nullptr;
}

//Удаление вершины по итератору
template<typename T>
void adjecency_list<T>::erase(vert_iterator& vertex_it) { erase(vertex_it._VertPtr); }

template<typename T>
void adjecency_list<T>::erase(typename vertex<T>::iterator_adjvert& vertex_it) 
{
	//erase(vertex_it._VertPtr); 
	std::vector<vertex<T>::iterator_adjvert> to_erase;
	for (auto adjecent_vertex = vertex_it._VertPtr->begin(); adjecent_vertex != vertex_it._VertPtr->end(); adjecent_vertex++)
		to_erase.push_back(adjecent_vertex);

	for (int i = 0; i < to_erase.size(); i++) vertex_it._VertPtr->erase(to_erase[i]);
	for (int i = 0; i < to_erase.size(); i++) change_pointers_by_name(to_erase[i]._VertPtr);

	for (int i = 0; i < to_erase.size(); i++)
		for (int j = 0; j < vertex_amount(); j++)
			if (to_erase[i]._VertPtr->get_name() == vertexes[j].get_name()) { vertexes[j] = *(to_erase[i]._VertPtr); }

	std::vector<vertex<T>>* new_vertexes = new std::vector<vertex<T>>(vertexes.size() - 1);
	int j = 0;
	for (int i = 0; i < vertexes.size(); i++, j++)
	{
		if (vertexes[i].get_name() != vertex_it._VertPtr->get_name()) new_vertexes->operator[](j) = vertexes[i];
		else j--;
	}
	vertexes.swap(*new_vertexes);
	new_vertexes = nullptr;
}

//Удадление ребра по двум указателям
template<typename T>
void adjecency_list<T>::erase_edge(vertex<T>* first_vertex_ptr, vertex<T>* second_vertex_ptr)
{
	first_vertex_ptr->erase(second_vertex_ptr);
	change_pointers_by_name(first_vertex_ptr);
	if (first_vertex_ptr->get_name() != second_vertex_ptr->get_name()) change_pointers_by_name(second_vertex_ptr);
	for (int i = 0; i < vertex_amount(); i++)
	{
		if (vertexes[i].get_name() == first_vertex_ptr->get_name()) vertexes[i] = *first_vertex_ptr;
		if (first_vertex_ptr->get_name() != second_vertex_ptr->get_name()) 
			if (vertexes[i].get_name() == second_vertex_ptr->get_name()) vertexes[i] = *second_vertex_ptr;
	}
}

//Удаление ребра по итератору на ребро
template<typename T>
void adjecency_list<T>::erase_edge(edje_iterator& edge_it) { erase_edge(edge_it._FirstVertexPtr, edge_it._SecondVertexPtr); }

template<typename T>
void adjecency_list<T>::erase_edge(typename vertex<T>::iterator_incedge& edge_it) { erase_edge(edge_it._FirstVertexPtr, edge_it._SecondVertexPtr); }


//Итератор для перебора вершин
template<typename T>
typename adjecency_list<T>::vert_iterator adjecency_list<T>::begin() { return vert_iterator(vertexes.begin()._Ptr, 0, vertexes.size()); }

template<typename T>
typename adjecency_list<T>::const_vert_iterator adjecency_list<T>::begin() const { return const_vert_iterator(vertexes.begin()._Ptr, 0, vertexes.size()); }

template<typename T>
typename adjecency_list<T>::vert_iterator adjecency_list<T>::end() { return vert_iterator(vertexes.end()._Ptr, vertexes.size(), vertexes.size()); }

template<typename T>
typename adjecency_list<T>::const_vert_iterator adjecency_list<T>::end() const { return const_vert_iterator(vertexes.end()._Ptr, vertexes.size(), vertexes.size()); }


//Reverse итератор для перебора вершин
template<typename T>
typename adjecency_list<T>::reverse_vert_iterator adjecency_list<T>::rbegin() { return reverse_vert_iterator(vertexes.end()._Ptr - 1, vertexes.size(), vertexes.size()); }

template<typename T>
typename adjecency_list<T>::const_reverse_vert_iterator adjecency_list<T>::rbegin() const { return const_reverse_vert_iterator(vertexes.end()._Ptr - 1, vertexes.size(), vertexes.size()); }

template<typename T>
typename adjecency_list<T>::reverse_vert_iterator adjecency_list<T>::rend() { return reverse_vert_iterator(vertexes.begin()._Ptr - 1, 0, vertexes.size()); }

template<typename T>
typename adjecency_list<T>::const_reverse_vert_iterator adjecency_list<T>::rend() const { return const_reverse_vert_iterator(vertexes.begin()._Ptr - 1, 0, vertexes.size()); }

//Итератор для перебора рёбер
template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::edje_begin() { return edje_iterator(&vertexes[0], vertexes.begin()._Ptr->adjecent_vertexes.begin()._Ptr, 0, edje_amount(), 0); }

template<typename T>
typename adjecency_list<T>::edje_iterator adjecency_list<T>::edje_end() 
{
	return edje_iterator(&vertexes[vertexes.size() - 1], vertexes[vertexes.size() - 1].adjecent_vertexes.end()._Ptr, edje_amount(), edje_amount(), vertexes[vertexes.size() - 1].degree());
}

template<typename T>
typename adjecency_list<T>::const_edje_iterator adjecency_list<T>::edje_begin() const { return const_edje_iterator(&vertexes[0], vertexes.begin()._Ptr->adjecent_vertexes.begin()._Ptr, 0, edje_amount(), 0); }

template<typename T>
typename adjecency_list<T>::const_edje_iterator adjecency_list<T>::edje_end() const
{
	return const_edje_iterator(&vertexes[vertexes.size() - 1], vertexes[vertexes.size() - 1].adjecent_vertexes.end()._Ptr, edje_amount(), edje_amount(), vertexes[vertexes.size() - 1].degree());
}

//Reverse итератор для перебора рёбер
template<typename T>
typename adjecency_list<T>::edje_reverse_iterator adjecency_list<T>::edje_rbegin()
{
	return edje_reverse_iterator(&vertexes[vertexes.size() - 1], vertexes[vertexes.size() - 1].adjecent_vertexes.end()._Ptr - 1, edje_amount(), edje_amount(), vertexes[vertexes.size() - 1].degree() - 1);
}

template<typename T>
typename adjecency_list<T>::edje_reverse_iterator adjecency_list<T>::edje_rend()
{
	return edje_reverse_iterator(&vertexes[0], vertexes[0].adjecent_vertexes.begin()._Ptr - 1, 0, edje_amount(), -1);
}

template<typename T>
typename adjecency_list<T>::const_edje_reverse_iterator adjecency_list<T>::edje_rbegin() const
{
	return const_edje_reverse_iterator(&vertex[vertexes.size() - 1], vertexes[vertexes.size() - 1].adjecent_vertexes.end()._Ptr - 1, edje_amount(), edje_amount(), vertexes[vertexes.size() - 1].degree() - 1);
}

template<typename T>
typename adjecency_list<T>::const_edje_reverse_iterator adjecency_list<T>::edje_rend() const
{
	return const_edje_reverse_iterator(&vertexes[0], vertexes[0].adjecent_vertexes.begin()._Ptr - 1, 0, edje_amount(), -1);
}

#endif // !_ADJECENCY_LIST_