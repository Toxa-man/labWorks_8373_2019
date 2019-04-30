#include <iostream>
#include <fstream>
#include <string>
#include <clocale>

typedef unsigned char byte;
using namespace  std;

#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define GETBITS(x)    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GETBYTE(x)    (GETBITS(x[0]) << 4 | GETBITS(x[1]))

class PNG
{
public:
	PNG(const char* szFileName)
	{
		ifstream file(szFileName, ios::binary | ios::ate);
		if (!file.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
			exit(0);
		}

		imageSize = (uint32_t)(file.tellg());
		imageBytes = new byte[imageSize];
		file.seekg(0, ios::beg);
		file.read(reinterpret_cast<char*>(imageBytes), imageSize);
		file.close();
	}

	bool checkSign()
	{
		return  pattern_scan("89 50 4E 47 0D 0A 1A 0A", (uint32_t)(imageBytes), 10);
	}

	bool checkIend()
	{
		return pattern_scan("49 45 4E 44", (uint32_t)(imageBytes), imageSize);
	}

	bool hasIdat()
	{
		return pattern_scan("?? ?? ?? ?? 49 44 41 54", (uint32_t)(imageBytes), imageSize);
	}

	bool hasIhdr()
	{
		return pattern_scan("49 48 44 52", (uint32_t)(imageBytes), 20);
	}

	void displayIdat()
	{
		PNG_CHUNK* chunk = nullptr;
		byte* start = imageBytes + 8;

		while(true)
		{
			chunk = (PNG_CHUNK*)start;
			chunk->chunkSize = _byteswap_ulong(chunk->chunkSize);
			if(!memcmp(chunk->sectionName, "IEND", 4))
				break;

			if(!memcmp(chunk->sectionName, "IDAT", 4))
			{
				printf_s("Position: %d\r\n", (uint32_t)(chunk) - (uint32_t)(imageBytes));
				byte* crc = (byte*)chunk + 8 + chunk->chunkSize;
				printf_s("CRC Sum: 0x%X%X%X%X\r\n\r\n", crc[0], crc[1], crc[2], crc[3]);
			}

			start += 12 + chunk->chunkSize;
		}
	}

	~PNG()
	{
		delete[] imageBytes;
	}

private:

	//Байты картинки
	byte* imageBytes;

	//Размер картинки
	uint32_t imageSize;

	//Структура чанка файла
	struct PNG_CHUNK
	{
		uint32_t chunkSize;
		char  sectionName[4];
	};


	//Функцию взяла с интернета, чтобы искать нужные байты в файле
	unsigned long pattern_scan(const char * signature, uint32_t start_addr, uint32_t size)
	{

		uint32_t end_addr = start_addr + size;
		const char* pat = signature;

		uint32_t first_match = 0;

		for (uint32_t cur = start_addr; cur < end_addr; cur++)
		{
			if (!*pat)
				return first_match;

			if (*(byte*)pat == '\?' || *(byte*)(cur) == GETBYTE(pat))
			{
				if (!first_match)
					first_match = cur;

				if (!pat[2])
					return first_match;

				if (*(uint16_t*)pat == '\?\?' || *(byte*)pat != '\?')
					pat += 3;
				else
					pat += 2;
			}
			else
			{
				pat = signature;
				first_match = 0;
			}
		}

		return 0;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	string fileName;
	cout << "Введите путь к картинке: ";
	getline(cin, fileName);
	PNG png(fileName.c_str());

	if(png.checkSign() == false)
	{
		cout << "Неверная сигнатура файла\r\n";
		return 0;
	}

	if (png.checkIend() == false)
	{
		cout << "Нет завершающего чанка\r\n";
		return 0;
	}

	if(png.hasIdat() == false)
	{
		cout << "Нет IDAT секций\r\n";
		return 0;
	}


	if (png.hasIhdr() == false)
	{
		cout << "Нет IHDR секции\r\n";
		return 0;
	}

	png.displayIdat();
}