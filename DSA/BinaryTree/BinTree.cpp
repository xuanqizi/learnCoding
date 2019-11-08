#include "BinNode.h"
#include <iostream>

using namespace std; 

template <typename T> class BinTree {
protected:
	int _size;
	BinNodePosi(T) _root;
	virtual int updateHeight(BinNodePosi(T) x);					//����x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x);					//����x�������ȵĸ߶�
public:
	int size() const { return _size; }							//const��ʾ���������޸���ĳ�Ա
	bool empty() const { return !_root; }
	BinNodePosi(T) root() { return _root; }
};

template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x) {
	return x->height = stature(x->lChild) > stature(x->rChild) ?
		stature(x->lChild) + 1 : stature(x->rChild) + 1;
}

template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
	while (x) {
		if (x->height == updateHeight(x)) {						//���߶�δ��
			break;												//���˳�ѭ��
		}
		x = x->parent;											//����������
	}
}

template <typename T> void preTrav(BinNodePosi(T) pRoot) {		//��������ǰ��������ݹ�ʵ�֣�
	if (!pRoot) { return; }
	/*do something*/
	cout << pRoot->data << endl;
	
	preTrav(pRoot->lChild);
	preTrav(pRoot->rChild);
}

template <typename T> void inTrav(BinNodePosi(T) pRoot) {		//������������������ݹ�ʵ�֣�
	if (!pRoot) { return; }
	inTrav(pRoot->lChild);
	/*do something*/
	cout << pRoot->data << endl;
	inTrav(pRoot->rChild);
}

template <typename T> void postTrav(BinNodePosi(T) pRoot) {		//�������ĺ����������ݹ�ʵ�֣�
	if (!pRoot) { return; }
	postTrav(pRoot->lChild);
	postTrav(pRoot->rChild);
	/*do something*/
	cout << pRoot->data << endl;
}

