#ifndef _PATH_H_
#define _PATH_H_

#include "graph.h"
#include <string>
#include <iostream>

GraphMatrix<string, string> setMap();							//����Ϣ¼��ͼ��
void findPath(GraphMatrix<string, string> map, int s, int t);	//����dijkstra�㷨�����·��
void printPlace();												//��ʾ�ص���Ϣ

#endif // !_PATH_H_