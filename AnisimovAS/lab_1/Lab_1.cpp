#include "pch.h"
#include <iostream>
#include <memory.h>

using T = int;

using namespace ::std;

class Vector
{
public:
	Vector(); 
	Vector(unsigned size1);
	Vector(unsigned size1, const T& val);
	Vector(const Vector&Vector1);

	Vector& operator =(const Vector&Vector1);

	void resize(unsigned size1);
	void push_back(const T& val);

	bool insert(unsigned pos, const T& val);	
	bool contains(const T& val);

	int find(const T& val);

	T& operator [](unsigned index);
	T* data1();

	unsigned Size();

	~Vector();

private:
	T*data;
	unsigned size;
};

Vector::Vector() // defualt constructor
{
	data = nullptr;

	size = 0;
}

Vector::Vector (unsigned size1) :size(size1) //mass. with defualt value
{
	data = new T[size];

	for (unsigned i = 0; i < size; i++)
	{
		data[i] = T();
	}
}

Vector::Vector(unsigned  size1, const T& val) //mass. with val value
{
	data = new T[size];

	for (unsigned i = 0; i < size; i++)
	{
		data[i] = val;
	}
}

Vector::Vector(const Vector&Vector1)
{
	size = Vector1.size;
	data = new T[size];

	memcpy(data, Vector1.data, sizeof(T)*size);
}

unsigned Vector::Size() //return value of mass.
{
	return size;
}

void Vector::resize(unsigned size1)
{
	T*buff;
	
	if (size1 > size)
	{
		buff = new T[size1];

		memcpy(buff, data, sizeof(T)*size);
		delete[]data;
		data = buff;

		for (unsigned i = size; i < size1; i++)
		{
			buff[i] = 0;
		}

		size = size1;
	}
	else
	{
		buff = new T[size];

		memcpy(buff, data, sizeof(T)*size1);

		delete[]data;
		data = buff;
		size = size1;
	}

	
}

bool Vector::insert(unsigned pos, const T& val)
{
	if (pos <= size)
	{
		resize(size + 1);

		for (unsigned i = pos; i < size; ++i)
		{
			data[i] = data[i - 1];
		}

		data[pos-1] = val;

		return (true);
	}
	else
	{
		return (false);
	}
}

void Vector::push_back(const T& val)
{
	insert(size, val);
}

bool Vector::contains(const T& val)
{
	for (unsigned i = 0; i < size; i++)
	{
		if (data[i] == val)
		{
			return (true);
		}
	}

	return (false);
}

T& Vector::operator [](unsigned index)
{
	return data[index];
}

int Vector::find(const T& val)
{
	for (unsigned i = 0; i < size; ++i)
	{
		if (val == data[i])
		{
			return (i);
		}

	}
			return (-1);
}

Vector& Vector::operator =(const Vector&Vector1)
{
	if (this != &Vector1)
	{
		size = Vector1.size;

		delete[]data;
		data = new T[size];

		memcpy(data, Vector1.data, sizeof(T)*size);
	}
	return *this;
}

T* Vector::data1()
{
	return (data);
}

Vector::~Vector() 
{
	size = 0;
	delete[]data;
}

int main()
{
	Vector Vector1(7);
	
	Vector1.resize(12);

	cout << "Actual size of Vector1: " << Vector1.Size() << endl;
	cout << endl;

	Vector1.insert(11, 1);

	cout << "Try to find '1' in Vector1: " << Vector1.find(1) << endl;
	cout << endl;

	Vector1.push_back(69);
	cout << "Try to find 69 in Vector1: " << Vector1.contains(69) << endl;
	cout << endl;


	cout << "Get Data: " << Vector1.data1() << endl;
}