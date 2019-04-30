#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream file;
bool Compare(unsigned char*arr1, int*arr2, int size);
void ReadCRC();
bool CheckSignature(int*normarr);
bool CheckIHDR(int*normarr);
int CheckOther(int*normIDAT, int*normIEND);
int Length(unsigned char*arr);
const int signaturesize = 8, chunksize = 4;

int main()
{
	int normsignature[signaturesize] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
	int normIHDR[chunksize] = { 0x49, 0x48, 0x44, 0x52 };
	int normIDAT[chunksize] = { 0x49, 0x44, 0x41, 0x54 };
	int normIEND[chunksize] = { 0x49, 0x45, 0x4E, 0x44 };
	cout << "Enter the file name:";
	string name;
	cin >> name;
	cout << endl;
	file.open(name + ".png", ios::binary);

	if (CheckSignature(normsignature))
	{
		cout << "Right signature" << endl<<endl;
	}
	else
	{
		cout << "Wrong signature" << endl;
		system("pause");
		return 0;
	}

	if (!CheckIHDR(normIHDR))
	{
		cout << "Wrong IHDR" << endl;
		system("pause");
		return 0;
	}
	else
	{
		cout << "Right IHDR" << endl<<endl;
	}

	int result = CheckOther(normIDAT, normIEND);

	if (result == 1)
	{
		result = CheckOther(normIDAT, normIEND);
	}
	else 
	{
		cout << "No IDAT"<<endl;
        system("pause");
		return 0;
	}

	while (result == 1)
	{
	   result = CheckOther(normIDAT, normIEND);
	}

	if (result == -1)
	{
		cout << "We found IEND! File parsed successfully!" << endl << endl;	
		system("pause");
		return 0;
	}
	else 
	{
		cout << "Wrong IEND" << endl<<endl;
	}
	system("pause");
	return 0;
}

bool CheckSignature(int*normarr)
{
	unsigned char ourpng[signaturesize];
	file.read((char*)&ourpng, sizeof(ourpng));
	for (int i = 0; i < signaturesize; i++)
	{
		if (ourpng[i] != normarr[i])
			return false;
	}
	return true;
}

bool Compare(unsigned char*arr1, int*arr2, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			return false;
		}
	}
	return true;
}

void ReadCRC()
{
	int k=0;
	unsigned char arr[chunksize];
	file.read((char*)&arr, sizeof(arr));
	for (int i = 0; i < chunksize; i++)
	{
		k=+(int)arr[i];
	}
    cout << hex<<showbase<<k << endl;
}

int Length(unsigned char*arr)
{
	for (int i = 0; i < chunksize / 2; ++i)
	{
		unsigned char t = arr[i];
		arr[i] = arr[chunksize - 1 - i];
		arr[chunksize - 1 - i] = t;
	}
	int*a = (int*)arr;
	return *a;
}

bool CheckIHDR(int*normarr)
{
	unsigned char ourpng[chunksize];
	file.read((char*)&ourpng, sizeof(ourpng));
	int length =Length(ourpng);
	file.read((char*)&ourpng, sizeof(ourpng));
	for (int i = 0; i < chunksize; i++)
	{
		if (ourpng[i] != normarr[i])
		{
			return false;
		}
	}
	file.seekg(length + chunksize, ios::cur);
	return 1;
}

int CheckOther(int*normIDAT, int*normIEND)
{
	unsigned char ourpng[chunksize];
	int pos = file.tellg();
	file.read((char*)&ourpng, sizeof(ourpng));
	int length = Length(ourpng);
	file.read((char*)&ourpng, sizeof(ourpng));

	if (Compare(ourpng, normIDAT, chunksize))
	{	
		file.seekg(length, ios::cur);
		cout << "Position of IDAT: " << dec << pos << "  Lenght: " << length << "  CRC: ";ReadCRC();
		cout << endl;
		return 1;
	}
	
	if (Compare(ourpng, normIEND, chunksize))
	{
		return -1;
	}

	if (!file.eof())		
	{
		file.seekg(length + chunksize, ios::cur);	
		CheckOther(normIDAT,normIEND);
	}
	else	
	{
		return 0;
	}
}
	
	