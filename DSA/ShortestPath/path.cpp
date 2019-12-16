#include "path.h"
#include "graph.cpp"
#include <stack>

void setMap(GraphMatrix<string, string> & map) {
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
}

void findPath(GraphMatrix<string, string> map, int s, int t) {
	/*���*/
	map.reset();
	map.priority(s) = 0;
	for (int i = 0; i < map.n; i++) {
		map.status(s) = VISITED;
		if (map.parent(s) != -1) {
			map.type(map.parent(s), s) = TREE;
		}
		for (int j = map.firstNbr(s); j > -1; j = map.nextNbr(s, j)) {						//���������ھ�
			if (map.status(j) == UNDISCOVERED && 
				(map.priority(j) > map.priority(s) + map.weight(s, j))) {					//�������ȼ�
				map.priority(j) = map.priority(s) + map.weight(s, j);
				map.parent(j) = s;
			}
		}
		for (int shortest = INT_MAX, j = 0; j < map.n; j++) {								//ѡ����һ�ڵ�
			if ((map.status(j) == UNDISCOVERED) && (map.priority(j) < shortest)) {
				shortest = map.priority(j);
				s = j;
			}
		}
	}
	/*��¼·��*/
	int totalLength = 0;								//�ܳ�
	stack<int> S;										//��¼·����ջ
	int p1 = 0, p2 = 0;									//�����ݴ�������
	S.push(t);
	while (map.parent(t) != -1) {						//�Կ�׷�ݵ���һ�ڵ�
		S.push(map.parent(t));
		t = map.parent(t);
	}
	/*���·���ͳ���*/
	p1 = S.top();
	S.pop();
	cout << map.vertex(p1) << "->";
	while (!S.empty()) {
		p2 = S.top();
		cout << map.edge(p1, p2) << "->";
		totalLength += map.weight(p1, p2);
		cout << map.vertex(p2);
		if (S.size() > 1) {
			cout << "->";
		}
		else {
			cout << endl;
		}
		p1 = p2;
		S.pop();
	}
	cout << "�ܳ�Ϊ��" << totalLength << endl;
}

void printPlace() {
	string place[10] =
	{ "��԰����","������","����","�ഺ�㳡","һ��","����¥B��",
		"һ���˶���","��ѵ����","�ֺ��ؽ�ѧԺ","һ��¥" };
	cout << "����ΪУ�ڸ����ص�ı��" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "��" << i + 1 << "�� " << place[i] << endl;
	}
}

bool checkInput(int begin, int end, int res) {
	if (res == -1) { return false; }
	if (begin < 1 || begin>10) {
		cout << "���������ų�����Χ" << endl;
		return false;
	}
	if (end < 1 || end>10) {
		cout << "������յ��ų�����Χ" << endl;
		return false;
	}
	if (begin == end) {
		cout << "վ��ԭ�ز���������~" << endl;
		return false;
	}
	return true;
}

int inputNum(int & begin, int & end) {
	cout << "����������ţ�";
	cin >> begin;
	if (cin.fail()) {
		cout << "�����˷Ƿ�����" << endl;
		return -1;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << "�������յ��ţ�";
	cin >> end;
	if (cin.fail()) {
		cout << "�����˷Ƿ�����" << endl;
		return -1;
	}
	return 0;
}

/*Ŀǰ�����ֻ֧�����¼������*/
//��1��	Ҫ����������ʱ�������ַ���
//��2��	��������ֳ�����1-10�ķ�Χ
//��3��	���������Ǹ������ᱻ�Զ���Ϊ����������ִ�г���
//��4��	���������յ���ͬ�����ض���Ӧ
