//code, concept, pseudocode references:
//splay function: geeks for geeks: https://www.geeksforgeeks.org/splay-tree-set-1-insert/
//Prof Aman's trees and balanced trees lecture slides
//stepik assignments
//Afnan Syed's Gator AVL (Project1)

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

    Node(){
        name = " ";
        work = " ";
        id = 0;
        left = nullptr;
        right = nullptr;
    }
    Node(string name, int id, string work){
        this->name = name;
        this->id = id;
        this->work = work;
        left = nullptr;
        right = nullptr;
    }
};

class SplayTree {

public:
    Node *n = nullptr;

    //code reference from Prof. Aman Lecture 4 Balanced Trees Lecture Slides pg. 12
    //code also used for submission on stepik 5.1.1
    Node* rotateLeft(Node *node){
        //your code here
        Node* a = node;  //root node
        Node* b = a->right;   //right child
        Node* x = a->right->left;  //root's successor
        b->left = a;  //assign child's left as root
        a->right = x;  //assign root's right as the successor

        return b;
    }


    //code reference from Prof. Aman Lecture 4 Balanced Trees Lecture Slides pg. 12
    //code also used for submission on stepik 5.1.1
    Node* rotateRight(Node *node){
        //your code here
        Node* c = node;    //root node
        Node* b = c->left;    //left child
        Node* y = c->left->right;    //root's predecessor
        b->right = c;    //assign child's left as root
        c->left = y;    //assign root's right as the predecessor

        return b;
    }


    //code reference from Prof. Aman Lecture 4 Balanced Trees Lecture Slides
    //code also used for submission on stepik 5.1.1
    Node* rotateLeftRight(Node *node){
        node->left = rotateLeft(node->left);  //perform left rotation on the root's left node
        Node* p = rotateRight(node);  //perform right rotation on the root
        return p; //return node
    }

    //code reference from Prof. Aman Lecture 4 Balanced Trees Lecture Slides
    //code also used for submission on stepik 5.1.3
    Node* rotateRightLeft(Node *node){
        node->right = rotateRight(node->right);  //perform right rotation on the root's right node
        Node* p = rotateLeft(node);  //perform left rotation on the root
        return p; //return node
    }


    //code concept reference from Prof. Amn
    //concept reference used to write this code: geeks for geeks: https://www.geeksforgeeks.org/splay-tree-set-1-insert/
    Node* splay(Node* root, int id){
        //if id at the root is the id given in the parameter, return root
        if(root->id == id){
            return root;
        }
        //while root id is not the given id
        while(root->id != id){
            //given id is greater than the root id, go into the right subtree
            if(id > root->id){
                //if given id is greater than the root's right child id, it is right heavy, perform left-left rotation
                //to bring the grandchild to the root
                if(id > root->right->id && root->right->right != nullptr){
                    root = rotateLeft(root);
                    root = rotateLeft(root);
                }
                    //if given id is less than the root's right child, right-left rotation
                else if(id < root->right->id && root->right->left != nullptr){
                    root = rotateRightLeft(root);
                }
                    //if the root does not have any grandchildren from the right subtree, do only left rotation
                else{
                    root = rotateLeft(root);
                }
            }

                //given id is less than the root id, go into the left subtree
            else if(id < root->id){
                //if given id is less than the root's less child id, it is left heavy, perform right-right rotation
                //to bring the grandchild to the root
                if(id < root->left->id && root->left->left != nullptr){
                    root = rotateRight(root);
                    root = rotateRight(root);
                }
                    //if given id is greater than the root's left child, left-right rotation
                else if(id > root->left->id && root->left->right != nullptr){
                    root = rotateLeftRight(root);
                }
                    //if the root does not have any grandchildren from the left subtree, do only right rotation
                else{
                    root = rotateRight(root);
                }
            }
        }

        //return root of the tree
        return root;
    }



    //insert helper function
    //code used from Prof Aman Lecture 3 Trees slides pg 34
    Node* insertNAME(Node* root, string name, int id, string work){

        //insert new node
        if (root == nullptr){
            return new Node(name, id, work);
        }
        //if id is less than the current node id, go in the left subtree
        if (id < root->id){
            root->left = insertNAME(root->left, name, id, work);
        }
            //if id is greater than the current node id, go in the right subtree
        else{
            root->right = insertNAME(root->right, name, id, work);
        }
        return root; //return root
    }

    //insert function
    Node* insertNAMEID(Node* root, string name, int id, string work){
        root = insertNAME(root, name, id, work); //insert
        root = splay(root, id); //splay
        return root;
    }

    //print Left most node (left most leaf node)
    Node* leftMost(Node* root){
        if(root->left == nullptr){ //if the next node is null
            return root; //return current root which is the left most leaf node
        }
        else{
            leftMost(root->left); //traversal through the left nodes
        }

        return root;
    }

    //delete node
    //code from Afnan Syed's Project 1 Gator AVL delete
    //iterating through the tree to get to id: concept reference : Jenny's lectures CS/IT NET&JRF video:
    //https://www.youtube.com/watch?v=ewRSYHStdSA
    Node* deleteNode(Node* root, int id) {

        Node *curr = root;  //create current node tracker
        Node *prev = nullptr;

        //while not at a wanted node
        while (curr->id != id) {
            //if current id is greater than the given id prev
            prev = curr;
            if (curr->id < id) {    //go into the right subtree
                curr = curr->right;
            }
                //if current id is less than the given id
            else if (curr->id > id) {
                curr = curr->left;  //go into the left subtree
            }
        }
        int previd = prev->id;

        //the id matches the current id
        if (curr->left == nullptr && curr->right == nullptr) { //if the current has no children
            delete curr; //set current to null
        }
        else if (curr->left != nullptr && curr->right == nullptr) { //if current has only left child
            curr = curr->left; //replace the current with the left child
        }
        else if (curr->right != nullptr && curr->left == nullptr) { //if the current has only right child
            curr = curr->right; //replace the current with the right child
        }
        else { //find the inorder successor
            if (curr->right->left == nullptr) { //if the current's right child has no left child
                //concept reference for deleting a node in an avl tree:
                //https://www.youtube.com/watch?v=LXdi_4kSd1o ("5.15 AVL Tree Deletion in Data structures" by Jenny's Lectures)
                //replace the current root with the current's right child
                curr->id = curr->right->id;
                curr->name = curr->right->name;
                curr->right = curr->right->right;
            }
            else {
                Node *nod = leftMost(root->right); //find the left most child of the subtree of the current's right child
                //concept reference for deleting a node in an avl tree:
                //https://www.youtube.com/watch?v=LXdi_4kSd1o ("5.15 AVL Tree Deletion in Data structures" by Jenny's Lectures)
                //reference TA Andrew Penton on Slack
                //replace the current root with the left most child
                curr->id = nod->id;
                curr->name = nod->name;
                delete nod;
                nod = nullptr; //assign that left most child as null

            }

        }

        root = splay(root, previd);


        return root;
    }

    //search name function, to return the new splayed tree
    Node* searchName(Node* root, int id) {
        Node* newR = splay(root, id);
        return newR;
    }


    //print preorder
    //preorder traversal code reference from Prof Aman Lecture 3 Trees slides pg 40
    void printPreorder(Node* root){
        if(root == nullptr){ //if tree is empty
        }
        else{
            cout << root->name << ": " << root->work << " " << root->id << endl; //print current node
            printPreorder(root->left); //traversal left subtree
            printPreorder(root->right); //traversal right subtree
        }
    }


};


int main() {
    SplayTree spl;





/*
   for(int i=0; i<100000; i++){
       spl.n = spl.insertNAMEID(spl.n, "Greta Gerwig", i, "lady bird");
   }
   */


    spl.n = spl.insertNAMEID(spl.n, "Greta Gerwig", 5, "lady bird");
    spl.n = spl.insertNAMEID(spl.n, "Tom Hiddleston", 20, "avengers");
    spl.n = spl.insertNAMEID(spl.n, "Cillian Murphy", 7, "peaky blinder");
    spl.n = spl.insertNAMEID(spl.n, "Tom Holland", 3, "actor");
    spl.n = spl.insertNAMEID(spl.n, "Johnny Depp", 25, "pirates of the carrabian");

    //   int num = 0;
    // spl.searchID(spl.n,"Tom Holland", 3);
    //  cout << num << endl;
    spl.n = spl.searchName(spl.n,25);
    //   cout << spl.n->work << endl;

    spl.n = spl.deleteNode(spl.n, 7);
    spl.printPreorder(spl.n);
    // cout << spl.n->name << " " << spl.n->id << endl;

    return 0;
};