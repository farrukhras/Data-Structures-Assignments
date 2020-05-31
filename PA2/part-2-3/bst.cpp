#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
void BST<T>::DestroyHelper(node<T>* node)
{
   // Delete node and it's children
   if (node != NULL)
   {
      DestroyHelper(node->left);
      DestroyHelper(node->right);
      delete node;
   }
}

template <class T>
BST<T>:: ~BST(){
    DestroyHelper(root);
}

template <class T>
int BST<T> :: height (node<T>* p){
    //return p == NULL ? 0 : p->height;
    if (p == NULL)
    {
        return 1;
    }
    else
    {
        int leftheight = height(p->left);
        int rightheight = height(p->right);

        if (leftheight > rightheight)
        {
            return 1 + leftheight;
        }
        else
        {
            return 1 + rightheight;
        }
    }
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return height(p->left) - height(p->right);
    }
}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
    // use this function to fix height of a node after insertion or deletion.

    p->height = height(p);

    return;
}

// ROTATING HELPERS
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
    //RIGHT RIGHT CASE
    node<T> *newroot = p->right; //newroot points to the root that will become the new root node after rotation
    p->right = newroot->left;

    newroot->left = p; // sets old root node as the left child of the new root node

    p->height = max(height(p->left), height(p->right)) + 1;
    newroot->height = max(height(newroot->right), p->height) + 1;

    p = newroot;
    //return p;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){
    //LEFT LEFT CASE
    node<T> *newroot = p->left; //newroot points to the root that will become the new root node after rotation
    p->left = newroot->right; // the right child of the to be new root node is now the left child of the old root node

    newroot->right = p; // sets old root node as the right child of the new root node

    p->height = 1 + max(height(p->left), height(p->right));
    newroot->height = 1 + max(height(newroot->left), p->height);

    p = newroot;
    //newroot->height = height(newroot);

    //return p;
}


template <class T>
node<T>* BST<T> :: balance(node<T>* p){
    //fixHeight(p);

    // ROTATION CASES FOR INSERTION

    int balfactor = balanceFactor(p);
    int balfactor1 = height(p->right) - height(p->left);

    // LEFT LEFT CASE
    if (balfactor > 1 && height(p->left->left) >= height(p->left->right))
    {
        return rotateright(p);
    }

    // RIGHT RIGHT CASE
    else if (balfactor < -1 && height( p->right->right ) >= height( p->right->left ))
    {
        return rotateleft(p);
    }

    //LEFT RIGHT CASE
    else if (balfactor > 1 && height(p->left->left) < height(p->left->right))
    {
        p->left = rotateleft(p->left);
        return rotateright(p);
    }

    // RIGHT LEFT CASE
    else if (balfactor < -1 && height(p->right->right) < height(p->right->left))
    {
        p->right = rotateright(p->right);
        return rotateleft(p);
    }

    p->height = max(height(p->left), height(p->right)) + 1;


    return p;
}

// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){
    root = insertHelper(value,k,root);
}

// insertion helper
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    if (p == NULL)
    {
        node<T> *temp = new node<T>(k, value);
        return temp;
    }
    if (k < p->key)
    {
        p->left = insertHelper(value, k, p->left);
    }
    else if (k > p->key)
    {
        p->right = insertHelper(value, k, p->right);
    }

    //return p;
    return balance(p);
}

template<class T>
node<T>* BST<T> :: search(T key){

    if (root == NULL || root->key == key)
    {
        return root;
    }

    node<T> *temp = root;
    while (temp != NULL && temp->key != key)
    {
        if (key < temp->key)
        {
            temp = temp->left;
        }
        else if (key > temp->key)
        {
            temp = temp->right;
        }
    }
    return temp;
}

// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){

    if (p == NULL)
    {
        return p;
    }

    else if (p->left == NULL)
    {
        return p;
    }
    else
    {
        return findmin(p->left);
    }
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
    return balance(p);
}

template<class T>
void BST<T>::printmin(){
    node<T>* temp = findmin(root);
    cout<<"MINIMUN IS: "<<temp->key<<endl;
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
    //Base case: if our root node is NULL
    if (p == NULL)
    {
        return p;
    }

    // if our key is less than root node ki key then we move into the left subtree of the root
    if (k < p->key)
    {
        p->left = remove(p->left, k);
    }

    // if our key is less than root node ki key then we move into the left subtree of the root
    else if (k > p->key)
    {
        p->right = remove(p->right, k);
    }

    // if we have found the key to be deleted then we implement the following code
    else
    {
        node<T> *temp;

        // CASE 1: root with no child or root with one child
        if (p->right == NULL)
        {
            temp = p->left;
            delete p;
            return temp;
        }

        else if (p->left == NULL)
        {
            temp = p->right;
            delete p;
            return temp;
        }

        // CASE 2: root with 2 children,
        //we find the in order successor of the node
        //and the smallest key in that subtree and replace
        //it with the node to be deleted
        node<T> *temp1 = findmin(p->right);
        p->key = temp1->key;
        p->right = remove(p->right, temp1->key);
    }

    //return p;
    return balance(p);
}

template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}
#endif
