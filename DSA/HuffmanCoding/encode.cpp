#include "huffman.h"
#include "encode.h"

bool encode() {
	char filename[30];
	char targetName[30];
	cout << "�������ѹ�����ļ�����";
	cin >> filename;
	cout << "������ѹ���ļ�����";
	cin >> targetName;
	int* stat = statistics(filename);				//ͳ���ַ�����Ƶ��
	HuffForest* forest = initForest(stat);			//��ʼ��Huffmanɭ��
	HuffTree* tree = buildTree(forest);				//����Huffman��
	HuffTable table;
	table = buildTable(table, tree->root(), "");	//���������
	if (!printStat(stat, targetName)) {
		return false;
	}
	fileEncoding(filename, table, targetName);
	cout << "ѹ���ɹ�" << endl;
	return true;
}

bool printStat(int* stat, char* targetFile) {
	ofstream out;
	out.open(targetFile,ios::out);
	for (int i = 0x20; i < N_CHAR + 0x20; i++) {
		if (stat[i - 0x20] > 0) {
			out << (char)i;
			out << stat[i - 0x20];
		}
	}
	out << endl;				//���Ƶ�ʱ��ֽ���
	out.close();
	return true;
}

void fileEncoding(char* textFile, HuffTable table, char* targetFile) {
	ifstream infile;				//�����ļ���
	ofstream outfile;				//д���ļ���
	infile.open(textFile, ios::in);
	outfile.open(targetFile, ios::app);
	string data;
	string output;
	char ch;
	while (infile.get(ch)) {		//�˴���ʹ�� infile >> data ��ԭ�������ַ����޷���ȡ�ո�
		data += ch;
	}
	for (size_t len = data.length(), i = 0; i < len; i++) {
		output += table[data[i]];
	}
	outfile << output;
}

//HashTable�Ľ�����������--���α�������ͬ