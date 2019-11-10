#include "BinNode.h"

using namespace std; 

template <typename T> class BinTree {
protected:
	int _size;
	BinNodePosi(T) _root;
	virtual int updateHeight(BinNodePosi(T) x);					//����x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x);					//����x�������ȵĸ߶�
public:
	BinTree(): _size(0),_root(NULL){ }							//���캯��
	~BinTree() {												//��������
		if (0 < _size) {
			remove(_root);
		} 
	}
	int size() const { return _size; }							//const��ʾ���������޸���ĳ�Ա
	bool empty() const { return !_root; }
	BinNodePosi(T) root() { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e);					//������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const & e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const & e);
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T);	//T��Ϊx������������,�����T
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T);	//T��Ϊx�����������룬�����T
	int remove(BinNodePosi(T) x);								//ɾ����x���ڵ�����������ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi(T) x);						//������x�ӵ�ǰ����ɾ����������ת��Ϊһ�Ŷ�������
	template<typename VST> void travLevel(VST & visit) {
		if (_root) {
			_root->travLevel(visit);
		}
	}
	template<typename VST> void travPre(VST & visit) {
		if (_root) {
			_root->travPre(_root,visit);
		}
	}
	template<typename VST> void travIn(VST & visit) {
		if (_root) {
			_root->travIn(_root,visit);
		}
	}
	template<typename VST> void travPost(VST & visit) {
		if (_root) {
			_root->travPost(_root,visit);
		}
	}
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

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const & e) {
	_size = 1;
	return _root = new BinNode<T>(e);
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x,T const & e) {
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const & e) {
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

template <typename T> BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& T) {
	x->lChild = T->_root;
	x->lChild->parent = x;
	_size += T->_size;
	updateHeightAbove(x);
	T->_root = NULL;
	T->_size = 0;
	T = NULL;
	return x;
}

template <typename T> BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& T) {
	x->rChild = T->_root;
	x->rChild->parent = x;
	_size += T->_size;
	updateHeightAbove(x);
	T->_root = NULL;
	T->_size = 0;
	T = NULL;
	return x;
}

template <typename T> int BinTree<T>::remove(BinNodePosi(T) x) {
	FromParentTo(*x) = NULL;			//���丸�ڵ�ָ������ָ����Ϊ��
	updateHeightAbove(x);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template <typename T> static int removeAt(BinNodePosi(T) x) {
	if (!x) { return 0; }
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);
	return n;
}

template <typename T> BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {
	FromParentTo(x) = NULL;
	updateHeightAbove(x);
	BinTree<T>* S = new BinTree<T>;
	S->_root = x;
	x->parent = NULL;
	S->_size = x->size();
	_size -= S->_size;
	return S;
}
