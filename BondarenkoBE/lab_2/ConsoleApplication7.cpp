#include "pch.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

const unsigned __int64 png_signature = 0x89504E470D0A1A0A;
const unsigned short chunk_name_size = 4;
const unsigned short chunk_size_size = 4;
const unsigned short chunk_CRC_32_size = 4;
const unsigned __int32 chunk_names[19] = {	*(__int32 *)"IHDR", *(__int32 *)"IEND", *(__int32 *)"IDAT", *(__int32 *)"PLTE",
											*(__int32 *)"bKGD", *(__int32 *)"cHRM", *(__int32 *)"gAMA", *(__int32 *)"hlST", 
											*(__int32 *)"iCCP", *(__int32 *)"iTXt", *(__int32 *)"pHYs", *(__int32 *)"sBIT", 
											*(__int32 *)"sPLT", *(__int32 *)"sRGB", *(__int32 *)"sTER", *(__int32 *)"tEXt", 
											*(__int32 *)"tIME", *(__int32 *)"tRNS", *(__int32 *)"zTXt"};

struct Chunk
{
	unsigned __int32 size = 0;
	char name[4] = { 0, 0, 0, 0 };
	char* information;
	unsigned __int32 CRC_32;
};

void read_chunk(std::ifstream &file, Chunk &chunk) {
	file.read((char*)&chunk.size, chunk_size_size);
	std::reverse((char*)&chunk.size, (char*)&chunk.size + chunk_size_size);
	file.read(chunk.name, chunk_name_size);
	delete[] chunk.information;
	chunk.information = new char[chunk.size];
	file.read(chunk.information, chunk.size);
	file.read((char*)&chunk.CRC_32, chunk_CRC_32_size);
	std::reverse((char*)&chunk.CRC_32, (char*)&chunk.CRC_32 + chunk_CRC_32_size);
}

int name_validate(char* name, bool &IDAT_existing) {
	if (*(__int32 *)name == chunk_names[0]) {
		std::cout << "Double IHDR fail!\n";
		return 3;
	}
	if (*(__int32 *)name == chunk_names[1]) {
		std::cout << "IEND was found!\n";
		if (IDAT_existing) {
			std::cout << "File parsed successfully!\n";
			return -1;
		}
		else {
			std::cout << "IDAT wasn't found!\n";
			return 5;
		}		
	}
	if (*(__int32 *)name == chunk_names[2]) {
		std::cout << name[0] << name[1] << name[2] << name[3] << " chunk found at ";
		IDAT_existing = true;
		return 0;
	}
	for (int i = 3; i < 19; ++i) {
		if (*(__int32 *)name == chunk_names[i]) {
			std::cout << name[0] << name[1] << name[2] << name[3] << " chunk found at ";
			return 0;
		}
	}
	std::cout << "Next chunk wasn't found (or wrong position)!\n";
	return 4;
}

int main()
{
	Chunk chunk;
	std::string path;
	std::cout << "Write path to test file: ";
	std::cin >> path;
	std::ifstream png_file(path, std::ios::binary);
	//Signature checking
	chunk.information = new char[sizeof(png_signature)];
	memset(chunk.information, 0, sizeof(png_signature));
	png_file.read(chunk.information, sizeof(png_signature));
	std::reverse(chunk.information, chunk.information + sizeof(png_signature));
	if (*((unsigned __int64 *)chunk.information) != png_signature) {
		std::cout << "Signature checking fail! Wrong signature\n";
		delete[] chunk.information;
		return 1;
	}
	else
		std::cout << "Signature checking done! Right PNG signature\n";
	//IHDR checking
	read_chunk(png_file, chunk);
	if (*(__int32 *)chunk.name != *(__int32 *)"IHDR") {
		std::cout << "IHDR finding fail!\n";
		delete[] chunk.information;
		return 2;
	}
	else
		std::cout << "IHDR was found!\n";
	//Other chunks
	int error_status = 0;
	unsigned __int32 previous_poz = png_file.tellg();
	bool IDAT_existing = false;
	while (true) {
		read_chunk(png_file, chunk);
		if (!(error_status = name_validate(chunk.name, IDAT_existing))) {
			std::cout << std::dec << previous_poz << "; Length: " << chunk.size << "; CRC: " << std::hex << "0x" << chunk.CRC_32 << "\n";
			previous_poz = png_file.tellg();
			continue;
		}
		else {
			delete[] chunk.information;
			return error_status;
		}
	}
}