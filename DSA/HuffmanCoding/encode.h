#ifndef _ENCODE_H_
#define _ENCODE_H_

#include <cstdio>

bool encode();					//ѹ������
bool printStat(int* stat, char* targetFile);							//��Ƶ�ʱ����ѹ���ļ���
void fileEncoding(char* textFile, HuffTable table,char* targetFile);		//���ݱ����������ļ����б���
void fileWriting(char* targetFile, string output);						//�������������ļ���


#endif // !_ENCODE_H_

