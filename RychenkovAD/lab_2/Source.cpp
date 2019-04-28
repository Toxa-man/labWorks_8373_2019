#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const long long valid_signature = 0x89504E470D0A1A0A;
const int chunk_block_size = 4;
const int chunk_name_size = 4;
const int CRC_size = 4;

void check_signature(ifstream &png, long long &signature)
{
	png.read((char*)& signature, sizeof(valid_signature));
	reverse((char*)& signature, (char*)& signature + sizeof(valid_signature));
}


void check_ihdr(ifstream &png, char Chunk_Name[], int &Chunk_length, int &CRC)
{
	png.read((char*)& Chunk_length, chunk_block_size);
	reverse((char*)& Chunk_length, (char*)& Chunk_length + chunk_block_size);
	png.read(Chunk_Name, chunk_name_size);
	Chunk_Name[4] = '\0';
	int pos = png.tellg();
	png.seekg(Chunk_length + chunk_block_size + pos);
}

void check_other_chunk(ifstream &png, char Chunk_Name[], int &Chunk_length, int &CRC, int &Content)
{
	png.read((char*)& Chunk_length, chunk_block_size);
	reverse((char*)& Chunk_length, (char*)& Chunk_length + chunk_block_size);
	png.read(Chunk_Name, chunk_name_size);
	Chunk_Name[4] = '\0';
	int pos = png.tellg();
	png.seekg(Chunk_length + pos);
	png.read((char*)& CRC, CRC_size);
	reverse((char*)& CRC, (char*)& CRC + CRC_size);
	png.seekg(Chunk_length + chunk_block_size + pos);
}

int main()
{
	string path;
	cin >> path;
	ifstream png;
	png.exceptions(ifstream::badbit | ifstream::failbit);
	bool no_idat = true;
	bool no_iend = true;

	try
	{
		png.open(path, ios::binary);

		long long signature;
		char Chunk_Name[chunk_name_size + 1];
		int Chunk_length;
		int Content;
		int CRC;

		check_signature(png, signature);
		if (signature != valid_signature)
		{
			throw exception("Signature is wrong");
		}
		cout << "Signature is OK" << endl;

		check_ihdr(png, Chunk_Name, Chunk_length, CRC);
		string Chunk_name_string(Chunk_Name);
		if (Chunk_name_string != "IHDR")
		{
			throw exception("IHDR is wrong");
		}
		cout << "IHDR is OK" << endl;
		
		while ((!(png.eof())) && (Chunk_name_string != "IEND"))
		{
			int pos = png.tellg();
			check_other_chunk(png, Chunk_Name, Chunk_length, CRC, Content);
			Chunk_name_string.replace(0, 5, Chunk_Name);

			if (Chunk_name_string == "IDAT")
			{
				no_idat = false;
				cout << Chunk_name_string << " chunk founded at " << dec << pos << "; Lenght:" << Chunk_length << "; CRC:" << hex << showbase << CRC << endl;
			}

			if (Chunk_name_string == "IEND")
			{
				no_iend = false;
				if (no_idat)
				{
					throw exception("No IDAT founded");
				}
				else
				{
					cout << "IEND founded" << endl;
					cout << "File parsed successfully" << endl;
				}
			}
		}

		if (no_idat)
		{
			throw exception("No IDAT founded");
		}

		if (no_iend)
		{
			throw exception("No IEND founded or bad position");
		}


		png.close();
	}

	catch (const ifstream::failure& ex)
	{
		if (!no_idat && no_iend)
		{
			cout << "No IEND found or bad position" << endl;
		}
		else 
		{
			cout << ex.what() << endl;
			cout << ex.code() << endl;
		}
		
		png.close();
	}

	catch (const exception& ex)
	{
		cout << ex.what() << endl;
		png.close();
	}

	_getch();
}