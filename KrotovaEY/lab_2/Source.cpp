#include <iostream>
#include <fstream> 
#include <string>
#include <conio.h>
#include <algorithm>
using namespace std;
class pro {
	ifstream png;
	static const int size_signature = 8, size_other = 4;
	int normal_signature[size_signature] = { 0x89, int('P'), int('N'), int('G'), 0x0D, 0x0A, 0x1A, 0x0A };
	int normal_name_of_IHDR[size_other] = { int('I'),int('H'),int('D'),int('R') };
	int normal_name_of_IDAT[size_other] = { int('I'),int('D'),int('A'),int('T') };
	int normal_name_of_IEND[size_other] = { int('I'),int('E'),int('N'),int('D') };
public:
	pro(string str);
	bool read_signature();
	int length(unsigned char*mas);
	bool read_IHDR();
	void read_CRC();
	int read_else();
	bool sravnenie(unsigned char*mas, int*mas2, int size);
	~pro();
};
	pro::pro(string str)
	{
		str = str + ".png";
		png.open(str, ios::binary);
	}
	bool pro::read_signature()
	{
		unsigned char mas[size_signature];
		png.read((char*)&mas, sizeof(mas));
		if (sravnenie(mas, normal_signature,size_signature))
		{
			cout << "signature is OK"<<endl;
			return true;
		}
		return false;
	}
	int pro::length(unsigned char*mas)
	{
		for (int i = 0; i < size_other / 2; ++i)
		{
			unsigned char t = mas[i];
			mas[i] = mas[size_other - 1 - i];
			mas[size_other - 1 - i] = t;
		}
		int*a = (int*)mas;
		return *a;
	}
	bool pro::read_IHDR()
	{
		unsigned char mas[size_other];
		png.read((char*)&mas, sizeof(mas));
		int length1 = length(mas);
		png.read((char*)&mas, sizeof(mas));
		if (sravnenie(mas, normal_name_of_IHDR, size_other))
		{

			png.seekg(length1+ size_other, ios::cur);
			cout << "IHDR OK"<<endl;
			return true;
		}
		return false;
	}
	void pro::read_CRC()
	{
		unsigned char mas[size_other];
		png.read((char*)&mas, sizeof(mas));
		for (int i = 0; i < size_other; ++i)
		{
			cout << hex<<int(mas[i]);
		}
	}
	int pro::read_else()
	{
		unsigned char mas[size_other];
		int i = png.tellg();
		png.read((char*)&mas, sizeof(mas));
		int length1 = length(mas);
		png.read((char*)&mas, sizeof(mas));
		if (sravnenie(mas, normal_name_of_IDAT, size_other))
		{
			png.seekg(length1, ios::cur);
			cout << "IDAT chunk founded at " <<dec<< i << "; Lenght:" << length1 << "; CRC:";
			read_CRC();
			cout << endl;
			return 1;
		}
		if (sravnenie(mas, normal_name_of_IEND, size_other))
		{
			return -1;
		}
		if (!png.eof())
		{
			png.seekg(length1 + size_other, ios::cur);
			read_else();
		}
		else {
			return 0;
		}
	}
	bool pro::sravnenie(unsigned char*mas, int*mas2,int size)
	{
		for (int i = 0; i < size; ++i)
		{
			if (mas[i] != mas2[i])
			{
				return false;
			}
		}
		return true;
	}
	pro::~pro()
	{
		png.close();
	}
int main()
{
	cout << "Enter file name:";
	string str;
	cin >> str;
	pro t(str);
	if (!t.read_signature())
	{
		cout << "signature is wrong"<<endl;
		_getch();
		return 0;
	}
	if (!t.read_IHDR())
	{
		cout << "IHDR wasn't found"<<endl;
		_getch();
		return 0;
	}
	int i = t.read_else();
	if (i == 1) 
	{
		i= t.read_else();
	}else
	{
		cout << "no IDAT founded";
		_getch();
		return 0;
	}
	while (i == 1)
	{
		i = t.read_else();
	}
	if (i==-1)
	{
		cout << "IEND founded" << endl << "File parsed successfully";
	}
	else
	{
		cout << "no IEND founded";
	}
	_getch();
	return 0;
}

