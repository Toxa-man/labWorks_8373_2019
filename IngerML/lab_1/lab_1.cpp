#include "pch.h"
#include <iostream>
#include <memory.h>
using namespace std;
using T = int;

class Vector
{
public:
	Vector();
	Vector(unsigned size_);
	Vector(unsigned size_,const T &val);
	Vector(const Vector&Vec);
	unsigned ReturnSize();
	void ReSize(unsigned NewSize);
	bool insert(unsigned pos, const T& val);
	void Push_Back(const T& val);
	bool contains(const T& val);
	int find(const T& val); 
	T*Data();
	Vector& operator =(const Vector&Vec);
	T& operator [](unsigned val);
	~Vector();
private:
	T *data;
	unsigned size;
};
Vector::Vector()
{
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
Vector::Vector(unsigned size_,const T &val)
{
	size = size_;
	data = new T[size];
	for (unsigned i = 0; i < size; i++)
	{
		data[i] = val;
	}
}
Vector::Vector(const Vector&Vec)
{
	size = Vec.size;
	data = new T[size];
	memcpy(data, Vec.data, sizeof(T)*size);
}
unsigned Vector::ReturnSize()
{
	return size;

}
void Vector::ReSize(unsigned NewSize)
{
	T*NewData;
	if (NewSize > size)
	{
		NewData = new T[NewSize];
		memcpy(NewData, data, sizeof(T)*size);
		delete[]data;
		data = NewData;
		for (unsigned i = size; i < NewSize; ++i)//for (unsigned i = size; i < NewSize; ++i)
		{
			data[i] = 0;
		}
		size = NewSize;

	}
	else
	{
		NewData = new T[size];
		memcpy(NewData, data, sizeof(T)*size);
		delete[]data;
		data = NewData;
		size = NewSize;
	}
}
bool Vector::insert(unsigned pos, const T& val)
{
	if (pos > size)
	{
		return false;
	}
	else
	{
		ReSize(ReturnSize() + 1);
		for (unsigned i = ReturnSize()- 1; i > pos; --i)
		{
			data[i] = data[i - 1];
		}
		data[pos] = val;
		return true;
	}
}
void Vector::Push_Back(const T& val)
{
	insert(ReturnSize(), val);
}
bool Vector::contains(const T& val)
{
	for (unsigned i = 0; i < size; ++i)
	{
		if (data[i] == val)
		{
			return true;
		}
	}
	return false;

}
int Vector::find(const T& val)
{
	for (unsigned  i = 0; i < size; ++i)
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
T& Vector::operator [](unsigned val)
{
	return data[val];
}
Vector& Vector::operator =(const Vector&Vec)
{
	if (this != &Vec)
	{
		size = Vec.size;
		delete[]data;
		data = new T[size];
		memcpy(data, Vec.data, sizeof(T)*size);
	}
	return *this;	
}
Vector::~Vector()
{
	size = 0;
	delete[]data;
}

int main()
{
	setlocale(LC_ALL, "ru");
	Vector myVector1();
	Vector myVector2(5);
	cout << "Размер первого массива:\t" << myVector2.ReturnSize() << endl;
	cout << "Массив: " << endl;
	for (unsigned i = 0; i < myVector2.ReturnSize(); i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (unsigned i = 0; i < myVector2.ReturnSize(); i++)
	{
		cout << myVector2[i] << "\t" ;
	}
	cout << endl;

	Vector myVector3(5, 2);
	cout << "Размер второго массива(myVector3(5, 2)):\t" << myVector3.ReturnSize() << endl;
	cout << "Массив: " << endl;
	for (unsigned i = 0; i < myVector3.ReturnSize(); i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (unsigned i = 0; i < myVector3.ReturnSize(); i++)
	{
		cout << myVector3[i] << "\t";
	}
	cout << endl;

	myVector3.ReSize(8);
	cout << "Новый массив, размером: " << myVector3.ReturnSize() << endl;
	for (unsigned i = 0; i < myVector3.ReturnSize(); i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (unsigned i = 0; i < myVector3.ReturnSize(); i++)
	{
		cout << myVector3[i] << "\t";
	}
	cout << endl;

	myVector3.insert(6, 999);
	cout << "Измененный массив, всавили на 6 место 999: " << endl;
	for (unsigned i = 0; i < myVector3.ReturnSize(); i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (unsigned i = 0; i < myVector3.ReturnSize(); i++)
	{
		cout << myVector3[i] << "\t";
	}
	cout << endl;

	myVector3.Push_Back(666);
	cout << "массив, в котором вконце добавленно число 666: " << endl;
	for (unsigned i = 0; i < myVector3.ReturnSize(); i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (unsigned i = 0; i < myVector3.ReturnSize(); i++)
	{
		cout << myVector3[i] << "\t";
	}
	cout << endl;

	cout << "Посмотрим есть ли в нашем массиве число 11?   "<< myVector3.contains(11) << endl;
	cout << "Добавим его в конец и найдем его номер по порядку:" << endl;
	myVector3.Push_Back(11);
	for (unsigned i = 0; i < myVector3.ReturnSize(); i++)
	{
		cout << myVector3[i] << "\t";
	}
	cout << endl;
	cout << "Номер числа 11: "<< myVector3.find(11) << endl << endl;
	system("pause");
	return 0;
}
