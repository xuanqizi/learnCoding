#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <hash_map>
#include <fstream>
#include <streambuf>

#define N_CHAR ((0x80))

#define IsChar(x) ((x) >= 0x20)
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define IsLeaf(x) (!( HasLChild(x) || HasRChild(x) ))

using namespace std;

struct HuffChar {
public:
	char ch;					//�ַ�
	int weight;					//Ƶ��
	HuffChar(char c, int w) : ch(c), weight(w) { };
	bool operator< (HuffChar const & hc) { return weight < hc.weight; }		//���������
	bool operator> (HuffChar const & hc) { return weight > hc.weight; }
	bool operator== (HuffChar const & hc) { return weight == hc.weight; }
	bool operator!= (HuffChar const & hc) { return weight != hc.weight; }
};

struct HTNode {								//���������Ľ��
public:
	HTNode* lChild;
	HTNode* rChild;
	HTNode* parent;
	HuffChar ch;
	HTNode(HuffChar c) :
		ch(c), lChild(NULL), rChild(NULL), parent(NULL){ }
	HTNode(HuffChar c,HTNode* lc,HTNode* rc, HTNode* p):
		ch(c),lChild(lc),rChild(rc),parent(p){ }
	HTNode* insertAsLC(HuffChar const & c);
	HTNode* insertAsRC(HuffChar const & c);
	bool operator< (HTNode const & n) { return ch.weight < n.ch.weight; }
	bool operator> (HTNode const & n) { return ch.weight > n.ch.weight; }
	bool operator== (HTNode const & n) { return ch.weight == n.ch.weight; }
	bool operator!= (HTNode const & n) { return ch.weight != n.ch.weight; }
};

struct HuffTree {							//��������
private:
	HTNode* _root;
	int _size;
public:
	HuffTree() :_root(NULL), _size(0){ }
	HTNode* root() { return _root; }
	void insertAsRoot(HuffChar ch);
	HTNode* attachAsLC(HuffTree* & t);		//�����������ӵ��������
	HTNode* attachAsRC(HuffTree* & t);		//�����������ӵ������Ҳ�
};

typedef list<HuffTree*> HuffForest;			//������ɭ��
typedef stdext::hash_map<char,string> HuffTable;		//�����������
typedef stdext::hash_map<string, char> RTable;			//��ת�����������


void printError(int situ);		//���������Ϣ
int* statistics(char* textFile);	//ͳ���ַ�����Ƶ��,����Ƶ������
HuffForest* initForest(int* statistics);		//��ʼ��������ɭ��
HuffTree* buildTree(HuffForest* forest);		//������������
HuffTree* findMin(HuffForest* forest);			//�ҳ�������ɭ���и���Ȩֵ��С����
HuffTable buildTable(HuffTable table, HTNode* node,string code);		//���������
RTable buildTable(RTable table, HTNode* node, string code, int & len);		//���������,����ȡ����볤��

#endif
