#include "ari.h";

/*��������Ҫʹ��VS2017���б��룬
��������VS2017����������õ�ԭ�����������������ʱ��Ҫ�½����������
ͬʱ��Ҫ�޸Ŀ���̨���ã��رտ��ٱ༭ģʽ�Ͳ���ģʽ�ſ���������*/

int main() {								//chen
	int loginResult = 0;					//��¼�û���¼�����0ʧ�ܣ�1�ɹ���
	User user;
	int systemContinue = 1;					//��ǳ����Ƿ�������У�0Ϊֹͣ��1Ϊ������

	SetConsoleTitle("Сѧ�����Բ�ϵͳ");

	while (!loginResult) {
		loginResult = loginInterface(&user);
		system("cls");
	}

	
	
	while (systemContinue) {
		if (user_read.isTeacher) {
			systemContinue = teacherInterface(&user);
		}
		else {
			systemContinue = studentInterface(&user);
		}
	}

	save();
	quit();

	return 0;
}