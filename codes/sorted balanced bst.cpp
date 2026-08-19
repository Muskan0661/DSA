
#include <iostream>
using namespace std;
class node{
    public:
    int n;
    node* left;
    node* right;
    node(int num)
    {
        n=num;
        left=right=NULL;
    }
};
node* helper(int num[], int st, int end)
{
    if(st > end) return NULL;
    int mid = (st+end)/2;
    node* root= new node(num[mid]);
    root->left= helper(num, st, mid-1);
    root->right = helper(num,mid+1, end);
    return root;
}
void inorder(node* root) {
    if (root == NULL) return;

    inorder(root->left);
    cout << root->n << " ";
    inorder(root->right);
}

int main() {
                            // sorted array of balanced bst
   int num[]={-10,-3,0,5,9};   //always have sorted array
  node* root= helper(num,0,4);
  cout<<"inorder transversal: ";
  inorder(root);

    return 0;
}