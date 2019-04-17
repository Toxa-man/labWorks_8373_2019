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
	Vector(int size);
	Vector(int size, const T& val);
	Vector(const Vector& vec);
	Vector& operator = (const Vector&vec);
	T& operator [] (unsigned index);
	unsigned sizevec();
	void resize(unsigned size);
	bool insert(unsigned pos, const T& val);
	void push_back(const T& val);
	bool contains(const T& val);
	int find(const T& val);
	T* getdata();
	~Vector();
};

Vector::Vector()
{
	size = 0;
	data = nullptr;
}

Vector::Vector(int size_)
{
	size = size_;
	data = new T[size];
	for (unsigned i = 0; i < size; i++)
	{
		data[i] = i;
	}
}

Vector::Vector(int size_, const T&val)
{
	size = size_;
	data = new T[size];
	for (unsigned i = 0; i < size; i++)
	{
		data[i] = val;
	}
}

Vector::Vector(const Vector&vec)
{
	size = vec.size;
	data = new T[size];
	memcpy(data, vec.data, sizeof(T)*size);
}

Vector& Vector::operator = (const Vector&vec)
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

unsigned Vector::sizevec()
{
	return size;
}

T& Vector::operator[](unsigned index)
{
	return data[index];
}

void Vector::resize(unsigned size_)
{
	T* buff_data = new T[size_];
	if (size_ >= size)
	{
		memcpy(buff_data, data, sizeof(T)*size);
		for (unsigned i = size; i < size_; i++)
		{
			buff_data[i] = 0;
		}
	}
	else
	{
		memcpy(buff_data, data, sizeof(T)*size_);
	}
	delete[]data;
	data = buff_data;
	size = size_;
}

bool Vector::insert(unsigned pos, const T& val)
{
	if (pos <= size)
	{
		resize(size + 1);
		for (unsigned i = pos; i < size - 1; i++)
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
	insert(size, val);
}

bool Vector::contains(const T& val)
{
	for (unsigned i = 0; i < size; i++)
	{
		if (data[i] == val)
			return true;
	}
	return false;
}

int Vector::find(const T& val)
{
	for (unsigned i = 0; i < size; i++)
	{
		if (data[i] == val)
			return i;
	}
	return -1;
}

T* Vector::getdata()
{
	return data;
}

Vector::~Vector()
{
	size = 0;
	delete[]data;
}

int main()
{
	Vector vec1(5), vec2(6, 2), vec3(7, 3);
	cout << "Vec1:" << endl;
	for (unsigned i = 0; i < vec1.sizevec(); i++)
	cout << vec1[i] << " ";
	cout << endl << endl;

	cout << "Vec2:" << endl;
	for (unsigned i = 0; i < vec2.sizevec(); i++)
	cout << vec2[i] << " ";

	cout << endl << endl;
	cout << "Vec3:" << endl;
	for (unsigned i = 0; i < vec3.sizevec(); i++)
	cout << vec3[i] << " ";
	cout << endl << endl;

	cout << "Resize Vec1(9):" << endl;
	vec1.resize(9);
	for (unsigned i = 0; i < vec1.sizevec(); i++)
	cout << vec1[i] << " ";
	cout << endl << endl;

	cout << "Insert Vec2(3,5):" << endl;
	vec2.insert(3, 5);
	for (unsigned i = 0; i < vec2.sizevec(); i++)
	cout << vec2[i] << " ";
	cout << endl << endl;

	cout << "Push Back Vec3(4):" << endl;
	vec3.push_back(4);
	for (unsigned i = 0; i < vec3.sizevec(); i++)
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
	for (unsigned i = 0; i < vec1.sizevec(); i++)
	cout << vec1[i] << " ";

	cout << endl << endl;
	cout << "vec4" << endl;
	Vector vec4(6);
	vec4.resize(4);
	for (unsigned i = 0; i < vec4.sizevec(); i++)
		cout << vec4[i];
	cout << endl << endl;
	

	system("pause");
	return 0;
}
