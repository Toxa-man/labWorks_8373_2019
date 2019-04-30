#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const char basic_signature[8] = { char(0x89), char(0x50), char(0x4E), char(0x47), char(0x0D), char(0x0A), char(0x1A), char(0x0A) };
const char basic_ihdr[4] = { char(0x49), char(0x48), char(0x44), char(0x52) };
const char basic_idat[4] = { char(0x49), char(0x44), char(0x41), char(0x54) };
const char basic_iend[4] = { char(0x49), char(0x45), char(0x4e), char(0x44) };
const int lenght_section = 4;
const int lenght_signature = 8;
int pos = 0;

class Png
{
	string path_file;
	ifstream fin;
	bool final = false;
public:
	Png();
	void set_path();
	void signature_check();
	void ihdr_check();
	void idat_iend_check();
	void crc_out(int pos);
	bool compare(char* first_arr, const char* second_arr);
	void reverse_for_lenght(char* arr, int size);
	~Png();
};

Png::Png()
{
	do
	{
		set_path();
		fin.open(path_file, ios::binary);
	} while (!fin.is_open());
	signature_check();
	if (final)
		ihdr_check();

	if (final)
		idat_iend_check();

	if (!final)
		cout << endl << "This png file is not valid" << endl;
	else
		cout << endl << "This png file is valid" << endl;
}

void Png::set_path()
{
	cout << "Please write the correct path of file" << endl;
	cin >> path_file;
}


Png::~Png()
{
	fin.close();
}

void Png::signature_check()
{
	char reading_signature[lenght_signature];
	fin.read((char*)&reading_signature, lenght_signature);
	if (compare(reading_signature, basic_signature))
	{
		cout << endl << "Signature is normal" << endl;
		final = true;
	}
	else
	{
		cout << endl << "Signature is wrong" << endl;
		final = false;
	}
}

void Png::ihdr_check()
{
	int lenght_ihdr;
	fin.read((char*)&lenght_ihdr, lenght_section);
	reverse_for_lenght((char*)&lenght_ihdr, lenght_section - 1);

	char reading_ihdr[lenght_section];
	fin.read((char*)&reading_ihdr, sizeof(reading_ihdr));

	if (compare(reading_ihdr, basic_ihdr))
	{
		cout << "IHDR is normal" << endl;
		final = true;
	}
	else
	{
		cout << "IHDR is wrong" << endl;
		final = false;
	}
	fin.seekg(lenght_ihdr + lenght_section, ios::cur);
}

void Png::idat_iend_check()
{ 
	bool iend = false;
	bool idat = false;
	do
	{
		pos = fin.tellg();
		int lenght_idat;
		fin.read((char*)&lenght_idat, lenght_section);
		reverse_for_lenght((char*)&lenght_idat, lenght_section - 1);

		char reading_idat[lenght_section];
		fin.read((char*)&reading_idat, lenght_section);

		if (compare(reading_idat, basic_idat))
		{
			idat = true;
			fin.seekg(lenght_idat, ios::cur);
			crc_out(pos);
		}

		if (compare(reading_idat, basic_iend))
		{
			cout << "IEND is founded" << endl;
			iend = true;
			final = true;
		}

		if (!idat)
		{
			fin.seekg(lenght_idat + lenght_section, ios::cur);
		}

	} while (!fin.eof() && !iend);

	if (!idat)
	{
		cout << "IDAT is not founded" << endl;
		final = false;
	}
	if (!iend)
	{
		cout << "IEND is not founded" << endl;
		final = false;
	}
}

void Png::crc_out(int pos)
{
	int crc;
	fin.read((char*)&crc, lenght_section);
	reverse_for_lenght((char*)&crc, lenght_section - 1);
	cout << "IDAT founded at " << dec << pos << "  CRC: ";
	cout << hex << crc << endl;
}

bool Png::compare(char* first_arr, const char* second_arr)
{
	for (int i = 0; i < sizeof(first_arr); i++)
	{
		if (first_arr[i] != second_arr[i])
			return false;
	}
	return true;
}

void Png::reverse_for_lenght(char* arr, int size)
{
	char val;
	for (int i = 0; i < size; i++)
	{
		val = arr[i];
		arr[i] = arr[size];
		arr[size] = val;
		size--;
	}
}

int main()
{
	Png png_check;
	
	system("pause");
	return 0;
}
