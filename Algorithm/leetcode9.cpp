/* Leetcode 9 Palidrome Number */
/* Determine whether an integer is a palindrome.
*  An integer is a palindrome when it reads the same backward as forward.*/

//˼·������һ������ַ�ת����ǰһ����жԱ�

class Solution {
public:
	bool isPalindrome(int x) {
		if (x == 0) { return true; }
		if (x < 0 || x % 10 == 0) { return false; }	//�ȴ���x<0��ĩλ��0���������
		int revert = 0;
		while (x > revert) {
			revert *= 10;
			revert += x % 10;
			x /= 10;
		}
		//λ��Ϊż��ʱ���Ƚ�ǰһ�����һ���Ƿ�һ��
		//λ��Ϊ����ʱ������ת����������һλ������ԭ�����бȽ�
		return (x == revert || x == revert / 10);
	}
};