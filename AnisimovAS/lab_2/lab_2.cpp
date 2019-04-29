#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>

using namespace std;

const int HEAD[8] = {-119, 80, 78, 71, 13, 10, 26, 10};

int open_file(string file_name)
{
	ifstream checker;

	checker.open(file_name.c_str(), ios::in);

	if (!checker)
	{
		checker.close();
		return false;
	}
	else
	{
		checker.close();
		return true;
	}
}

bool check_png(string file_name)
{
	ifstream file; 
	int length; 
	int position = 8;

	cout << "Attempting to open " << file_name << endl;

	file.open(file_name, ios::binary);   
	
	length = file.rdbuf()->pubseekoff(0, ios_base::end);  
	
	file.rdbuf()->pubseekoff(0, ios_base::beg); 

	char *content = new char[length]; 

	file.read(content, length); 

	for (int i = 0; i < position; i++) 
	{
		if ((int)content[i] != HEAD[i]) 
		{			
			cout << "PNG signature ERROR" << endl;
			
			delete []content;
			return false;
		}
	}
	
	bool idat = false; 

	while (position < length) 
	{
		cout << "Position[" << position << "]\t";

		int length_of_block = 0;
		string name_of_block = "";
		string crc = "";

		for (int i = 0; i < 4; i++) 
		{
			length_of_block += abs((uint8_t)content[position + i]) * pow(16, 2 * (3 - i));
		}

		position += 4; 

		for (int i = 0; i < 4; i++) 
		{
			name_of_block += content[position + i];
		}

		if (position == 12) 
		{
			if (name_of_block != "IHDR")
			{
				cout << " IHDR ERROR" << endl;

				delete[]content;
				return false;
			}
		}

		if ((int)length_of_block + 8 > length - position) 
		{
			cout << " IEND ERROR" << endl;

			delete[]content;
			return false;
		}

		cout << " Name[" << name_of_block << "]\t";
		cout << " CRC[";
		for (int i = length_of_block + 4; i < length_of_block + 8; i++)
		{
			cout << dec << (int)content[position + i] << " ";
		}
		cout << "]" << endl;

		position += length_of_block + 8; 

		if (name_of_block == "IDAT") 
		{
			idat = true; 
		}		
	}
	
	if (idat == false)
	{
		cout << endl << "IDAT ERROR (not found)" << endl;
		
		file.close();
		delete[]content;
		return false;
	}
	
	file.close();
	delete[]content;
	return true;
}

int main()
{
		string filename;
		cout << "Enter path to file: ";
		cin >> filename;
		cout << endl;

		while (open_file(filename) != true)
		{
			cout << "Enter correct path to file: ";
			cin >> filename;
			cout << endl;
		}

		if (check_png(filename)==true)
		{
			cout << "File correct" << endl;
		}

	system("pause");
	return 0;
}