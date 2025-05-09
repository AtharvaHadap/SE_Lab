#include <bits/stdc++.h>
using namespace std;

class node {
public:
	char value;
	node* left;
	node* right;
	node* next = NULL;

	node(char c) {
		this->value = c;
		left = NULL;
		right = NULL;
	}
	node() {
		left = NULL;
		right = NULL;
	}
	friend class Stack;
	friend class expression_tree;
};

class Stack {
	node* head = NULL;

public:
	void push(node* x) {
		if (head == NULL) {
			head = x;
		}
		else {
			x->next = head;
			head = x;
		}
	}

	node* pop() {
		node* p = head;
		head = head->next;
		return p;
	}
	friend class expression_tree;
};

class expression_tree {
public:
	void inorder(node* x) {
		if (x == NULL)
			return;
		inorder(x->left);
		cout << x->value << " ";
		inorder(x->right);
	}
};

int main() {
	string s = "ABC*+D/";
	Stack e;
	expression_tree a;
	node *x, *y, *z;
	int l = s.length();

	for (int i = 0; i < l; i++) {
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
			z = new node(s[i]);
			x = e.pop();
			y = e.pop();
			z->left = y;
			z->right = x;
			e.push(z);
		}
		else {
			z = new node(s[i]);
			e.push(z);
		}
	}

	cout << "The Inorder Traversal of Expression Tree: ";
	a.inorder(z);
	cout << endl;
	return 0;
}