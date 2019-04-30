#include "pch.h"
#include<iostream>
#include <string>
#include <fstream>
using namespace std;
int Turning_from_mass_to_number(char*buffer)
{
	unsigned int Num = 0;
	for (int i = 0; i < 4; i++)
	{
		Num = Num | (unsigned char)buffer[i];
		if (i != 3)
			Num = Num << 8;
	}
	return Num;
}
bool signature_test(ifstream&file, char*buffer)
{
	int signature[8] = { 137,80,78,71,13,10,26,10 };
	file.read(buffer, 8);
	for (int i = 0; i < 8; i++)
	{
		if (buffer[i] != (char)signature[i])
		{
			return false;
		}
		return true;
	}
}
bool IHDR_test(ifstream&file, char*buffer, int&size)
{
	int normal_IHDR[4] = { int('I'),int('H'),int('D'),int('R') };
	file.read(buffer, 4);
	size = Turning_from_mass_to_number(buffer);
	file.read(buffer, 4);
	file.seekg(size, ios::cur);
	for (int i = 0; i < 4; ++i)
	{
		if (buffer[i] !=(char)normal_IHDR[i])
		{
			return false;
		}
	}
	return true;
}
bool IEND_test(ifstream&file, char*buffer)
{
	int normal_IEND[4] = { int('I'),int('E'),int('N'),int('D') };
	for (int i = 0; i < 4; ++i)
	{
		if (buffer[i] != (char)normal_IEND[i])
		{
			return false;
		}
	}
	return true;
}
void IDAT_test(ifstream&file, char*buffer, int&size)
{
	 int normal_IDAT[4] = { int('I'),int('D'),int('A'),int('T') };
	 bool IEND = 0;
	 int count = 0;
	 int ierror = 0;
	 int place;
	 file.read(buffer, 4);
	 while (!file.eof() && IEND == 0)
	 {
		 place = file.tellg(); 
		 file.read(buffer, 4);
		 size = Turning_from_mass_to_number(buffer);
		 file.read(buffer, 4);
		  for (int i = 0; i < 4; ++i)
			 {
				 if (buffer[i] == (char)normal_IDAT[i])
				 {
					 ierror = 0;
				 }
				 else
				 {
					 ierror = 1;
					 break;
				 }
			 }
		 if (ierror == 1)
		 {
			 IEND = IEND_test(file, buffer);
		 }
		 file.seekg(size, ios::cur);
		 file.read(buffer, 4);
		 
		 if (ierror == 0)
		 {
			 count++;
			 cout << "IDAT был найде: " << place << " Lenght " << size << " " << "CRC: 0x";
			 for (int i = 0; i < 4; i++)
			 {
				 printf("%x", (unsigned char)buffer[i]);
			 }
			 cout << endl;
		 }
		 size = 0;
	 }
	if(ierror == 1 )
	{
		if(count != 0)
		{ 
			if (IEND == 1 )
			{
			 cout << "IEND был найден" << endl;
			}
			else
			{
				cout << "IEND не был обнаружен";
			}
		}
		else if (count == 0)
		{ 
			cout << "не парвильные IDAT" << endl;
		}
	}
}
int main()
{
	setlocale(LC_ALL, "ru");
	int size = 0;
	int ierror = 0;
	char buffer[8] = {};
	int error = 0;
	cout << "Введите название файла, только название(без расширения): ";
	string name = "text";
	cin >> name;
	ifstream file;
	name = name + ".png";
	file.open (name, ios::binary);
	if (signature_test(file, buffer))
	{
		cout<<"signature в порядке" << endl;
	}
	else
	{
		cout << "Ошибка: неправильная signature!" << endl;
		error = 1;
	}
	if (error == 0)
	{
		if (IHDR_test(file, buffer, size))
		{
			cout << "IHDR в порядке!" << endl;
		}
		else
		{
			cout << "Ошибка IHDR " << endl;
			error = 1;
		}
	}
	if (error == 0)
	{
		IDAT_test(file, buffer, size);
	}
		file.close();
	system("pause");
}