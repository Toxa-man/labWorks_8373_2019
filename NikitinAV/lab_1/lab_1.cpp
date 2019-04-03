#include <iostream>
#include <conio.h>
#include <memory.h>
using namespace std;
using T = int;
class Vector {
public:
	Vector();
	Vector(unsigned sizearg);
	Vector(unsigned sizearg, const T& val);
	Vector(const Vector&vector);
	unsigned vectorsize();
	void resize(unsigned customsize);
	bool insert(unsigned pos, const T& val);
	void push_back(const T& val);
	bool contains(const T&val);
	T find(const T&val);
	T* getData();
	~Vector();
	T& operator[](unsigned index);
	Vector&operator=(const Vector&vector);
private:
	T* data;
	unsigned size;
};
Vector::Vector() {
	size = 0;
	data = nullptr;
}
Vector::Vector(unsigned sizearg) {
size = sizearg;
data = new T [size];
for (unsigned i = 0; i < size; i++){
	data[i] = i;
}
}
Vector::Vector(unsigned sizearg, const T& val) {
	size = sizearg;
	 data = new T [size];
	for (unsigned i = 0; i < size; i++) {
		data[i] = val;
	}
}
unsigned Vector::vectorsize() {
	return size;
}
void Vector::resize(unsigned customsize) {
	T* temp;
	if (customsize <= size) {
		temp = new T [customsize];
		memcpy(temp, data, sizeof(T)*customsize);
		delete[] data;
		data = temp;
		size = customsize;
	}
	else {
		temp = new T[customsize];
		memcpy(temp, data, sizeof(T)*size);
		delete[] data;
		data = temp;
		for (unsigned i = size; i < customsize; i++) {
			data[i] = 0;
		}
		size = customsize;
	}
}
bool Vector::insert(unsigned pos,const T& val) {
	if (pos <= size) {
		resize(size + 1);	
		for (unsigned i = size-1; i >=pos; i--) {
			data[i] = data[i-1];
		}
		data[pos] = val;
		return true;
	}
	else {
		return false;
	}
}
void Vector::push_back(const T& val) {
	insert(size,val);
}
bool Vector::contains(const T&val) {
	for (unsigned i = 0; i < size; i++) {
		if (data[i] == val){
			return true;
		}
	}
	return false;
}
T Vector::find(const T&val) {
	for (unsigned i = 0; i < size; i++) {
		if (data[i] == val) {
			return i;
		}
}
	return -1;
}
T* Vector::getData() {
	return data;
}
Vector::~Vector() {
	delete[]data;
}
T& Vector::operator[](unsigned index) {
	return data[index];
}
Vector::Vector(const Vector&vector){
	size = vector.size;
	data = new T[vector.size];
	memcpy(data, vector.data, sizeof(T)*size);
	}
Vector&Vector::operator=(const Vector&vector) {
	if (this != &vector) {
		size = vector.size;
		delete[]data;
		data = new T[size];
		memcpy(data, vector.data, sizeof(T)*size);
	}
	return *this;
}
int main() {
	Vector vector1(5);
	Vector vector2(7, 9);
	cout << "Vector num 1\n";
	for (unsigned i = 0; i < vector1.vectorsize(); i++) {
		cout << vector1[i] << " ";
	}
	cout << "\nVector num 2\n";
	for (unsigned i = 0; i < vector2.vectorsize(); i++) {
		cout << vector2[i] << " ";
	}
	cout << "\nVector num 1s size is " << vector1.vectorsize();
	cout << endl << "Vector num 2s size is " << vector2.vectorsize() << endl;
	vector1.resize(6);
	cout << "Vector num 1 after resize(6)\n";
	for ( unsigned i = 0; i < vector1.vectorsize(); i++) {
		cout << vector1[i] << " ";
	}
	vector2.resize(5);
	cout << "\nVector num 2 after resize(5)\n";
	for (unsigned i = 0; i < vector2.vectorsize(); i++) {
		cout << vector2[i] << " ";
	}
	vector1.insert(5, 3);
	cout << "\nVector num 1 after insert(5,3)\n";
	for (unsigned i = 0; i < vector1.vectorsize(); i++) {
		cout << vector1[i] << " ";
	}
	vector2.insert(4, 2);
	cout << "\nVector num 2 after insert(4,2)\n";
	for (unsigned i = 0; i < vector2.vectorsize(); i++) {
		cout << vector2[i] << " ";
	}
	vector1.push_back(7);
	cout << "\nVector num 1 after push_back(7)\n";
	for (unsigned i = 0; i < vector1.vectorsize(); i++) {
		cout << vector1[i] << " ";
	}
	vector2.push_back(4);
	cout << "\nVector num 2 after push_back(4)\n";
	for (unsigned i = 0; i < vector2.vectorsize(); i++) {
		cout << vector2[i] << " ";
	}
	cout << "\nVector num 1 contains(8) check\n" << vector1.contains(8);
	cout<<"\nVector num 2 contains(9) check\n"<<vector2.contains(9);
	cout << "\nVector num 2 find(2) check\n" << vector2.find(2);
	cout << "\nVector num 1 operator[](5) check\n" << vector1.operator[](5);
	cout << "\nVector num 2 getData check\n" << vector2.getData();
	Vector a(3); // Copy-constructor check
	Vector b(a); // copy-constructor check
	Vector c(3);
	Vector d(5);
	c = d; // operator assigment check
	_getch();
}
