#include "huffman.h"
#include "decode.h"
#include <fstream>

bool decode() {
	char filename[30];
	char targetName[30];
	cout << "���������ѹ���ļ�����";
	cin >> filename;
	cout << "������Ŀ���ļ�����";
	cin >> targetName;
	int* stat = readStat(filename);
	HuffForest* forest = initForest(stat);
	HuffTree* tree = buildTree(forest);
	RTable table;
	int maxLength = 0;
	table = buildTable(table, tree->root(), "", maxLength);
	fileDecoding(filename, targetName, table, maxLength);
	cout << "��ѹ�ɹ����ļ���Ϊ��" << targetName << endl;
	return true;
}

int* readStat(char* filename) {
	char c;			//���Զ�ȡ�ַ�
	int sta;			//���Զ�ȡƵ��ֵ
	int* stat = new int[N_CHAR];		//��¼Ƶ�ʵ�����
	FILE* fp = fopen(filename, "r");
	while (true) {
		fscanf(fp, "%c", &c);
		if (c == '\n') {					
			break;
		}
		fscanf(fp, "%d", &sta);
		if (sta == '\n') {
			break;
		}
		stat[c - 0x20] = sta;
	}
	return stat;
}

void fileDecoding(char* filename, char* targetName, RTable table,int maxLength) {
	ifstream infile;
	ofstream outfile;
	infile.open(filename, ios::in);
	outfile.open(targetName,ios::out);
	string data;
	string code;
	getline(infile, data);			//��ȡ֮ǰ��ͳ����Ϣ���ٴ˴���Ч��
	getline(infile, data);			//��ȡ�洢�ı���
	for (size_t len = data.length(), i = 0; i < len; i++) {
		for (;;) {
			code += data[i];
			if (table.count(code)) {		//�ҵ������Ӧ���ַ�
				char c = table[code];
				outfile << c;
				break;
			}
			i++;
		}
		code.clear();
	}
	infile.close();
	outfile.close();
}
