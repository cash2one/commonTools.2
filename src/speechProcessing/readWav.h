#ifndef READ_WAV_HEAD_H__
#define READ_WAV_HEAD_H__

#include <iostream>
#include <fstream>
#include <string.h>
#include<math.h>
#include<cmath>
#include<stdlib.h>
#include <bitset>
#include <iomanip>
#include <vector>
using namespace std;

//struct wav_struct
//{
//	unsigned long file_size;		//�ļ���С
//	unsigned short channel;			//ͨ����
//	unsigned long frequency;		//����Ƶ��
//	unsigned long Bps;				//Byte��
//	unsigned short sample_num_bit;	//һ��������λ��
//	unsigned long data_size;		//���ݴ�С
//	unsigned char *data;			//��Ƶ���� ,����Ҫ����ʲô�Ϳ�����λ���ˣ�������ֻ�ǵ����ĸ�������
//};
class wavStruct
{
	public:
		wavStruct();
		~wavStruct();
	public:
		unsigned long file_size;		//�ļ���С
		unsigned short channel;			//ͨ����
		unsigned long frequency;		//����Ƶ��
		unsigned long Bps;				//Byte��
		unsigned short sample_num_bit;	//һ��������λ��
		unsigned long data_size;		//���ݴ�С
		unsigned char *data;			//��Ƶ���� ,����Ҫ����ʲô�Ϳ�����λ���ˣ�������ֻ�ǵ����ĸ�������
	public:
		int readWav(string& filename, vector<string>& data, vector<double>& float_data,unsigned long size);
		int postProcessingFloatSequence(vector<double>& float1, int32_t& begin, int32_t& end, int32_t& size);
};
 
//int readWav(string& filename, unsigned char* data, vector<double>& float_data,unsigned long size);


#endif
