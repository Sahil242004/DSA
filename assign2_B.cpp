#include<iostream>
#include<math.h>
#include<queue>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    int data;

    Node(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

Node* insert(Node* root, int data) {
    if(root==nullptr) return new Node(data);

    if(data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right,data);
    }

    return root;
}

void preorder(Node* root) {
    if(root==nullptr) return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if(root==nullptr) return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

void postorder(Node* root) {
    if(root==nullptr) return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}

bool search(Node* root, int key) {
    if(root==nullptr) {
        cout<<"Not found!\n";
        return false;
    }
    if(root->data == key) {
        cout<<"Found!\n";
        return true;
    }
    else if(root->data < key) {
        return search(root->right, key);
    }
    else {
        return search(root->left, key);
    }
}

void levelOrderTraversal(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); 

        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();

            cout << current->data << " ";

            // Enqueue left and right children
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        cout << endl; 
    }
}


Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == nullptr) return root;

    if (value < root->data) {
        root->left = deleteNode(root->left, value); 
    } 
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } 
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


int main(){
     Node* root = nullptr;
    while(true) {
        cout<<endl;
        cout<<endl;
        cout<<"What you want to do :\n";
        cout<<"1-->Insert in BST\n";
        cout<<"2-->Inorder Display\n";
        cout<<"3-->Preorder Display\n";
        cout<<"4-->Postorder Display\n";
        cout<<"5-->BFS\n";
        cout<<"6-->Delete in BST\n";
        cout<<"7-->Search in BST\n";
        int dir;
        cin>>dir;
        if(dir==1) {
            while(true) {
                cout<<"Enter data to insert : "; 
                int data;
                cin>>data;
                if(data==-1) {
                    break;
                }
            root = insert(root,data);
            }
        }
        if(dir==2) {
            inorder(root);
        }
        if(dir==3) {

            preorder(root);
        }
        if(dir==4) {
            postorder(root);

        }
        if(dir==5) {
            levelOrderTraversal(root);
        }
        if(dir==6) {
            int data;
            cout<<"Enter what you want to delete : \n";
            cin>>data;
            bool res = deleteNode(root, data);
            cout<<res;
        }
        if(dir==7) {
            int key;
            cout<<"Enter what you wanna search : \n";
            cin>>key;
            search(root, key);
        }
        if(dir==-1) {
        break;     
        }
    }
    
    
    return 0;
}

// 4 3 5 1 6 2 7