#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <fstream>
using namespace std;

class Node {
    public:
        bool isLeaf;
        vector<int> keys;
        Node* ptr2next;
        union ptr {
            vector<Node*> ptr2Tree;
            vector<FILE*> dataPtr;
            ptr();
            ~ptr();
        } ptr2TreeOrData;
        friend class BPlusTree;
    public:
        Node();
};

class BPlusTree {
    private:
        int maxIntChildLimit;
        int maxLeafNodeLimit;
        Node* root;
        void insertInternal(int x, Node** cursor, Node** child);
        Node** findParent(Node* cursor, Node* child);
        Node* firstLeftNode(Node* cursor);
    public:
        BPlusTree();
        BPlusTree(int degreeInternal, int degreeLeadf);
        Node* getRoot();
        int getMaxIntChildLimit();
        int getMaxLeafNodeLimit();
        void setRoot(Node*);
        void display(Node* cursor);
        void seqDisplay(Node* cursor);
        void search(int key);
        void insert(int key, FILE* filePtr);
        void removeKey(int key);
        void removeInternal(int x, Node* cursor, Node* child);
};

#endif