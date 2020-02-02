/* Leetcode 10 Regular Expression Matching */
/* Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
*	'.' Matches any single character.
*	'*' Matches zero or more of the preceding element.
*	The matching should cover the entire input string (not partial).
*/

#include <string>
#include <vector>

//ʹ�û����㷨

using namespace std;

class Solution {
public:
	bool isMatch(string s, string p) {
		if (p.empty()) { return s.empty(); }
		bool firstMatch = !s.empty() && (s[0] == p[0] || p[0] == '.');
		if (p.size() >= 2) {
			if (p[1] == '*') {
				return isMatch(s, p.substr(2)) || (firstMatch&&isMatch(s.substr(1), p));
			}	//ǰ��Ϊ*ǰ���ظ�0�ε����������Ϊ*ǰ���ظ�n(n>=1)�ε����
				//��n=1�������isMatch����һ��Ϊn = 0�����
		}
		return firstMatch && isMatch(s.substr(1), p.substr(1));
	}
};