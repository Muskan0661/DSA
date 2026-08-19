#include<iostream>
using namespace std;

struct node {
    
    int data;
    node* left;
    node* right;
    int height;
};

int height(node* n)
{
    if(n==NULL) return 0;
    return n->height;
}

node* newnode(int data)
{
    node* n= new node();
    n->data= data;
    n->left = n->right= NULL;
    n->height=1;
    return n;
}

int getbalance(node* n){
    
    if(n==NULL) return 0;
    return height(n->left)-height(n->right);
}

void updateheight(node* n)
{
    n->height= 1+max(height(n->left), height(n->right));
}

node* insert(node* root, int key)
{
    if(root==NULL) return  newnode(key);
    if(key< root->data) root->left= insert(root->left, key);
    else root->right=insert(root->right,key);
    
    updateheight(root);
    return root;
}

void printbalance(node* root)
{
    if(root==NULL) return;
    printbalance(root->left);
    cout<<"node "<<root->data <<"-> balance factor "<<getbalance(root)<<endl;
    printbalance(root->right);
}

void printTree(node* root, int space=0, int gap=5)
{
    if(root==NULL) return;
    
    space += gap;
    printTree(root->right, space);
    
    cout<<endl;
    for(int i=gap; i<space; i++)
    
        cout<<" ";
        cout<<root->data<<"\n";
        printTree(root->left, space);
    
}

int main()
{
    node* root=NULL;
    int n=5;
    int value[n]={10,5,15,3,7};

    for(int i=0; i<n; i++){
        root=insert(root, value[i]);
    }
    
     // Insert 12
    root = insert(root, 12);

    // Print balance factors
    cout << "Balance Factors:\n";
    printbalance(root);

    // Print height
    cout << "\nHeight of tree: " << height(root) << endl;

    // Final tree
    cout << "\nFinal AVL Tree:\n";
    printTree(root);

}
