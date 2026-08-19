#include<iostream>
using namespace std;

class node
{

public:
    int data;
    node* next;

    node(int val)
    {
        data = val;
        next = NULL;
    }
};

class list
{
    node* head;
    node* tail;

public:
    list()
    {
        head = tail = NULL;
    }

    void push_front(int val)   //suppose we have 2->1->null
    {
        node* newnode = new node(val);  //first make a newnode  make newnode

        if (head == NULL)   //if head==null
        {
            head = tail = newnode;  //head= tail=newnode
            return;
        }

        newnode->next = head; //sec points newnode to old one
        head = newnode; //then move head to new code
    }

    void push_back(int val)      //suppose we have 3->2->1->NULL and we want to add (1) first new node then transfer tail to newnode make newnode tail (tail=newnode)
    {
        node* newnode= new node(val);
        if(head==NULL)
        {
            head=tail=newnode;
        }
        else
        {
            tail->next=newnode;
            tail=newnode;
        }
    }

   void pop_front()        //suppose we have 3->2->1->null and we want to delete 3
    {                  // first we make it temp, transfer head to next value (2) , then make 3 null and delete it

     if (head == NULL)
        {
            cout << "LL is empty\n";
            return;
        }

        node* temp=head;
        head=head->next;
         if (head == NULL)   // only one node case
          {  tail = NULL;

    }    temp->next=NULL;
        delete temp;
    }

   void pop_back()   //suppose we have 3->2->1->null and we want to delete 1
    {
         if (head == NULL)
    {
        cout << "LL is empty\n";
        return;
    }
    if (head == tail)   // only one node
    {
        delete head;
        head = tail = NULL;
        return;
    }

       node* temp = head;   //make head temp (humesha head hi temp banega )
    while (temp->next != tail)  //jab tak temp->next last node tak(tail) tak nhi jata
    {
        temp = temp->next;  //tab tak har baar temp ko temp ke next equal
    }

         delete tail; //delete tail
    tail = temp;     //tail bocome temp
    tail->next = NULL;  //point tail next o null
}


    void print()
    {
        node* temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    } };

int main()
{
    list l1;

    cout<<"push front: "<<endl;
    l1.push_front(10);
    l1.push_front(20);
    l1.push_front(30);
     l1.print();

    cout<<endl;

    cout<<"push back: "<<endl;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.print();

cout<<endl;

     cout<<"combine push "<<endl;
    l1.push_front(300);
    l1.push_front(400);
    l1.push_back(500);
    l1.print();

    cout<<endl;

    cout<<"pop front: "<<endl;
     l1.pop_front();
    l1.print();

    cout<<endl;

    cout<<"pop back: "<<endl;
     l1.pop_back();
     l1.print();
}
