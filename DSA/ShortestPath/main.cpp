#include "path.h"

int main() {
	GraphMatrix<string, string> map;
	setMap(map);
	int begin = 0;
	int end = 0;
	printPlace();
	cout << "����������ţ�";
	cin >> begin;
	cout << "�������յ��ţ�";
	cin >> end;
	findPath(map, begin-1, end-1);
	return 0;
}