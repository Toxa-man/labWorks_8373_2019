#include "pch.h"
#include <iostream>
#include<fstream>
#include<iostream>
#include<conio.h>
#include<string>
#include<string.h>
using namespace std;

const unsigned long long normal_signature = 0x89504E470D0A1A0A;
const int crc_size = 4;
const int len_size = 4;
const int name_size = 4;
const int sign_size = 8;


enum chunks {
	IHDR, IDAT, IEND, OTHER
};


struct chunk{
	chunks type = OTHER;
	unsigned length;
	char name[5] = { 0, 0, 0, 0 };
	unsigned crc;

};

struct png_file {
	bool idat = false;
	bool iend = false;
};

bool valid_signature(ifstream &file) {
	
	unsigned long long recieved_signature;
	file.read((char*)&recieved_signature, sign_size);
	reverse((char*)&recieved_signature, (char*)&recieved_signature + sign_size);
	if (recieved_signature == normal_signature) {
		return true;
	}
	else {
		return false;
	}
	
}

chunk read_chunk(ifstream &file, int Size) {
	chunk Momental_Chunk;
	file.read((char*)&Momental_Chunk.length, len_size);
	reverse((char*)&Momental_Chunk.length, (char*)&Momental_Chunk.length + len_size);

	file.read(Momental_Chunk.name, name_size);
	if (strcmp(Momental_Chunk.name, "IHDR") == 0) {
		Momental_Chunk.type = IHDR;
	}
	else if (strcmp(Momental_Chunk.name, "IDAT") == 0) {
		Momental_Chunk.type = IDAT;
	}
	else if (strcmp(Momental_Chunk.name, "IEND") == 0) {
		Momental_Chunk.type = IEND;
	}
	int pos = file.tellg();
	file.seekg(pos + Momental_Chunk.length);
	file.read((char*)&Momental_Chunk.crc, crc_size);
	reverse((char*)&Momental_Chunk.crc, (char*)&Momental_Chunk.crc + crc_size);

	return Momental_Chunk;
}

bool find_ihdr(ifstream &file, chunk& Momental_Chunk, png_file &input, int size){
	Momental_Chunk = read_chunk(file, size);
	if (Momental_Chunk.type == IHDR) {
		return true;
	}
	else {
		return false;
	}
}

int file_len(ifstream& file)
{
	int size = 0;
	file.seekg(0, std::ios::end);
	size = file.tellg();
	file.seekg(0, std::ios::beg);
	return size;
}
int main()
{
	cout << "write path to file" << endl;

	string path;
	cin >> path;
	ifstream file(path, ios::binary);

	while (!file) {
		cout << "wrong path, try again:  " << endl;
		cin >> path;
		file.open(path, ios::binary);
	}

	int size = file_len(file);
	png_file input;
	chunk Momental_Chunk;
	if (valid_signature(file)) {
		cout << "Signature is ok  " << endl;
	}
	else {
		cout << "Wrong signature  " << endl;
		_getch();
		return 0;
	}
	if (find_ihdr(file, Momental_Chunk, input, size)) {
		cout << "IHDR is ok" << endl;
	}
	else {
		cout << "Wrong IHDR" << endl;
		_getch();
		return 0;
	}
	int pos = file.tellg();
	while (pos < size && pos > 0)  {
		Momental_Chunk = read_chunk(file, size);
		pos = file.tellg();
		if (Momental_Chunk.type == IDAT) {
			input.idat = true;
			cout << "IDAT found ,  " << "position:  " << dec << pos - Momental_Chunk.length - 12 << ",  Length: " << Momental_Chunk.length;
			cout << ", crc:   " << hex <<  Momental_Chunk.crc << endl;

		}
		else if (Momental_Chunk.type == IEND) {
			input.iend = true;
			cout << "IEND found" << endl;
			pos = file.tellg();
			if (pos == size) {
				break;
			}
			else {
				cout << "Bad position" << endl;
				return 0;
			}
		}
		pos = file.tellg();
	}
	if (input.idat && input.iend) { cout << "Successfully parsed! "; }
	else if (!input.idat) { cout << "No idat found"; }
	else if (!input.iend) { cout << "No iend found or bad position"; }
	
	_getch();
}
