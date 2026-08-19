#include <iostream>
using namespace std;

/*
 * ═══════════════════════════════════════════════════
 *  NODE STRUCTURE
 *  Each node holds:
 *    - val   : the actual data
 *    - left  : pointer to left child  (smaller values)
 *    - right : pointer to right child (larger values)
 * ═══════════════════════════════════════════════════
 */
struct Node {
    int val;
    Node* left;
    Node* right;

    // Constructor — initializes node with a value,
    // left and right pointers set to null by default
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};


/*
 * ═══════════════════════════════════════════════════
 *  BST CLASS
 *  Wraps all operations on the tree.
 *  Only stores a pointer to the root node.
 * ═══════════════════════════════════════════════════
 */
class BST {
public:
    Node* root;

    // Constructor — empty tree starts with null root
    BST() : root(nullptr) {}


    // ─────────────────────────────────────────────────
    //  INSERT
    //  Logic:
    //    - If spot is empty → place the node here
    //    - If val < current → go LEFT
    //    - If val > current → go RIGHT
    //    - Duplicates are ignored
    //
    //  Time:  O(log n) average | O(n) worst (skewed tree)
    //  Space: O(log n) recursion stack
    // ─────────────────────────────────────────────────
    Node* insert(Node* node, int val) {
        // Base case: found an empty spot → create new node here
        if (!node) return new Node(val);

        if (val < node->val)
            node->left = insert(node->left, val);   // go left
        else if (val > node->val)
            node->right = insert(node->right, val); // go right
        // if val == node->val → duplicate, do nothing

        return node; // return current node back up the call stack
    }

    // Public wrapper — user just calls insert(val)
    void insert(int val) {
        root = insert(root, val);
    }


    // ─────────────────────────────────────────────────
    //  SEARCH
    //  Logic:
    //    - If node is null → value not found
    //    - If val == current → found it!
    //    - If val < current → search left subtree
    //    - If val > current → search right subtree
    //
    //  Time:  O(log n) average | O(n) worst
    // ─────────────────────────────────────────────────
    Node* search(Node* node, int val) {
        // Base cases: empty tree OR value found
        if (!node || node->val == val) return node;

        if (val < node->val)
            return search(node->left, val);  // must be in left subtree
        else
            return search(node->right, val); // must be in right subtree
    }

    // Public wrapper — returns true if found, false if not
    bool search(int val) {
        return search(root, val) != nullptr;
    }


    // ─────────────────────────────────────────────────
    //  GET MINIMUM
    //  In a BST, the smallest value is always
    //  the leftmost node — keep going left until
    //  there's no more left child.
    //
    //  Time: O(h) where h = height of tree
    // ─────────────────────────────────────────────────
    Node* getMin(Node* node) {
        while (node->left)       // keep going left
            node = node->left;
        return node;             // leftmost node = minimum
    }


    // ─────────────────────────────────────────────────
    //  GET MAXIMUM
    //  Opposite of getMin — largest value is the
    //  rightmost node.
    //
    //  Time: O(h)
    // ─────────────────────────────────────────────────
    Node* getMax(Node* node) {
        while (node->right)      // keep going right
            node = node->right;
        return node;             // rightmost node = maximum
    }


    // ─────────────────────────────────────────────────
    //  DELETE
    //  3 cases to handle:
    //
    //  Case 1 — Node is a LEAF (no children):
    //           Just remove it directly.
    //           Example: delete 3
    //                10              10
    //               /  \    →       /  \
    //              5    15         5    15
    //             /
    //            3 ← remove
    //
    //  Case 2 — Node has ONE child:
    //           Replace node with its only child.
    //           Example: delete 5 (only has left child 3)
    //                10              10
    //               /  \    →       /  \
    //              5    15         3    15
    //             /
    //            3
    //
    //  Case 3 — Node has TWO children:
    //           Find the INORDER SUCCESSOR (smallest
    //           value in right subtree), copy its
    //           value here, then delete the successor.
    //           Example: delete 10
    //                10              12
    //               /  \    →       /  \
    //              5    15         5    15
    //                  /  \               \
    //                 12   20              20
    //           (12 is inorder successor of 10)
    //
    //  Time:  O(log n) average | O(n) worst
    // ─────────────────────────────────────────────────
    Node* deleteNode(Node* node, int val) {
        // Base case: value not found in tree
        if (!node) return nullptr;

        if (val < node->val)
            // Value is smaller → delete from left subtree
            node->left = deleteNode(node->left, val);

        else if (val > node->val)
            // Value is larger → delete from right subtree
            node->right = deleteNode(node->right, val);

        else {
            // Found the node to delete — handle 3 cases:

            // Case 1: Leaf node — no children
            if (!node->left && !node->right) {
                delete node;
                return nullptr; // nothing to replace it with
            }

            // Case 2a: Only right child exists
            if (!node->left) {
                Node* tmp = node->right; // save right child
                delete node;
                return tmp;              // right child takes this spot
            }

            // Case 2b: Only left child exists
            if (!node->right) {
                Node* tmp = node->left;  // save left child
                delete node;
                return tmp;              // left child takes this spot
            }

            // Case 3: Both children exist
            // Find inorder successor = smallest in RIGHT subtree
            Node* successor = getMin(node->right);

            // Copy successor's value into current node
            // (effectively "replacing" the deleted node)
            node->val = successor->val;

            // Now delete the successor from right subtree
            // (it's guaranteed to be a simple case — at most one child)
            node->right = deleteNode(node->right, successor->val);
        }

        return node;
    }

    // Public wrapper
    void deleteNode(int val) {
        root = deleteNode(root, val);
    }


    // ─────────────────────────────────────────────────
    //  INORDER TRAVERSAL  →  Left, Root, Right
    //  Key property: inorder on a BST always gives
    //  values in SORTED (ascending) order.
    //
    //  Example tree:       Inorder output:
    //       10             3 5 7 10 12 15 20
    //      /  \
    //     5    15
    //    / \   / \
    //   3   7 12  20
    //
    //  Time: O(n) — visits every node once
    // ─────────────────────────────────────────────────
    void inorder(Node* node) {
        if (!node) return;         // base case: empty subtree
        inorder(node->left);       // 1. visit left
        cout << node->val << " ";  // 2. print current
        inorder(node->right);      // 3. visit right
    }


    // ─────────────────────────────────────────────────
    //  PREORDER TRAVERSAL  →  Root, Left, Right
    //  Useful for: copying a tree, serialization.
    //  Visits root BEFORE its children.
    //
    //  Preorder output: 10 5 3 7 15 12 20
    //
    //  Time: O(n)
    // ─────────────────────────────────────────────────
    void preorder(Node* node) {
        if (!node) return;
        cout << node->val << " ";  // 1. print current (root first)
        preorder(node->left);      // 2. visit left
        preorder(node->right);     // 3. visit right
    }


    // ─────────────────────────────────────────────────
    //  POSTORDER TRAVERSAL  →  Left, Right, Root
    //  Useful for: deleting a tree, evaluating
    //  expression trees. Visits root AFTER children.
    //
    //  Postorder output: 3 7 5 12 20 15 10
    //
    //  Time: O(n)
    // ─────────────────────────────────────────────────
    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);     // 1. visit left
        postorder(node->right);    // 2. visit right
        cout << node->val << " ";  // 3. print current (root last)
    }


    // ─────────────────────────────────────────────────
    //  HEIGHT
    //  Height = number of edges on longest path
    //  from root to a leaf.
    //
    //  Calculated recursively:
    //    height = 1 + max(left height, right height)
    //  Empty tree has height 0.
    //
    //  Time:  O(n) — must visit every node
    //  Space: O(h) — recursion stack depth
    // ─────────────────────────────────────────────────
    int height(Node* node) {
        if (!node) return 0;  // empty tree = height 0
        int leftH  = height(node->left);   // height of left subtree
        int rightH = height(node->right);  // height of right subtree
        return 1 + max(leftH, rightH);     // current node adds 1
    }


    // ─────────────────────────────────────────────────
    //  DESTRUCTOR — Memory Cleanup
    //  Postorder traversal to delete all nodes.
    //  Must delete children before parent to avoid
    //  memory leaks.
    // ─────────────────────────────────────────────────
    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);   // delete left subtree first
        destroy(node->right);  // delete right subtree
        delete node;           // then delete current node
    }

    ~BST() { destroy(root); }  // called automatically when BST goes out of scope
};


/*
 * ═══════════════════════════════════════════════════
 *  MAIN — Driver Code
 * ═══════════════════════════════════════════════════
 */
int main() {
    BST bst;

    // Insert values — tree will look like:
    //        10
    //       /  \
    //      5    15
    //     / \   / \
    //    3   7 12  20
    for (int v : {10, 5, 15, 3, 7, 12, 20})
        bst.insert(v);

    // ── Traversals ──
    cout << "Inorder   : "; bst.inorder(bst.root);   cout << "\n"; // sorted
    cout << "Preorder  : "; bst.preorder(bst.root);  cout << "\n"; // root first
    cout << "Postorder : "; bst.postorder(bst.root); cout << "\n"; // root last

    // ── Search ──
    cout << "\nSearch 7  : " << (bst.search(7)  ? "Found" : "Not found") << "\n";
    cout << "Search 99 : " << (bst.search(99) ? "Found" : "Not found") << "\n";

    // ── Min / Max ──
    cout << "\nMin    : " << bst.getMin(bst.root)->val << "\n"; // leftmost
    cout << "Max    : " << bst.getMax(bst.root)->val << "\n";   // rightmost

    // ── Height ──
    cout << "Height : " << bst.height(bst.root) << "\n"; // 3

    // ── Delete ──
    cout << "\nAfter deleting 5  : "; bst.deleteNode(5);
    bst.inorder(bst.root); cout << "\n";

    cout << "After deleting 15 : "; bst.deleteNode(15);
    bst.inorder(bst.root); cout << "\n";

    cout << "After deleting 10 : "; bst.deleteNode(10);
    bst.inorder(bst.root); cout << "\n";

    return 0;
}