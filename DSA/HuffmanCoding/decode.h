#ifndef _DECODE_H_
#define _DECODE_H_

#include <cstdio>

bool decode();					//��ѹ����
int* readStat(char* filename);	//�����ַ�Ƶ�ʱ�
void fileDecoding(char* filename, char* targetName, RTable table, int maxLength);

#endif // !_DECODE_H_
