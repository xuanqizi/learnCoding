/*keyboard.cpp*/

//��������ͼ���������Ե��չ�¯�ģ�����ʵ����̫����
//��ϧ�ⷽ������̫��������

#include <Windows.h>

using namespace std;

void keyboardEvent1(int n);					//ͨ��keybd_event����

int main() {
	keyboardEvent1(10000);
	return 0;
}

void keyboardEvent1(int n) {
	for (int i = 0; i < n; i++) {
		keybd_event('A', 0, 0, 0);
		keybd_event('A', 0, KEYEVENTF_KEYUP, 0);
		Sleep(500);
		keybd_event('W', 0, 0, 0);
		keybd_event('W', 0, KEYEVENTF_KEYUP, 0);
		Sleep(500);
		keybd_event('D', 0, 0, 0);
		keybd_event('D', 0, KEYEVENTF_KEYUP, 0);
		Sleep(500);
	}
}