#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "fstream"
const int T_Size = 7, esc_code = 27,
Signature_Length = 8, IEND_Length = 8,
Chunk_Length_Length = 4,
Chunk_Name_Length = 4, CRC_Length = 4, Half_Second_Delay = 500;

const unsigned char Standard_Signature[Signature_Length] = { 137, 'P', 'N', 'G', 13, 10, 26, 10 },
IHDR_Name[Chunk_Name_Length] = { 'I', 'H', 'D', 'R' },
IDAT_Name[Chunk_Name_Length] = { 'I', 'D', 'A', 'T' },
IEND_Name[Chunk_Name_Length] = { 'I', 'E', 'N', 'D' },
IEND_Chunk[IEND_Length] = { 'I', 'E', 'N', 'D', 174, 66, 96, 130 };
enum class Chunk_Type { UNKNOWN, IDAT, IEND };
struct png_file
{
	std::string Name_Of_File;
	std::ifstream stream;
	bool Signature_Founded = false;
	bool IHDR_Chunk_Founded = false;
	bool IDAT_Chunk_Founded = false;
	bool IEND_Chunk_Founded = false;
	std::streamoff Chunk_Start;
	unsigned int Cur_Chunk_Len = 0;
	unsigned int pos = 0;
	unsigned int Cur_Chunk_CRC;
	std::streamoff File_End;
};
void Show_Signature_Status(bool Status)
{
	if (Status)
	{
		std::cout << "Signature is OK" << std::endl;
	}
	else
	{
		std::cout << "Signature is wrong" << std::endl;
	}
}
void Check_Signature(png_file &file)
{
	char* buf = new char[Signature_Length];
	buf[0] = 0;
	file.Signature_Founded = true;
	file.stream.read(buf, Signature_Length);
	for (int i = 0; i < Signature_Length; ++i)
	{
		if (buf[i] != (char)Standard_Signature[i])
		{
			i = Signature_Length;
			file.Signature_Founded = false;
		}
	}
	file.pos += Signature_Length;
	delete[]buf;
}

void Set_Start_Of_Chunk(png_file &file)
{
	file.Chunk_Start = file.stream.tellg();
}
unsigned int Get_Length_Of_Chunk(png_file &file)
{
	unsigned int buf = 0;
	char* Ptr = (char*)&buf;
	Set_Start_Of_Chunk(file);
	for (int i = 0; i < Chunk_Length_Length; ++i)
	{
		file.stream.get(Ptr[Chunk_Length_Length - i - 1]);
	}
	file.pos += Chunk_Length_Length;
	file.Cur_Chunk_Len = buf;
	return buf;
}
unsigned int Get_CRC(png_file& file)
{
	char* Ptr = (char*)&file.Cur_Chunk_CRC;
	for (int i = 0; i < CRC_Length; ++i)
	{
		file.stream.get(Ptr[CRC_Length - i - 1]);
		file.pos++;
	}
	return file.Cur_Chunk_CRC;
}
void Show_IHDR_Status(bool Status)
{
	if (Status)
	{
		std::cout << "IHDR OK" << std::endl;
	}
	else
	{
		std::cout << "IHDR wasn't found" << std::endl;
	}
}

void Check_IHDR(png_file &file)
{
	char* buf = new char[Chunk_Name_Length];
	buf[0] = 0;
	file.IHDR_Chunk_Founded = true;
	Get_Length_Of_Chunk(file);
	file.stream.read(buf, Chunk_Name_Length);
	for (int i = 0; i < Chunk_Name_Length; ++i)
	{
		if (buf[i] != IHDR_Name[i])
		{
			file.IHDR_Chunk_Founded = false;
		}
	}
	file.pos += Chunk_Name_Length;
	file.pos += file.Cur_Chunk_Len;
	Get_CRC(file);
	file.stream.seekg(file.pos, std::ios_base::beg);
	delete[]buf;
}
Chunk_Type Get_Chunk_Type(png_file &file)
{
	char* buf = new char[Chunk_Name_Length];
	buf[0] = 0;
	Get_Length_Of_Chunk(file);
	Chunk_Type result = Chunk_Type::IDAT;
	bool Is_IDAT = true;
	file.stream.read(buf, Chunk_Name_Length);
	for (int i = 0; i < Chunk_Name_Length; ++i)
	{
		if (buf[i] != IDAT_Name[i])
		{
			Is_IDAT = false;
			result = Chunk_Type::IEND;
			i = Chunk_Name_Length;
		}
	}
	if (!Is_IDAT)
	{
		for (int i = 0; i < Chunk_Name_Length; ++i)
		{
			if (buf[i] != IEND_Name[i])
			{
				result = Chunk_Type::UNKNOWN;
				i = Chunk_Name_Length;
			}
		}
	}
	file.pos += Chunk_Name_Length;
	delete[]buf;
	return result;
}
void Show_IDAT_Status_And_Chunk_Info(png_file& file)
{
	if (file.IDAT_Chunk_Founded)
	{
		std::cout << "IDAT chunk founded at " << file.Chunk_Start <<
			"; Length: " << file.Cur_Chunk_Len << "; CRC: " << std::hex <<
			file.Cur_Chunk_CRC << std::endl << std::dec;
	}
	else
	{
		std::cout << "No IDAT founded or invalid" << std::endl;
	}
}
void Check_IDAT(png_file &file)
{
	file.IDAT_Chunk_Founded = true;
	file.pos += file.Cur_Chunk_Len;
	file.stream.seekg(file.pos, std::ios_base::beg);
	Get_CRC(file);
	Show_IDAT_Status_And_Chunk_Info(file);
}
void Skip_Unknown_Chunk(png_file &file)
{
	file.pos += file.Cur_Chunk_Len;
	file.stream.seekg(file.pos, std::ios_base::beg);
	Get_CRC(file);
}
void Show_IEND_Status(png_file& file)
{
	if (file.IEND_Chunk_Founded)
	{
		std::cout << "IEND founded" << std::endl << "File parsed succesfully" << std::endl;
	}
	else
	{
		std::cout << "No IEND founded or bad position" << std::endl;
	}
}
void Check_IEND(png_file &file)
{
	file.IEND_Chunk_Founded = true;
	file.stream.seekg(file.pos + 4, std::ios_base::beg);
}
void Test_Begin(png_file &file)
{
	file.stream.open(file.Name_Of_File, std::ios::binary);
	file.stream.seekg(0, std::ios_base::end);
	file.File_End = file.stream.tellg();
	file.stream.seekg(0, std::ios_base::beg);
	Check_Signature(file);
	Show_Signature_Status(file.Signature_Founded);
	if (file.Signature_Founded)
	{
		Check_IHDR(file);
		Show_IHDR_Status(file.IHDR_Chunk_Founded);
		if (file.IHDR_Chunk_Founded)
		{
			do
			{
				switch (Get_Chunk_Type(file))
				{
				case Chunk_Type::UNKNOWN:
					Skip_Unknown_Chunk(file);
					break;
				case Chunk_Type::IDAT:
					Check_IDAT(file);
					break;
				case Chunk_Type::IEND:
					Check_IEND(file);
					break;
				}
			} while (file.pos < file.File_End);
			if (!file.IDAT_Chunk_Founded)
			{
				Show_IDAT_Status_And_Chunk_Info(file);
			}
			else
			{
				Show_IEND_Status(file);
			}
		}
	}
	file.stream.close();
}
int main()
{
	char k = 0;

	while (k != esc_code)
	{
		Sleep(Half_Second_Delay);
		png_file file;
		std::cout << "enter file name with .png postfix" << std::endl;
		std::getline(std::cin, file.Name_Of_File);
		//file.Name_Of_File = "normal_file.png";
		//file.Name_Of_File = "wrong_signature.png";
		//file.Name_Of_File = "no_IDAT.png";
		//file.Name_Of_File = "wrong_IHDR.png";
		//file.Name_Of_File = "wrong_IEND.png";
		Test_Begin(file);
		std::cout << "Press any botton to test another file (press esc for quit)" << std::endl;
		k = _getch();
	}
	return 0;
}
