
#include "pch.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
unsigned char signature[] = { 137,80,78,71,13,10,26,10 };
unsigned char chunk_IHDR[] = { int('I'),int('H'),int('D'),int('R') };
unsigned char chunk_IDAT[] = { int('I'),int('D'),int('A'),int('T') };
unsigned char chunk_IEND[] = { int('I'),int('E'),int('N'),int('D') };
int pos = 8, size_IHDR=0, size_IDAT=0, CRC=0;


bool Check_name(ifstream& file,unsigned char* normal_name) {
	unsigned char arr[4];
	file.read((char*)&arr, sizeof(arr));
	for (int i = 0; i < 4; i++) {
		if (arr[i] == normal_name[i]) {
		}
		else {
			return 0;
		}
	}
	return 1;
}
int Lenght_of_chunk(unsigned char* arr) {
	cout << endl;
	for (int i = 0; i < 2; i++) {
		unsigned char temp = arr[i];
		arr[i] = arr[3 - i];
		arr[3 - i] = temp;
	}
	int*lenght_of_chunk = (int*)arr;
	return *lenght_of_chunk;
}
bool Signature(ifstream& file) {
	unsigned char arr[8];
	file.read((char*)&arr, sizeof(arr));
	for (int i = 0; i < pos; i++) {
		if (arr[i] == signature[i]) {
		}
		else {
			return 0;
		}
	}
	file.seekg(pos, file.beg);
	return 1;
}
bool IHDR(ifstream&file) {
	unsigned char arr[4];
	file.read((char*)&arr, sizeof(arr));
	size_IHDR=Lenght_of_chunk(arr);
	pos += 4;
	if (!Check_name(file, chunk_IHDR)) { return 0; };
	pos+=size_IHDR+4;
	file.seekg(pos, file.beg);
	return 1;
}

void IDAT(ifstream&file,int size_of_file) {
	pos += 4; 
	file.seekg(pos, file.beg);
	cout << size_of_file;
	while (pos<=size_of_file-4) {
		if (!Check_name(file, chunk_IDAT)) {
			pos++;
			file.seekg(pos, file.beg);
		}
		else {
			pos -=4;
			file.seekg(pos, file.beg);
			unsigned char arr[4];
			file.read((char*)&arr, sizeof(arr));
			cout << "IDAT chunk founded at " << pos;
			size_IDAT = Lenght_of_chunk(arr);
			cout << "	Lenght of chunk:" << size_IDAT;
			pos += 8 + size_IDAT;
			file.seekg(pos, file.beg);
			file.read((char*)&arr, sizeof(arr));
			cout <<hex<< "	CRC:";
			for (int i = 0; i < sizeof(arr); ++i)
			{
				cout << int(arr[i]);
			}
			cout <<dec<< endl;
			pos += 4;
			file.seekg(pos, file.beg);
		}
	}
}
bool IEND(ifstream&file) {
	file.seekg(-8, file.end);
	if (!Check_name(file, chunk_IEND)) {
		return 0;
	}
	return 1;
}


int main()
{
	cout << "Input path: ";
	string str;
	cin >> str;
	ifstream file;
	file.open(str+".png", ios::binary);
	file.seekg(0, file.end);
	int size_of_file = file.tellg();
	file.seekg(0, file.beg);
	
	if (!Signature(file)) {
		cout << "Signature is NOT OK";
		return 0;
	}
	else { 
		cout << "Signature is OK";
	}
	cout << endl;
	if (!IHDR(file)) {
		cout << "IHDR wasn't founded ";
		return 0;
	}
	else { cout << "IHDR founded"<<endl;
	};
	
	IDAT(file,size_of_file);
	cout << endl;
	if (!IEND(file)) {
		cout << "IEND wasn't founded ";
		return 0;
	}
	else {
		cout << "IEND founded";
	};
	cout <<endl<< "File parsed successfully";
	file.close();
	return 0;
}
