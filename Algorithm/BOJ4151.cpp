/* ����OJ 4151 ��Ӱ�� */
/*��ѧ����Ӱ���ڱ���ٰ�! ���죬�ڱ�����ط��˶ಿ��Ӱ������ÿ����Ӱ�ķ�ӳʱ�����䣬
�����ص��ĵ�Ӱ������ͬʱ�����˵�����غϣ��������������Կ����ٲ���Ӱ��*/

//˼·��̰���㷨������ѡ�����ʱ����ĵ�Ӱ

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Movie {
	int begin;
	int end;
	Movie(int a, int b) :
		begin(a), end(b){ }
};

bool comp(const Movie &m1, const Movie &m2) { return m1.end < m2.end; }

int main() {
	int n;
	int i;
	int begin, end;
	vector<Movie> movies;
	while (cin >> n) {
		if (n == 0) { break; }
		int count = 0;
		for (i = 0; i < n; i++) {
			cin >> begin >> end;
			movies.push_back(Movie(begin, end));
		}
		sort(movies.begin(), movies.end(), comp);		//������ʱ������
		end = 0;
		for (int i = 0; i < n; i++) {
			if (movies[i].begin >= end) {
				end = movies[i].end;
				count++;
			}
		}
		cout << count << endl;
		movies.clear();
	}
	return 0;
}