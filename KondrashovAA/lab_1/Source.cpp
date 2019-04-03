#include <iostream>

using namespace std;

template<typename T>
class Vector {
public:
	Vector(); 
	Vector(unsigned size); 
	Vector(unsigned size, const T& val); 
	Vector(const Vector<T>& vec); 
	unsigned size() const; 
	void resize(unsigned size); 
	bool insert(unsigned pos, const T& val); 
	void push_back(const T& val); 
	bool contains(const T& val) const; 
	T& operator [](unsigned index); 
	int find(const T& val) const; 
	T* data() const; 
	Vector<T> operator =(const Vector<T>& vec); 
	~Vector();
private:
	unsigned Size;
	T* Data;
};

template<typename T>
Vector<T>::Vector() : Size(0), Data(nullptr) {}

template<typename T>
Vector<T>::Vector(unsigned size) : Size(size) {
	Data = new T[Size]();
}

template<typename T>
Vector<T>::Vector(unsigned size, const T& val) : Size(size) {
	Data = new T[Size];
	for (unsigned i = 0; i < Size; i++) {
		Data[i] = val;
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T>& vec) : Size(vec.size()) {
	if (Size) {
		Data = new T[Size];
		for (unsigned i = 0; i < Size; i++) {
			Data[i] = vec.data()[i];
		}
	}
	else {
		Data = nullptr;
	}
}

template<typename T>
unsigned Vector<T>::size() const {
	return Size;
}

template<typename T>
void Vector<T>::resize(unsigned size) {
	if (size) {
		T* temp = new T[size];
		for (unsigned i = 0; i < size; i++) {
			if (i < Size) {
				temp[i] = Data[i];
			}
			else {
				temp[i] = T();
			}
		}
		delete[] Data;
		Data = temp;
	}
	else {
		delete[] Data;
		Data = nullptr;
	}
	Size = size;
}

template<typename T>
bool Vector<T>::insert(unsigned pos, const T& val) {
	if (pos > Size) {
		return false;
	}
	else {
		this->resize(Size + 1);
		for (unsigned i = 0; i < Size - pos - 1; i++) {
			Data[Size - i - 1] = Data[Size - i - 2];
		}
		Data[pos] = val;
		return true;
	}
}

template<typename T>
void Vector<T>::push_back(const T& val) {
	this->resize(Size + 1);
	Data[Size - 1] = val;
}

template<typename T>
bool Vector<T>::contains(const T& val) const {
	for (unsigned i = 0; i < Size; i++) {
		if (Data[i] == val) {
			return true;
		}
	}
	return false;
}

template<typename T>
T& Vector<T>::operator [](unsigned index) {
	return Data[index];
}

template<typename T>
int Vector<T>::find(const T& val) const {
	for (int i = 0; i < Size; i++) {
		if (Data[i] == val) {
			return i;
		}
	}
	return -1;
}

template<typename T>
T* Vector<T>::data() const {
	return Data;
}

template<typename T>
Vector<T> Vector<T>::operator =(const Vector<T>& vec) {
	if (Data != vec.data()) {
		Size = vec.size();
		delete[] Data;
		Data = new T[Size];
		for (int i = 0; i < Size; i++) {
			Data[i] = vec.data()[i];
		}
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector() {
	delete[] Data;
}

void print_vec(Vector<int>& vec) {
	cout << "Size: " << vec.size() << endl 
		<< "Data: ";
	if (vec.data()) {
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i] << " ";
		}
	}
	else {
		cout << "empty array";
	}
	cout << endl;
}

int main() {
	cout << "Default constructor" << endl;
	Vector<int> vec1;
	print_vec(vec1);

	cout << "One argument constructor" << endl;
	Vector<int> vec2(3);
	print_vec(vec2);

	cout << "Two arguments constructor" << endl;
	Vector<int> vec3(4, 2);
	print_vec(vec3);

	cout << "Copy constructor:" << endl;
	Vector<int> vec4 = vec3;
	print_vec(vec4);

	cout << "Assigment operator" << endl;
	vec4 = Vector<int>(5, 5);
	print_vec(vec4);

	cout << "resize" << endl;
	vec4.resize(8);
	print_vec(vec4);

	cout << "insert" << endl;
	if (vec4.insert(3, 3)) {
		print_vec(vec4);
	}
	else {
		cout << "error" << endl;
	}

	cout << "push_back" << endl;
	vec4.push_back(2);
	print_vec(vec4);

	cout << "contains 5" << endl;
	cout << vec4.contains(5) << endl;

	cout << "contains 9" << endl;
	cout << vec4.contains(9) << endl;

	cout << "find 3" << endl;
	cout << vec4.find(3) << endl;

	cout << "find 9" << endl;
	cout << vec4.find(9) << endl;

	cin.get();
	return 0;
}