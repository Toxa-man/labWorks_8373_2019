#include<iostream>
#include <string>
#include <fstream>
using namespace std;
int signature[8] = { 137,80,78,71,13,10,26,10 };
int IHDR = (int)'IHDR';
int IDAT = (int)'IDAT';
int IEND = (int)'IEND';
int perevod_v_int(char(bytes[4]))
{
	unsigned char uch[4];
	for (int i = 0; i < 4; i++)
		uch[i] = bytes[i];
	unsigned int count = 0;
	for (int i = 0; i < 4; i++)
	{
		count |= uch[i];
		if (i != 3)
			count <<= 8;
	}
	return count;
}
bool signature_chek(ifstream&png, char bytes[8])
{
	png.read(bytes, 8);
	int size = 0;
	for (int i = 0; i < 8; i++) 
	{
		if (bytes[i] != (char)signature[i])
			return 0;
	}
	return 1;
}
bool IHDR_chek(ifstream&png, char bytes[4],int& size)
{
	int IHDR_chek;
	png.read(bytes, 4);
	size = perevod_v_int(bytes);
	png.read(bytes, 4);
	IHDR_chek = perevod_v_int(bytes);
	if (IHDR_chek!= IHDR)
		return 0;
	
	return 1;
}
void IDATandIEND_chek(ifstream&png, char bytes[4], int& size)
{
	unsigned char CRC[4];
	int index = 0;
	int place;
	unsigned int IDAT_chek = 0;
	png.seekg(size + 4, ios::cur);
    size = 0;
	bool iend = 0;
	int error = 0;
	unsigned int CRC2;
	{
			while (!png.eof() && iend == 0)
			{
				place = png.tellg();
				png.read(bytes, 4);
				size = perevod_v_int(bytes);
				png.read(bytes, 4);
				IDAT_chek = perevod_v_int(bytes);
				if (IDAT_chek == IDAT) 
				{
					error = 0;
				}
				else
				{
					error = 1;
					if (IDAT_chek == IEND)
						iend = 1;
				}

				png.seekg(size, ios::cur);
				png.read(bytes, 4);
				for (int i = 0; i < 4; i++)
				{
					CRC[i] = bytes[i];
				}
				if (error == 0)
				{
					index++;
					cout << "IDAT chunk founded at " << place << " Lenght " << size << " "<< "CRC: 0x";
					for (int i = 0; i < 4; i++)
						cout << hex << (int)CRC[i];
					cout << endl;
					cout.unsetf(ios::hex);
				}
				size = 0;
				IDAT_chek = 0;
			}
			if (iend == 1 && error == 1 && index != 0)
				cout << "IEND was found" << endl;
			if (error == 1 && index == 0)
				cout << "Wrong IDAT" << endl;
		}
		if (iend == 0)
		{
			cout << "IEND was not found";
		}
}
int main()
{
	char bytes[8];
	bool error = 0;
	cout << "Input path: ";
	string path;
	cin >> path;
    int size = 0;
	ifstream png("no_IDAT.png", ios::binary);
	if (signature_chek(png, bytes))
		cout << "Signature is GOOD" << endl;
	else
	{
		cout << "Wrong signature!" << endl;
		error = 1;
	}
	if (error == 0)
	{
			if (IHDR_chek(png, bytes, size))
				cout << "IHDR is GOOD" << endl;
			else
			{
				cout << "Something wrong with IHDR" << endl;
				error = 1;
			}
	}
	if (error == 0)
		IDATandIEND_chek(png, bytes, size);
	png.close();
    system("pause");
}