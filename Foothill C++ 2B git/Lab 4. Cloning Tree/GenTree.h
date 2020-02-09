//
//  GenTree.h
//  GenTree - A general tree in the (sibling, child) representation.
//  
//  This header file defines the API and has been written for you.
//  You need to complete the implementation of this class in the
//  corresponding cpp file.
//
//  Note: We're gonna expose Node as public in this lab. This way you
//  can run quick and easy tests on the tree algorithms from main.
//  When you're satisfied with the data manipulation code, you can
//  make Node private and manage all the memory within the class.
//  In professionally released code, you would typically not expose
//  the payload container.
//
//  Created by Anand Venkataraman on 12/24/18.
//  Copyright © 2018 Anand Venkataraman. All rights reserved.
//

#ifndef GenTree_h
#define GenTree_h

#include <iostream>

class GenTree {
public:
    class Node;
    
private:
    Node *root;
    
public:
    GenTree(Node *p = nullptr) : root(p) {}
    GenTree(const GenTree& that) { *this = that; }
    GenTree& operator=(const GenTree& that); // Deep clone

    Node *getRoot() const { return root; }
    Node *setRoot(Node *p) { return root = p; }
    std::string toString() const;
    bool deleteNodes();

    // The == operator returns true if the two trees are structurally
    // identical. But actual node pointers may be different.
    bool operator==(const GenTree& that) const;
    bool operator!=(const GenTree& that) const { return !(*this == that); }
    friend std::ostream& operator<<(std::ostream& os, const GenTree& tree) {
        return os << tree.toString();
    };

    // inner class
    class Node {
    private:
        std::string data;
        Node *sibling, *child;
        
    public:
        Node(std::string s = "") : data(s), sibling(nullptr), child(nullptr) {}
        Node(const Node& that);
        const Node& operator=(const Node& that); // Deep clone
        ~Node();

        void setData(std::string s) { data = s; }
        void setSibling(Node *p) { sibling = p; }
        void setChild(Node *p) { child = p; }
        std::string getData() const { return data; }
        Node *getSibling() const { return sibling; }
        Node *getChild() const { return child; }
        
        bool operator==(const Node& that) const;
        bool operator!=(const Node& that) const { return !(*this == that); }
    };
};

#endif /* GenTree_h */
