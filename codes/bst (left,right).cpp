
#include <iostream>
using namespace std;

class node{
    public:
    string key;
    node * left;
    node* right;
    
    node(string val)
    {
        key=val;
        left=right=NULL;
    }
    
};
node * bst(node* root , string target)
{
    if(root==NULL || root->key== target)
    {
        return root;
    }
    
    if(target < root->key)
    {
        return bst(root->left , target);
    }
    else 
        return bst(root->right , target);
}
int main() {
    // Write C++ code here
    std::cout << "Try programiz.pro\n";
     node* root = new node("muskan");    //right string should be greater than left one
    root->left = new node("lara");      //as muskan >lara , lara <suha
    root->right = new node("suah");
    root->left->right = new node("rutba");

    string target = "lara";
    node* result = bst(root, target);

    if (result != NULL)
        cout << "Contact found: " << result->key << endl;
    else
        cout << "Contact not found" << endl;


    return 0;
}