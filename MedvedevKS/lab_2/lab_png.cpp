#include "pch.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
using namespace std;

enum issue {
	all_right,
	wrong_signature,
	wrong_ihdr,
	wrong_idat,
	wrong_iend
};

void reverse(char* start, char* end) {
	while (start < end) {
		swap(*start++, *end--);
	}
}

issue signature_check(ifstream& in) {
	long unsigned long recivedSignature;
	const long long unsigned pngSignature = 0x89504E470D0A1A0A;
	const unsigned signatureSize = 8/*bytes*/;
	in.read((char*)& recivedSignature, signatureSize);
	reverse((char*)& recivedSignature, (char*)& recivedSignature + signatureSize - 1);
	if (recivedSignature == pngSignature) {
		return all_right;
	}
	else {
		return wrong_signature;
	}
}

issue IHDR_check(ifstream& in) {
	const unsigned	IHDR_name = 0x49484452,
					IHDR_length = 13/*bytes*/,
					chunkSectionSize = 4/*bytes*/;
	unsigned recivedName, recivedLength;
	in.read((char*)&recivedLength, chunkSectionSize);
	reverse((char*)& recivedLength, (char*)& recivedLength + chunkSectionSize - 1);
	if (recivedLength != IHDR_length) {
		return wrong_ihdr;
	}
	in.read((char*)& recivedName, chunkSectionSize);
	reverse((char*)& recivedName, (char*)& recivedName + chunkSectionSize - 1);
	if (recivedName != IHDR_name) {
		return wrong_ihdr;
	}
	unsigned pos = in.tellg();
	in.seekg(pos + IHDR_length + chunkSectionSize);
	return all_right;
}

issue otherChuncks_check(ifstream& in, bool& IDAT_founded) {
	const unsigned	IDAT_name = 0x49444154,
					IEND_name = 0x49454E44,
					IEND_length = 0,
					chunkSectionSize = 4/*bytes*/;
	unsigned recivedLength, recivedName = 0, recivedCRC;
	unsigned long long pos, fileSize;
	pos = in.tellg();
	in.seekg(0, ios::end);
	fileSize = in.tellg();
	in.seekg(pos);
	while (pos < fileSize) {
		in.read((char*)& recivedLength, chunkSectionSize);
		reverse((char*)& recivedLength, (char*)& recivedLength + chunkSectionSize - 1);
		in.read((char*)& recivedName, chunkSectionSize);
		reverse((char*)& recivedName, (char*)& recivedName + chunkSectionSize - 1);
		pos = in.tellg();
		switch (recivedName) {
		case(IDAT_name):
			IDAT_founded = true;
			cout << "IDAT chunk founded at " << dec << pos - 2 * chunkSectionSize << "; Length: " << recivedLength << ";";
			in.seekg(pos + recivedLength);
			in.read((char*)& recivedCRC, chunkSectionSize);
			reverse((char*)& recivedCRC, (char*)& recivedCRC + chunkSectionSize - 1);
			cout << " CRC: " << hex << showbase << recivedCRC << endl;
			break;

		case(IEND_name):
			if (recivedLength != 0) {
				return wrong_iend;
			}
			if (pos != fileSize - chunkSectionSize) {
				return wrong_iend;
			}
			else {
				return all_right;
			}
			break;

		default:		
			in.seekg(pos + recivedLength + chunkSectionSize);
		}
	}
	return wrong_iend;
}

int main()
{
	bool IDAT_founded = false;

	ifstream in("C:\\Users\\demur\\Desktop\\build\\img\\normal_file.png", ios::binary);

	if (signature_check(in)) {
		cout << "Signature is wrong\n";
		_getch();
		return wrong_signature;
	}
	else {
		cout << "Signature is OK\n";
	}

	if (IHDR_check(in)) {
		cout << "Wrong IHDR\n";
		_getch();
		return wrong_ihdr;
	}
	else {
		cout << "IHDR is OK\n";
	}

	if (otherChuncks_check(in, IDAT_founded)) {
		cout << "No IEND founded or bad position\n";
		_getch();
		return wrong_iend;
	}
	else {
		if (IDAT_founded) {
			cout << "IEND founded\n" << "File parsed successfully\n";
		}
		else {
			cout << "No IDAT founded\n";
			_getch();
			return wrong_idat;
		}
	}
	_getch();
}
