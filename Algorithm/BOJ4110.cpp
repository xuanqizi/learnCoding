/* ����OJ 4110 ʥ�����˵�����-Santa Clau��s Gifts */
/*ʥ���������ˣ��ڳ���A��ʥ������׼���ַ��ǹ��������ж��䲻ͬ���ǹ���ÿ���ǹ����Լ��ļ�ֵ��������
* ÿ���ǹ������Բ�ֳ�����ɢװ��ϴ��ߡ�ʥ�����˵�ѱ¹���ֻ�ܳ���һ���������ǹ�������ʥ����������ܴ��߶���ֵ���ǹ���
*/
/* ���룺
��һ��������������ɣ��ֱ�Ϊ�ǹ�����������n(1 <= n <= 100)��ѱ¹�ܳ��ܵ��������������w��0 < w < 10000�����������ÿո������
����n��ÿ�ж�Ӧһ���ǹ�������������ɣ��ֱ�Ϊһ���ǹ��ļ�ֵ������v������������w���м��ÿո������
*/
//��������ʥ�������ܴ��ߵ��ǹ�������ܼ�ֵ������1λС�������Ϊһ�У��Ի��з�������

#define _CRT_SECURE_NO_WARNINGS 
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Candy {
	int value;
	int weight;
	Candy(int v,int w):
		value(v),weight(w){ }
};

bool comp(const Candy &c1, const Candy &c2);

int main() {
	int n, w;
	int value, weight;
	int i = 0;
	double total = 0.0;
	cin >> n >> w;
	vector<Candy> candies;
	for (i = 0; i < n; i++) {
		cin >> value;
		cin >> weight;
		candies.push_back(Candy(value, weight));
	}
	sort(candies.begin(), candies.end(), comp);		//���ǹ��䰴��ֵ/�����ȴӸߵ�������
	weight = 0;										//���Լ���������
	i = 0;
	while (weight < w && i < n) {
		if (w - weight >= candies[i].weight) {
			total += candies[i].value;
			weight += candies[i++].weight;
		}
		else {
			total += ((w - weight)*1.0 / candies[i].weight) * candies[i].value;
			weight = w;
		}
	}
	printf("%.1f\n", total);
	return 0;
}

bool comp(const Candy &c1, const Candy &c2) {
	double r1 = c1.value / c1.weight;
	double r2 = c2.value / c2.weight;
	return r1 > r2;					//��������
}