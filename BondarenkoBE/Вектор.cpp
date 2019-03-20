#include "pch.h"
#include <iostream>
#include <string>
using T = int;

class Vector{
	public:
		Vector(unsigned size, const T& val);
		unsigned size();
		void resize(unsigned size);
		bool insert(unsigned pos, const T& val);
		void push_back(const T& val);
		bool contains(const T& val);
		T& operator [](unsigned index);
		int find(const T& val);
		T* data();
		Vector(const Vector&vec);
		Vector& operator =(const Vector&vec);
		~Vector();
	private:
		T* Data = nullptr;
		unsigned Size = 0;
};

Vector::Vector(unsigned size = 1, const T& val = 0) {
	Data = new T[size];
	Size = size;
	for (unsigned i = 0; i < Size; ++i)
		Data[i] = val;
}

unsigned Vector::size() {
	return Size;
}

void Vector::resize(unsigned size) {
	T* Buf_Data = new T[size];
	if (size > Size) {
		memcpy(Buf_Data, Data, Size * sizeof(T));
		for (unsigned i = Size; i < size; ++i)
			Buf_Data[i] = 0;
	}
	else memcpy(Buf_Data, Data, size * sizeof(T));
	delete []Data;
	Data = Buf_Data;
	Size = size;
}

bool Vector::insert(unsigned pos, const T& val) {
	resize(Size + 1);
	memmove(Data + pos + 1, Data + pos, (Size - pos - 1) * sizeof(T));
	Data[pos] = val;
	if (Data[pos] == val)
		return true; 
	else
		return false;
}

void Vector::push_back(const T& val) {
	resize(Size + 1);
	Data[Size - 1] = val;
}

bool Vector::contains(const T& val) {
	for (unsigned i = 0; i < Size; ++i)
		if (Data[i] == val) return true;
	return false;
}

T& Vector::operator [](unsigned index) {
	return Data[index];
}

int Vector::find(const T& val) {
	for (unsigned i = 0; i < Size; ++i)
		if (Data[i] == val) return i;
	return -1;
}

T* Vector::data() {
	return Data;
}

Vector::Vector(const Vector&vec) {
	Size = vec.Size;
	delete []Data;
	Data = new T[Size];
	memcpy(Data, vec.Data, sizeof(T)*Size);
}

Vector& Vector::operator =(const Vector&vec) {
	if (this != &vec) {
		Size = vec.Size;
		delete[]Data;
		Data = new T[Size];
		memcpy(Data, vec.Data, sizeof(T)*Size);
	}
	return *this;
}

Vector::~Vector() {
	Size = 0;
	delete []Data;
}

int main()
{
	Vector vec_1;
	Vector vec_2(5);
	Vector vec_3(10,5);
	std::cout << "First vector size: " << vec_1.size() << std::endl;
	for (unsigned i = 0; i < vec_1.size(); ++i)
		std::cout << vec_1[i] << ' ';
	std::cout << std::endl;
	std::cout << "Second vector size: " << vec_2.size() << std::endl;
	for (unsigned i = 0; i < vec_2.size(); ++i)
		std::cout << vec_2[i] << ' ';
	std::cout << std::endl;
	std::cout << "Third vector size: " << vec_3.size() << std::endl;
	for (unsigned i = 0; i < vec_3.size(); ++i)
		std::cout << vec_3[i] << ' ';
	std::cout << std::endl;
	vec_2[3] = 5;
	std::cout << "Second vector after fourth element value changing: ";
	for (unsigned i = 0; i < vec_2.size(); ++i)
		std::cout << vec_2[i] << ' ';
	std::cout << std::endl;
	vec_2.resize(10);
	std::cout << "Second vector size after resize to 10: " << vec_2.size() << std::endl;
	for (unsigned i = 0; i < vec_2.size(); ++i)
		std::cout << vec_2[i] << ' ';
	std::cout << std::endl;
	vec_2.resize(3);
	std::cout << "Second vector size after resize to 3: " << vec_2.size() << std::endl;
	for (unsigned i = 0; i < vec_2.size(); ++i)
		std::cout << vec_2[i] << ' ';
	std::cout << std::endl;
	if (vec_3.insert(7, 7))
		std::cout << "Inserting complete succesfully!" << std::endl;
	else
		std::cout << "Bl*n" << std::endl;
	std::cout << "Third vector size after insert 7 in position with index 7: " << vec_3.size() << std::endl;
	for (unsigned i = 0; i < vec_3.size(); ++i)
		std::cout << vec_3[i] << ' ';
	std::cout << std::endl;
	vec_3.push_back(7);
	std::cout << "Third vector size after insert 7 in last position: " << vec_3.size() << std::endl;
	for (unsigned i = 0; i < vec_3.size(); ++i)
		std::cout << vec_3[i] << ' ';
	std::cout << std::endl;
	std::cout << "Is there 8 is third array?: " << vec_3.contains(8) << std::endl;
	std::cout << "Is there 7 is third array?: " << vec_3.contains(7) << std::endl;
	std::cout << "What position has first 7?: " << vec_3.find(7) << std::endl;
	std::cout << "What adress in hash has third vector?: " << vec_3.data() << std::endl;
	Vector vec_new(vec_3);
	vec_2 = vec_3;
	std::cout << "Copy constructor and assigment operator check (using third vec). Sizes of vectors: " << vec_new.size() << " and " << vec_2.size() << std::endl;
	for (unsigned i = 0; i < vec_new.size(); ++i)
		std::cout << vec_new[i] << ' ';
	std::cout << std::endl;
	for (unsigned i = 0; i < vec_2.size(); ++i)
		std::cout << vec_2[i] << ' ';
	std::cout << std::endl;
}