#ifndef _STACK_H_
#define _STACK_H_

#define STACKSIZE 100

template<typename T> class Stack {
protected:
	int topPos;					//ջ������λ��
	T arr[STACKSIZE];			//���Դ洢���ݵ�����
public:
	Stack();					//���캯��
	void push(T data);
	T top() const;
	T pop();
	bool empty() const;
	int size() const;
	void clear();
};

#endif
