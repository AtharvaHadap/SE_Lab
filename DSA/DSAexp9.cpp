#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword, meaning;
    Node *left, *right;
    int height;
    Node(string k, string m) : keyword(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) {
        return node ? node->height : 0; 
    }
    int balanceFactor(Node* node) { 
        return height(node->left) - height(node->right); 
    }
    void updateHeight(Node* node) { 
        node->height = max(height(node->left), height(node->right)) + 1; 
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* node) {
        int bf = balanceFactor(node);
        if (bf > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* insert(Node* node, string keyword, string meaning) {
        if (!node) return new Node(keyword, meaning);
        if (keyword < node->keyword) node->left = insert(node->left, keyword, meaning);
        else if (keyword > node->keyword) node->right = insert(node->right, keyword, meaning);
        else node->meaning = meaning;  
        updateHeight(node);
        return balance(node);
    }

    Node* deleteNode(Node* node, string keyword) {
        if (!node) return node;
        if (keyword < node->keyword) node->left = deleteNode(node->left, keyword);
        else if (keyword > node->keyword) node->right = deleteNode(node->right, keyword);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) { delete node; return nullptr; }
                *node = *temp;
                delete temp;
            } else {
                Node* temp = node->right;
                while (temp && temp->left) temp = temp->left;
                node->keyword = temp->keyword;
                node->meaning = temp->meaning;
                node->right = deleteNode(node->right, temp->keyword);
            }
        }
        updateHeight(node);
        return balance(node);
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->keyword << ": " << node->meaning << endl;
        inOrder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insertKeyword(string keyword, string meaning) {
        root = insert(root, keyword, meaning);
    }

    void deleteKeyword(string keyword) {
        root = deleteNode(root, keyword);
    }

    void updateKeyword(string keyword, string meaning) {
        root = insert(root, keyword, meaning);
    }

    void display() {
        inOrder(root);
    }

    int maxComparisons() {
        return height(root);
    }
};

int main() {
    AVLTree dictionary;

    dictionary.insertKeyword("Engineer", "HeadAche");
    dictionary.insertKeyword("Doctor", "Ham nhi bacha paye");
    dictionary.insertKeyword("Neta", "corruption");

    cout<<endl;
    cout << "Dictionary in Ascending Order:" << endl;
    dictionary.display();

    cout<<endl;
    cout << "Updating 'Doctor' meaning..." << endl;
    dictionary.updateKeyword("Doctor", "but paisa bhut hai!");

    dictionary.display();

    cout<<endl;
    cout << "Deleting 'Neta'..." << endl;
    dictionary.deleteKeyword("Neta");

    dictionary.display();

    cout<<endl;
    cout << "Max Comparisons for Searching: " << dictionary.maxComparisons() << endl;

    return 0;
}