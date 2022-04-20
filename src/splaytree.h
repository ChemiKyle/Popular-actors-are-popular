//references:
//concept of splay function: geeks for geeks: https://www.geeksforgeeks.org/splay-tree-set-1-insert/
// insert function code: Prof Aman's trees and balanced trees lecture slides
//code for rotations: stepik assignments
//code for rotations and deleteNode method: Afnan Syed's Gator AVL (Project1)
//concept for deletion: Jenny's Lectures https://www.youtube.com/watch?v=ewRSYHStdSA&t=216s

#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

//code also used in Afnan Syed's Gator AVL (Project1)
struct Node{
    string name;
    string work;
    int id;
    Node* left;
    Node* right;

    Node(){
        name = "";
        work = "";
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
    //code also used in Afnan Syed's Gator AVL (Project1)
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
    //code also used in Afnan Syed's Gator AVL (Project1)
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
    //code also used in Afnan Syed's Gator AVL (Project1)
    Node* rotateLeftRight(Node *node){
        node->left = rotateLeft(node->left);  //perform left rotation on the root's left node
        Node* p = rotateRight(node);  //perform right rotation on the root
        return p; //return node
    }

    //code reference from Prof. Aman Lecture 4 Balanced Trees Lecture Slides
    //code also used for submission on stepik 5.1.3
    //code also used in Afnan Syed's Gator AVL (Project1)
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
        while(root->id != id ){
            //given id is greater than the root id, go into the right subtree
            if(id > root->id ){
                if(id == root->right->id){
                    root = rotateLeft(root);
                }
                    //if given id is greater than the root's right child id, it is right heavy, perform left-left rotation
                    //to bring the grandchild to the root
                else if(id > root->right->id && root->right->right != nullptr){
                    root = rotateLeft(root);
                    root = rotateLeft(root);
                }
                    //if given id is less than the root's right child, right-left rotation
                else if(id < root->right->id && root->right->left != nullptr ){
                    root = rotateRightLeft(root);
                }
                    //if the root does not have any grandchildren from the right subtree, do only left rotation
                else if(root->right != nullptr && root->right->right == nullptr && root->right->left == nullptr){
                    root = rotateLeft(root);
                }
                else{
                    return root;
                }
            }

                //given id is less than the root id, go into the left subtree
            else if(id < root->id) {

                if(id == root->left->id){
                    root = rotateRight(root);
                }
                    //if given id is less than the root's less child id, it is left heavy, perform right-right rotation
                    //to bring the grandchild to the root
                else if (id < root->left->id && root->left->left != nullptr) {
                    root = rotateRight(root);
                    root = rotateRight(root);
                }
                    //if given id is greater than the root's left child, left-right rotation
                else if (id > root->left->id && root->left->right != nullptr) {
                    root = rotateLeftRight(root);
                }
                    //if the root does not have any grandchildren from the left subtree, do only right rotation
                else if (root->left != nullptr && root->left->right == nullptr && root->left->left == nullptr) {
                    root = rotateRight(root);
                }
                else{
                    return root;
                }
            }

        }

        //return root of the tree
        return root;
    }



    //insert helper function
    //concept used from Prof Aman Lecture 3 Trees slides pg 34
    Node* insertNAMEID(Node* root, string name, int id, string work){

        //create new node
        Node* newNode = new Node(name, id, work);

        //if root is empty
        if(root == nullptr){
            return newNode;
        }
            //graft the rest of the tree as either the right or left child
        else if(root->id == id){
            return root;
        }
        else if(id > root->id){
            newNode->left = root;
        }
        else if(id < root->id){
            newNode->right = root;
        }

        return newNode; //return root
    }


    //print largest node is the tree
    void largest(Node* root, int& l){
        if(root == nullptr){ //if tree is empty
        }
        else{
            //if current id is greater than the previous largest
            if(root->id > l){
                l = root->id;
            }
            printPreorder(root->left); //traversal left subtree
            printPreorder(root->right); //traversal right subtree
        }
    }

    //find and splay node with the largest id
    Node* splayLargest(Node* root){
        int large = 0;
        largest(root, large);  //find largest id
        root = splay(root, large);  //splay largest id

        return root;
    }

    //remove function
    //bottom up splaying: splay node, then
    //concept reference: (5.21 splay tree deletion Jenny's Lectures) https://www.youtube.com/watch?v=ewRSYHStdSA&t=216s
    Node* deleteID(Node* root, int id){
        root = splay(root, id);  //splay id
        if(root->left == nullptr && root->right == nullptr){ //if the root has no children
            root = nullptr; //set root to null
            return root;
        }
        else if(root->left != nullptr && root->right == nullptr){ //if root has only left child
            root = root->left; //replace the root with the left child
            return root;
        }
        else if(root->right != nullptr && root->left == nullptr){ //if the root has only right child
            root = root->right; //replace the root with the right child
            return root;
        }
        else{
            Node* r = root->right;  //root's right child
            Node* b = splayLargest(root->left);    //largest node in the left subtree is now root's left child
            Node* y = b->right;    //root's predecessor
            b->right = r;    //assign child's right as root
            r->left = y;    //assign root's left as the predecessor
            return b;
        }
    }

    //search name function, to return the new splayed tree
    Node* searchName(Node* root, int id, string& found) {
        Node* newR = splay(root, id);
        //if id is found
        if(newR->id == id){
            found = "sucessful";
        }
            //if id is not found
        else if(newR->id != id){
            found = "unsucessful";
        }
        return newR;
    }


    //print preorder
    //preorder traversal code reference from Prof Aman Lecture 3 Trees slides pg 40
    void printPreorder(Node* root){
        if(root == nullptr){ //if tree is empty
        }
        else{
            cout << root->name << ":    " << root->work << "   " << root->id << endl; //print current node
            printPreorder(root->left); //traversal left subtree
            printPreorder(root->right); //traversal right subtree
        }
    }


};



/*
//testing functions through main
int main() {

    SplayTree spl;

    string found = "";

    //insert name, id, and work
    spl.n = spl.insertNAMEID(spl.n, "Christian Bale", 1, "Batman: The Dark Knight Rises");
    spl.n = spl.insertNAMEID(spl.n, "Greta Gerwig", 2, "Lady Bird");
    spl.n = spl.insertNAMEID(spl.n, "Cillian Murphy", 3, "Peaky Blinders");
    spl.n = spl.insertNAMEID(spl.n, "Tom Cruise", 4, "Mission Impossible");
    spl.n = spl.insertNAMEID(spl.n, "Ann Hathaway", 5, "Inception");
    spl.n = spl.insertNAMEID(spl.n, "Mads Mikkelsen", 6, "Hannibal");

    //print preorder
    cout << "Pre order traversal of tree after insertion" << endl;
    spl.printPreorder(spl.n);

    //search Tom Cruise
    spl.n = spl.searchName(spl.n,4, found);

    cout << endl << endl;


    cout << "Pre order traversal of tree after search" << endl;
    //print preorder
    spl.printPreorder(spl.n);


    //delete
    spl.n = spl.deleteID(spl.n,3);

    cout << endl << endl;
    cout << "Pre order traversal of tree after deletion" << endl;
    //print preorder
    spl.printPreorder(spl.n);


    return 0;
};
 */
