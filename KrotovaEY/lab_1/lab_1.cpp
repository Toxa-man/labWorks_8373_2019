#include <iostream>
#include <conio.h>
#include <cstring>
using namespace std;

using T = int;

class Vector
{
public:
	Vector();
	Vector(unsigned _size);
	Vector(unsigned _size, const T& val);
	~Vector();
	unsigned Size();
	void resize(unsigned _size);
	bool insert(unsigned pos, const T& val);
	void push_back(const T& val);
	bool contains(const T& val);
	T& operator [](unsigned index);
	int find(const T& val);
	T* Data();
	Vector(const Vector& vec);
	Vector& operator =(const Vector& vec);
private:
	T *data;
	unsigned size;
};

Vector::Vector()
{
	size = 0;
	data = nullptr;
}

Vector::Vector(unsigned _size)
{
	size = _size;
	data = new T[size];
	for (int i = 0; i < size; ++i)
	{
		data[i] = T();
	}
}

Vector::~Vector()
{
	size = 0;
	delete[]data;
}

Vector::Vector(unsigned _size, const T& val)
{
	size = _size;
	data = new T[size];
	for (int i = 0; i < size; ++i)
	{
		data[i] = val;
	}
}

unsigned Vector::Size()
{
	return size;
}

void Vector::resize(unsigned _size)
{
	T*tef = data;
	data = new T[_size];
	if (_size <= size)
	{
		memcpy(data, tef, sizeof(T)*_size);
	}
	else
	{
		memcpy(data, tef, sizeof(T)*size);
		for (int i = size; i < _size; ++i)
		{
			data[i] = 0;
		}
	}
	delete[]tef;
	size = _size;
}

bool Vector::insert(unsigned pos, const T& val)
{
	if ((pos > size)||(!pos))
	{
		return false;
	}
	else
	{
		resize(size + 1);
		for (int i = pos; i < size; ++i)
		{
			data[i] = data[i - 1];
		}
		data[pos-1] = val;
		return true;
	}
}

void Vector::push_back(const T& val)
{
	resize(size + 1);
	insert(size, val);
	resize(size - 1);
}

bool Vector::contains(const T& val)
{
	if (find(val) == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

T& Vector::operator [](unsigned index)
{
	return data[index];
}

int Vector::find(const T& val)
{
	for (int i = 0; i < size; ++i)
	{
		if (data[i] == val)
		{
			return i;
		}
	}
	return -1;
}

T* Vector::Data()
{
	return data;
}

Vector:: Vector(const Vector& vec) 
{
	size = vec.size;
	data = new T[size];
	memcpy(data, vec.data, sizeof(T)*size);
}
Vector& Vector::operator =(const Vector& vec)
{
	if (this != &vec)
	{
		size = vec.size;
		delete[]data;
		data = new T[size];
		memcpy(data, vec.data, sizeof(T)*size);
	}
	return *this; 
}

int main()
{
	setlocale(0, "");
	unsigned size;
	cout << "Введите размер";
	cin >> size;
	Vector vec1(size);
	for (int i = 0; i < size; ++i)
	{
		cout << vec1[i];
	}
	cout << endl;
	int r = 6;
	Vector vec2(size, r);
	for (int i = 0; i < size; ++i)
	{
		cout << vec2[i];
	}
	cout << endl;
	cout << vec1.Size()<<endl;
	vec1 = vec2;
	cout << "Введите новый размер";
	unsigned size2;
	cin >> size2;
	vec1.resize(size2);
	for (int i = 0; i < size2; ++i)
	{
		cout << vec1[i];
	}
	cout << endl;
	vec2.insert(3, 7);
	vec2.push_back(1);
	for (int i = 0; i < vec2.Size(); ++i)
	{
		cout << vec2[i];
	}
	T a;
	cout << "Какое число проверить";
	cin >> a;
	cout << vec2.contains(a) << vec2.find(a)<<endl;	
	cout << vec2.Data();
	_getch();
}