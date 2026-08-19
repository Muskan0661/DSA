#include<iostream>
#include<unordered_map>
using namespace std;

struct Node
{
	int val;
	Node* next;
	Node* random;

	Node(int _val)
	{
		val= _val;
		next= NULL;
		random= NULL;
	}
};

Node* copyRandomList(Node*  head)
{
	if(head==NULL)
	return NULL;

//ok we have to copy the list with random pointers
// 1)copy
//supose we have 7->13->11->10->1->null  we have to copy that

 unordered_map<Node*, Node*> m;       //Map: old node -> new Node
                                      //one is old node and other is new node

Node* newhead= new Node(head->val);    //new node jiske andar purane node ki val  (copy of original head)
                                       // 7=head (old)     neadhead= new Node(7)
                                       //  7=7(new onw)
    m[head]=newhead;                       //n for the head =newhead means 7=7
//two pointers for other values

 Node * oldtemp= head->next;                   //directing to 13 now
 Node * newtemp= newhead;                      //now we want to copy 13 to newtemp

   while(oldtemp!=NULL)                     //repaet these 4 steps till (1)=null
  {

   Node * copyNode = new Node(oldtemp->val);   //copy oldtemp(13) to copynode

   m[oldtemp]=copyNode;                    //map of new info of every oldtemp value
   newtemp->next =copyNode;                        //newtemp=13

   //now to update
   oldtemp= oldtemp->next;
   newtemp= newtemp->next;
                             }

// 2)link wiht random pointers
   oldtemp=head;                      // re-initializetion of both
   newtemp=newhead;

   while(oldtemp!=NULL)
{
    if (oldtemp->random != NULL)
    newtemp->random = m[oldtemp->random];  //search oldtemp value to random and form connection to newtemp random
    oldtemp= oldtemp->next;         //update oldtemp and newtemp
    newtemp=newtemp->next;
}
  return newhead;
}

void printlist(Node * head)
{
	while(head != NULL)
	{
		cout<<" val: "<<head->val << ", random: ";
		if(head->random)
		{
			cout<<head->random->val;
		}
		else
		cout<<"NULL ";
		cout<<endl;
		head= head->next;
	}
}

int main()
{
	int n;
	cout<<" enter num of nodes: ";
	cin>>n;

if(n==0) return 0;

Node** nodes = new Node*[n];

cout<<"enter node values: ";
for(int i=0; i<n; i++)
{
	int val;
	cin>>val;
	nodes[i]= new Node(val);

	if(i>0)
	nodes[i-1]->next = nodes[i];
}

cout<<"enter random indices (-1 for NULL) : ";
for(int i=0; i<n; i++)
{
	int idx;
	cin>>idx;
	if(idx !=-1)
	nodes[i]->random = nodes[idx];
}

    Node* head = nodes[0];

    cout<<" original list: \n";
    Node* copiedhead = copyRandomList(head);
    printlist(copiedhead);

}
