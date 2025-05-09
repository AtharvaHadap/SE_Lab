#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Node {
public:
    string data;
    vector<Node*> children;
    Node(string d) { data = d; }
    ~Node() { for (Node* child : children) delete child; }
};

void levelTraversal(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            Node* curr = q.front();
            q.pop();
            cout << curr->data << " ";
            for (Node* child : curr->children) q.push(child);
        }
        cout << endl;
    }
}
int main() {
    string title;
    cout << "Enter book title: ";
    cin >> title;
    Node* root = new Node(title);
    
    int chapters;
    cout << "Enter number of chapters: ";
    cin >> chapters;
    
    for (int i = 0; i < chapters; i++) {
        string chap;
        cout << "Enter chapter " << i + 1 << ": ";
        cin >> chap;
        Node* chapter = new Node(chap);
        root->children.push_back(chapter);
        
        int sections;
        cout << "Enter number of sections in " << chap << ": ";
        cin >> sections;
        
        for (int j = 0; j < sections; j++) {
            string sec;
            cout << "Enter section " << j + 1 << " in " << chap << ": ";
            cin >> sec;
            chapter->children.push_back(new Node(sec));
        }
    }
    cout << "\nTree Structure:\n";
    levelTraversal(root);
    delete root;
    return 0;
}