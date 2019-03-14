#include <iostream>
#include <memory.h>

using namespace std;


template<typename T>
class Vector
{
private:
	T* arr;
	unsigned size;

public:

	Vector();
	Vector(const Vector &other);
	Vector(unsigned size);
	Vector(unsigned size, const T& val);

	unsigned Size();


	void resize(unsigned size);
	bool insert(unsigned int pos, const T& val);
	void push_back(const T& val);

	bool contains(const T& val);
	int find(const T& val);
	
	T* data();

	T &operator [](unsigned index)
	{
		return arr[index];
	}
	
	Vector &operator =(const Vector &second)
	{
		this->size = second.size;
		delete[] this->arr;
		this->arr = new T[second.size];
		memcpy(this->arr, second.arr, second.size * sizeof(T));
		return *this;
	}

	~Vector();
};

template<typename T>
Vector<T>::Vector()
{
	size = 0;
}

template<typename T>
Vector<T>::Vector(const Vector &other)
{
	this->size = other.size;
	this->arr = new T[other.size];
	memcpy(this->arr, other.arr, size * sizeof(T));
}

template<typename T>
Vector<T>::Vector(unsigned size)
{
	this->size = size;
	arr = new T[size];
	memset(arr, 0, size * sizeof(T));
}

template<typename T>
Vector<T>::Vector(unsigned size, const T& val)
{
	this->size = size;
	arr = new T[size];
	for (unsigned i = 0; i < size; i++)
		arr[i] = val;
}

template<typename T>
unsigned Vector<T>::Size()
{
	return size;
}

template<typename T>
void Vector<T>::resize(unsigned size)
{
	T* buf = new T[size];
	if (this->size > size)
		memcpy(buf, arr, size * sizeof(T));
	else
	{
		memcpy(buf, arr, this->size * sizeof(T));
		memset(&buf[this->size], 0, (size - this->size) * sizeof(T));
	}

	delete[] arr;
	arr = new T[size];
	this->size = size;
	memcpy(arr, buf, size * sizeof(T));
	delete[] buf;
}

template<typename T>
bool Vector<T>::insert(unsigned int pos, const T& val)
{
	if ((pos >= 0) && (pos <= size))
	{
		T* buf = new T[size + 1];
		memcpy(buf, arr, (pos - 1) * sizeof(T));
		buf[pos - 1] = val;
		for (unsigned i = pos; i < size + 1; i++)
		{
			buf[i] = arr[i - 1];
		}
		delete[] arr;
		arr = new T[size + 1];
		size += 1;
		memcpy(arr, buf, size * sizeof(T));


		delete[] buf;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
void Vector<T>::push_back(const T& val)
{
	T* buf = new T[size + 1];
	memcpy(buf, arr, size * sizeof(T));
	buf[size] = val;
	delete[] arr;
	size += 1;
	arr = new T[size];
	memcpy(arr, buf, size * sizeof(T));
	delete[] buf;
}

template<typename T>
bool Vector<T>::contains(const T& val)
{
	for (unsigned i = 0; i < size; i++)
	{
		if (arr[i] == val)
			return true;
	}
	return false;
}

template<typename T>
int Vector<T>::find(const T& val)
{
	for (unsigned i = 0; i < size; i++)
	{
		if (arr[i] == val)
			return i;
	}
	return -1;
} 

template<typename T>
T* Vector<T>::data()
{
	return this->arr;
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] arr;
}




int main()
{
	Vector<int> a;
	int size = 3;
	Vector<double> b(size);
	cout << "Created vector B on 3 value: ";
	for (unsigned i = 0; i < b.Size(); i++)
		cout << b[i] << " ";

	cout << "\n\n";


	b.push_back(5);
	cout << "Added value 5 using push_back: ";
	for (unsigned i = 0; i < b.Size(); i++)
		cout << b[i] << " ";

	cout << "\n\n";


	b.resize(6);
	cout << "Resized vector B by 6 elements: ";
	for (unsigned i = 0; i < b.Size(); i++)
		cout << b[i] << " ";

	cout << "\n\n";
	
	
	b.insert(5, 8);
	cout << "Added value 8 with index 5 for vector B using insert function: ";
	for (unsigned i = 0; i < b.Size(); i++)
		cout << b[i] << " ";

	cout << "\n\n";
	
	cout << "Search for a value of 8 in a vector B using contains: " << b.contains(8) << endl;
	cout << "Search for a value of 50 in a vector B using contains: " << b.contains(50) << "\n" << endl;
	cout << "Search for a value of 8 in a vector B using find: " << b.find(8) << endl;
	cout << "Search for a value of 50 in a vector B using find: " << b.find(50) << endl;
	cout << "\n\n";

	Vector<double> d(4, 6);
	cout << "Created vector D on 4 value filled with 6: ";
	for (unsigned i = 0; i < d.Size(); i++)
		cout << d[i] << " ";

	cout << "\n\n";

	
	Vector<double> g(b);
	cout << "Created copy of the vector vector B: ";
	for (unsigned i = 0; i < g.Size(); i++)
		cout << g[i] << " ";

	cout << "\n\n";


	

	g = d;
	cout << "Check assignment operation: ";
	for (unsigned i = 0; i < g.Size(); i++)
		cout << g[i] << " ";
	cout << "\n\n";

	cout << "Check data function: " << b.data() << endl;
}