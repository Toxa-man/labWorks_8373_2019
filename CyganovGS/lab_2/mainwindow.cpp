#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPlainTextEdit>
#include <QString>
#include <fstream>
#include <algorithm>

using namespace std;

const int signatureSize=8, chunkSize=4;
const int signature[8]={137, 80, 78, 71, 13, 10, 26, 10};
const int IHDR[4]={(int)'I', (int)'H', (int)'D', (int)'R'};
const int IDAT[4]={(int)'I', (int)'D', (int)'A', (int)'T'};
const int IEND[4]={(int)'I', (int)'E', (int)'N', (int)'D'};


bool isEqual(char *ch, const int *in){
    for(int i=0; i<chunkSize; i++){
        if(ch[i]!=in[i]){
            return false;
        }
    }
    return true;
}

bool isSignature(ifstream &file){
    char checkedSign[signatureSize]={};
    file.read(checkedSign, signatureSize);
    for(int i=0; i<signatureSize; i++){
        if(checkedSign[i]!=(char)signature[i]){
            return false;
        }
    }
    return true;
}

unsigned int toInt(char revInt[chunkSize]){
    swap(revInt[0], revInt[3]);
    swap(revInt[1], revInt[2]);
    unsigned int*answ=(unsigned int*)revInt;
    return *answ;
}

class Chunk{
    private:
        unsigned int pos;
        int length;
        char typeName[chunkSize];
        int CRC;
    public:
        void setData(ifstream &file);
        char* getType();
        QString aboutChunk();
        void cleanChunk();
};

void Chunk::setData(ifstream &file){
    pos=file.tellg();
    char len[chunkSize];
    file.read((char*)len, chunkSize);
    length=toInt(len);
    file.read((char*)typeName, chunkSize);
    file.seekg(length, ios::cur);
    char temp[chunkSize];
    file.read((char*)temp, chunkSize);
    CRC=toInt(temp);
}

char* Chunk::getType(){
    return typeName;
}

QString Chunk::aboutChunk(){
    if(isEqual(this->typeName, IDAT)){
        QString ab="IDAT chunk founded at "+QString::number(pos)+"; Length: "+QString::number(length)+"; CRC: "+QString("%1").arg(CRC, 0, 16).toUpper();
        return ab;
    }else if(isEqual(this->typeName, IEND)){
        return "IEND is OK";
    }
}

void Chunk::cleanChunk(){
    pos=0;
    length=0;
    for(int i=0; i<chunkSize; i++){
        typeName[i]=0;
    }
    CRC=0;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle("PNG Parser");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{           ui->myTextEdit->clear();
            QString path;
            path=ui->myLineEdit->text();
            string s=path.toStdString();
            bool haveIDAT=false, haveIEND=false;
            ifstream parsedFile(s.c_str(), ios::binary);
            if(parsedFile.is_open()){
                if(isSignature(parsedFile)){
                    ui->myTextEdit->appendPlainText("Signature is OK");
                    Chunk chunk;
                    chunk.setData(parsedFile);
                    if(isEqual(chunk.getType(), IHDR)){
                        ui->myTextEdit->appendPlainText("IHDR is OK");
                        //chunk.setData(parsedFile);
                        while(!(parsedFile.eof()) && !isEqual(chunk.getType(), IEND)){
                            chunk.cleanChunk();
                            //cout<<parsedFile.tellg()<<endl;
                            chunk.setData(parsedFile);
                            if(isEqual(chunk.getType(), IDAT)){
                                haveIDAT=true;
                                ui->myTextEdit->appendPlainText(chunk.aboutChunk());
                            }else if(isEqual(chunk.getType(), IEND) && haveIDAT){
                                haveIEND=true;
                                ui->myTextEdit->appendPlainText(chunk.aboutChunk());
                            }
                        }
                        if(!haveIDAT){
                            ui->myTextEdit->appendPlainText("IDAT wasn't found");
                        }else if(!haveIEND){
                            ui->myTextEdit->appendPlainText("No IEND");
                        }else{
                            ui->myTextEdit->appendPlainText("File parsed successfully");
                        }
                    }else{
                        ui->myTextEdit->appendPlainText("IHDR wasn't found");
                    }
                }else{
                    ui->myTextEdit->appendPlainText("Signature wasn't found");
                }
            }else{
                ui->myTextEdit->appendPlainText("Something goes wrong. Please try again.");
            }
            parsedFile.close();
}
