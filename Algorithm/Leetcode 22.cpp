/* Leetcode 22 Generate Parentheses */
/*����n�����������ŵĶ���������д��һ��������ʹ���ܹ��������п��ܵĲ�����Ч��������ϡ�*/

//����ʹ�û����㷨

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> v;
		backtrack(v, "", 0, 0, n);
		return v;
	}

	void backtrack(vector<string>& v, string curr, int open, int close, int max) {
		if (curr.size() == max * 2) {
			v.push_back(curr);
			return;
		}
		if (open < max) {
			backtrack(v, curr + "(", open + 1, close, max);
		}
		if (close < open) {
			backtrack(v, curr + ")", open, close + 1, max);
		}
	}
};