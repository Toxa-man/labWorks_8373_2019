#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
using namespace std;

const long long unsigned png_sign = 0x89504E470D0A1A0A;
const unsigned	png_ihdr = 0x49484452;
const unsigned	idat_name = 0x49444154;
const unsigned iend_name = 0x49454E44;
const unsigned sign_size = 8;
const unsigned ihdr_len = 13;
const unsigned chunk_size = 4;

void reverse(char* start, char* end) {
	while (start < end) {
		swap(*start++, *end--);
	}
}

bool sign_ch(ifstream& img) {
	long unsigned long our_img;
	img.read((char*)& our_img, sign_size);
	reverse((char*)& our_img, (char*)& our_img + sign_size - 1);
	if (our_img == png_sign) {
		return true;
	}
	else {
		return false;
	}
}

bool ihdr_ch(ifstream& img) {
	unsigned png_ihdr, png_ihdr_len;
	img.read((char*)&png_ihdr_len, chunk_size);
	reverse((char*)& png_ihdr_len, (char*)& png_ihdr_len + chunk_size - 1);
	if (png_ihdr_len != ihdr_len) {
		return false;
	}
	img.read((char*)& png_ihdr, chunk_size);
	reverse((char*)& png_ihdr, (char*)& png_ihdr + chunk_size - 1);
	if (png_ihdr != png_ihdr) {
		return false;
	}
	unsigned pos = img.tellg();
	img.seekg(pos + ihdr_len + chunk_size);
	return true;
}

bool ot_chunks(ifstream& img, bool& idat_is) {
	unsigned len, name = 0, our_crc;
	unsigned long long pos, file_size;
	pos = img.tellg();
	img.seekg(0, ios::end);
	file_size = img.tellg();
	img.seekg(pos);
	while (pos < file_size) {
		img.read((char*)& len, chunk_size);
		reverse((char*)& len, (char*)& len + chunk_size - 1);
		img.read((char*)& name, chunk_size);
		reverse((char*)& name, (char*)& name + chunk_size - 1);
		pos = img.tellg();
		if (name == idat_name) {
			idat_is = true;
			cout << "IDAT chunk is " << dec << pos - 2 * chunk_size << endl;
			cout << "His length: " << len << "," << endl;
			img.seekg(pos + len);
			img.read((char*)& our_crc, chunk_size);
			reverse((char*)& our_crc, (char*)& our_crc + chunk_size - 1);
			cout << "CRC: " << our_crc << endl;
			cout << "--------------------" << endl;
		}
		else if (name == iend_name) {
			if (len != 0) {
				return false;
			}
			if (pos != file_size - chunk_size) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			img.seekg(pos + len + chunk_size);
		}
	}
	return false;
}

int main()
{
	int count_err = 0;

	ifstream in("C:\\Users\\jterl\\Desktop\\normal_file.png", ios::binary);

	bool idat_is = false;
	if (sign_ch(in)) {
		cout << "Signature is okay" << endl;
	}
	else {
		cout << "Signature is NOT okay" << endl;
		count_err = 1;
	}
	if (count_err != 1) {
		if (ihdr_ch(in)) {
			cout << "IHDR is okay" << endl;
		}
		else {
			cout << "IHDR is NOT okay" << endl;
			count_err = 1;
		}
		if (count_err != 1) {
			cout << "--------------------" << endl;
			if (ot_chunks(in, idat_is)) {
				if (idat_is) {
					cout << "IEND is okay" << endl;
					cout << "File is GOOD" << endl;
				}
				else {
					cout << "IDAT is NOT find" << endl;
				}
			}
			else {
				cout << "IEND is NOT okay";
			}
		}
	}

	return 0;
}