/* Leetcode 24 Swap Nodes in Pairs */
/**
* Given a linked list, swap every two adjacent nodes and return its head.
* You may not modify the values in the list's nodes, only nodes itself may be changed.
*/

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
	ListNode(int x):val(x),next(NULL){ }
};

class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		ListNode* pHead = new ListNode(-1);		//�Զ���һ��ͷ�ڵ�
		pHead->next = head;
		ListNode* prev = pHead;
		ListNode* first = NULL;
		ListNode* second = NULL;
		while (head && head->next) {
			//��ֵ
			first = head;
			second = head->next;
			//����
			first->next = second->next;		//1->3
			second->next = first;			//2->1
			prev->next = second;			//prev->2
			//����head��prev��ֵ
			prev = first;
			head = prev->next;
		}
		return pHead->next;
	}
};