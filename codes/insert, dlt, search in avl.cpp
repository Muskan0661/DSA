#include <iostream>
using namespace std;

// Structure of a node in AVL Tree
struct Node {
    int key;        // value stored in node
    Node *left;     // pointer to left child
    Node *right;    // pointer to right child
    int height;     // height of the node (used for balancing)
};

// Function to get height of a node
int height(Node *n) {
    // If node is NULL, height is 0
    return (n == NULL) ? 0 : n->height;
}

// Function to calculate balance factor
int getBalance(Node *n) {
    // Balance = left subtree height - right subtree height
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

// Function to create a new node
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = node->right = NULL; // initially no children
    node->height = 1; // new node is always leaf, so height = 1
    return node;
}

// RIGHT ROTATION (for LL imbalance)
Node* rightRotate(Node *y) {
    Node *x = y->left;   // x becomes new root
    Node *T2 = x->right; // subtree to be reattached

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights after rotation
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // return new root
}

// LEFT ROTATION (for RR imbalance)
Node* leftRotate(Node *x) {
    Node *y = x->right;  // y becomes new root
    Node *T2 = y->left;  // subtree to be reattached

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // return new root
}

// INSERT a key into AVL Tree
Node* insert(Node* node, int key) {

    // Step 1: Perform normal BST insertion
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // duplicates not allowed

    // Step 2: Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Step 3: Get balance factor
    int balance = getBalance(node);

    // Step 4: Handle 4 imbalance cases

    // LL Case (Left Left)
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR Case (Right Right)
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR Case (Left Right)
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case (Right Left)
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return unchanged node pointer
    return node;
}

// Find node with minimum value (used in deletion)
Node* minValueNode(Node* node) {
    Node* current = node;

    // Go to leftmost node
    while (current->left != NULL)
        current = current->left;

    return current;
}

// DELETE a node from AVL Tree
Node* deleteNode(Node* root, int key) {

    // Step 1: Perform standard BST delete
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node found

        // Case 1: One or no child
        if ((root->left == NULL) || (root->right == NULL)) {

            Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } 
            // One child case
            else {
                *root = *temp; // copy contents
            }

            delete temp;
        } 
        // Case 2: Node with two children
        else {
            Node* temp = minValueNode(root->right); // inorder successor

            root->key = temp->key; // copy successor value
            root->right = deleteNode(root->right, temp->key); // delete successor
        }
    }

    // If tree had only one node
    if (root == NULL)
        return root;

    // Step 2: Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Step 3: Get balance factor
    int balance = getBalance(root);

    // Step 4: Fix imbalance

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// SEARCH a value in AVL Tree
bool search(Node* root, int key) {

    // Base case: not found
    if (root == NULL)
        return false;

    // If found
    if (root->key == key)
        return true;

    // Search left or right subtree
    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Inorder traversal (prints sorted values)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " "; // visit node
        inorder(root->right);
    }
}

// MAIN FUNCTION
int main() {
    Node* root = NULL;

    // Insert elements
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);

    // Print tree
    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;

    // Search element
    cout << "Search 30: " 
         << (search(root, 30) ? "Found" : "Not Found") << endl;

    // Delete element
    root = deleteNode(root, 30);

    // Print after deletion
    cout << "After deletion (30): ";
    inorder(root);
    cout << endl;

    return 0;
}