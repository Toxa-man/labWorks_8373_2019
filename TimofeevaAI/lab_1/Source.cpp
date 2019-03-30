#include <iostream>
#include <memory.h>
#include <algorithm>

using namespace std;
using T = int;
class Vector 
{ 
unsigned sizeofarr;
T*arr;
public:
	Vector();
	Vector(unsigned size);
	Vector(unsigned size, const T & val);
	unsigned Size();
	void Resize(unsigned newsize);
	bool Insert(unsigned pos, const T & val);
	void push_back(const T & val);
	bool contains(const T & val);
    T& operator[](unsigned index);
	int find(const T & val);
	T* data();
	Vector(const Vector& vec);
	Vector &operator =(const Vector& vec);
	~Vector();
};

Vector::Vector()
{
	sizeofarr = 0;
	arr = nullptr;
}

Vector::Vector(unsigned size)
{
	sizeofarr = size;
	arr = new T[size];
	for (unsigned i = 0; i < size; ++i)
	{
		arr[i] = T();
	}
}

Vector::Vector(unsigned size, const T & val)
{
	sizeofarr = size;
	arr = new T[size];
	for (unsigned i = 0; i < size; ++i)
	{
		arr[i] = val;
	}
}

unsigned Vector::Size()
{
	return sizeofarr;
}

void Vector::Resize(unsigned newsize)
{
	T *helparr = arr;
	arr = new T[newsize];
	if (newsize > sizeofarr)
	{
		memcpy(arr, helparr, sizeof(T)*sizeofarr);
		for (unsigned i = sizeofarr; i < newsize; i++)
		{
			arr[i] = 0;
		}
	}
	else
	{
		memcpy(arr, helparr, sizeof(T)*newsize);
	}
	delete[]helparr;
	sizeofarr = newsize;
}

bool Vector::Insert(unsigned pos, const T & val)
{

	if (pos <= sizeofarr) 
	{
		Resize(sizeofarr + 1);
		for (unsigned i = sizeofarr-1; i > pos; --i)
		{
			arr[i] = arr[i-1];
		}
		arr[pos] = val;
		return true;
	}
	else
	{
		return false;
	}
}

void Vector::push_back(const T & val)
{
	Insert(sizeofarr, val);
}

bool Vector::contains(const T & val)
{
	for (unsigned i = 0; i < sizeofarr; ++i)
	{
		if (arr[i] == val)
		{
			return true;
		}
	}
	return false;
}

T& Vector::operator[](unsigned index)
{
	return arr[index];
}

int Vector::find(const T & val)
{
	for (unsigned i = 0; i < sizeofarr; ++i)
	{
		if (arr[i] == val)
		{
			return i;
		}
	}
	return -1;
}

T* Vector::data()
{
	return arr;
}

Vector::Vector(const Vector& vec)
{
	sizeofarr = vec.sizeofarr;
	arr = new T[sizeofarr];
	memcpy(arr, vec.arr, sizeof(T)*sizeofarr);
}

Vector & Vector::operator =(const Vector& vec)
{
	if (this != &vec)
	{
		sizeofarr = vec.sizeofarr;
		delete[]arr;
		arr = new T[sizeofarr];
		memcpy(arr, vec.arr, sizeof(T)*sizeofarr);
	}
	return *this;
}

Vector:: ~Vector()
{ 
	sizeofarr = 0;
	delete[] arr;
}

int main() //I made two different vectors to show two different cases at the same time
{
	unsigned size1,size2,index,forindex;
	int number,forinsert, forpushback, forcontains, forfind;
	
	cout <<"Enter size of vector1:"<<endl;
    cin >> size1;
	cout << "Enter size of vector2 (for example less than size1)" << endl;
	cin >> size2;
	cout <<"Enter number for vector2: "<<endl;
	cin >>number;
	cout << "First array: ";
	Vector first(size1);
	for (unsigned i = 0; i < size1; ++i)
	{
		cout << first[i] << " ";
	}
	cout << endl << endl;
	cout << "Second array: ";
	Vector second(size2, number);
	for (unsigned i = 0; i < size2; ++i)
	{
		cout << second[i] << " ";
	}
	cout << endl << endl;
	int forresize = ((first.Size() + second.Size()) / 2);
	first.Resize(forresize);
	second.Resize(forresize);
	cout << "Resized first array:";
	for (unsigned i = 0; i < first.Size(); ++i)
	{
		cout << first[i] << " ";
	}
	cout << endl << endl;
	cout << "Resized second array:";
	for (unsigned i = 0; i < second.Size(); ++i)
	{
		cout << second[i] << " ";
	}

	cout << endl << endl<<"Enter index for insert: "<<endl;
	cin >> index;
	cout << "Enter number for insert: " << endl;
	cin >> forinsert;
	first.Insert(index, forinsert);
	cout << "Insert: ";
	for (unsigned i = 0; i < first.Size(); ++i)
	{
		cout << first[i] << " ";
	}
	cout << endl << endl;
	
	cout << "Enter number for pushback: " << endl;
	cin >> forpushback;
	first.push_back(forpushback);
	cout << "Pushback: ";
	for (unsigned i = 0; i < first.Size(); i++)
	{
		cout << first[i] << " ";
	}
	cout << endl << endl;
	
	cout << "Enter number checked for contain: " << endl;
	cin >> forcontains;
	if (first.contains(forcontains))
	{
		cout << "it is true! First contains val " << endl;
	}
	else
	{
		cout << "it is false! First do not contain val " << endl << endl;
	}

	cout << "Enter index for operator function: "<<endl;
	cin >> forindex;
	cout << "Element found by index:  " << first.operator[](forindex) << endl << endl;
	
	cout << "Enter number for finding: " << endl;
	cin >> forfind;
	cout << "index of chosen element:  " << first.find(forfind) << endl << endl;
	
	cout << "Pointer to buffer: " << first.data() << endl << endl;

	system("pause");
	return 0;
}