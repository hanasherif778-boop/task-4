#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int v) {
        data = v;
        left = right = nullptr;
    }
};

class Tree {
public:
    Node* root;

    Tree() {
        root = nullptr;
    }

    
    ~Tree() {
        destroyTree(root);
    }

private:
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    
    Node* insert(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);

        return node;
    }

    
    void inOrder(Node* node) {
        if (node == nullptr)
            return;

        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    
    bool search(Node* node, int value) {
        if (node == nullptr)
            return false;

        if (node->data == value)
            return true;

        if (value < node->data)
            return search(node->left, value);

        return search(node->right, value);
    }

    
    Node* findMin(Node* node) {
        if (node == nullptr)
            return nullptr;

        while (node->left != nullptr)
            node = node->left;

        return node;
    }

    
    Node* deleteNode(Node* root, int value) {
        if (root == nullptr)
            return nullptr;

        if (value < root->data)
            root->left = deleteNode(root->left, value);

        else if (value > root->data)
            root->right = deleteNode(root->right, value);

        else {
            
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }

            
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }

        return root;
    }

    
    int height(Node* node) {
        if (node == nullptr)
            return -1; 

        int lh = height(node->left);
        int rh = height(node->right);

        return 1 + max(lh, rh);
    }

    
    void levelOrder() {
        if (!root)
            return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            cout << curr->data << " ";

            if (curr->left != nullptr)
                q.push(curr->left);

            if (curr->right != nullptr)
                q.push(curr->right);
        }

        cout << endl;
    }
};

int main() {
    Tree t;

    
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 35};
    for (int i = 0; i < 9; i++) {
        t.root = t.insert(t.root, values[i]);
    }

    cout << "InOrder: ";
    t.inOrder(t.root);
    cout << endl;

    cout << "Height: " << t.height(t.root) << endl;

    cout << "Search 35: " << t.search(t.root, 35) << endl;
    cout << "Search 99: " << t.search(t.root, 99) << endl;

    
    t.root = t.deleteNode(t.root, 10);
    cout << "After del 10: ";
    t.inOrder(t.root);
    cout << endl;

    
    t.root = t.deleteNode(t.root, 20);
    cout << "After del 20: ";
    t.inOrder(t.root);
    cout << endl;

    
    t.root = t.deleteNode(t.root, 30);
    cout << "After del 30: ";
    t.inOrder(t.root);
    cout << endl;

    cout << "LevelOrder: ";
    t.levelOrder();

    return 0;
}