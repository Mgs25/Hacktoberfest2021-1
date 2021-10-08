#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct BstNode {
    int data;
    BstNode* left;
    BstNode* right;
};

BstNode* CreateNewNode(int data) {
    BstNode* newNode = new BstNode();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

BstNode* Insert(BstNode* root, int data) {
    if (root == nullptr)
        root = CreateNewNode(data);
    else if (data < root->data)
        root->left = Insert(root->left, data);
    else
        root->right = Insert(root->right, data);
    return root;
}

bool Search(BstNode* root, int data) {
    if (root == nullptr) 
        return false;
    if (root->data == data)
        return true;
    else if (data <= root->data)
        return Search(root->left, data);
    else
        return Search(root->right, data);
}

int FindMin(BstNode* root) {
    if (root == nullptr)
        return -1;
    else if (root->left == nullptr)
        return root->data;
    return FindMin(root->left);
}

BstNode* FindMax(BstNode* root) {
    if (root == nullptr)
        return nullptr;
    else if (root->right == nullptr)
        return root;
    return FindMax(root->right);
}

int FindHeight(BstNode* root) { // O(n)
    if (root == nullptr)
        return -1;
    return max(FindHeight(root->left),FindHeight(root->right)) + 1;
}
 
void InOrder(BstNode* root) { // O(n)
    if (root == nullptr)
        return;
    InOrder(root->left);
    cout << root->data << ' ';
    InOrder(root->right);
}

void PreOrder(BstNode* root) { // O(n)
    if (root == nullptr)
        return;
    cout << root->data << ' ';
    PreOrder(root->left);
    PreOrder(root->right);
}

void PostOrder(BstNode* root) { // O(n)
    if (root == nullptr)
        return;
    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->data << ' ';
}

void LevelOrder(BstNode* root) { // O(n)
    if (root == nullptr) return;
    queue<BstNode*> Q;
    Q.push(root);
    while (!Q.empty()) {
        BstNode* current = Q.front();
        cout << current->data << ' ';
        if (current->left != nullptr) Q.push(current->left);
        if (current->right != nullptr) Q.push(current->right);
        Q.pop();
    }
}

BstNode* Delete(BstNode* root, int data) {
    if (root == nullptr)
        return root;
    else if (data < root->data)
        root->left = Delete(root->left, data);
    else if (data > root->data)
        root->right = Delete(root->right, data);
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr) {
            BstNode* parent = root;
            root = root->right;
            delete parent;
        }
        else if (root->right == nullptr) {
            BstNode* parent = root;
            root = root->left;
            delete parent;
        }
        else {
            BstNode* max_node = FindMax(root->left);
            root->data = max_node->data;
            root->left = Delete(root->left, max_node->data);
        }
    }
    return root;
}

bool IsBstUtil(BstNode* root, int minValue, int maxValue) {
    if (root == nullptr)
        return true;
    if (root->data > minValue && root->data < maxValue
        && IsBstUtil(root->left, minValue, root->data)
        && IsBstUtil(root->right, root->data, maxValue))
            return true;
    return false;
}

bool IsBst(BstNode* root) {
    return IsBstUtil(root, INT_MIN, INT_MAX);
}


int main() {
    BstNode* root = nullptr;
    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 30);
    root = Insert(root, 8);
    root = Insert(root, -1);
    root = Insert(root, 99);
    root = Insert(root, 25);

    cout << FindMin(root) << endl;
    cout << FindMax(root)->data << endl;
    cout << FindHeight(root) << endl;
    
    // Depth first traversal
    PreOrder(root);
    cout << endl;
    InOrder(root);
    cout << endl; 
    PostOrder(root);
    cout << endl;
    // Breadth first traversal
    LevelOrder(root);
    cout << endl;

    cout << IsBst(root);
    
    Delete(root, 99);
    
    cout << Search(root, 99) << endl;

    // continue with inorder successor
    // implement every function

    return 0;
} 
