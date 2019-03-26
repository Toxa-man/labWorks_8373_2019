#include<iostream>
#include <memory.h>
using T = int;

using namespace std;

class Vector {
	T* data;
	unsigned Size;

public:
		Vector();						//дефолтный конструктор
		Vector(unsigned size_);			//создаёт массив размером size и заполняет его дефолтными значениями, т.е. T()
		Vector(unsigned size_, const T& val);	//создаёт массив размером size и заполняет его значением val
		unsigned size();				//возвращает размер массива
		void resize(unsigned size_);		//приравнивает размера массива к size; если новый размер больше старого - новые элементы заполнить нулями
		bool insert(unsigned pos, const T& val);	//вставляет val в позицию pos; возвращает true | false в зависимости от успеха операции
		void push_back(const T& val);	//добавляет val в конец массива
		bool contains(const T& val);	//возвращает true если val присуствует в массиве и false в противном случае
		T& operator[](unsigned index);	// обращение к элементу с индексом index. При этом должно быть возможно как читать значение, так и изменять его
		int find(const T& val);			//возвращает индекс первого вхождения val в массив или -1 в случае его отсутствия
		T* return_data();				//возвращает указатель на внутренний буфер
		Vector(const Vector&vec);		//copy-constructor
		Vector& operator=(const Vector&vec);	//assigment operator
		~Vector();						//destructor
};

Vector::Vector() {
	Size = 0;
	data = nullptr;
}

Vector::Vector(unsigned size_) {
	Size = size_;
	data = new T[size_];
	for (unsigned i = 0; i < Size; i++) {
		data[i] = T();
	}
}

Vector::Vector(unsigned size_, const T& val) {
	Size = size_;
	data = new T[Size];
	for (unsigned i = 0; i < Size; i++) {
		data[i] = val;
	}
}



unsigned Vector::size() {
	return Size;
}

void Vector::resize(unsigned newsize) {
	T* temp = new T[newsize];
	if (newsize > Size) {
		memcpy(temp, data, sizeof(T) * Size);
		for (unsigned i = Size; i < newsize; i++) {
			temp[i] = 0;
		}
		delete[]data;
	}
	else {
		memcpy(temp, data, sizeof(T) * newsize);
		delete[]data;
	}
	Size = newsize;
	data = temp;
}

bool Vector::insert(unsigned pos, const T& val) {
	if (pos <= Size) {
		resize(Size + 1);
		for (unsigned i = Size-1; i > pos; i--) {
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
	insert(Size, val);
}

bool Vector::contains(const T& val) {
	for (unsigned i = 0; i < Size; i++) {
		if (val == data[i]) {
			return true;
		}
	}
	return false;
}

T& Vector::operator[](unsigned index) {
	return data[index];
}

int Vector::find(const T& val) {
	for (unsigned i = 0; i < Size; i++) {
		if (val == data[i]) {
			return i;
		}
	}
	return -1;
}

T* Vector::return_data() {
	return data;
}

Vector::Vector(const Vector&vec) {
	Size =vec.Size;
	data = new T[Size];
	memcpy(data, vec.data, sizeof(T)*Size);
}

Vector& Vector::operator =(const Vector&vec) {
	if (this != &vec) {
		Size = vec.Size;
		delete[]data;
		data = new T[Size];
		memcpy(data, vec.data, sizeof(T)*Size);
		return *this;
	}
}

Vector::~Vector() {
	Size = 0;
	delete[]data;
}

int main() {
	Vector vector1(10);
	Vector vector2(5, 2);
	cout <<"vector1 size: "<< vector1.size() << endl;
	cout << "vector1 : ";
	for (unsigned i = 0; i < vector1.size(); i++) {
		cout << vector1[i] << ' ';
	}
	cout << endl << "vector2 size: " << vector2.size() << endl;
	cout << "vector2 : ";
	for (unsigned i = 0; i < vector2.size(); i++) {
		cout << vector2[i] << ' ';
	}
	vector2.resize(11);
	cout << endl <<"vector2 resize" << vector2.size() << endl;
	vector2.insert(4, 3);
	cout << "vector2 insert (4,3)" << endl;
	for (unsigned i = 0; i < vector2.size(); i++) {
		cout << vector2[i] << ' ';
	}
	vector2.push_back(7);
	cout << endl << "push_back 7 in vector2"<<endl;
	for (unsigned i = 0; i < vector2.size(); i++) {
		cout << vector2[i] << ' ';
	}
	cout << endl <<"contains(7): " << vector2.contains(7) << "  contains(100): " << vector2.contains(100) <<endl;
	cout << "find(2): " << vector2.find(2) << "  find(9): " << vector2.find(9) << endl;
	vector2[5] = 13;
	cout << "vector2[5] = "  << vector2[5] <<endl;
	cout << "data : " << vector2.return_data() << endl;
	vector1 = vector2;
	cout << "vector1 = vector2 and vector 1 now :" << endl;
	for (unsigned i = 0; i < vector1.size(); i++) {
		cout << vector1[i] << ' ';
	}
	system("pause");
}
