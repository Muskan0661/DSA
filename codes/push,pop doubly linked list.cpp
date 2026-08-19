#include<iostream>
using namespace std;

class node{
	public:
	int val;
	node* next;
	node* prev;

	node(int val)
	{
		this->val=val;
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
			node* newnode = new node(val);

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

		void push_back(int val)
		{
          node* newnode = new node(val);
          if(head== NULL)
          {
          	head=tail= newnode;
		  }
		  else {
		  	newnode->prev= tail;
		  	tail->next= newnode;
		  	tail= newnode;
		  }
		}

	void pop_front()
		{
           if(head==NULL)
           {
           	cout<<"doubly lnked list is empty: ";
           	return;
		   }
		   node* temp= head;
		   head= head->next;

		   if(head!=NULL)
		   {
		   	  head->prev= NULL;
		   }
		   temp->next= NULL;
		   delete temp;
		}

	void pop_back()
		{
			if(head==NULL)
			{
				cout<<"doubly linked list is empty\n";
				return;
			}
			node* temp= tail;
			tail= tail->prev;
			if(tail!=NULL)
			{
			tail->next=NULL; }

			temp->prev=NULL;

		}

		void print()
		{
		   node* temp= head;
		   while( temp != NULL)
		   {
		   	 cout<<temp->val <<"<=>";
		   	 temp= temp->next;
		   }
		   cout<<"NULL\n";
		}

};

int main ()
{
	doublylist dll;

cout<<"push front: ";
	dll.push_front(10);
    dll.push_front(20);
    dll.push_front(30);
    dll.print();
    cout<<"pop front: ";
    dll.pop_back();
    dll.print();

cout<<"push back: ";
    dll.push_back(1);
    dll.push_back(2);
    dll.push_back(3);
    dll.print();
    cout<<"pop back: ";
     dll.pop_back();
    dll.print();
}