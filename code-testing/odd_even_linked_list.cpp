#include <iostream>
#include <cmath>

// Definition for singly-linked list.
struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

ListNode* oddEvenList(ListNode* head) 
{
	  if (!head || !head->next || !head->next->next)
    return head;

    ListNode* head_next = head->next;
	int num = 0;
	ListNode* curr = head;
	ListNode* curr_next = head->next;
	ListNode* curr_next_next = head->next->next;

	while (curr_next_next) {
        std::cout << curr->val << ", " << curr_next->val << "," << curr_next_next->val << std::endl;
		curr->next = curr_next_next;
		num++;
		curr = curr_next;
		curr_next = curr_next_next;
		curr_next_next = curr_next_next->next;

        
	}

        std::cout << curr->val << ", " << curr_next->val << "," << "num:"<< num <<std::endl;
	if (num %2)
        curr_next->next = head_next;
	else			
        curr->next = head_next;
	
    return head;
}



int main() {

	ListNode v1(1);
	ListNode v2(2);
	ListNode v3(3);
	ListNode v4(4);
	ListNode v5(5);
	ListNode v6(6);
	ListNode v7(7);
	ListNode v8(8);
	ListNode v9(9);

	v1.next = &v2;
	v2.next = &v3;
	v3.next = &v4;
	v4.next = &v5;
	

	oddEvenList(&v1);
	return 0;
}
