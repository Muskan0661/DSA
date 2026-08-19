// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

class stack{
    
    int arr[100];
    int top;
    
    public:
    stack()
    {
        top=-1; }
    
    
    void push(int val)
    {
        if(top==99)
        {
            cout<<"stack overflow: ";
            return;
        }
        
        top++;
        arr[top]=val;
        cout<<"stack value: "<<val<<endl;
    }
    
    void pop()
    {
        if(top==-1)
        {
            cout<<"stack underflow: \n";
            return;
        }
        
        cout<<arr[top]<<"  popped " <<endl;
        top--;
    }
    
    void peek()
    {
        if(top==-1)
        {
            return;
        }
        cout<<"top: "<<arr[top]<<endl;
    }
    
     void display()
    {
        if (top == -1)
        {
            cout << "Stack is empty\n";
            return;
        }

        cout << "Stack elements:\n";

        for (int i = top; i >= 0; i--)
        {
            cout << arr[i] << endl;
        }
    }
    
    void reverse()
    {
    	if (top == -1)
        {
            cout << "Stack is empty\n";
            return;
        }

        cout << "reverse stack elements:\n";

        for (int i = 0; i <=top; i++)
        {
            cout << arr[i] << endl;
        }
	}
};

int main() {
    // Write C++ code here
    stack s;
    int val;
    for(int i=0; i<3; i++)
    {
        cin>>val;
        s.push(val);
    }
    s.pop();
    s.peek();
    s.display();
    s.reverse();
    return 0;
}