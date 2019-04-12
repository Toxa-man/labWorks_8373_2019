#include <iostream>
#include <memory.h>
using namespace std;
using T = int;

class vector {
public:
	vector();
	vector(unsigned Size_);
	vector(unsigned Size_, const T&val);
	unsigned size();
	void resize(unsigned Size_);
	bool insert(unsigned pos, const T&val);
	void push_back(const T&val);
	bool contains(const T&val);
	T& operator [](unsigned index);
	int find(const T&val);
	T* get_data();
	vector& operator =(const vector&vec);
	~vector();
	vector(const vector&vec);
private:
	T*data;
	unsigned Size;
};

vector::vector() {
	Size = 0;
	data = nullptr;
}

vector::vector(unsigned Size_) {
	Size = Size_;
	data = new T[Size];
	for (unsigned i = 0; i < Size; ++i) {
		data[i] = T();
	}
}

vector::vector(unsigned Size_, const T&val) {
	Size = Size_;
	data = new T[Size];
	for (unsigned i = 0; i < Size; ++i) {
		data[i] = val;
	}
}

unsigned vector::size() {
	return Size;
}

void vector::resize(unsigned Size_) {
	T*buffer = data;
	data = new T[Size_];
	if (Size_ > Size) {
		memcpy(data, buffer, sizeof(T)*Size);
		for (int i = Size; i < Size_; ++i) {
			data[i] = 0;
		}
	}
	else {
		memcpy(data, buffer, sizeof(T)*Size_);
	}
	delete[]buffer;
	Size = Size_;
}

bool vector::insert(unsigned pos, const T&val) {
	if (pos <= size()) {
		resize(size() + 1);
		for (int i = pos; i < size(); ++i) {
			data[i] = data[i - 1];
		}
		data[pos] = val;
		return true;
	}
	else {
		return false;

	}
}

void vector::push_back(const T&val) {
	resize(size() + 1);
	data[size() - 1] = val;
}

bool vector::contains(const T&val) {
	for (unsigned i = 0; i < Size; ++i) {
		if (val == data[i]) {
			return true;
		}
	}
	return false;
}

T& vector::operator [](unsigned index) {
	return data[index];
}

int vector::find(const T&val) {
	for (unsigned i = 0; i < Size; ++i) {
		if (val == data[i]) {
			return i;
		}
	}
	return -1;
}

T* vector::get_data() {
	return data;
}

vector& vector::operator =(const vector&vec) {
	if (this != &vec) {
		Size = vec.Size;
		delete[]data;
		data = new T[Size];
		memcpy(data, vec.data, sizeof(T)*Size);
	}
	return *this;
}

vector::~vector() {
	Size = 0;
	delete[]data;
}

vector::vector(const vector&vec) {
	Size = vec.Size;
	data = new T[Size];
	memcpy(data, vec.data, sizeof(T)*Size);
}

int main() {
	setlocale(0, "");
	unsigned size;
	cout << "Введите размер вектора: ";
	cin >> size;
	vector vec1(size);
	cout << "Вектор: ";
	for (int i = 0; i < size; ++i)
	{
		cout << vec1[i] << " ";
	}
	T number;
	cout << endl << "Введите число: ";
	cin >> number;
	vector vec2(size, number);
	cout << "Получившийся вектор: ";
	for (int i = 0; i < size; ++i)
	{
		cout << vec2[i] << " ";
	}
	cout << endl << "Его размер: " << vec2.size() << endl;
	vec1 = vec2;
	unsigned size2;
	cout << "Введите новый размер вектора: ";
	cin >> size2;
	vec1.resize(size2);
	size = size2;
	cout << "Вектор: ";
	for (int i = 0; i < size2; ++i)
	{
		cout << vec1[i] << " ";
	}
	cout << endl << "Размер: " << vec1.size() << endl;
	T num1, num2, num3, num4;
	cout << "Вставим число в вектор, введите число: ";
	cin >> num1;
	vec1.insert(3, num1);
	for (int i = 0; i < vec1.size(); ++i)
		cout << vec1[i] << " ";
	cout << endl;
	cout << "Размер вектора: " << vec1.size() << endl;
	cout << "Вставим число в конец вектора, введите число: ";
	cin >> num2;
	vec1.push_back(num2);
	for (int i = 0; i < vec1.size(); ++i)
		cout << vec1[i] << " ";
	cout << endl;
	cout << "Размер вектора: " << vec1.size() << endl;
	cout << "Найдем число (введите число): ";
	cin >> num3;
	cout << "Вектор содержит число " << num3 << "? (0 - нет, 1 - да): " << vec1.contains(num3) << endl;
	cout << "Найдем число (введите число) и его индекс: ";
	cin >> num4;
	cout << "Число " << num4 << " и его индекс ('-1' - нет в векторе): " << vec1.find(num4) << endl;
	cout << "Указатель на внутренний вектор:" << vec1.get_data() << endl;
	return 0;
}