#include <iostream>
#include <memory.h>
using namespace std;
using T = int;
class Vector {
public:
	Vector();
	~Vector();
	Vector(unsigned size);
	Vector(unsigned size, const T& val);
	unsigned size();
	void resize(unsigned size);
	bool insert(unsigned pos, const T& val);
	void push_back(const T& val);
	bool contains(const T& val);
	T & operator [](unsigned index);
	int find(const T& val);
	T* data();
	Vector&operator = (const Vector& vec);
	Vector(const Vector&vec);
private:
	unsigned Size;
	T*mass;
};
Vector::Vector()
{
	Size = 0;
	mass = nullptr;
};
Vector::~Vector()
{
	Size = 0;
	delete[]mass;
};
Vector::Vector(unsigned size)
{
	Size = size;
	mass = new T[Size];
	for (int i = 0; i < Size; ++i)
		mass[i] = T();
};
Vector::Vector(unsigned size, const T& val)
{
	Size = size;
	mass = new T[Size];
	for (int i = 0; i < Size; ++i)
		mass[i] = val;
}
unsigned Vector::size()
{
	return Size;
}
void Vector::resize(unsigned size)
{
	T*old_mass = mass;
	mass = new T[size];
	if (size > Size)
	{
		memcpy(mass, old_mass, sizeof(T)*Size);
		for (int i = Size; i < size; ++i)
			mass[i] = 0;
	}
	else
		memcpy(mass, old_mass, sizeof(T)*size);
	delete[]old_mass;
	Size = size;
}
bool Vector::insert(unsigned pos, const T& val)
{
	if (pos <= Size)
	{
		resize(Size + 1);
		for (int i = Size-1; i > pos; --i)
			mass[i] = mass[i - 1];
		mass[pos-1] = val;
		return true;
	}
	else
		return false;
}
void Vector::push_back(const T& val)
{
	resize(Size + 1);
	mass[Size-1] = val;
}
bool Vector::contains(const T& val)
{
	bool prov = false;
	for (int i = 0; i < Size; ++i)
	{
		if (mass[i] == val)
			prov = true;
	}
	return prov;
}
T & Vector::operator [](unsigned index)
{
	return mass[index];
}
int Vector::find(const T& val)
{
	int index = -1;
	for (int i = 0; i<Size; ++i)
	{
		if (mass[i]==val)
			index = i;
	}
	return index;
}
T* Vector::data()
{
	return mass;
}
Vector&Vector::operator =(const Vector&vec)
{
	if (this != &vec) 
	{
		Size = vec.Size;
		delete[]mass;
		mass = new int[Size];
		memcpy(mass, vec.mass, sizeof(int)*Size);
		return*this;
	}
}
Vector::Vector(const Vector&vec)
{
	Size = vec.Size;
	mass = new T[Size];
	memcpy(mass, vec.mass, sizeof(T)*Size);
}
int main()
{

	unsigned Size;
	cout << "Input size: ";
	cin >> Size;
	Vector vect(Size);
	cout << "The vector is: ";
	for (int i = 0; i < Size; ++i)
		cout << vect[i]<<" ";
	cout << endl;
	T val;
	cout << "Input number: ";
	cin >> val;
	Vector vect1(Size, val);
	cout << "The vector is: ";
	for (int i = 0; i < Size; ++i)
		cout << vect1[i] << " ";
	cout<<endl<< "The size is:" << vect.size() << endl;
	int new_size;
	cout << "Input new size: ";
	cin >> new_size;
	vect.resize(new_size);
	Size = new_size;
	cout << "The vector is: ";
	for (int i = 0; i < Size; ++i)
		cout << vect[i];
	cout << endl<< "The size is:" << vect.size() << endl;
	cout << "Insert number into vector: ";
	if (vect.insert(5, 7) == true)
	{
		Size = Size + 1;
		for (int i = 0; i < Size; ++i)
			cout << vect[i];
	}
	cout <<endl<< "The size is:" << vect.size() << endl;
	cout << "Insert number at the end of vector: ";
	vect.push_back(val);
	Size++;
	for (int i = 0; i < Size; ++i)
		cout << vect[i];

	cout <<"Vector contains number(0-no,1-yes):"<< vect.contains(val)<<endl;
	cout << "Vector contains 9 and its index(-1-no number):" << vect.find(9) << endl;
	cout << "Pointer to internal buffer:" << vect.data()<<endl;
	system("pause");
}