#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) {
        val = x;
        next = NULL;
    }
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        ListNode* before = NULL;
        ListNode* current = head;
        ListNode* next = NULL;

        while (current != NULL) {
            next = current->next;      // save next node
            current->next = before;    // reverse link
            before = current;          // move before
            current = next;            // move current
        }

        return before; // new head
    }
};

void printList(ListNode* head) {
    while (head != NULL) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);

    cout << "Original list:\n";
    printList(head);

    Solution s;
    head = s.reverseList(head);

    cout << "\nReversed list:\n";
    printList(head);

    return 0;
}
