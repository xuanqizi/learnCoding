/* POJ 1661 Help Jimmy */
/*	"Help Jimmy" ������ͼ��ʾ�ĳ�������ɵ���Ϸ����ͼ�ԣ�
*	�����а���������Ⱥ͸߶ȸ�����ͬ��ƽ̨����������͵�ƽ̨���߶�Ϊ�㣬�������ޡ�
*	Jimmy������ʱ��0�Ӹ�������ƽ̨��ĳ����ʼ���䣬���������ٶ�ʼ��Ϊ1��/�롣��Jimmy�䵽ĳ��ƽ̨��ʱ����Ϸ��ѡ�����������������ܣ����ܶ����ٶ�Ҳ��1��/�롣
*	��Jimmy�ܵ�ƽ̨�ı�Եʱ����ʼ�������䡣Jimmyÿ������ĸ߶Ȳ��ܳ���MAX�ף���Ȼ�ͻ�ˤ������ϷҲ�������
*	���һ�����򣬼���Jimmy���׵���ʱ���ܵ�����ʱ�䡣
*/
//Input:
//��һ���ǲ������ݵ�����t��0 <= t <= 20����ÿ��������ݵĵ�һ�����ĸ�����N��X��Y��MAX���ÿո�ָ���
//N��ƽ̨����Ŀ�����������棩��X��Y��Jimmy��ʼ�����λ�õĺ������꣬MAX��һ����������߶ȡ�
//��������N��ÿ������һ��ƽ̨����������������X1[i]��X2[i]��H[i]��H[i]��ʾƽ̨�ĸ߶ȣ�X1[i]��X2[i]��ʾƽ̨���Ҷ˵�ĺ����ꡣ
//1 <= N <= 1000��-20000 <= X, X1[i], X2[i] <= 20000��0 < H[i] < Y <= 20000��i = 1..N������������ĵ�λ�����ס�

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct board {
	int x1;
	int x2;
	int h;
	board():
		x1(0),x2(0),h(0){ }
};

bool comp(const board &b1, const board &b2);		//�Զ���ȽϺ���
int boardBelow(int curr,vector<board> v,int x,int max);		//�жϵ�ǰλ���·��Ƿ��а���

int main() {
	int t = 0;
	const int INF = 0x3f3f3f3f;	//���ڱ�ʾ��
	int n, x, y, max;
	cin >> t;					//t�ǲ������ݵ�����
	for (int t1 = 0; t1 < t; t1++) {
		cin >> n >> x >> y >> max;
		vector<int> leftMinTime(n + 1, 0);
		vector<int> rightMinTime(n + 1, 0);
		vector<board> boards(n + 1, board());	
		for (int i = 1; i <= n; i++) {
			cin >> boards[i].x1;
			cin >> boards[i].x2;
			cin >> boards[i].h;
		}
		boards[0].x1 = x;
		boards[0].x2 = x;
		boards[0].h = y;								//0�Ű��ӵĸ߶ȼ�ΪJimmy�ĳ�ʼ�߶�
		sort(boards.begin() + 1, boards.end(), comp);		//�����Ӱ��ո߶Ƚ��н�������
		for (int i = n; i >= 0; i--) {
			//����leftMinTime
			int below = boardBelow(i, boards, boards[i].x1, max);
			if (below == -1) {								//������·�û�а���
				if (boards[i].h > max) {
					leftMinTime[i] = INF;
				}
				else {
					leftMinTime[i] = boards[i].h;
				}
			}
			else {
				leftMinTime[i] = boards[i].h - boards[below].h +
					min(leftMinTime[below] + boards[i].x1 - boards[below].x1,
						rightMinTime[below] + boards[below].x2 - boards[i].x1);
			}
			//����rightMinTime
			below = boardBelow(i, boards, boards[i].x2, max);
			if (below == -1) {
				if (boards[i].h > max) {
					rightMinTime[i] = INF;
				}
				else {
					rightMinTime[i] = boards[i].h;
				}
			}
			else {
				rightMinTime[i] = boards[i].h - boards[below].h +
					min(leftMinTime[below] + boards[i].x2 - boards[below].x1,
						rightMinTime[below] + boards[below].x2 - boards[i].x2);
			}
		}	//i-loop
		cout << leftMinTime[0] << endl;
	}	//t1-loop
	return 0;
}

bool comp(const board &b1, const board &b2) {
	return b1.h > b2.h;							//��������
}

int boardBelow(int curr, vector<board> v, int x,int max) {
	for (int i = 1; i < v.size(); i++) {
		if (i == curr) { continue; }
		if (x >= v[i].x1&&x <= v[i].x2&&v[i].h < v[curr].h) {
			if (abs(v[i].h - v[curr].h) <= max) {
				return i;
			}
		}
	}
	return -1;
}

//����˼·����̬�滮(DP),�����ÿ�����ӵ���˺��Ҷ˵����������ʱ��
//����һ��ʼJimmy���ڳ���Ϊ0��0�Ű����ϣ����ս����ΪleftMinTime[0]

/*		α���룺
if (����k������·�û����������) {
	if (����k�ĸ߶�h(k) > MAX) {
		leftMinTime(k) = ��;
	}
	else {
		leftMinTime(k) = h(k);
	}
else if (����k������·��İ��ӱ��Ϊm) {
	leftMinTime(k) = h(k) - h(m) +
		min(leftMinTime(m) + x1(k) - x1(m), rightMinTime(m) + x2(m) - x1(k));
}
*/
