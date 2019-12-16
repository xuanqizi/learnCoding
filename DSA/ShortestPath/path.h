#ifndef _PATH_H_
#define _PATH_H_

#include "graph.h"
#include <string>
#include <iostream>

void setMap(GraphMatrix<string, string> & map);					//����Ϣ¼��ͼ��
void findPath(GraphMatrix<string, string> map, int s, int t);	//����dijkstra�㷨�����·��
void printPlace();												//��ʾ�ص���Ϣ
bool checkInput(int begin, int end, int res);					//��������Ƿ���ȷ
int inputNum(int & begin, int & end);							//�����û�������Ϣ

#endif // !_PATH_H_