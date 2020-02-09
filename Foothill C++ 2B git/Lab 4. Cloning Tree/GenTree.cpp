//
//  GenTree.cpp
//  GenTree - Out-of-line method defs
//
//  Created by Anand Venkataraman on 12/24/18.
//  Copyright © 2018 Anand Venkataraman. All rights reserved.
//
//  Your piece of the cake is to complete the TODO items. I've made sure
//  to leave enough tasty bits for you.
//

#include "GenTree.h"

#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

// Helper function. Calls the overloaded Node equality operator
// after making the necessary null checks for trivial cases.
// Note that the final check is the recursive equality test
// between Nodes (not node pointers)
bool isEqual(GenTree::Node *p, GenTree::Node *q) {
    if (p == nullptr && q != nullptr) return false;
    if (p != nullptr && q == nullptr) return false;
    if (p != nullptr && q != nullptr && *p != *q)
        return false;
    return true;
}

// NOTE: We only need this to be public if an external source allocates and
// adds nodes on the heap to the tree. Once the tree code is polished up
// clients should only have to deal with the payload and the GenTree destructor
// ought to take care of freeing memory allocated during GenTree inserts.
bool GenTree::deleteNodes() {
    if (this->root == nullptr) return false;

    delete this->root; // MAKE SURE GenTree::Node has a recursively defined destructor.
    return true;
}

// Recursive equivalence check. Two trees are equivalent if
// every node has the same set of siblings in the same order AND
// the same set of children in the same order.
bool GenTree::operator==(const GenTree& that) const {
    return isEqual(this->root, that.root);
}

// Again, I'm gonna give this method to you 'cuz it's too much fun. If you want
// to do it yourself. Delete it and implement your own. Maybe recursively first
// and then non-recursively.
//
// Non-recursive tree dump starting at root (= this)
// Format - Multiple lines of the form:
//    root: RootData
//    RootData: child_1 child_2 ...
//    child_1: child_11 child_12 ...
//    child_11: child_111 child_112 ...
//    ...
string GenTree::toString() const {
    if (this->root == nullptr) return "";
    
    stringstream ss;
    queue<Node *> nq;

    ss <<"# ROOT is " << root->getData() <<"\n";
    ss <<"# The following lines are of the form:\n";
    ss <<"#   node: child1 child2...\n";
    nq.push(root);
    
    while(!nq.empty()) {
        Node *p = nq.front(); nq.pop(); // Node to process
        // Print the node and all its children, push each child
        ss << p->getData() << ":";
        for (p = p->getChild(); p != nullptr; p = p->getSibling()) {
            ss << " " << p->getData();
            if (p->getChild() != nullptr) nq.push(p);
        }
        ss << "\n";
    }
    
    return ss.str();
}

// ---- GenTree::Node methods --------------------------------------------------

// Recursive copy ctr
GenTree::Node::Node(const GenTree::Node& that) {
   // TODO
   /* Type your code here */
    this->setData(that.getData());
   this->sibling = that.sibling == nullptr? nullptr : new Node(*that.sibling);
   /* Type your code here */
   this->child = that.child == nullptr? nullptr : new Node(*that.child);
}

// Recursive destructor. I'm gonna give this to you. It could really
// mess your day up (or make it) if you get this wrong.
GenTree::Node::~Node() {
    if (this->sibling != nullptr) delete this->sibling;
    if (this->child != nullptr) delete this->child;
}

// Assignment operator: Create a deep clone of that into this.
// Diff pointers, but same content in the same relative positions.
GenTree& GenTree::operator=(const GenTree& that) {
    // TODO
    /* Type your code here */
    Node* root = this->getRoot();
    // If root is not nullptr, then first delete the tree.
    if (root != nullptr) {
        delete root;
    }
    
    // Deep copy the tree.
    this->setRoot(new Node(*that.getRoot()));
    return *this;
}

// A node, p, is "considered" equivalent to another node q IFF
//  they have "equal" data AND
//  their next siblings are "equal" AND
//  their first children are "equal" to each other
bool GenTree::Node::operator==(const GenTree::Node& that) const {
    // TODO
    /* Type your code here */
    // If data not equal, return false.
    if (this->getData() != that.getData()) return false;
    
    // If sibling not equal, return false.
    if ((this->getSibling() != nullptr && that.getSibling() == nullptr) ||
        (this->getSibling() == nullptr && that.getSibling() != nullptr) ||
        (this->getSibling() != nullptr &&
         that.getSibling() != nullptr &&
         *this->getSibling() != *that.getSibling())) {
        return false;
    }
    
    // If child not equal, return false;
    if ((this->getChild() != nullptr && that.getChild() == nullptr) ||
        (this->getChild() == nullptr && that.getChild() != nullptr) ||
        (this->getChild() != nullptr &&
         that.getChild() != nullptr &&
         *this->getChild() != *that.getChild())) {
            return false;
    }
    return true;
}
