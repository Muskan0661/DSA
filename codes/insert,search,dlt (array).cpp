// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
class node {
    public:
    int data;
    node* left;
    node * right;
    
    node(int d)
    {
        data=d;
        left=right=NULL;
    }
};

node * bst (node * root , int target)
{
    if(root==NULL || root->data==target)
    {
        return root;
    }
    
    if (root->data > target )
    return bst(root->left , target);
    else 
    return bst(root->right , target);

}
node * insert ( node * root , int n)
{
    if (root==NULL) return new node(n);
    
    if (root->data > n)
    root->left= insert(root->left , n);
    else  if (root->data < n)
    root->right= insert(root->right , n);
    return root;
}

node* findmin(node* root)
{
    while(root->left !=NULL)
    {
        root=root->left;
    }
    return root;
}
node * deletion(node * root , int n)
{
    if(root==NULL) return root;   //loacate nodes
    
    if(root->data > n )    //left locate
     {  root->left=deletion(root->left ,n); }
         
    else if (root->data < n )              //right locate
    {  root->right=deletion(root->right, n); }
    
    else {    // 3 cases
        
        if(root->left==NULL) {   //case 1 and 2
        node* temp=root->right;   //when node has only right child
        delete root;
        return temp; }
        
        else if(root->right==NULL) {   //when node has only left child
        node* temp=root->left;
        delete root;
        return temp; }
        
        //from right we delete smallest value 
        node* temp = findmin(root->right);  //case 3 , when has 2 or more child
        root->data = temp->data;       //find min, replace data
        root->right = deletion(root->right , temp->data); //delete from right
    }
    return root;
}

void inorder(node * root, int arr[] , int &index)
{
    if(root==NULL) return;
    inorder(root->left , arr, index);
    arr[index++]=root->data;
    inorder(root->right, arr, index);
}

int main() {
    // Write C++ code here
    std::cout << "Try programiz.pro\n";
     int arr[]={21,24,35,43,91,33};
     int size=sizeof(arr)/sizeof(arr[0]);
     
     node* root = NULL;
     
       for(int i=0; i<size; i++)
     {
          cout<<arr[i]<<" ";
     }
     cout<<endl;
     for(int i=0; i<size; i++)
     {
         root=insert(root, arr[i]);
     }
     
   
   int num=57;
    if (num < root->data)
        cout << num << " goes LEFT of root\n";
    else
        cout << num << " goes RIGHT of root\n";
    
    root=insert(root,num); 
     
   int target= 81;
   node* result= bst(root, target);
   
   if (result !=NULL) 
      cout<<"score: "<<result->data <<" found."<<endl;
   else
      cout<<"score: "<<target<<" no found"<<endl;
   
   int del=91;
   root=deletion(root,del);
   cout<<"score: "<<del <<" is deleted! "<<endl;
   
   int resultArr[100];
   int index=0;
   
   inorder(root, resultArr, index);
   cout<<"BST in array form (sorted): ";
   for(int i=0; i<index; i++)
   {
       cout<<resultArr[i]<<" ";
   }
     
    return 0;
}