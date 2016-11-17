#include <iostream>
#include <fstream>
#include <string.h>
#include<math.h>
#include<cmath>
#include<stdlib.h>
#include <bitset>
#include <iomanip>

using namespace std;

struct my_wave
{
unsigned long chunckId;
unsigned long chunkSize;
unsigned long format;
unsigned long subChunk1Id;
unsigned long subChunk1Size;
unsigned short audioFormat;
unsigned short numChannels;
unsigned long sampleRate;
unsigned long byteRate;
unsigned short blockAlign;
unsigned short bitsPerSampel;
unsigned long subChunk2Id;
unsigned long subChunk2Size;
unsigned char *z_data;
};

int main(int argc, char **argv)
{
	ifstream fs;
	ofstream ofs;
	my_wave MW;
	//��ȡԭʼ�ļ�
	fs.open("../data/add_score.wav", ios::binary | ios::in); //�����Ҫ�޸ĳ������ļ�·��
	ofs.open("waveout.wav", ios::binary | ios::out); //��ȡ���ļ�д�����ļ�
	
	//��ȡwav�ļ��������ֶ�
	fs.seekg(0);
	fs.read((char*)&MW.chunckId, sizeof(MW.chunckId));
	
	fs.seekg(0x04);
	fs.read((char*)&MW.chunkSize, sizeof(MW.chunkSize));
	
	fs.seekg(0x08);
	fs.read((char*)&MW.format, sizeof(MW.format));
	
	fs.seekg(0x0c);
	fs.read((char*)&MW.subChunk1Id, sizeof(MW.subChunk1Id));
	
	fs.seekg(0x10);
	fs.read((char*)&MW.subChunk1Size, sizeof(MW.subChunk1Size));
	
	fs.seekg(0x14);
	fs.read((char*)&MW.audioFormat, sizeof(MW.audioFormat));
	
	fs.seekg(0x16);
	fs.read((char*)&MW.numChannels, sizeof(MW.numChannels));
	
	fs.seekg(0x18);
	fs.read((char*)&MW.sampleRate, sizeof(MW.sampleRate));
	
	fs.seekg(0x1c);
	fs.read((char*)&MW.byteRate, sizeof(MW.byteRate));
	
	fs.seekg(0x20);
	fs.read((char*)&MW.blockAlign, sizeof(MW.blockAlign));
	
	fs.seekg(0x22);
	fs.read((char*)&MW.bitsPerSampel, sizeof(MW.bitsPerSampel));
	
	fs.seekg(0x24);
	fs.read((char*)&MW.subChunk2Id, sizeof(MW.subChunk2Id));
	
	fs.seekg(0x28);
	fs.read((char*)&MW.subChunk2Size, sizeof(MW.subChunk2Size));
	
	MW.z_data = new unsigned char[MW.subChunk2Size];
	fs.seekg(0x2c);
	fs.read((char *)MW.z_data, sizeof(char)*MW.subChunk2Size);
	
	//���wav�ļ��������ֶΣ��Թ�����
	cout << MW.chunckId << endl;
	cout << MW.chunkSize << endl;
	cout << MW.format << endl;
	cout << MW.subChunk1Id << endl;
	cout << MW.subChunk1Size << endl;
	cout << MW.audioFormat << endl;
	cout << MW.numChannels << endl;
	cout << MW.sampleRate << endl;
	cout << MW.byteRate << endl;
	cout << MW.blockAlign << endl;
	cout << MW.bitsPerSampel << endl;
	cout << MW.subChunk2Id << endl;
	cout << MW.subChunk2Size << endl;
	cout <<"�������ݣ�"<< endl;
	for (int k = 0; k < MW.subChunk2Size; k++){
		printf("%x",MW.z_data[k]);
	}

	//��ÿ���ֶ�ԭ�ⲻ����д���µ�.wav�ļ���
	ofs.write((char*)&MW.chunckId, sizeof(MW.chunckId));
	ofs.write((char*)&MW.chunkSize, sizeof(MW.chunkSize));
	ofs.write((char*)&MW.format, sizeof(MW.format));
	ofs.write((char*)&MW.subChunk1Id, sizeof(MW.subChunk1Id));
	ofs.write((char*)&MW.subChunk1Size, sizeof(MW.subChunk1Size));
	ofs.write((char*)&MW.audioFormat, sizeof(MW.audioFormat));
	ofs.write((char*)&MW.numChannels, sizeof(MW.numChannels));
	ofs.write((char*)&MW.sampleRate, sizeof(MW.sampleRate));
	ofs.write((char*)&MW.byteRate, sizeof(MW.byteRate));
	ofs.write((char*)&MW.blockAlign, sizeof(MW.blockAlign));
	ofs.write((char*)&MW.bitsPerSampel, sizeof(MW.bitsPerSampel));
	ofs.write((char*)&MW.subChunk2Id, sizeof(MW.subChunk2Id));
	ofs.write((char*)&MW.subChunk2Size, sizeof(MW.subChunk2Size));
	ofs.write((char*)MW.z_data, sizeof(char)*MW.subChunk2Size);
	
	fs.close();
	ofs.close();
	delete[] MW.z_data;
	system("pause");
}
