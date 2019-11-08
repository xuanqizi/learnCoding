#ifndef _BINNODE_H_
#define _BINNODE_H_

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p)?(p)->height:-1)

template <typename T> struct BinNode {
	BinNodePosi(T) parent, lChild, rChild;
	T data;
	int size();
	int height;
	template <typename T> BinNode<T>(T const &e, BinNode<T> parent);
	BinNodePosi(T) insertAsLC(T const &);
	BinNodePosi(T) insertAsRC(T const &);
	BinNodePosi(T) succ();									//(�������������)��ǰ�ڵ��ֱ�Ӻ��
	template <typename VST> void travLevel(VST &);			//������α���
	template <typename VST> void travPre(VST &);			//�����������
	template <typename VST> void travIn(VST &);				//�����������
	template <typename VST> void travPost(VST &);			//�����������
};

#endif // !_BINNODE_H_

