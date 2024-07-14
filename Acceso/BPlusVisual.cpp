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
    vector<Node*> ptr2Tree;  // Punteros a otros nodos
    Node* ptr2next;  // Puntero al siguiente nodo hoja
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
    void exportToDot(Node* cursor, ofstream& file);
public:
    BPlusTree();
    BPlusTree(int degreeInternal, int degreeLeaf);
    Node* getRoot();
    int getMaxIntChildLimit();
    int getMaxLeafNodeLimit();
    void setRoot(Node*);
    void display(Node* cursor);
    void insert(int key);
    void search(int key);
    void exportTreeToDot(const string& filename);
};

Node* parent = NULL;

Node::Node() {
    this->isLeaf = false;
    this->ptr2next = NULL;
}

BPlusTree::BPlusTree() {
    this->maxIntChildLimit = 4;
    this->maxLeafNodeLimit = 3;
    this->root = NULL;
}

BPlusTree::BPlusTree(int degreeInternal, int degreeLeaf) {
    this->maxIntChildLimit = degreeInternal;
    this->maxLeafNodeLimit = degreeLeaf;
    this->root = NULL;
}

int BPlusTree::getMaxIntChildLimit() {
    return maxIntChildLimit;
}

int BPlusTree::getMaxLeafNodeLimit() {
    return maxLeafNodeLimit;
}

Node* BPlusTree::getRoot() {
    return this->root;
}

void BPlusTree::setRoot(Node* ptr) {
    this->root = ptr;
}

Node* BPlusTree::firstLeftNode(Node* cursor) {
    if (cursor->isLeaf) {
        return cursor;
    }
    for (int i = 0; i < cursor->ptr2Tree.size(); i++) {
        if (cursor->ptr2Tree[i] != NULL) {
            return firstLeftNode(cursor->ptr2Tree[i]);
        }
    }
    return NULL;
}

void BPlusTree::insert(int key) {
    if (root == NULL) {
        root = new Node;
        root->isLeaf = true;
        root->keys.push_back(key);
    } else {
        Node* cursor = root;
        Node* parent = NULL;
        while (!cursor->isLeaf) {
            parent = cursor;
            for (int i = 0; i < cursor->keys.size(); i++) {
                if (key < cursor->keys[i]) {
                    cursor = cursor->ptr2Tree[i];
                    break;
                }
                if (i == cursor->keys.size() - 1) {
                    cursor = cursor->ptr2Tree[i + 1];
                    break;
                }
            }
        }
        if (cursor->keys.size() < maxLeafNodeLimit) {
            int i = 0;
            while (key > cursor->keys[i] && i < cursor->keys.size()) {
                i++;
            }
            cursor->keys.insert(cursor->keys.begin() + i, key);
        } else {
            vector<int> tempKeys = cursor->keys;
            tempKeys.push_back(key);
            sort(tempKeys.begin(), tempKeys.end());
            int mid = tempKeys.size() / 2;
            cursor->keys.resize(mid);
            cursor->keys.assign(tempKeys.begin(), tempKeys.begin() + mid);

            Node* newLeaf = new Node;
            newLeaf->isLeaf = true;
            newLeaf->keys.assign(tempKeys.begin() + mid, tempKeys.end());
            newLeaf->ptr2next = cursor->ptr2next;
            cursor->ptr2next = newLeaf;

            if (cursor == root) {
                Node* newRoot = new Node;
                newRoot->keys.push_back(newLeaf->keys[0]);
                newRoot->ptr2Tree.push_back(cursor);
                newRoot->ptr2Tree.push_back(newLeaf);
                root = newRoot;
            } else {
                insertInternal(newLeaf->keys[0], &parent, &newLeaf);
            }
        }
    }
}

void BPlusTree::insertInternal(int x, Node** cursor, Node** child) {
    if ((*cursor)->keys.size() < maxIntChildLimit) {
        int i = 0;
        while (x > (*cursor)->keys[i] && i < (*cursor)->keys.size()) {
            i++;
        }
        (*cursor)->keys.insert((*cursor)->keys.begin() + i, x);
        (*cursor)->ptr2Tree.insert((*cursor)->ptr2Tree.begin() + i + 1, *child);
    } else {
        vector<int> tempKeys = (*cursor)->keys;
        vector<Node*> tempPtr = (*cursor)->ptr2Tree;
        int i = 0;
        while (x > tempKeys[i] && i < tempKeys.size()) {
            i++;
        }
        tempKeys.insert(tempKeys.begin() + i, x);
        tempPtr.insert(tempPtr.begin() + i + 1, *child);
        int mid = tempKeys.size() / 2;

        Node* newInternal = new Node;
        newInternal->keys.assign(tempKeys.begin() + mid + 1, tempKeys.end());
        newInternal->ptr2Tree.assign(tempPtr.begin() + mid + 1, tempPtr.end());

        (*cursor)->keys.resize(mid);
        (*cursor)->ptr2Tree.resize(mid + 1);

        if (*cursor == root) {
            Node* newRoot = new Node;
            newRoot->keys.push_back(tempKeys[mid]);
            newRoot->ptr2Tree.push_back(*cursor);
            newRoot->ptr2Tree.push_back(newInternal);
            root = newRoot;
        } else {
            insertInternal(tempKeys[mid], findParent(root, *cursor), &newInternal);
        }
    }
}

Node** BPlusTree::findParent(Node* cursor, Node* child) {
    if (cursor->isLeaf || cursor->ptr2Tree[0]->isLeaf) {
        return NULL;
    }
    for (int i = 0; i < cursor->ptr2Tree.size(); i++) {
        if (cursor->ptr2Tree[i] == child) {
            return &cursor;
        } else {
            Node** parent = findParent(cursor->ptr2Tree[i], child);
            if (parent != NULL) {
                return parent;
            }
        }
    }
    return NULL;
}

void BPlusTree::display(Node* cursor) {
    if (cursor != NULL) {
        for (int i = 0; i < cursor->keys.size(); i++) {
            cout << cursor->keys[i] << " ";
        }
        cout << endl;
        if (!cursor->isLeaf) {
            for (int i = 0; i < cursor->ptr2Tree.size(); i++) {
                display(cursor->ptr2Tree[i]);
            }
        }
    }
}

void BPlusTree::search(int key) {
    if (root == NULL) {
        cout << "Tree is empty\n";
    } else {
        Node* cursor = root;
        while (cursor != NULL) {
            for (int i = 0; i < cursor->keys.size(); i++) {
                if (key < cursor->keys[i]) {
                    cursor = cursor->ptr2Tree[i];
                    break;
                }
                if (i == cursor->keys.size() - 1) {
                    cursor = cursor->ptr2Tree[i + 1];
                    break;
                }
            }
            if (cursor->isLeaf) {
                for (int i = 0; i < cursor->keys.size(); i++) {
                    if (cursor->keys[i] == key) {
                        cout << "Found\n";
                        return;
                    }
                }
                cout << "Not found\n";
                return;
            }
        }
        cout << "Not found\n";
    }
}

void BPlusTree::exportToDot(Node* cursor, ofstream& file) {
    if (cursor != NULL) {
        if (cursor->isLeaf) {
            file << "  node" << cursor << " [label=\"";
            for (int i = 0; i < cursor->keys.size(); i++) {
                file << cursor->keys[i];
                if (i < cursor->keys.size() - 1) file << "|";
            }
            file << "\", shape=record];\n";
        } else {
            file << "  node" << cursor << " [label=\"<f0>";
            for (int i = 0; i < cursor->keys.size(); i++) {
                file << "|<f" << i + 1 << ">" << cursor->keys[i];
            }
            file << "\", shape=record];\n";
        }

        if (!cursor->isLeaf) {
            for (int i = 0; i < cursor->ptr2Tree.size(); i++) {
                if (cursor->ptr2Tree[i] != NULL) {
                    file << "  node" << cursor << ":f" << i << " -> node" << cursor->ptr2Tree[i] << ";\n";
                    exportToDot(cursor->ptr2Tree[i], file);
                }
            }
        }
    }
}

void BPlusTree::exportTreeToDot(const string& filename) {
    ofstream file;
    file.open(filename.c_str());
    file << "digraph BPlusTree {\n";
    file << "  node [shape=record];\n";
    exportToDot(root, file);
    file << "}\n";
    file.close();
}

void insertion(BPlusTree** Btree) {
    int rolNo;

    cout << "Numero de Registro: ";
    cin >> rolNo;

    (*Btree)->insert(rolNo);
    cout << "Insercion del rol: " << rolNo << " exitosa." << endl;
}

void searching(BPlusTree* Btree) {
    int rolNo;
    cout << "Rol a buscar? ";
    cin >> rolNo;

    Btree->search(rolNo);
}

void printing(BPlusTree* BTree) {
    BTree->display(BTree->getRoot());
}

void exportToDot(BPlusTree* BTree) {
    string filename;
    cout << "Nombre del archivo .dot: ";
    cin >> filename;
    BTree->exportTreeToDot(filename);
    cout << "Exportacion a " << filename << " exitosa." << endl;
}

int main() {
    BPlusTree* BTree = new BPlusTree(4, 4);  // Grado del árbol B+

    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insertar\n";
        cout << "2. Buscar\n";
        cout << "3. Imprimir\n";
        cout << "4. Exportar a .dot\n";
        cout << "5. Salir\n";
        cout << "Seleccionar una opcion: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertion(&BTree);
                break;
            case 2:
                searching(BTree);
                break;
            case 3:
                printing(BTree);
                break;
            case 4:
                exportToDot(BTree);
                break;
            case 5:
                exit(0);
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo.\n";
        }
    }

    return 0;
}