#ifndef _CALCULATE_H_
#define _CALCULATE_H_

#define IsOpt(x) ((x=='+')||(x=='-')||(x=='*')||(x=='/'))

bool paren(const char* string,int len);			//�ж������Ƿ�ƥ��
bool checkChar(const char* string, int len);	//����Ƿ��зǷ�����
bool checkInput(const char* string, int len);	//�������ı��ʽ�Ƿ�Ϸ�
bool checkOpt(const char* string, int len);		//���������ʽ�Ƿ���������������
void toRPN(const char* exp, int len,string& rpn);		
bool isDigit(char c);							//�ж��ַ��Ƿ�Ϊ����
int orderBetween(const char top, const char c);	//�Ƚ�����������ȼ���С
int getPri(char c);								//��ȡ��������ȼ���С��ֵ
float calcu(float opnd1, char op, float opnd2);	//��Ԫ����
float rpnCal(string rpn);						//�����沨��ʽ
float readNumber(string str, Stack<float> &opnd);	//��ȡ����

#endif
