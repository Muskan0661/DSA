#include<iostream>
using namespace std;

class node{
	int val;
	node* next;
	node* prev;

	node(int val)
	{
		data=val;
		next=prev=NULL;
	}
};

class doublylist{
	node* head;
	node* tail;

	public:
		doublylist()
		{
			head=tail=NULL;
		}
		void push_front(int val)
		{
			node newnode = new node(val);

			if(head==NULL)
			{
                head=tail= newnode;
			}
			else
			{
			    newnode->next = head;
			    head->prev = newnode;
			    head = newnode;
			}
		}

		void print()
		{
		   node* temp= head;
		   while( temp != NULL)
		   {
		   	 cout<<temp->data <<"<=>";
		   	 temp= temp->next;
		   }
		   cout<<"NULL\n";
		}

};

int main ()
{
	doublylist dll;
    dll.push_front(1);
    dll.push_front(2);
    dll.push_front(3);

}