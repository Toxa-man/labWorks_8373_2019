#include <iostream>

using namespace std;
using T = int;
class Vector 
{ 
unsigned sizeofarr;
	
public:
	int *arr;
	Vector();

	Vector(unsigned size)
	{
		sizeofarr = size;
		arr = new T[size];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = T();
		}
		for (int i = 0; i < size; ++i)
		{
			cout<< arr[i]<<" ";
		}
		cout << endl << endl;
	}


	Vector(unsigned size, const T & val)
	{
		sizeofarr = size;
		arr = new T[size];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = val;
		}
		for (int i = 0; i < size; ++i)
		{
			cout << arr[i] << " ";
		}
		cout << endl << endl;
	}

	unsigned Size()
	{
		return sizeofarr;
	}


	void Resize(unsigned newsize) 
	{
		T *helparr;
		if (newsize > sizeofarr)
		{
			helparr = new T[newsize];
			memcpy(helparr, arr, sizeof(int)*sizeofarr);
			delete[]arr;
			arr = new T[newsize];
			memcpy(arr, helparr, sizeof(int)*newsize);
			for (int i = sizeofarr; i < newsize; ++i)
			{
				arr[i] = 0;
			}
			delete[] helparr;
			sizeofarr = newsize;
		}
		else 
		{
			helparr = new T[sizeofarr];
			memcpy(helparr, arr, sizeof(int)*sizeofarr);
			delete[]arr;
			arr = new T[newsize];
			memcpy(arr,helparr, sizeof(int)*newsize);
			delete[] helparr;
			sizeofarr = newsize;
		}
	}

	bool Insert(unsigned pos, const T & val)
	{

		if ((pos < sizeofarr) || (pos = sizeofarr))
		{
			Resize(sizeofarr + 1);
			for (int i = pos; i < sizeofarr-1; i++)
			{
				arr[i+1] = arr[i];
			}
			arr[pos] = val;
			return true;
		}
		else 
		{
			return false;
		}
	}

	void push_back(const T & val) 
	{
			Insert(sizeofarr, val);
	}

	bool contains(const T & val)
	{
		for (int i=0;i<sizeofarr;++i) 
		{
			if (arr[i]==val) 
			{
				return true;
			}
		}
		return false;
	}

	T operator[](unsigned index) 
	{
		return arr[index];
	}

	int find(const T & val)
	{
		for (int i=0;i<sizeofarr;++i) 
		{
			if (arr[i] == val)
			{
				return i+1;
			}
		}
		return -1;
	}

	T* data()
	{
		return arr;
	}

	Vector(const Vector& vec)
	{
		sizeofarr = vec.sizeofarr;
		arr = new T[sizeofarr];
		memcpy(arr, vec.arr, sizeof(int)*sizeofarr);
	}

	Vector &operator =(const Vector& vec)
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

	~Vector()
	{
		delete[] arr;
	}
};

void foo()
{

	cout << "First array: ";
	Vector first(10);
	cout << "Second array: ";
	Vector second(5, 3);
	cout << "Size of first array: " << first.Size() << endl << endl;
	cout << "Size of second array: " << second.Size() << endl << endl;
	first.Resize(7);
	second.Resize(7);
	cout <<"Resized first array:";
	for (unsigned i = 0; i < first.Size(); ++i)
	{
		cout << first.arr[i]<<" ";
	}
	cout << endl << endl;
	cout << "Resized second array:";
	for (unsigned i = 0; i < second.Size(); ++i)
	{
		cout << second.arr[i] << " ";
	}
	cout << endl << endl;
	first.Insert(6, 11);
	cout << "Insert: ";
	for (unsigned i = 0; i < first.Size(); ++i)
	{
		cout << first.arr[i]<<" ";
	}
	cout << endl << endl;
	first.push_back(8);
	cout << "Pushback: ";
	for (int i = 0; i < first.Size(); ++i)
	{
		cout << first.arr[i] << " ";
	}
	cout << endl << endl;

	if (first.contains(9))
	{
		cout << "it is true! First contains val " << endl;
	}
	else
	{
		cout << "it is false! First do not contain val "<<endl<<endl;
	}

	cout<<"Element of array:  "<<first.operator[](6)<<endl<<endl;

	cout<<"index of chosen element:  "<<first.find(11)<<endl<<endl;

	cout <<"Pointer to buffer: "<<first.data() << endl<<endl;
}

int main() 
{
	foo(); 
	system("pause");
	return 0;
}

