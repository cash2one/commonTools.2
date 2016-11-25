#include <iostream>  
#include <stdio.h>  
#include <string>
using namespace std;  
/* 
read a  wav voice by c++ language 
*/  
typedef struct wave_tag  
{  
    char ChunkID[4];                    // "RIFF"��־  
    unsigned int ChunkSize;     // �ļ�����(WAVE�ļ��Ĵ�С, ����ǰ8���ֽ�)  
    char Format[4];                     // "WAVE"��־  
    char SubChunk1ID[4];                // "fmt "��־  
    unsigned int SubChunk1Size; // �����ֽ�(����)  
    unsigned short int AudioFormat;     // ��ʽ���(10HΪPCM��ʽ����������)  
    unsigned short int NumChannels;     // ͨ����(������Ϊ1, ˫����Ϊ2)  
    unsigned short int SampleRate;      // ������(ÿ��������), ��ʾÿ��ͨ���Ĳ����ٶ�  
    unsigned int ByteRate;          // ������Ƶ���ݴ�������, ��ֵΪ:ͨ����*ÿ������λ��*ÿ����������λ��/8  
    unsigned short int BlockAlign;      // ÿ����������λ��(���ֽ���), ��ֵΪ:ͨ����*ÿ����������λֵ/8  
    unsigned short int BitsPerSample;   // ÿ����������λ��, ��ʾÿ�������и�������������λ��.  
    char deathDate[4];  
    char SubChunk2ID[4];                // ���ݱ��"data"  
    unsigned int SubChunk2Size; // �������ݵĳ���  
  
} WAVE;  
  
int main(int argc, char *argv[])  
{  
    FILE *fp;  
    WAVE wav; 
	string filename = argv[1];
    fp=fopen(filename.c_str(),"rb");   
    fread(&wav, sizeof(struct wave_tag), 1, fp);  
    cout<<wav.ChunkID<<endl;                    // "RIFF"��־  
    cout<<wav.ChunkSize<<endl;      // �ļ�����(WAVE�ļ��Ĵ�С, ����ǰ8���ֽ�)  
    cout<<wav.Format<<endl;                     // "WAVE"��־  
    cout<<wav.SubChunk1ID<<endl;                // "fmt "��־  
    cout<<wav.SubChunk1Size<<endl;  // �����ֽ�(����)  
    cout<<wav.AudioFormat<<endl;        // ��ʽ���(10HΪPCM��ʽ����������)  
    cout<<wav.NumChannels<<endl;        // ͨ����(������Ϊ1, ˫����Ϊ2)  
    cout<<wav.SampleRate<<endl;     // ������(ÿ��������), ��ʾÿ��ͨ���Ĳ����ٶ�  
    cout<<wav.ByteRate<<endl;           // ������Ƶ���ݴ�������, ��ֵΪ:ͨ����*ÿ������λ��*ÿ����������λ��/8  
    cout<<wav.BlockAlign<<endl;     // ÿ����������λ��(���ֽ���), ��ֵΪ:ͨ����*ÿ����������λֵ/8  
    cout<<wav.BitsPerSample<<endl;  // ÿ����������λ��, ��ʾÿ�������и�������������λ��.  
    cout<<wav.deathDate<<endl;  
    cout<<wav.SubChunk2ID<<endl;                // ���ݱ��"data"  
    cout<<wav.SubChunk2Size<<endl;  
      
    return 0;  
}  
