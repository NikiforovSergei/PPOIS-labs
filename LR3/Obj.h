#pragma once
template <class T>
class Obj
{
protected:
	T data;
public:
	Obj() {};

	Obj(T value)
	{
		data = value;
	}

	Obj operator=(T &value)
	{
		data = value;
	}

	friend bool operator> (const Obj &left, const Obj& right)
	{
		return left.data > right.data;
	}

	friend bool operator< (const Obj &left, const Obj &right)
	{
		return left.data < right.data;
	}

	friend bool operator>=(const Obj& left,const Obj& right)
	{
		return std::rel_ops::operator>=(left,right);
	}

	friend bool operator<=(const Obj& left,const Obj& right)
	{
		return std::rel_ops::operator<=(left,right);
	}

	friend std::ostream& operator<<(std::ostream& os, Obj& obj)
	{
		return os << obj.data;
	}
};