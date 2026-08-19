 #include<iostream>
 using namespace std;
 class node{

public:
 	int val;
 	node* next;

 node(int val)
 {
 	this->val=val;
 	next=NULL;
 }
 };

class circular{
	node* head;
	node* tail;

public:
	circular()
	{
		head=tail=NULL;
	}

	void insertAtHead(int val)
	{
		node* newnode= new node(val);
		if(head==NULL)
		{
			head=tail=newnode;
			tail->next=head;
		}
		else
		{
			newnode->next = head;
            head = newnode;
            tail->next = head;
		}
	}

	void insertAtTail(int val)
	{
		node* newnode = new node(val);
		if(head==NULL)
		{
			head=tail=newnode;
			tail->next= newnode;
		}
		else
		{
			newnode->next= head;
			tail->next= newnode;
			tail=newnode;
		}
	}

	void deleteHead()
	{
		if(head==NULL)   //empty
		{
			return;
		}

		else if (head==tail)   //single node
                {
                	delete head;
                	head=tail=NULL;
				}

		else {                      //multiple node

			 node* temp=head;     //1->2->3->null   here 1=head=temp , tailis pointing to 1
			 head=head->next;    //update head=2;
			 tail->next=head;    // now tail will point to 2
			 temp->next= NULL;    //1=null
			 	delete temp;      //delete 1
		}
	}


		void deleteTail()
	{
		if(tail==NULL)
		{
			cout<<"tail is empty: ";
			return;
		}

		else if(head==tail)   //single node
                {
                	delete head;
                	head=tail=NULL;
				}

		else {

        node* temp=tail;
        node* prev= head;
       while(prev->next != tail)
        {
    	prev=prev->next;
                         	}
         tail=prev;
		 tail->next = head;
		  temp->next = NULL;
		  	delete temp;
		}
	}

    void print()
    {
    	if(head== NULL) return;
    	cout<<head->val <<"->";
    	node* temp= head->next;

    	while(temp!=head)
    	{
    		cout<<temp->val<<" ->";
    		temp= temp->next;
		}
		cout<<temp->val<<endl;
	}
};

int main ()
{
   circular cll;
    cout<<"insert at head: ";
    cll.insertAtHead(1);
    cll.insertAtHead(2);
    cll.insertAtHead(3);
    cll.print();

cout<<"delete head: ";
     cll.deleteHead();
     cll.print();

cout<<"insert at tail: ";
     cll.insertAtTail(10);
     cll.insertAtTail(20);
     cll.insertAtTail(30);
     cll.print();

cout<<"delete tail: ";
     cll.deleteTail();
     cll.print();

}

