/* Leetcode 19 Remove Nth Node From End of List */
/*����һ������ɾ������ĵ����� n ���ڵ㣬���ҷ��������ͷ��㡣*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x):
		val(x),next(NULL){ }
};

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* dummy = new ListNode(0);		//����һ���ƽ����Ϊ����ͷ
		dummy->next = head;						//���Լ򻯲����������
		ListNode *p1 = dummy, *p2 = dummy;
		for (int i = 0; i <= n; i++) {
			p1 = p1->next;
		}
		while (p1) {							//����״̬��p1ָ��ս�㣬p2ָ��Ҫɾ������ǰ��
			p1 = p1->next;
			p2 = p2->next;
		}
		ListNode* temp = p2->next->next;
		p2->next = temp;
		return dummy->next;
	}
};