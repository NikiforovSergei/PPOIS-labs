#include "Mnogochlen.h"

Mnogochlen::Mnogochlen(int power)
{
	this->f = new double[power + 1];
	this->power = power;
	for (int i = 0; i <= power; i++)
	{
		this->f[i] = 0;
	}
}

void Mnogochlen::set(int index, double num)
{
	this->f[this->power - index] = num;
}

void Mnogochlen::print()
{
	for (int i = power; i > -1; i--)
	{
		if (this->f[i] != 0)
		{
			if (this->f[i] > 0 && i != power)
				cout << "+";
			cout << this->f[i];
			if (i != 0)
				cout << "x";
			if (i != 0 && i != 1)
				cout << "^" << i;
		}
	}
	cout << endl;
}

Mnogochlen Mnogochlen::operator +(const Mnogochlen& other)
{
	int n;
	if (this->power > other.power)
		n = this->power;
	else
		n = other.power;
	Mnogochlen a(n);
	a.copy(*this);
	Mnogochlen b(n);
	b.copy(other);
	Mnogochlen temp(n);

	for (int i = 0; i <= n; i++)
	{
		temp.f[i] = a.f[i] + b.f[i];
	}
	return temp;
}

Mnogochlen& Mnogochlen::operator +=(const Mnogochlen& other)
{
	*this = *this + other;
	return *this;
}

Mnogochlen Mnogochlen::operator -(const Mnogochlen& other)
{
	int n;
	if (this->power > other.power)
		n = this->power;
	else
		n = other.power;
	Mnogochlen a(n);
	a.copy(*this);
	Mnogochlen b(n);
	b.copy(other);
	Mnogochlen temp(n);

	for (int i = 0; i <= n; i++)
	{
		temp.f[i] = a.f[i] - b.f[i];
	}
	return temp;
}

Mnogochlen& Mnogochlen::operator -=(const Mnogochlen& other)
{
	*this = *this - other;
	return *this;
}

Mnogochlen Mnogochlen::operator *(const Mnogochlen& other)
{
	int l, i, j, k;
	int n = this->power + other.power;
	Mnogochlen temp(n);
	for (k = 0; k <= n; k++)
	{
		for (i = 0; i <= this->power; i++)
		{
			for (j = 0; j <= other.power; j++)
			{
				if (i + j == k)
					temp.f[k] += this->f[i] * other.f[j];
			}
		}
	}
	return temp;
}

Mnogochlen& Mnogochlen::operator *=(const Mnogochlen& other)
{
	*this = *this * other;
	return *this;
}

Mnogochlen Mnogochlen::operator /(const Mnogochlen& other)
{
	if (this->power < other.power)
	{
		cout << ">:(";
		Mnogochlen temp(0);
		return temp;
	}
	else
	{
		Mnogochlen a(this->power);
		a.copy(*this);
		int x = a.power;
		int y = other.power;
		int m = this->power - other.power;
		Mnogochlen temp(m);
		while (m > -1)
		{
			temp.f[m] = a.f[x] / other.f[y];
			for (int k = 0; k <= y; k++)
			{
				a.f[x - k] = a.f[x - k] - other.f[y - k] * temp.f[m];
			}
			m--;
			x--;
		}
		if (!a.Zero())
		{
			cout << "ostatok: ";
			a.print();
		}
		return temp;
	}
}

Mnogochlen& Mnogochlen::operator /=(const Mnogochlen& other)
{
	if (this->power < other.power)
	{
		Mnogochlen temp(-1);
		*this = temp;
		return temp;
	}
	else
	{
		Mnogochlen a = *this;
		int x = a.power;
		int y = other.power;
		int m = this->power - other.power;
		Mnogochlen temp(m);
		while (m > -1)
		{
			temp.f[m] = a.f[x] / other.f[y];
			for (int k = 0; k <= y; k++)
			{
				a.f[x - k] = a.f[x - k] - other.f[y - k] * temp.f[m];
			}
			m--;
			x--;
		}
		*this = temp;
		return *this;
	}
}

Mnogochlen& Mnogochlen::operator =(const Mnogochlen& other)
{
	this->power = other.power;

	if (this->f != nullptr)
	{
		delete this->f;
	}

	this->f = new double[other.power + 1];

	for (int i = 0; i <= other.power; i++)
	{
		this->f[i] = other.f[i];
	}
	return *this;
}

double Mnogochlen::operator()(double x)
{
	double sum = 0;
	for (int i = 0; i <= this->power; i++)
	{
		sum += this->f[i] * pow(x, i);
	}
	return sum;
}

double Mnogochlen::operator[](int index)
{
	return this->f[index];
}

bool Mnogochlen::operator ==(const Mnogochlen& other)
{
	bool b = true;
	if (this->power != other.power)
	{
		b = false;
	}
	else
	{
		for (int i = 0; i <= this->power; i++)
		{
			if (this->f[i] != other.f[i])
				b = false;
		}
	}
	return b;
}

bool Mnogochlen::operator !=(const Mnogochlen& other)
{
	bool b = true;
	if (*this == other)
		b = false;
	return b;
}

Mnogochlen Mnogochlen::copy(const Mnogochlen& other)
{
	for (int i = 0; i <= other.power; i++)
	{
		this->f[i] = other.f[i];
	}
	return *this;
}

bool Mnogochlen::Zero()
{
	bool t = true;
	for (int i = 0; i <= power; i++)
	{
		if (this->f[i] != 0)
			t = false;
	}
	return t;
}