#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

struct Node{
    string name;
    string work;
    int id;
    Node* left;
    Node* right;
    Node* parent;

    Node(){
        name = " ";
        work = " ";
        id = 0;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    Node(string name, int id, string work){
        this->name = name;
        this->id = id;
        this->work = work;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class SplayTree {

public:
    Node *n = nullptr;
    Node* pa = nullptr;
    Node* splayNode = nullptr;

    //code reference from Prof. Aman Lecture 4 Balanced Trees Lecture Slides pg. 12
    //code also used for submission on stepik 5.1.1
    Node *rotateLeft(Node *node) {
        Node *a = node;  //root node
        Node *b = a->right;   //right child
        Node *x = a->right->left;  //root's successor
        Node* g = a->parent;
        b->left = a;  //assign child's left as root
        a->right = x;  //assign root's right as the successor
        a->parent = b;
        x->parent = a;
        b->parent = g;

        return b;
    }

    //code reference from Prof. Aman Lecture 4 Balanced Trees Lecture Slides pg. 12
    //code also used for submission on stepik 5.1.1
    Node* rotateRight(Node *node)
    {
        Node* c = node;    //root node
        Node* b = c->left;    //left child
        Node* y = c->left->right;    //root's predecessor
        Node* g = c->parent;
        b->right = c;    //assign child's right as root
        c->left = y;    //assign root's left as the predecessor
        c->parent = b;
        y->parent = c;
        b->parent = g;


        return b;
    }


    //code reference from Prof. Aman Lecture 4 Balanced Trees Lecture Slides
    //code also used for submission on stepik 5.1.1
    Node* rotateLeftRight(Node *node)
    {
        node->left = rotateLeft(node->left);  //perform left rotation on the root's left node
        Node* p = rotateRight(node);  //perform right rotation on the root
        return p; //return node
    }

    //code reference from Prof. Aman Lecture 4 Balanced Trees Lecture Slides
    //code also used for submission on stepik 5.1.3
    Node* rotateRightLeft(Node *node)
    {
        node->right = rotateRight(node->right);  //perform right rotation on the root's right node
        Node* p = rotateLeft(node);  //perform left rotation on the root
        return p; //return node
    }


    Node* splay(Node* root, Node* curr){
        while(curr->parent != nullptr) {

            //if parent is the root
            if (curr->parent->parent == nullptr) {
                //child is left child
                if (curr == curr->parent->left) {
                    curr = rotateRight(curr->parent);
                }
                    //child is right child
                else if (curr == curr->parent->right) {
                    curr = rotateLeft(curr->parent);

                }
            }

            else{
                //left-left heavy, right-right
                if(curr == curr->parent->left && curr->parent == curr->parent->parent->left){
                    curr = rotateRight(curr->parent->parent);
                    curr = rotateRight(curr->parent);
                }
                //right-right heavy, left-left
                else if(curr == curr->parent->right && curr->parent == curr->parent->parent->right){
                    curr = rotateLeft(curr->parent->parent);
                    curr = rotateLeft(curr->parent);
                }
                //left-right
                else if(curr == curr->parent->left && curr->parent == curr->parent->parent->right){
                    curr = rotateLeftRight(curr->parent->parent);
                }
                //right-left
                else if(curr == curr->parent->right && curr->parent == curr->parent->parent->left){
                    curr = rotateRightLeft(curr->parent->parent);
                }

            }
        }
        return curr;
    }



    //insert helper function
    //code used written by Prof Aman Lecture 4 Balanced Trees slides pg 15
    Node* insertN(Node* root, string name, int id, string work, Node* paren){

        if (root == nullptr){
            Node* curr = new Node(name, id, work); //insert node
            curr->parent = paren;
            pa = curr;
            return curr;
        }
        else if (id < root->id){ //if id is less than the current root id
            paren = root;
            root->left = insertN(root->left, name, id, work, paren);
        }
        else { //if id is greater than the current root id
            paren = root;
            root->right = insertN(root->right, name, id, work, paren);
        }

        return root;
    }

    //insert function
    Node* insertNAMEID(Node* root, string name, int id, string work) {
        Node* paren = nullptr;
        root = insertN(root, name, id, work, paren); //insert name and id and return updated tree

      //  root = splay(root, pa);
        return root;
    }

    //search name function
    //preorder traversal reference from Prof Aman Lecture 3 Trees slides pg 38
    void searchName(Node* root, string name) {
        if (root == nullptr) { //if name not found
        } else {
            if (name == root->name) {
                cout << root->name << ": " << root->work << endl; //print current node
                splayNode = root;
            }
            searchName(root->left, name); //traverse through left subtree
            searchName(root->right, name); //traverse through right subtree
        }
    }





    //print inorder
    //inorder traversal code reference from Prof Aman Lecture 3 Trees slides pg 40
    void printInorder(Node* root){
        if(root == nullptr){ //if tree is empty
        }
        else{
            printInorder(root->left); //traversal left subtree
            cout << root->name <<  ": " << root->work << endl; //print current node
            printInorder(root->right); //traversal right subtree
        }
    }


};


int main() {
    SplayTree spl;

    spl.n = spl.insertNAMEID(spl.n, "Tom Hiddleston", 3, "actor");
    spl.n = spl.insertNAMEID(spl.n, "Cillian Murphy", 7, "actor");
    spl.n = spl.insertNAMEID(spl.n, "Tom Hardy", 20, "actor, producer");
    spl.n = spl.insertNAMEID(spl.n, "Greta Gerwig", 28, "actor, writer, director");
    //spl.n = spl.insertNAMEID(spl.n, "Tom Holland", 23, "actor");

      spl.printInorder(spl.n);
      spl.searchName(spl.n,"Cillian Murphy");



        return 0;
    }
