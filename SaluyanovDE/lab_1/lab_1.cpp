#include "stdafx.h"
#include <iostream>
#include <memory.h>
using T = int;

class vector
{
public:
	vector();
	vector(unsigned Size_);
	vector(unsigned Size_, const T&val);
	vector(const vector&vec);
	unsigned size();
	void resize(unsigned NewSize);
	bool insert(unsigned pos, const T&val);
	void push_back(const T&val);
	bool contains(const T&val);
	int find(const T&val);
	T* get_data();
	vector& operator =(const vector&vec);
	T& operator [](unsigned val);
	~vector();
private:
	T*data;
	unsigned Size;
};
vector::vector()
{
	Size = 0;
	data = nullptr;
}
vector::vector(unsigned Size_):Size(Size_)
{
	data = new T[Size];
	for (unsigned i = 0; i < Size; ++i)
	{
		data[i] = T();
	}
}
vector::vector(unsigned Size_, const T&val):Size(Size_)
{
	data = new T[Size];
	for (unsigned i = 0; i < Size; ++i)
	{
		data[i] = val;
	}
}
vector::vector(const vector&vec)
{
	Size = vec.Size;
	data = new T[Size];
	memcpy(data, vec.data, sizeof(T)*Size);
}
unsigned vector::size()
{
	return Size;
}
void vector::resize(unsigned NewSize)
{
	T*buffer;
	if (NewSize > Size)
	{
		buffer = new T[NewSize];
		memcpy(buffer, data, sizeof(T)*Size);
		delete[]data;
		data = buffer;
		for (unsigned i = Size; i < NewSize; ++i)
		{
			data[i] = 0;
		}
		Size = NewSize;
	}
	else
	{
		buffer = new T[Size];
		memcpy(buffer, data, sizeof(T)*Size);
		delete[]data;
		data = buffer;
		Size = NewSize;
	}
}
bool vector::insert(unsigned pos, const T&val)
{
	if (pos > Size)
	{
		return false;
	}
	else
	{
		resize(size() + 1);
		for (unsigned i = size() - 1; i > pos; --i)
		{
			data[i] = data[i - 1];
		}
		data[pos] = val;
		return true;
	}
}
void vector::push_back(const T&val)
{
	insert(size(), val);
}
bool vector::contains(const T&val)
{
	for (unsigned i = 0; i < Size; ++i)
	{
		if (val == data[i])
		{
			return true;
		}
	}
	return false;
}
int vector::find(const T&val)
{
	for (unsigned i = 0; i < Size; ++i)
	{
		if (val == data[i])
		{
			return i;
		}
	}
	return -1;
}
T* vector::get_data()
{
	return data;
}
vector& vector::operator =(const vector&vec)
{
	if (this != &vec)
	{
		Size = vec.Size;
		delete[]data;
		data = new T[Size];
		memcpy(data, vec.data, sizeof(T)*Size);
		return *this;
	}
}
T& vector::operator [](unsigned val)
{
	return data[val];
}
vector::~vector()
{
	Size = 0;
	delete[]data;
}

int main()
{
	vector vec00();
	vector vec0(4);
	vector vec1(0);
	std::cout << "vector 1 size is: ";
	std::cout << vec1.size() << '\n';
	vec1.resize(5);
	std::cout << "vector 1 size after resize is: ";
	std::cout << vec1.size() << '\n';
	vector vec2(5, 3);
	std::cout << "vector 2 values (vector vec2(5, 3)) is: \n";
	for (unsigned i = 0; i < vec2.size(); ++i)
	{
		std::cout << i << " value: ";
		std::cout << vec2[i] << '\n';
	}
	vec2[3] = 4;
	std::cout << "vector 2 3rd value after assignment(4) is: ";
	std::cout << vec2[3] << '\n';
	vec2.resize(6);
	std::cout << "vector 2 values after resize (old size < new size): \n";
	for (unsigned i = 0; i < vec2.size(); ++i)
	{
		std::cout << i << " value: ";
		std::cout << vec2[i] << '\n';
	}
	vec2.resize(4);
	std::cout << "vector 2 values after resize (old size >= new size): \n ";
	for (unsigned i = 0; i < vec2.size(); ++i)
	{
		std::cout << i << " value: ";
		std::cout << vec2[i] << '\n';
	}
	std::cout << "check for insert 55 in pos 3 and 22 in pos 22 (1 - pos inhere vector size, 0 - pos beyond vector size): ";
	std::cout << vec2.insert(3, 55) << ", " << vec2.insert(22, 22) << '\n';
	std::cout << "check for insert (written out value in pos 3): ";
	std::cout << vec2[3] << '\n';
	std::cout << "check for push_back(33) function (written out last value of vector after pushback): ";
	vec2.push_back(33);
	std::cout << vec2[vec2.size() - 1] << '\n';
	std::cout << "check for contains 33 and 566 function (1 - contains, 0 - not contains): ";
	std::cout << vec2.contains(33) << ", " << vec2.contains(566) << '\n';
	std::cout << "check for find 33 and 533 function (-1 - error, there is no assignment value,"
		<< "other output - position of assignment value): ";
	std::cout << vec2.find(33) << ", " << vec2.find(533) << '\n';
	std::cout << "check for get_data function: ";
	std::cout << vec2.get_data();

	return 0;
}
