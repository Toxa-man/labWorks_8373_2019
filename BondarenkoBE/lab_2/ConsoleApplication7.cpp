#include "pch.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

const uint64_t png_signature = 0x89504E470D0A1A0A;
const unsigned short chunk_name_size = 4;
const unsigned short chunk_size_size = 4;
const unsigned short chunk_CRC_32_size = 4;
const uint32_t chunk_names[19] = {	*(uint32_t *)"IHDR", *(uint32_t *)"IEND", *(uint32_t *)"IDAT", *(uint32_t *)"PLTE",
									*(uint32_t *)"bKGD", *(uint32_t *)"cHRM", *(uint32_t *)"gAMA", *(uint32_t *)"hlST",
									*(uint32_t *)"iCCP", *(uint32_t *)"iTXt", *(uint32_t *)"pHYs", *(uint32_t *)"sBIT",
									*(uint32_t *)"sPLT", *(uint32_t *)"sRGB", *(uint32_t *)"sTER", *(uint32_t *)"tEXt",
									*(uint32_t *)"tIME", *(uint32_t *)"tRNS", *(uint32_t *)"zTXt"};

struct Chunk
{
	uint32_t size = 0;
	char name[4] = { 0, 0, 0, 0 };
	char* information;
	uint32_t CRC_32;
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
	if (*(uint32_t *)name == chunk_names[0]) {
		std::cout << "Double IHDR fail!\n";
		return 3;
	}
	if (*(uint32_t *)name == chunk_names[1]) {
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
	if (*(uint32_t *)name == chunk_names[2]) {
		std::cout << name[0] << name[1] << name[2] << name[3] << " chunk found at ";
		IDAT_existing = true;
		return 0;
	}
	for (int i = 3; i < 19; ++i) {
		if (*(uint32_t *)name == chunk_names[i]) {
			std::cout << name[0] << name[1] << name[2] << name[3] << " chunk found at ";
			return 0;
		}
	}
	std::cout << "Next chunk wasn't found (or wrong position)!\n";
	return 4;
}

int main(int argc, char* argv[])
{
	Chunk chunk;
	std::string path;
	if (argc == 1) {
		path = "test.png";
		std::cout << "Write path to test file: ";
		std::cin >> path;
	}
	else 
		path = argv[1];
	std::ifstream png_file(path, std::ios::binary);
	//Signature checking
	chunk.information = new char[sizeof(png_signature)];
	memset(chunk.information, 0, sizeof(png_signature));
	png_file.read(chunk.information, sizeof(png_signature));
	std::reverse(chunk.information, chunk.information + sizeof(png_signature));
	if (*((uint64_t *)chunk.information) != png_signature) {
		std::cout << "Signature checking fail! Wrong signature\n";
		delete[] chunk.information;
		return 1;
	}
	else
		std::cout << "Signature checking done! Right PNG signature\n";
	//IHDR checking
	read_chunk(png_file, chunk);
	if (*(uint32_t *)chunk.name != *(uint32_t *)"IHDR") {
		std::cout << "IHDR finding fail!\n";
		delete[] chunk.information;
		return 2;
	}
	else
		std::cout << "IHDR was found!\n";
	//Other chunks
	int error_status = 0;
	uint32_t previous_poz = png_file.tellg();
	bool IDAT_existing = false;
	while (true) {
		read_chunk(png_file, chunk);
		if (!(error_status = name_validate(chunk.name, IDAT_existing))) {
			std::cout << std::dec << previous_poz << "; Length: " << chunk.size << "; CRC: " << std::hex << "0x" << chunk.CRC_32 << "\n";
			previous_poz = png_file.tellg();
		}
		else {
			delete[] chunk.information;
			return error_status;
		}
	}
}