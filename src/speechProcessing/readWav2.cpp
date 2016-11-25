#include <iostream>
#include <fstream>
#include <string.h>
#include<math.h>
#include<cmath>
#include<stdlib.h>
#include <bitset>
#include <iomanip>
#include <algorithm>

//Ҫ��int main()��ǰ����Ϻ�������������Ϊ��ĺ���д��main�����ĺ���
int hex_char_value(char ss);
int hex_to_decimal(const char* s);
//string hex_to_binary(char* szHex);
using namespace std;
 
struct wav_struct
{
	unsigned long file_size;		//�ļ���С
	unsigned short channel;			//ͨ����
	unsigned long frequency;		//����Ƶ��
	unsigned long Bps;				//Byte��
	unsigned short sample_num_bit;	//һ��������λ��
	unsigned long data_size;		//���ݴ�С
	unsigned char *data;			//��Ƶ���� ,����Ҫ����ʲô�Ϳ�����λ���ˣ�������ֻ�ǵ����ĸ�������
};
 
int main(int argc, char **argv)
{
	fstream fs;
	wav_struct WAV;
	string filename = argv[1];
	fs.open(filename.c_str(), ios::binary | ios::in);
 
	//	fs.seekg(0x04);				//���ļ������л�ȡ�ļ���С
	//	fs.read((char*)&WAV.file_size,sizeof(WAV.file_size));
	//	WAV.file_size+=8;
 
	fs.seekg(0, ios::end);		//��c++���÷�������ļ���С
	WAV.file_size = fs.tellg();
 
	fs.seekg(0x14);
	fs.read((char*)&WAV.channel, sizeof(WAV.channel));
 
	fs.seekg(0x18);
	fs.read((char*)&WAV.frequency, sizeof(WAV.frequency));
 
	fs.seekg(0x1c);
	fs.read((char*)&WAV.Bps, sizeof(WAV.Bps));
 
	fs.seekg(0x22);
	fs.read((char*)&WAV.sample_num_bit, sizeof(WAV.sample_num_bit));
 
	fs.seekg(0x28);
	fs.read((char*)&WAV.data_size, sizeof(WAV.data_size));
 
	cout << "�ļ���СΪ  ��" << WAV.file_size << endl;
	cout << "��Ƶͨ����  ��" << WAV.channel << endl;
	cout << "����Ƶ��	��" << WAV.frequency << endl;
	cout << "Byte��	  ��" << WAV.Bps << endl;
	cout << "����λ��	��" << WAV.sample_num_bit << endl;
	cout << "��Ƶ���ݴ�С��" << WAV.data_size << endl;
	cout << "���10�����ݣ�" << endl;
 	
	WAV.data = new unsigned char[WAV.data_size];
	fs.seekg(0x2c);
	fs.read((char *)WAV.data, sizeof(char)*WAV.data_size);
 
	bool iszero = 1;
	for (unsigned long i =0; i<WAV.data_size; i++)
	//for (unsigned long i =0; i<WAV.data_size; i = i + 2)
	{
		if(WAV.data[i] != 0)
			iszero = 0;
		if(iszero == 1)
			;//continue;
		//printf("%x ", WAV.data[i]);
		//continue;
		//�ұ�Ϊ���
		unsigned long data_low = WAV.data[i];
		unsigned long data_high = WAV.data[i + 1];
		double data_true = data_high * 256 + data_low;
		//printf("%d ",data_true);
		long data_complement = 0;	   
		//ȡ��˵����λ������λ��
		int my_sign = (int)(data_high / 128);
		//printf("%d ", my_sign);
		if (my_sign == 1)
		{
			data_complement = data_true - 65536;
		}
		else
		{
			data_complement = data_true;
		}
		//printf("%d ", data_complement);
		setprecision(4);
		double float_data = (double)(data_complement/(double)32768);	
		printf("%f ", float_data);
 
		//data_normalization[i] = (char)float_data;
		//printf("%f ", data_normalization[i]);	 
		//bitset<8>lsc_high(data_high);
		//string high_binary = lsc_high.to_string();		
		//bitset<8> low_binary (low_data);			
	}
	cout << endl;
	fs.close();
 
	delete[] WAV.data;
	//system("pause");
 
}
int hex_char_value(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	//assert(0);
	return 0;
}
int hex_to_decimal(char* szHex)
{
	int len = 2;
	int result = 0;
	for (int i = 0; i < len; i++)
	{
		result += (int)pow((float)16, (int)len - i - 1) * hex_char_value(szHex[i]);
	}
	return result;
}
/*
string hex_to_binary(char* szHex)
{
	int len = 2;
	string result;
	for (int i = 0; i < len;i++)
}
*/
