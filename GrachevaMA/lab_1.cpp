#include <iostream>
#include <locale>

using namespace std;

class Vector
{
	using T = int;
public:
	Vector()
	{
		buffer = nullptr;
		razmer = 0;
	}
	Vector(size_t size)
	{
		buffer = new T[size];
		setmem(buffer, 0, size);
		razmer = size;
	}

	Vector(size_t size, const T& val)
	{
		buffer = new T[size];
		setmem(buffer, val, size);
		razmer = size;
	}


	size_t size()
	{
		return razmer;
	}

	void resize(size_t size) 
	{
		T* var = new T[size];
		if (size > razmer) {
			memcpy(var, buffer, sizeof(T)*size);
			for (unsigned i = razmer; i < size; i++)
			{
				var[i] = 0;
			}
		}
		else {
			memcpy(var, buffer, sizeof(T)*size);
		}

		buffer = var;
		razmer = size;
	}

	bool insert(size_t pos, const T& val)
	{
		if (pos > razmer - 1)
			return false;

		if (pos == 0)
		{
			T* buf = new T[++razmer];
			buf[0] = val;
			memcpy(buf + 1, buffer, (razmer - 1) * sizeof(T));
			delete[] buffer;
			buffer = buf;
			return true;
		}

		if (pos == razmer - 1)
		{
			T* buf = new T[++razmer];
			buf[razmer - 1] = val;
			memcpy(buf, buffer, (razmer - 1) * sizeof(T));
			delete[] buffer;
			buffer = buf;
			return true;
		}

		T* buf = new T[++razmer];
		buf[pos] = val;
		memcpy(buf, buffer, sizeof(T) * (pos));
		memcpy(buf + pos + 1, buffer + pos, (razmer - pos - 1) * sizeof(T));
		delete[] buffer;
		buffer = buf;
		return true; 
	}


	void push_back(const T& val)
	{
		insert(razmer - 1, val);
	}

	bool contains(const T& val)
	{
		for (size_t i = 0; i < razmer; i++)
			if (buffer[i] == val)
				return true;

		return false;
	}

	int find(const T& val)
	{
		for (size_t i = 0; i < razmer; i++)
			if (buffer[i] == val)
				return i;

		return -1;
	}



	T& operator[](size_t index) const
	{
		if (index >= razmer)
		{
			cout << "Индекс превышает размер вектора";
			exit(0);
		}
		return buffer[index];
	}


	T* data()
	{
		return buffer;
	}
private:
	T* buffer = nullptr;
	size_t razmer = 0;

	void setmem(T* data, const T& val, size_t size)
	{
		for (size_t i = 0; i < size; i++)
		{
			buffer[i] = val;
		}
	}
};

int main()
{

	setlocale(LC_ALL, "ru");
	unsigned size;
	cout << "Введите размер вектора ";
	cin >> size;
	Vector vector(size);
	cout << "Вектор: ";
	for (int i = 0; i < size; i++)
	{
		cout << vector[i] << " ";
	}
	cout << endl;

	int number;
	cout << "Введите число ";
	cin >> number;
	Vector vector1(size, number);
	cout << endl;
	cout << "Вектор:  ";
	for (int i = 0; i < size; i++)
	{
		cout << vector1[i] << " ";
	}
	cout << endl << "Размер " << vector1.size() << endl;
	int NewSize;
	cout << "Введите новый размер вектора ";
	cin >> NewSize;
	vector1.resize(NewSize);
	size = NewSize;
	cout << endl;
	cout << "Вектор: ";
	for (int i = 0; i < size; ++i)
		cout << vector1[i] << " ";
	cout << endl << "Размер:" << vector1.size() << endl;
	number = 0;
	int pos = 0;
	cout << "Введите число и позицию для вставки в вектор: ";
	cin >> number >> pos;
	if (vector1.insert(pos, number) == true)
	{
		size = size + 1;
		for (int i = 0; i < size; i++)
			cout << vector1[i] << " ";
	}
	
	cout << "Встака в конец вектора: ";
	vector1.push_back(number);
	size++;
	for (int i = 0; i < size; i++)
		cout << vector1[i] << " ";
	cout << endl;
	cout << "Вектор содержит число (0-нет,1-да):" << vector1.contains(number) << endl;
	cout << "Содержит число: ";
	int cont;
	cin >> cont;
	cout << "Вектор содержит " << cont << " и его индекс (-1 - нет числа):" << vector1.find(cont) << endl;
	cout << "Указатель на внутренний буфер:" << vector1.data() << endl;

	system("pause>nul");
}
