/*keyboard.cpp*/

//��������ͼ���������Ե��չ�¯�ģ�����ʵ����̫����
//��ϧ�ⷽ������̫��������

#include <Windows.h>

using namespace std;

void keyboardEvent1(int n);					//ͨ��keybd_event����
void keyboardEvent2(int n);					//������д��Ӳ��ɨ����

int main() {
//	keyboardEvent1(10000);
	keyboardEvent2(10000);
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

void keyboardEvent2(int n) {
	for (int i = 0; i < n; i++) {
		keybd_event('A', 0x1e, 0, 0);
		Sleep(10);
		keybd_event('A', 0x9e, KEYEVENTF_KEYUP, 0);
		Sleep(500);
		keybd_event('W', 0x11, 0, 0);
		Sleep(10);
		keybd_event('W', 0x91, KEYEVENTF_KEYUP, 0);
		Sleep(500);
		keybd_event('D', 0x20, 0, 0);
		Sleep(10);
		keybd_event('D', 0xa0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
	}
	//�ڲ����в�����д��Ӳ��ɨ����󣬵�һ��ģ�ⰴ��������Ч�ˣ���ϧÿ�ζ�ֻ�е�һ����Ч
	//��Ҫ��Ч�����лؿ���̨���л�ȥ- -
}

