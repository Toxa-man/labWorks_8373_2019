#include "pch.h"
#include <iostream>
#include <algorithm>
#include <memory.h>

using T = int;

class vec {
	unsigned size;
	T* data;
public:
	vec();
	vec(unsigned size_);
	vec(unsigned size_, const T& val);
	vec(const vec& obj);
	~vec();

	vec& operator=(const vec obj);
	T& operator[](unsigned index);
	
	unsigned gsize();
	T* gdata();
	void resize(unsigned size_);
	bool insert(unsigned pos, const T& val);
	void push_back(const T& val);
	bool contains(const T& val);
	int find(const T & val);
	void print();
};

vec::vec() {
	size = 0;
	data = nullptr;
}

vec::vec(unsigned size_) {
	size = size_;
	data = new T[size];
	for (int i = 0; i < size; i++) {
		data[i] = i;
	}
}

vec::vec(unsigned size_, const T& val) {
	size = size_;
	data = new T[size];
	std::fill(data, data + size, val);
}

vec::vec(const vec& obj) {
	size = obj.size;
	data = new T[size];
	memcpy(data, obj.data, sizeof(T)*size);
}

vec::~vec() {
	size = 0;
	delete[]data;
}

vec& vec::operator=(const vec obj) {
	if (this != &obj) {
		size = obj.size;
		delete[]data;
		data = new T[size];
		memcpy(data, obj.data, sizeof(T)*size);
	}
	return *this;
}

T& vec::operator[](unsigned index) {
	return data[index];
}

unsigned vec::gsize() {
	return size;
}

T* vec::gdata() {
	return data;
}

void vec::resize(unsigned size_) {
	T* temp_data = new T[size];
	memcpy(temp_data, data, sizeof(T)*size);
	delete[]data;
	data = new T[size_];
	if (size_ <= size) {
		memcpy(data, temp_data, sizeof(T)*size_);
	}
	else {
		memcpy(data, temp_data, sizeof(T)*size);
		for (int i = size; i < size_; i++) {
			data[i] = 0;
		}
	}
	delete[]temp_data;
	size = size_;
}

bool vec::insert(unsigned pos, const T& val) {
	if (pos > size) {
		return false;
	}
	T* temp_data = new T[size];
	memcpy(temp_data, data, sizeof(T)*size);
	delete[]data;
	size++;
	data = new T[size];
	unsigned i(0);
	bool l(0);
	while (i < size) {
		if (i == pos) {
			data[i] = val;
			l++;
		}
		else {
			data[i] = temp_data[i - l];
		}
		i++;
	}
	delete[]temp_data;
}

void vec::push_back(const T& val) {
	insert(size, val);
}

bool vec::contains(const T& val) {
	for (int i = 0; i < size; i++) {
		if (data[i] == val) {
			return true;
		}
	}
	return false;
}

int vec::find(const T& val) {
	for (int i = 0; i < size; i++) {
		if (data[i] == val) {
			return i;
		}
	}
	return -1;
}

void vec::print() {
	for (int i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}

void foo(vec kek) {

}

int main()
{
	vec kek(5), kek1;
	kek = kek;
	kek[4] = 3;
	kek.resize(10);
	kek.resize(2);
	kek.insert(2, 1337);
	kek.push_back(1008);
	std::cout << kek.contains(4) << "\n";
	std::cout << kek.find(1337) << "\n";
	kek.print();
	system("pause");
}
