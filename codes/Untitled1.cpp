#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
};

// Find middle of linked list
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    if (n == 0) return 0;

    int x;
    cout << "Enter values: ";

    // Create head
    cin >> x;
    ListNode* head = new ListNode;  //read the first value
    head->val = x;          //store value in node
    head->next = NULL;        //next = NULL means no node after it yet

                         //This node is the starting point of the linked list

    ListNode* temp = head;  // create temp=head

    // Create remaining nodes
    for (int i = 1; i < n; i++) {
        cin >> x;
        ListNode* newNode = new ListNode;   //create new node
        newNode->val = x;
        newNode->next = NULL;

        temp->next = newNode;   //link previous node to new
        temp = newNode;
    }

    // Find middle
    ListNode* mid = middleNode(head);
    cout << "Middle node value: " << mid->val;

    return 0;
}
