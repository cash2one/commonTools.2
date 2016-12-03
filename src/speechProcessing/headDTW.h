/***dtwrecoge.h*********************************************************************/
#ifndef dtwrecoge_h
#define dtwrecoge_h

#include<stdio.h>
#include<math.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

//#define DTWMAXNUM 2000
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):(-(a)))
#define DTWVERYBIG 100000000.0

class DTW_{

	public:
		DTW_();
		~DTW_();
	public:
		/*****************************************************************************/
		/* DTWDistance������������֮���ƥ�����
		/* A,B�ֱ�Ϊ��һ�ڶ������飬I��JΪ�����鳤�ȣ�rΪƥ�䴰�ڵĴ�С
		/* r�Ĵ�Сһ��ȡΪ���鳤�ȵ�1/10��1/30
		/* ������������֮���ƥ�����,������أ�1.0���������鳤��̫����
		/*****************************************************************************/
		// double DTWDistanceFun(double *A,int32_t I,double *B,int32_t J,int32_t r);
		double DTWDistanceFun(vector<double>& A, vector<double>& B, int32_t r);
		double DTWDistanceFunOri(vector<double>& A, vector<double>& B, int32_t r);
		double DTWDistanceFun(vector<double>& A, int32_t& begin1, int32_t& end1, vector<double>& B, int32_t& begin2, int32_t& end2, int32_t r);
		
		/*****************************************************************************/
		/* DTWTemplate�����н���ģ��Ĺ���
		/* ����AΪ�Ѿ������õ�ģ�壬�������Ժ����ѵ��������ʱ��
		/* ���ѽ����õ�ģ����Ϊ��һ��������IΪģ��ĳ��ȣ������ģ���в��ٸı�
		/* BΪ�¼����ѵ��������JΪB�ĳ��ȣ�turnΪѵ���Ĵ������ڵ�һ��
		/* ���������齨��ģ��ʱ��rΪ1�����ǳ���Ȩֵ�Ŀ���
		/* temp����ƥ������ѵ�����ģ�壬����temp[DTWMAXNUM]��������������ѵ����ģ��ĳ���
		/* �����������-1������ѵ������֮����������Ҫ����ѡ��ѵ��������
		/* ttΪ����֮��������ֵ�����ж���
		/*****************************************************************************/
		int32_t DTWTemplate(double *A,int32_t I,double *B,int32_t J,double *temp,int32_t turn,double tt,double *rltdistance);

	public:
		double **dtwpath;
		double **distance;

};


#endif
