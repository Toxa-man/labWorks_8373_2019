#include<iostream>
#include<fstream>
using namespace std;
int signature[8] = { 137,80,78,71,13,10,26,10 };
int IHDR = (int)'IHDR';
int IDAT = (int)'IDAT';
int IEND = (int)'IEND';

int to_Int(char bit[4])
{
	unsigned int counter = 0;
	for (int i = 0; i <4; i++)
	{
		counter |= (unsigned char)bit[i];
		if (i != 3)
			counter <<= 8;
	}
	return counter;
}
bool signatur(ifstream&png, char bit[8])
{
	png.read(bit, 8);
	for (int i = 0; i < 8; i++)
	{
		if ((unsigned char)bit[i] != signature[i])
			return false;
	}
	return true;
}

bool IHDR_CHEK(ifstream&png, char bit[4], int& size)
{
	unsigned int IHDR_ch = 0;
	png.read(bit, 4);
	size = to_Int(bit);
	png.read(bit, 4);
	IHDR_ch = to_Int(bit);
	if (IHDR_ch == IHDR)
		return true;
	else
		return false;
}
bool IEND_CHEK(ifstream&png, char bit[4], int& size)
{
	unsigned int IEND_ch = 0;
	IEND_ch = to_Int(bit);
	if (IEND_ch == IEND)
		return true;
	else
		return false;
}
void  IDAT_CHEK(ifstream&png, char bit[4], int& size)
{
	unsigned int IDAT_ch = 0;
	unsigned char CRC[4] = {};
	int position = 0;
	int buf = 0;
	int iend = 0;
	int check = 0;
	png.seekg(size + 4, ios::cur);
	while (!png.eof() && iend == 0)
	{
		position = png.tellg();
		png.read(bit, 4);
		size = to_Int(bit);
		png.read(bit, 4);
		IDAT_ch = to_Int(bit);
		if (IDAT_ch == IDAT)
			buf = 0;
		else
		{
			buf = 1;
			if (IEND_CHEK(png, bit, size)==1)
				iend = 1;
		}
		png.seekg(size, ios::cur);
		png.read(bit, 4);
		for (int i = 0; i < 4; i++)
		{
			CRC[i] = bit[i];
		}
		if (buf == 0) {
			check++;
			cout << "IDAT chunk founded at " << position << "; Lenght:" << size << "; CRC: 0x";
			for (int i = 0; i < 4; i++)
			{
				cout <<hex<< ( int )CRC[i];
			}
			cout << endl;
			cout.unsetf(ios::hex);
		}
	}
	
	if ((buf == 1) && (check == 0))
	{
		cout << "IDAT no founded" << endl;
	}
	if (iend==0)
	{
		cout << "IEND no founded" << endl;
		
	}
	else
	{
		cout << "IEND founded" << endl;
	}
	

}

void final(ifstream&png, char bit[8], int& size)
{
	if (signatur(png, bit)) {
		cout << "Signature is OK" << endl;

		if (IHDR_CHEK(png, bit, size)) {
			cout << "IHDR  is OK" << endl;
			IDAT_CHEK(png, bit, size);
		}

		else
			cout << "IHDR wasn't found" << endl;
	}
	else
		cout << "Signature is wrong " << endl;

}
int main()
{
	char bit[8] = {};
	int size = 0;
	cout << "normal_file:" << endl;
	ifstream png("normal_file.png", ios::binary);
	final(png, bit, size);
	cout << endl;
	png.close();
	system("pause");
}
