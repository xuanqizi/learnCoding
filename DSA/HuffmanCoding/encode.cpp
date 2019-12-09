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
	for (int i = 0; i < N_CHAR ; i++) {
		if (stat[i] > 0) {
			out << (char)i;
			out << stat[i];
		}
	}
	out << '^';				//���Ƶ�ʱ��ֽ���
	out.close();
	return true;
}

void fileEncoding(char* textFile, HuffTable table, char* targetFile) {
	ifstream infile;				//�����ļ���
	infile.open(textFile, ios::in);
	string data;
	string output;
	char ch;
	while (infile.get(ch)) {		//�˴���ʹ�� infile >> data ��ԭ�������ַ����޷���ȡ�ո�
		data += ch;
	}
	for (size_t len = data.length(), i = 0; i < len; i++) {
		output += table[data[i]];
	}
	fileWriting(targetFile, output);
}

void fileWriting(char* targetFile, string output) {
	ofstream outfile;
	outfile.open(targetFile, ios::app);
	const int len = output.length();
	outfile << len;
	char data = 0;						//��outputÿ8λת��Ϊchar��
	unsigned char and_bit[] = { 0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE };
										//�ֱ��Ӧ01111111 -> 11111110
	unsigned char or_bit[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
										//�ֱ��Ӧ10000000 -> 00000001
	int i = 0;
	for (i = 0; i < len; i++) {
		if (output[i] == '0') {
			data &= and_bit[i % 8];		//��char�ĵ� i%8 λ��Ϊ0
		}
		else {
			data |= or_bit[i % 8];		//��char�ĵ� i%8 λ��Ϊ1
		}
		if (i % 8 == 7) {
			outfile << data;
			data = 0;
		}
	}
	if (i - 1 % 8 != 7) {
		outfile << data;
	}
	outfile.close();
}