#include "huffman.h"
#include "encode.h"
#include "decode.h"


int main() {
	int mode = 0;			//��Ҫ���еĲ���ģʽ��1Ϊѹ����2Ϊ��ѹ��
	cout << "������Ҫ���еĲ�����" << endl;
	cout << "��1��ѹ��" << endl;
	cout << "��2����ѹ" << endl;
	scanf("%d", &mode);
	switch (mode) {
	case 2:decode(); break;
	case 1:encode(); break;
	default:printError(1);
	}
	system("pause");
	return 0;
}