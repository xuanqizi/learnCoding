#include "path.h"

int main() {
	GraphMatrix<string, string> map = setMap();
	int begin = 0;
	int end = 0;
	printPlace();
	cout << "����������ţ�";
	cin >> begin;
	cout << "�������յ��ţ�";
	cin >> end;
	findPath(map, begin, end);
	return 0;
}