#include "Stack.h"
#include <cstdio>
#include <iostream>

using namespace std;

/*�������ջ��ɾ������ʱֻ��ȥ�޸�ջ����λ�ã���û�н�ԭ�е������޸Ļ�0*/

template<typename T> Stack<T>::Stack() {
	topPos = -1;		//�趨ջ��λ��Ϊ-1������ջ��
	memset(arr, 0, STACKSIZE);
}

template<typename T> void Stack<T>::push(T data) {
	arr[++topPos] = data;
}

template<typename T> T Stack<T>::pop() {
	if (topPos == -1) {								//���ջΪ��ջ����ʾ
		printf("No element in current stack.");
		return -1;
	}
	return arr[topPos--];
}

template<typename T> T Stack<T>::top() const {
	if (topPos == -1) {
		printf("No element in current stack.");
		return -1;
	}
	return arr[topPos];
}

template<typename T> bool Stack<T>::empty() const{
	if (topPos == -1) { return true; }
	return false;
}

template<typename T> int Stack<T>::size() const {
	return topPos + 1;
}

template<typename T> void Stack<T>::clear(){
	topPos = -1;
}
