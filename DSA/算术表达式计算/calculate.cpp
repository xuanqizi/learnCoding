#include "Stack.h"
#include "Stack.cpp"
#include "calculate.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool paren(const char* string,int len) {
	Stack<char> s = Stack<char>();										//����������ŵ�ջ
	for (int i = 0; i < len; i++) {
		if (string[i] == '(') {				//������ַ�Ϊ�����ţ�ѹջ
			s.push(string[i]);							
		}
		else if (string[i] == ')') {		//������ַ�Ϊ������
			if (s.empty()) { return false; }			//��ջ�գ���ƥ��
			s.pop();									//���򣬵���ջ������
		}
	}
	return s.empty() ? true : false;				//������������ջΪ�գ���ȫ��ƥ�䣬���ǿգ���δƥ��
}

bool checkInput(const char* string, int len) {
	if (!paren(string,len)) {
		cout << "������ʽ�����Ų�ƥ��" << endl;
		system("pause");
		return false;
	}
	if (!checkChar(string, len)) { 
		cout << "������ʽ�к��зǷ�����" << endl;
		system("pause");
		return false;
	}
	if (!checkOpt(string, len)) {
		cout << "������ʽ��ʽ����" << endl;
		system("pause");
		return false;
	}
	return true;
}

bool checkChar(const char* string, int len) {
	char validChar[] = { '0','1','2','3','4','5','6','7'
						,'8','9','+','-','*','/','#','.','(',')' };
	bool valid = true;
	for (int i = 0; i < len; i++) {
		valid = false;
		for (int j = 0; j < 18; j++) {
			if (string[i] == validChar[j]) {
				valid = true;
				break;
			}
		}
		if (!valid) { return false; }
	}
	return true;
}

bool checkOpt(const char* string, int len) {
	bool isOpt = false;
	for (int i = 0; i < len; i++) {
		if (IsOpt(string[i])) {
			if (isOpt) {							//����һ���ַ�ҲΪ������
				return false;
			}
			isOpt = true;
		}
		else {
			isOpt = false;
		}
	}
	return true;
}

void toRPN(const char* exp, int len, string& rpn) {									
	Stack<char> optr = Stack<char>();				//������ջ
	
	optr.push('z');									//ѹ��һ�����ȼ�Ϊ0���ַ�,���һ��ʼ�ĶԱ�����

	for (int i = 0; i < len; i++) {
		if (isDigit(exp[i])) {
			rpn += exp[i];							//��������֣���ֱ�Ӽ����ַ�����
		}
		else {
			rpn += " ";								//�������żӿո񣨱��������沨��ʽ�е���������
			int order = orderBetween(optr.top(), exp[i]);
			if (order == -1) {		//ջ��������ȵ�ǰ����������(��ջ��Ϊ������)
				optr.push(exp[i]);								//���ջ
			}
			else if (order == 0) {	//������������
				while (optr.top() != '(') {
					rpn += optr.pop();							//����ֱ����(��Ϊֹ
				}
				optr.pop();										//��������Ҳ����
			}
			else if (order == 1) {
				rpn += optr.pop();
				optr.push(exp[i]);
			}
		}
	}
	while (optr.top() != 'z') {									//��������ջ������ʣ�����������
		rpn += optr.pop();
	}
}

bool isDigit(char c) {
	const char digit[] = { '0','1','2','3','4','5',
							'6','7','8','9','.' };			//δ����С�������
	for (int i = 0; i < 11; i++) {
		if (digit[i] == c) {
			return true;
		}
	}
	return false;
}

int orderBetween(const char top, const char cur) {
	/*����ǰ���ȼ�����ջ�����򷵻�-1����curΪ�����ţ�����0�����򷵻�1*/
	if (cur == ')') {
		return 0;
	}
	if (top == '(') { return -1; }
	return getPri(cur) > getPri(top) ? -1 : 1;
}

int getPri(char c) {
	if (c == 'z') {
		return 0;
	}
	if (c == '+' || c == '-') {
		return 1;
	}
	if (c == '*' || c == '/') {
		return 2;
	}
	if (c == '#') {
		return 3;
	}
	if (c == '(') { return 4; }
	return 1;
}

float calcu(float opnd1, char op, float opnd2) {
	switch (op) {
	case '+':return opnd1 + opnd2;
	case '-':return opnd1 - opnd2;
	case '*':return opnd1 * opnd2;
	case '/':return opnd1 / opnd2;
	default:exit(-1);
	}
}

float rpnCal(string rpn) {
	Stack<float> opnd = Stack<float>();				//������ջ
	string str;										//�����ݴ���
	float opnd1 = 0.0;
	float opnd2 = 0.0;
	for (size_t i = 0; i < rpn.size(); i++) {
		if (isDigit(rpn[i])) {
			str += rpn[i];
		}
		else {
			if (!str.empty()) {
				readNumber(str, opnd);
				str.clear();
			}
			if (rpn[i] == '#') {									//����һԪ������
				opnd1 = opnd.pop();
				opnd1 = 0.0 - opnd1;
				opnd.push(opnd1);
			}
			else if (rpn[i] != ' ') {													//��Ԫ�����
				opnd2 = opnd.pop();										//���˳��ķ��ұߣ����˳��ķ����
				opnd1 = opnd.pop();
				char optr = rpn[i];
				opnd.push(calcu(opnd1, optr, opnd2));					//����opnd.push(opnd.pop(),optr,opnd.pop())
																		//������Ҳ��֪��Ϊʲô
			}
		}
	}
	return opnd.pop();
}

float readNumber(string str, Stack<float> &opnd) {
	stringstream ss;
	float number = 0.0;
	ss << str;
	ss >> number;
	opnd.push(number);
	return number;
}