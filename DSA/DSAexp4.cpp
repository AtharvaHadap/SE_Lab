#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

class Btree {
public:
    Node* root;

    Btree() { root = nullptr; }

    Node* insert(Node* temp, int Indata) {
        if (!temp) return new Node(Indata);
        if (Indata < temp->data) temp->left = insert(temp->left, Indata);
        else temp->right = insert(temp->right, Indata);
        return temp;
    }

    void insert(int Indata) { root = insert(root, Indata); }

    void inorder(Node* temp) {
        if (temp) {
            inorder(temp->left);
            cout << temp->data << " ";
            inorder(temp->right);
        }
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }
    
    int findMin(Node* temp) {
        while (temp && temp->left) temp = temp->left;
        return temp ? temp->data : -1;
    }

    int findMin() { return findMin(root); }
    
    void swapChildren(Node* temp) {
        if (!temp) return;
        swap(temp->left, temp->right);
        swapChildren(temp->left);
        swapChildren(temp->right);
    }

    void swapChildren() { swapChildren(root); }
    
    bool search(Node* temp, int value) {
        if (!temp) return false;
        if (temp->data == value) return true;
        return value < temp->data ? search(temp->left, value) : search(temp->right, value);
    }

    bool search(int value) { return search(root, value); }
    
    void inputData(int entries) {
        int d1;
        for (int i = 1; i <= entries; i++) {
            cin >> d1;
            insert(d1);
        }
    }
    
    void levelTraversal(Node* root) {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << endl;
    }
    
    void levelTraversal() { levelTraversal(root); }
};

int main() {
    Btree bt;
    int entries, searchValue;
    cin >> entries;
    bt.inputData(entries);
    bt.inorderTraversal();
    bt.levelTraversal();
    cout << "Minimum Value: " << bt.findMin() << endl;
    bt.swapChildren();
    cout << "Tree after swapping children: ";
    bt.levelTraversal();
    cin >> searchValue;
    cout << (bt.search(searchValue) ? "Found" : "Not Found") << endl;
    return 0;
}