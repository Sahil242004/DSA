//Assignment 2 :
// ((x+5)/3)-(3x+8)
// a*b+c/d
// 2*3/(2-1)+5*(4-1)
// 4/(2-(-8*3))
// 2+3-(6*4/8)+7
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype> // isalnum function vaparnyasathichi library.

using namespace std;

struct Node {
    string data;
    Node *lchild;
    Node *rchild;

    
    Node(string datavalue) {
        data = datavalue;
        lchild = NULL;
        rchild = NULL;
    }
};

struct ExpressionTree {
    // he fuction operators cha precedance return karte.
    int precedence(char c) {
        if (c == '+' || c == '-') return 1;
        if (c == '*' || c == '/') return 2;
        if (c == '^') return 3;
        return -1;
    }

    // infix la postfix madhe convert karnyasathiche function.
    string infixToPostfix(const string& infix) {
        stack<char> st;
        string postfix;
        int n = infix.length();
        
        for (int i = 0; i < n; i++) {
            char c = infix[i];

            if (isalnum(c)) { 
                postfix += c;
                while (i + 1 < n && isalnum(infix[i + 1])) {
                    postfix += infix[++i];
                }
                postfix += ' '; // hi line multicharacter oprend la space deun separte karte.
            } 
            else if (c == '(') { 
                st.push(c);
            } 
            else if (c == ')') { 
                while (!st.empty() && st.top() != '(') {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                if (st.empty()) {
                    throw runtime_error("Mismatched parentheses");
                }
                st.pop();
            } else if (c == '-') {
                // hi else if condition negative number handle karte
                if (i == 0 || (!isalnum(infix[i - 1]) && infix[i - 1] != ')')) {
                    postfix += c; // Treat as a negative sign
                    while (i + 1 < n && isalnum(infix[i + 1])) {
                        postfix += infix[++i];
                    }
                    postfix += ' ';
                } else {
                    // Treat as a subtraction operator
                    while (!st.empty() && precedence(st.top()) >= precedence(c) && st.top() != '(') {
                        postfix += st.top();
                        postfix += ' ';
                        st.pop();
                    }
                    st.push(c);
                }
            } else { 
                while (!st.empty() && precedence(st.top()) >= precedence(c) && st.top() != '(') {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                st.push(c);
            }
        }

        while (!st.empty()) {
            if (st.top() == '(') {
                throw runtime_error("Mismatched parentheses");
            }
            postfix += st.top();
            postfix += ' ';
            st.pop();
        }

        return postfix;
    }

    //he function postfix expression la expression tree madhe convert karte.
    Node* constructTree(const string& postfix) {
        stack<Node*> st;
        istringstream iss(postfix);
        string token;

        while (iss >> token) {
            if (token.length() == 1 && !isalnum(token[0])) { 
                if (st.size() < 2) {
                    throw runtime_error("Invalid postfix expression");
                }
                Node* t = new Node(token);

                Node* t1 = st.top(); st.pop();
                Node* t2 = st.top(); st.pop();

                t->rchild = t1;
                t->lchild = t2;

                st.push(t);
            } else { 
                Node* t = new Node(token);
                st.push(t);
            }
        }

        if (st.size() != 1) {
            throw runtime_error("Invalid postfix expression");
        }

        return st.top();
    }

    // Non-recursive traversals
    void nonRecursiveInorder(Node* root) {
        stack<Node*> s;
        Node* curr = root;

        while (curr != NULL || !s.empty()) {
            while (curr != NULL) {
                s.push(curr);
                curr = curr->lchild;
            }
            curr = s.top();
            s.pop();
            cout << curr->data << " ";
            curr = curr->rchild;
        }
    }

    void nonRecursivePreorder(Node* root) {
        if (root == NULL) return;

        stack<Node*> nodeStack;
        nodeStack.push(root);

        while (!nodeStack.empty()) {
            Node* node = nodeStack.top();
            cout << node->data << " ";
            nodeStack.pop();

            if (node->rchild) nodeStack.push(node->rchild);
            if (node->lchild) nodeStack.push(node->lchild);
        }
    }

    void nonRecursivePostorder(Node* root) {
        if (root == NULL) return;

        stack<Node*> s1, s2;
        s1.push(root);
        Node* node;

        while (!s1.empty()) {
            node = s1.top();
            s1.pop();
            s2.push(node);

            if (node->lchild) s1.push(node->lchild);
            if (node->rchild) s1.push(node->rchild);
        }

        while (!s2.empty()) {
            node = s2.top();
            s2.pop();
            cout << node->data << " ";
        }
    }
};

int main() {
    ExpressionTree et;
    Node* root = NULL;
    string infix;
    string postfix;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Convert Infix to Postfix and Construct Expression Tree\n";
        cout << "2. Non-recursive Inorder Traversal\n";
        cout << "3. Non-recursive Preorder Traversal\n";
        cout << "4. Non-recursive Postorder Traversal\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter infix expression: ";
                //errorhandling part
                cin.ignore(); 
                getline(cin, infix);
                try {
                    postfix = et.infixToPostfix(infix);
                    cout << "Postfix expression: " << postfix << endl;
                    root = et.constructTree(postfix);
                    cout << "Expression tree constructed.\n";
                } catch (const runtime_error& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 2:
                if (root == NULL) {
                    cout << "Tree not constructed. Please construct the tree first.\n";
                } else {
                    cout << "Non-recursive Inorder traversal: ";
                    et.nonRecursiveInorder(root);
                    cout << endl;
                }
                break;
            case 3:
                if (root == NULL) {
                    cout << "Tree not constructed. Please construct the tree first.\n";
                } else {
                    cout << "Non-recursive Preorder traversal: ";
                    et.nonRecursivePreorder(root);
                    cout << endl;
                }
                break;
            case 4:
                if (root == NULL) {
                    cout << "Tree not constructed. Please construct the tree first.\n";
                } else {
                    cout << "Non-recursive Postorder traversal: ";
                    et.nonRecursivePostorder(root);
                    cout << endl;
                }
                break;
            case 5:
                cout << "Exit\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
