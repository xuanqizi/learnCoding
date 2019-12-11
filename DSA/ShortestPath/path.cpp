#include "path.h"
#include "graph.cpp"

GraphMatrix<string, string> setMap() {
	GraphMatrix<string, string> map;
	string place[10] =
	{ "��԰����","������","����","�ഺ�㳡","һ��","����¥B��",
		"һ���˶���","��ѵ����","�ֺ��ؽ�ѧԺ","һ��¥" };		//�ص�����
	string pathName[] = { "����·����","���δ������(1)","����",
		"��Զ���(1)","���δ������(2)","���δ������(1)","��Զ���(2)",
		"����·","����·","����·","��ҵ��","��֪��С·","���δ������(2)",
		"����·","����·һ��" };												//��·��
	int pathlen[] = { 538,452,702,439,362,588,761,397,
		251,257,419,621,806,633,1400 };											//��·����
	int pathV1[] = { 1,1,3,4,5,5,5,4,2,9,0,0,3,4,2 };							//��·�ڵ�1										
	int pathV2[] = { 2,3,4,5,6,7,8,2,9,6,3,1,7,7,8 };							//��·�ڵ�2
	//�Ͼ���ĿҪ������Լ�ѡ���ص㣬��Ȼ����ǾͲ����ļ���ȡ�����Լ�����Ѷ���- -
	/*��ȡ�ص㣬�Ե����ʽ����ͼ��*/
	for (int i = 0; i < 10; i++) {
		map.insert(place[i]);
	}
	/*��ȡ��·���Աߵķ�ʽ����ͼ��*/
	for (int i = 0; i < 15; i++) {						//�����������ĵ�·
		map.insert(pathName[i], pathlen[i], pathV1[i], pathV2[i]);
		map.insert(pathName[i], pathlen[i], pathV2[i], pathV1[i]);
	}
	return map;
}

void findPath(GraphMatrix<string, string> map, int s, int t) {
	int totalLength = 0;														//�ܳ�
	map.reset();
	map.priority(s) = 0;
	for (int i = 0; i < map.n; i++) {
		map.status(s) = VISITED;
		if (map.parent(s) != -1) {
			map.type(map.parent(s), s) = TREE;
			totalLength += map.weight(map.parent(s), s);
			cout << map.edge(map.parent(s), s) << "->";
		}
		cout << map.vertex(s);
		if (s == t) {
			cout << endl;
			break;																//ѡ���Ľڵ�ΪĿ��ڵ�������ѭ��
		}
		else {
			cout << "->";
		}
		for (int j = map.firstNbr(s); j > -1; j = map.nextNbr(s, j)) {						//���������ھ�
			if (map.status(j) == UNDISCOVERED && 
				(map.priority(j) > map.priority(s) + map.weight(s, j))) {		//�������ȼ�
				map.priority(j) = map.priority(s) + map.weight(s, j);
				map.parent(j) = s;
			}
		}
		int temp = 0;
		for (int shortest = INT_MAX, j = 0; j < map.n; j++) {							//ѡ����һ�ڵ�
			if ((map.status(j) == UNDISCOVERED) && (map.priority(j) < shortest)) {
				shortest = map.priority(j);
				temp = j;
			}
		}
		s = temp;
	}
	cout << "�ܳ�Ϊ��" << totalLength << endl;
}

void printPlace() {
	string place[10] =
	{ "��԰����","������","����","�ഺ�㳡","һ��","����¥B��",
		"һ���˶���","��ѵ����","�ֺ��ؽ�ѧԺ","һ��¥" };
	cout << "����ΪУ�ڸ����ص�ı��";
	for (int i = 0; i < 10; i++) {
		cout << "��" << i + 1 << "�� " << place[i] << endl;
	}
}
