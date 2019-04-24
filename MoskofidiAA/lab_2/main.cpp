#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void reverse(char* beg, char* end) {
    while (beg < end) {
        swap(*beg, *end);
        ++beg;
        --end;
    }
}

bool signatureTest(ifstream &file, bool &firstTest) {
    const long long unsigned testSign = 727905341920923785; // 0x89504E470D0A1A0A в десятичной и реверснутое
    long long unsigned forCompare;
    file.read((char*) &forCompare, 8);
    if (forCompare == testSign)
        firstTest = true;
    return firstTest;
}

bool ihdrTest(ifstream &file, bool &secondTest, ofstream &out) {
    const long unsigned testName = 1380206665; // то же самое
    long unsigned ihdrSizeCheck;
    long unsigned ihdrNameCheck;
    int i(0);
    file.read((char*) &ihdrSizeCheck, 4);
    reverse((char*) &ihdrSizeCheck, (char*) &ihdrSizeCheck + 4 - 1);
    file.read((char*) &ihdrNameCheck, 4);
    if (ihdrNameCheck == testName)
        secondTest = true;
    file.seekg(ihdrSizeCheck + 4, ios::cur); // пропускаю оставшуюся часть IHDR чанка
    return secondTest;
}

void idatIendTest(ifstream &file, ofstream &out) {
    const long unsigned idatTestName = 1413563465;
    const long unsigned iendTestName = 1145980233;
    long unsigned idatSize;
    long unsigned nameCheck;
    long unsigned idatCRC;
    unsigned position;

    position = file.tellg(); // записываю позицию чанка
    file.read((char*) &idatSize, 4); // размер встретившегося чанка
    reverse((char*) &idatSize, (char*) &idatSize + 4 - 1);
    file.read((char*) &nameCheck, 4); // имя встретившегося чанка
    if(nameCheck == idatTestName) {
        while (nameCheck == idatTestName) {
            file.seekg(position + 8 + idatSize); // перепрыгивает соответственно размеру основной блок
            file.read((char *) &idatCRC, 4); // читает CRC
            reverse((char *) &idatCRC, (char *) &idatCRC + 4 - 1); // реверс

            out << "IDAT chunk was found at position " << dec << position << "; "; // вывод позиции идат блока
            out << "CRC: " << hex << showbase << idatCRC << endl; // перевод в хекс и вывод CRC

            position = file.tellg(); // позиция следующего чанка
            file.read((char *) &idatSize, 4); // размер следующего чанка
            reverse((char*) &idatSize, (char*) &idatSize + 4 - 1);
            file.read((char *) &nameCheck, 4); // имя следующего чанка
        }
        if(nameCheck == iendTestName) {
            out << "IEND test: done" << endl;
            out << "This PNG is valid" << endl;
        }
        else {
            out << "Wrong IEND";
            exit(0);
        }
    }
    else {
        out << "Wrong IDAT" << endl;
        exit(0);
    }
}

int main() {
    ifstream file("normal.png", ios::binary);
    ofstream out("out.txt", ios::binary);

    size_t size(0);
    bool firstTest(false);
    bool secondTest(false);

    file.seekg(0, ios::end);
    size = static_cast<size_t>(file.tellg());
    file.seekg(0, ios::beg);

    out << "File size: " << size << endl;
    if (signatureTest(file, firstTest))
        out << "Signature test: done" << endl;
    else {
        out << "Wrong signature" << endl;

        return 0;
    }
    if (ihdrTest(file, secondTest, out))
        out << "IHDR test: done" << endl;
    else {
        out << "Wrong IHDR" << endl;
        return 0;
    }
    idatIendTest(file, out);
    file.close();
    out.close();
    return 0;
}
