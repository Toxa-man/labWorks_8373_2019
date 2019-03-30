#include <iostream>
#include <memory.h>
using namespace std;
using T = int;
class Vector {
public:
	Vector();
	Vector(unsigned sizee);
	Vector(unsigned sizee, const T& val);
	unsigned Size();
	void resize(unsigned sizee);
	bool insert(unsigned pos, const T& val);
	void push_back(const T& val);
	bool contains(const T& val);
	T& operator[] (unsigned index);
	int find(const T& val);
	T*get_data();
	Vector&operator= (const Vector&vec);
	~Vector();
	Vector(const Vector&vec);

private:
	T*data;
	unsigned size;
};
Vector::Vector() {
	size = 0;
	data = nullptr;
}

Vector::Vector(unsigned sizee)
{
	size = sizee;
	data = new T[size];
	for (unsigned i = 0; i < size; i++) {
		data[i] = T();
	}
}

Vector::~Vector() {
	size = 0;
	delete[]data;
}

Vector::Vector(unsigned sizee, const T& val)
{
	size = sizee;
	data = new T[sizee];
	for (unsigned i = 0; i < size; i++)
	{
		data[i] = val;
	}
}
unsigned Vector::Size()
{
	return size;
}

void Vector::resize(unsigned sizee)
{
	T*var = data;
	data = new T[sizee];
	if (sizee > size) {
		memcpy(data, var, sizeof(T)*sizee);
		for (unsigned i = size; i < sizee; i++)
		{
			data[i] = 0;
		}
	}
	else {
		memcpy(data, var, sizeof(T)*sizee);
	}

	delete[]var;
	size = sizee;
}

bool Vector::insert(unsigned pos, const T& val)
{
	if (pos <= size)
	{
		resize(size + 1);
		for (unsigned i = pos; i < size; i++)
		{
			data[i] = data[i - 1];
		}
		data[pos - 1] = val;
		return true;
	}
	else
		return false;
}

void Vector::push_back(const T& val)
{
	resize(size + 1);
	insert(size + 1, val);
}

bool Vector::contains(const T& val)
{
	for (unsigned i = 0; i < size; i++)
	{
		if (data[i] == val) {
			return true;
		}
	}
	return false;
}

T & Vector::operator[] (unsigned index)
{
	return data[index];
}

int Vector::find(const T& val)
{
	for (unsigned i = 0; i < size; i++)
	{
		if (data[i] == val) {
			return i;
		}
	}
	return -1;
}

T* Vector::get_data()
{
	return data;
}

Vector::Vector(const Vector&vec) {
	size = vec.size;
	data = new int[size];
	memcpy(data, vec.data, sizeof(int)*size);
}

Vector&Vector::operator = (const Vector &vec) {
	if (this != &vec) {
		size = vec.size;
		delete[]data;
		data = new int[size];
		memcpy(data, vec.data, sizeof(int)*size);
	}
	return*this;
}

int main()
{
	unsigned size;
	cout << "Input the size of the vector: ";
	cin >> size;
	Vector vector(size);
	cout << "Vector :  ";
		for (int i = 0; i < size; i++)
		{
			cout << vector[i]<<" ";
		}
	cout << endl;
	
	T number;
	cout << "input number: ";
	cin>>number;
	Vector vector1(size, number);
	cout << endl;
	cout << "Vector :  ";
	for (int i = 0; i < size; i++)
	{
		cout << vector1[i] << " ";
	}
	cout << endl<< "Size: " << vector1.Size() << endl;
	int NewSize;
	cout << "Input the  new size of the vector: ";
	cin >> NewSize;
	vector.resize(NewSize);
	size = NewSize;
	cout << endl;
	cout << "Vector: ";
	for (int i = 0; i < size; ++i)
		cout << vector[i]<<" ";
	cout << endl << "Size:" << vector.Size() << endl;
	cout << "Insert number into vector: ";
	if (vector.insert(3, 8) == true)
	{
		size = size + 1;
		for (int i = 0; i < size; i++)
			cout << vector[i]<<" ";
	}
	cout << endl << "The size is:" << vector.Size() << endl;
	cout << "Insert number at the end of vector: ";
	vector.push_back(number);
	size++;
	for (int i = 0; i < size; i++)
		cout << vector[i] << " ";
	cout << endl;
	cout << "Vector contains number(0-no,1-yes):" << vector.contains(number) << endl;
  cout<<"Containts number: ";
  int cont;
  cin>>cont;
	cout << "Vector contains"<<cont<<" and its index(-1-no number):" << vector.find(cont) << endl;
	cout << "Pointer to internal buffer:" << vector.get_data() << endl;

	system("pause");
}
