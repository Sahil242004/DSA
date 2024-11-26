#include<iostream>
#include<math.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

Node* buildTree(Node* root) {
    cout<<"Enter the data : "<<endl;
    int data;
    cin>>data;

    if(data==-1) {
        return nullptr;
    }

    root = new Node(data);
    cout<<"Enter the data to insert at left of "<<root->data<<endl;
    root->left = buildTree(root->left);
    cout<<"Enter the data to insert at right of "<<root->data<<endl;
    root->right = buildTree(root->right);

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

int depth(Node* root) {
    if(root == nullptr) {
        return 0;
    }

    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);
    return 1 + max(leftDepth, rightDepth);
}


void leafNode(Node* root) {
    if(root==nullptr) {
        return;
    }

    if(root->left == nullptr && root->right == nullptr) {
        cout<<root->data<<" ";
    }
     leafNode(root->left);
     leafNode(root->right);
}


Node* copyTree(Node* root) {
    if (root == nullptr) {
        return nullptr;
    }

    Node* newNode = new Node(root->data);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

int main() {
    
        Node* root = nullptr;
    while(true) {
        cout<<endl;
        cout<<endl;
        cout<<"What you want to do :\n";
        cout<<"1-->Build tree\n";
        cout<<"2-->Inorder Display\n";
        cout<<"3-->Preorder Display\n";
        cout<<"4-->Postorder Display\n";
        cout<<"5-->Depth\n";
        cout<<"6-->Leaf Node\n";
        cout<<"7-->Create copy\n";
        int dir;
        cin>>dir;
        if(dir==1) {
            root = buildTree(root);
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
            cout<<"depth of tree is: "<<depth(root)<<endl;
        }
        if(dir==6) {
            cout<<"leaf node are: ";
            leafNode(root);
        }
        if(dir==7) {
            copyTree(root);
            cout<<"Tree copy has been created";
        }
        if(dir==-1) {
        break;     
        }
    }
    
    
    // cout<<endl;
    // cout<<"--------------------"<<endl;
    // cout<<depth(root);
    // cout<<endl;
    // cout<<"-----------------"<<endl;
    // leafNode(root);
    // cout<<endl;
    // cout<<"-----------------"<<endl;
    // inorder(root);
    return 0;
}

// 1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 7 -1 -1

// cout<<"Enter data by insert : ";
//     int d;
//     cin>>d;
//     insert(root, d)