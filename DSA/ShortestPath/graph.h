#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <limits.h>
#include <vector>

using namespace std;

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;			
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;

template <typename Tv, typename Te> class Graph {
public:
	virtual void reset() = 0;
	//����
	int n;				//��������
	virtual int insert(Tv& const) = 0;		//���붥�㣬���ر��
	virtual Tv remove(int) = 0;		//ɾ�����㼰������ߣ����ظö�������
	virtual Tv& vertex(int) = 0;	//��ȡ���������
	virtual int inDegree(int) = 0;
	virtual int outDegree(int) = 0;
	virtual int& dTime(int) = 0;
	virtual int& fTime(int) = 0;
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;
	//��
	int e;				//������
	virtual bool exists(int, int) = 0;
	virtual void insert(Te const&, int, int, int) = 0;
	virtual Te remove(int, int) = 0;
	virtual EType& type(int, int) = 0;
	virtual Te& edge(int, int) = 0;		//��ȡ�ߵ�����
	virtual int& weight(int, int) = 0;
	//�㷨
	virtual void dijkstra(int) = 0;					//���·��Dijkstra�㷨
};

template <typename Tv> struct Vertex {
	Tv data;
	int inDegree, outDegree;
	VStatus status;
	int dTime, fTime;
	int parent;
	int priority;
	Vertex(Tv & const d):
		data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),
		dTime(-1),fTime(-1),priority(INT_MAX){ }

};

template <typename Te> struct Edge {
	Te data;
	int weight;
	EType type;
	Edge(Te const & d, int w):
		data(d),weight(w),type(UNDETERMINED){ }
};

template <typename Tv, typename Te> class GraphMatrix : public Graph<Tv, Te> {
private:
	vector<Vertex<Tv>> V;		//���㼯
	vector<vector<Edge<Te>*>> E;//�߼�
public:
	int n;
	int e;
	GraphMatrix() { n = e = 0; }
	~GraphMatrix() {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				delete E[j][k];
			}
		}
	}
	void reset();
	//�������
	Tv & vertex(int i) { return V[i].data; }
	int inDegree(int i) { return V[i].inDegree; }
	int outDegree(int i) { return V[i].outDegree; }
	VStatus & status(int i) { return V[i].status; }
	int & dTime(int i) { return V[i].dTime; }
	int & fTime(int i) { return V[i].dTime; }
	int & parent(int i) { return V[i].parent; }
	int & priority(int i) { return V[i].priority; }
	int nextNbr(int i, int j);				//��Ѱ�ҵ��ھ�j��������һ���ھ�
	int firstNbr(int i) { return nextNbr(i, n); }
	int insert(Tv& const);
	Tv remove(int i);
	//�߲���
	bool exists(int i, int j);
	Te & edge(int i, int j) { return E[i][j]->data; }
	EType & type(int i, int j) { return E[i][j]->type; }
	int & weight(int i, int j) { return E[i][j]->weight; }
	void insert(Te const& edge, int w, int i, int j);
	Te remove(int i, int j);
	//�㷨
	void dijkstra(int);
};

#endif