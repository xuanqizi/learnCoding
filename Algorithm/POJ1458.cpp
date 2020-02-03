/* POJ 1458 Common Subsequence */
/*A subsequence of a given sequence is the given sequence with some elements (possible none) left out. 
* Given a sequence X = < x1, x2, ..., xm > another sequence Z = < z1, z2, ..., zk > is a subsequence of X 
* if there exists a strictly increasing sequence < i1, i2, ..., ik > of indices of X such that for all j = 1,2,...,k, xij = zj. 
* For example, Z = < a, b, f, c > is a subsequence of X = < a, b, c, f, b, c > with index sequence < 1, 2, 4, 6 >. 
* Given two sequences X and Y the problem is to find the length of the maximum-length common subsequence of X and Y.*/

//˼·����̬�滮(DP)
//P(i,j)��ʾs1[i]��ǰ��s2[j]��ǰ(����������)���ַ������γɵĹ����Ӵ�����
//�߽�������P(0,n)=0,P(n,0)=0
//������Ŀ�ο���Leetcode 10

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {
	string s1, s2;
	while (cin >> s1 >> s2) {
		int len1 = s1.size();
		int len2 = s2.size();
		vector<vector<int> > dp(len1 + 1, vector<int>(len2 + 1, 0));//POJʹ��G++��������<vector<int> >��������һ���ո�
		for (int i = 1; i <= len1; i++) {				//��0�к͵�0�о�Ϊ0��������в���
			for (int j = 1; j <= len2; j++) {
				if (s1[i - 1] == s2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else {
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		cout << dp[len1][len2] << endl;
	}
	return 0;
}