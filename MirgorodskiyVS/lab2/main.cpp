#include<iostream> 
#include<fstream> 
#include<memory.h> 
using namespace std; 

const unsigned signa_size = 8; 

void reverse(char* inception, char* end) { 
while (inception < end) { 
swap(*inception++, *end--); 
} 
} 

void signaturetest(ifstream &picture) { 
long long unsigned signa_from_file; 
long long unsigned valid_signa = 727905341920923785 //0x89504E470D0A1A0A в десятичной; 

picture.read((char*)& signa_from_file, signa_size); 
reverse((char*)& signa_from_file, (char*)& signa_from_file + signa_size - 1); 

if (signa_from_file == valid_signa) { 
cout « "Signature is OK" « endl; 
} 
else { 
cout « "Signature is wrong" « endl; 
system("pause"); 
} 
} 

void IHDRtest(ifstream &picture) { 
unsigned ihdr_length; 
unsigned ihdr_type; 
unsigned valid_ihdr = 0x49484452; 
picture.read((char*)& ihdr_length, 4);// место для IHDR 
reverse((char*)& ihdr_length, (char*)& ihdr_length + 4 - 1); 

if (ihdr_length != 13) { /* 13 == 00 00 00 0D */ 
cout « "IHDR is wrong" « endl; 
system("pause"); 
} 

picture.read((char*)& ihdr_type, 4);// место для чанка IHDR 
reverse((char*)& ihdr_type, (char*)& ihdr_type + 4 - 1); 

if (ihdr_type != valid_ihdr) { 
cout « "IHDR is wrong" « endl; 
system("pause"); 
} 
cout « "IHDR is OK" « endl; 
picture.seekg(13 + 4, ios::cur);// 13 байт для чанка, 4 bytes - для CRC 
} 

void IEND_IDATtest(ifstream &picture) { 
const unsigned sizeof_attribute = 4, type_idat = 0x49444154, 
type_iend = 0x49454E44, length_iend = 0; 
unsigned length = 1, crc, type = 1, pos = picture.tellg(); 

picture.seekg(0, ios::end); 
unsigned file_size = picture.tellg(); 
int i = 0; 

picture.seekg(pos, ios::beg); 
while (length != 0 && pos != file_size) { 
pos = picture.tellg(); 
picture.read((char*)& length, sizeof_attribute); 
reverse((char*)& length, (char*)& length + sizeof_attribute - 1); 

picture.read((char*)& type, sizeof_attribute); 
reverse((char*)& type, (char*)& type + sizeof_attribute - 1); 

picture.seekg(length, ios::cur); 
picture.read((char*)& crc, sizeof_attribute); 
reverse((char*)& crc, (char*)& crc + sizeof_attribute - 1); 
if (length == 0) break; 
if (type == type_idat) { 
i++; 
cout « "IDAT chunk founded at " « dec « pos « "; Length: " « length « ";"" CRC: " « hex « showbase « crc « endl; 
} 
} 
if (i == 0) { 
cout « "No IDAT founded" « endl; 
system("pause"); 
} 
if (type != type_iend && pos != file_size - sizeof_attribute) { 
cout « "No IEND founded or bad position" « endl; 
system("pause"); 
} 
cout « "IEND founded" « endl « "File built successfully" « endl; 

} 
int main() { 
ifstream picture("D:\\1\\s_v_am\\nottrue_IHDR.png", ios::binary); 
signature_test(picture); 
IHDR_test(picture); 
IEND_and_IDAT_test(picture); 
system("pause"); 
}
