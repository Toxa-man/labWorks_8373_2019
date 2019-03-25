#include <iostream>
#include <memory.h>

using T = unsigned;
using namespace std;

class Vector
{
	unsigned size;
	T* data;
public:
	Vector();
	Vector(T size);
	Vector(T size, const T& val);
	Vector(const Vector& vec);
	Vector& operator = (const Vector&vec);
	unsigned sizevec();
	void resize(T size);
	bool insert(T pos, const T& val);
	void push_back(const T& val);
	bool contains(const T& val);
	T& operator [] (T index);
	int find(const T& val);
	T* getdata();
	~Vector();
};

Vector::Vector()
{
	size = 0;
	data = nullptr;
}

Vector::Vector(T size_)
{
	size = size_;
	data = new T[size];
	for (T i = 0; i < size; i++)
	{
		data[i] = i;
	}
}

Vector::Vector(T size_, const T& val)
{
	size = size_;
	data = new T[size];
	for (T i = 0; i < size; i++)
	{
		data[i] = val;
	}
}

unsigned Vector::sizevec()
{
	return size;
}

void Vector::resize(T size_)
{
	T* newdata = new T[size_];
	if (size_ >= size)
	{
		memcpy(newdata, data, sizeof(T)*size);
		for (T i = size; i < size_; i++)
		{
			newdata[i] = 0;
		}
	}
	else
	{
		memcpy(newdata, data, sizeof(T)*size_);
	}
	delete[]data;
	data = newdata;
	size = size_;
}

bool Vector::insert(T pos, const T& val)
{
	if (pos <= size)
	{
		resize(size + 1);
		for (T i = pos + 1; i < size-1; i++)
		{
			data[i + 1] = data[i];
		}
		data[pos] = val;
		return true;
	}
	else
		return false;
}

void Vector::push_back(const T& val)
{
	insert(sizevec(), val);
}

bool Vector::contains(const T& val)
{
	for (T i = 0; i < size; i++)
	{
		if (data[i] == val)
			return true;
	}
	return false;
}

T& Vector::operator[](T index)
{
	return data[index];
}

int Vector::find(const T& val)
{
	for (T i = 0; i < size; i++)
	{
		if (data[i] == val)
			return i;
	}
	return -1;
}

T * Vector::getdata()
{
	return data;
}

Vector::~Vector()
{
	size = 0;
	delete[]data;
}

Vector::Vector(const Vector & vec)
{
	size = vec.size;
	data = new T[size];
	memcpy(data, vec.data, sizeof(T)*size);
}

Vector & Vector::operator = (const Vector & vec)
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
	Vector vec1(5), vec2(6, 2), vec3(7, 3);
	cout << "Vec1:" << endl;
	for (T i = 0; i < vec1.sizevec(); i++)
		cout << vec1[i] << " ";
	cout << endl << endl;
	cout << "Vec2:" << endl;
	for (T i = 0; i < vec2.sizevec(); i++)
		cout << vec2[i] << " ";
	cout << endl << endl;
	cout << "Vec3:" << endl;
	for (T i = 0; i < vec3.sizevec(); i++)
		cout << vec3[i] << " ";
	cout << endl << endl;

	cout << "Resize Vec1(9):" << endl;
	T size_ = 9;
	vec1.resize(size_);
	for (T i = 0; i < vec1.sizevec(); i++)
		cout << vec1[i] << " ";
	cout << endl << endl;

	cout << "Insert Vec2(3,5):" << endl;
	vec2.insert(3, 5);
	for (T i = 0; i < vec2.sizevec(); i++)
		cout << vec2[i] << " ";
	cout << endl << endl;

	cout << "Push Back Vec3:" << endl;
	vec3.push_back(4);
	for (T i = 0; i < vec3.sizevec(); i++)
		cout << vec3[i] << " ";
	cout << endl << endl;

	cout << "Contains Vec2(5):" << endl;
	cout << vec2.contains(5) << endl;
	cout << "Contains Vec2(4):" << endl;
	cout << vec2.contains(4) << endl << endl;

	cout << "Sum index 2 and 3 in Vec2:" << endl;
	cout << vec1[2] + vec1[3];
	cout << endl << endl;

	cout << "Find 5 in Vec2" << endl;
	cout << vec2.find(5);
	cout << endl << endl;

	cout << "Copy Vec2 to Vec1" << endl << "Vec1:" << endl;
	vec1 = vec2;
	for (T i = 0; i < vec1.sizevec(); i++)
		cout << vec1[i] << " ";

	return 0;
}