#include<iostream>
using namespace std;

struct Node {

	int val;
	Node* next;

	Node(int x)
	{
		val=x;
		next= NULL;
	}
};

class Solution {

public:
    Node* mergeTwoLists(Node* list1, Node* list2) {

            if(list1==NULL || list2==NULL)
            {
                if(list1==NULL) return list2;
                else return list1;
            }
           if(list1->val <= list2->val)
           {
              list1->next=mergeTwoLists(list1->next, list2);
              return list1;
           }
           else
           {
              list2->next=mergeTwoLists(list1, list2->next);
              return list2;
           }

    }
};

void printlist(Node* head)
{

      while(head!=NULL)
      {
      	cout<<head->val<<"-> ";
      	head=head->next;
	  }
	  cout<<"NULL\n";
}

int main()
{
	Node* list1 = new Node(1);  //list 1
	list1->next= new Node(3);
	list1->next->next= new Node(5);
    printlist(list1);

	Node* list2 = new Node(2);  //list2
	list2->next= new Node(4);
	list2->next->next= new Node(6);
	list2->next->next->next= new Node(7);

     printlist(list2);

	Solution s;
	Node* merged= s.mergeTwoLists(list1, list2);
	cout<<"Merged lists: ";
	printlist(merged);

}
