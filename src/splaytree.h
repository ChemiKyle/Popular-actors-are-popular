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
        while(root->id != id){
            //given id is greater than the root id, go into the right subtree
            if(id > root->id){
                if(root->right == nullptr){ //id is not found
                    return root;
                }
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
                if(root->left == nullptr){ //id is not found
                    return root;
                }
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
    //code also used in Afnan Syed's Gator AVL (Project1)
    Node* insertNAME(Node* root, string name, int id, string work){

        //insert new node
        if (root == nullptr){
            return new Node(name, id, work);
        }
        else if(root->id == id){
            return root;
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
    //code also used in Afnan Syed's Gator AVL (Project1)
    Node* leftMost(Node* root){
        if(root->left == nullptr){ //if the next node is null
            return root; //return current root which is the left most leaf node
        }
        else{
            leftMost(root->left); //traversal through the left nodes
        }

        return root;
    }

    //remove helper function
    //code from Afnan Syed's Project 1 Gator AVL delete
    //Code reference also using from the Project 1 Overview slides
    //concept reference for deleting a node in an avl tree:
    //https://www.youtube.com/watch?v=LXdi_4kSd1o ("5.15 AVL Tree Deletion in Data structures" by Jenny's Lectures)
    Node* deleteNode(Node* root, int id, int& prevID) {
        if(root == nullptr){ //if root is null
            return nullptr; //return null
        }
        if (id < root->id){ //if id is less than the root id
            if(root->left->id == id){
                prevID = root->id;
            }
            root->left = deleteNode(root->left, id, prevID); //traversal left subtree  (code from Project 1 Overview Slides)
        }
        else if (id > root->id){ //if id is greater than the root id
            if(root->right->id == id){
                prevID = root->id;
            }
            root->right = deleteNode(root->right, id, prevID); //traversal right subtree
        }
        else{ //the id matches the current id
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
            else{ //find the inorder successor
                if(root->right->left == nullptr){ //if the root's right child has no left child
                    //concept reference for deleting a node in an avl tree:
                    //https://www.youtube.com/watch?v=LXdi_4kSd1o ("5.15 AVL Tree Deletion in Data structures" by Jenny's Lectures)
                    //replace the current root with the root's right child
                    root->id = root->right->id;
                    root->name = root->right->name;
                    root->right = root->right->right;
                    return root;
                }
                else{
                    Node* nod = leftMost(root->right); //find the left most child of the subtree of the root's right child
                    //concept reference for deleting a node in an avl tree:
                    //https://www.youtube.com/watch?v=LXdi_4kSd1o ("5.15 AVL Tree Deletion in Data structures" by Jenny's Lectures)
                    //reference TA Andrew Penton on Slack
                    //replace the current root with the left most child
                    root->id = nod->id;
                    root->name = nod->name;
                    delete nod;
                    nod = nullptr; //assign that left most child as null
                    return root;

                }

            }

        }
        return root;
    }

    //remove function
    //bottom up splaying: delete node first (bst deletion), then splay the parent node
    //concept reference: (5.21 splay tree deletion Jenny's Lectures) https://www.youtube.com/watch?v=ewRSYHStdSA&t=216s
    Node* deleteID(Node* root, int id){
        int prevID; //keep track or previous id
        root = deleteNode(root, id, prevID); //delete node
        root = splay(root, prevID);  //splay previous id
        return root;
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
            cout << root->name << ": " << root->work << " " << root->id << endl; //print current node
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

    spl.n = spl.insertNAMEID(spl.n, "Greta Gerwig", 5, "lady bird");
    spl.n = spl.insertNAMEID(spl.n, "Tom Hiddleston", 20, "avengers");
    spl.n = spl.insertNAMEID(spl.n, "Cillian Murphy", 7, "peaky blinder");
    spl.n = spl.insertNAMEID(spl.n, "Tom Holland", 3, "actor");
    spl.n = spl.insertNAMEID(spl.n, "Johnny Depp", 25, "pirates of the carrabian");


     spl.n = spl.searchName(spl.n,30, found);
   //   spl.n = spl.deleteID(spl.n, 7);
   //   spl.printPreorder(spl.n);
   // cout << spl.n->name << " " << spl.n->id << endl;

        return 0;
    };

*/