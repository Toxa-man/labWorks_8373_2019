#include "pch.h"
#include <iostream>
#include <conio.h>
using T = unsigned int;


class Vector
{
private:
	T* data;
	unsigned size;
public:
	Vector();
	Vector(unsigned size_);
	Vector(unsigned size_, const T& val);
	Vector(const Vector& vec);
	~Vector();
	unsigned Size();
	void resize(unsigned size_);
	bool insert(unsigned pos, const T& val);
	void push_back(const T& val);
	bool contains(const T& val);
	T& operator [](unsigned index);
	int find(const T& val);
	T* Data();
	void print();
	Vector& operator =(const Vector& vec);
};

Vector::Vector() {
	size = 0;
	data = nullptr;
}
Vector::Vector(unsigned size_)
{
	size = size_;
	data = new T[size];
	for (unsigned i = 0; i < size; i++)
	{
		data[i] = T();
	}
}
Vector::Vector(unsigned size_, const T& val)
{
	size = size_;
	data = new T[size];
	for (unsigned i = 0; i < size; i++)
	{
		data[i] = val;
	}
}
Vector::Vector(const Vector& vec)
{
	size = vec.size;
	data = new T[size];
	memcpy(data, vec.data, sizeof(T)*size);
}
Vector::~Vector()
{
	size = 0;
	delete[] data;
}
unsigned Vector::Size()
{
	return size;
}
void Vector::resize(unsigned size_)
{
	T* ptr = new T[size_];
	if (size_ >= size)
	{
		memcpy(ptr, data, sizeof(T)*size);
		for (int i = size; i < size_; i++)
		{
			ptr[i] = 0;
		}
	}
	else
	{
		memcpy(ptr, data, sizeof(T)*size_);
	}
	delete[] data;
	size = size_;
	data = ptr;
}
bool Vector::insert(unsigned pos, const T& val)
{
	if (pos <= size)
	{
		resize(size + 1);
		T temp1, temp2;
		temp2 = val;
		for (int i = pos; i < size; i++)
		{
			temp1 = data[i];
			data[i] = temp2;
			std::swap(temp1, temp2);
		}
		return true;
	}
	else
	{
		return false;
	}
}
void Vector::push_back(const T& val)
{
	insert(size, val);
}
bool  Vector::contains(const T& val)
{
	for (int i = 0; i < size; i++)
	{
		if (data[i] == val)
		{
			return true;
		}
	}
	return false;
}
T& Vector::operator [](unsigned index)
{
	return data[index];
}
int Vector::find(const T& val)
{
	int result = -1;
	for (int i = 0; i < size; i++)
	{
		if (data[i] == val)
		{
			result = i;
			break;
		}
	}
	return result;
}
void Vector::print()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << data[i] << ' ';
	}
	std::cout << std::endl;
}
T* Vector::Data() 
{
	return data;
}

Vector& Vector::operator =(const Vector& vec)
{
	if (this != &vec)
	{
		size = vec.size;
		delete[] data;
		data = new T[size];
		memcpy(data, vec.data, sizeof(T)*size);
	}
	return *this;
}
int main()
{
	Vector a(5, 5);
	a.print();
	
	std::cout << "Size():  " << a.Size() << std::endl;
	a.resize(7);
	std::cout << "resize(7),    Size():  " << a.Size() << std::endl;
	a.insert(3, 1);
	
	std::cout << "insert (3, 1):  ";
	a.print();
	
	a.push_back(0);
	std::cout << "push_back(0):  ";
	a.print();
	
	std::cout << "contains(0):  " << a.contains(0) << "  contains(67):  " << a.contains(67)<< std::endl;
	std::cout << "find(0):  " << a.find(0) << "  find(67):  " << a.find(67) << std::endl;
	a[3] = 8;
	std::cout << "a[3] = 8" << std::endl;
	a.print();
	std::cout << "Data():  " << a.Data() << std::endl;
	Vector b(10, 3);
	a = b;
	std::cout << "Vector b(10,3), a = b, a:  ";
	a.print();
	_getch();
	return 0;
}