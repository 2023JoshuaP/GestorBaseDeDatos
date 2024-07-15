#include "BPlusTree.h"

Node* parent = NULL;

Node::ptr::ptr() {}

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
    for (int i = 0; i < cursor->ptr2TreeOrData.ptr2Tree.size(); i++) {
        if (cursor->ptr2TreeOrData.ptr2Tree[i] != NULL) {
            return firstLeftNode(cursor->ptr2TreeOrData.ptr2Tree[i]);
        }
    }
    return NULL;
}

Node** BPlusTree::findParent(Node* cursor, Node* child) {
    if (cursor->isLeaf || cursor->ptr2TreeOrData.ptr2Tree[0]->isLeaf) {
        return NULL;
    }
    for (int i = 0; i < cursor->ptr2TreeOrData.ptr2Tree.size(); i++) {
        if (cursor->ptr2TreeOrData.ptr2Tree[i] == child) {
            parent = cursor;
        }
        else {
            Node* tempCursor = cursor->ptr2TreeOrData.ptr2Tree[i];
            findParent(tempCursor, child);
        }
    }
    return &parent;
}

void BPlusTree::display(Node* cursor) {
    if (cursor == NULL) {
        return;
    }
    queue<Node*> q;
    q.push(cursor);

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node* u = q.front();
            q.pop();
            for (int val : u->keys) {
                cout << val << " ";
            }
            cout << "|| ";

            if (u->isLeaf != true) {
                for (Node* v : u->ptr2TreeOrData.ptr2Tree) {
                    q.push(v);
                }
            }
        }
        cout << endl;
    }
}

void BPlusTree::seqDisplay(Node* cursor) {
    Node* firstLeft = firstLeftNode(cursor);

    if (firstLeft == NULL) {
        cout << "No hay datos." << endl;
        return;
    }

    while (firstLeft != NULL) {
        for (int i = 0; i < firstLeft->keys.size(); i++) {
            cout << firstLeft->keys[i] << " ";
        }
        firstLeft = firstLeft->ptr2next;
    }
    cout << endl;
}

void BPlusTree::search(int key) {
    if (root == NULL) {
        cout << "No hay tuplas de insercion." << endl;
        return;
    }

    Node* cursor = root;
    while (cursor->isLeaf == false) {
        int index = upper_bound(cursor->keys.begin(), cursor->keys.end(), key) - cursor->keys.begin();
        cursor = cursor->ptr2TreeOrData.ptr2Tree[index];
    }

    int index = lower_bound(cursor->keys.begin(), cursor->keys.end(), key) - cursor->keys.begin();

    if (index == cursor->keys.size() || cursor->keys[index] != key) {
        cout << "No existe la clave." << endl;
        return;
    }

    string fileName = "../Archivos/";
    string data;
    fileName += to_string(key) + ".txt";
    FILE* filePtr = fopen(fileName.c_str(), "r");
    cout << "Clave Encontrada." << endl;
    cout << "Data correspondiente es: ";
    char ch = fgetc(filePtr);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(filePtr);
    }
    fclose(filePtr);
    cout << endl;
}

void BPlusTree::insert(int key, FILE* filePtr) {
    if (root == NULL) {
        root = new Node;
        root->isLeaf = true;
        root->keys.push_back(key);
        new (&root->ptr2TreeOrData.dataPtr) vector<FILE*>;
        root->ptr2TreeOrData.dataPtr.push_back(filePtr);
        cout << key << ": es la Raiz" << endl;
        return;
    }
    else {
        Node* cursor = root;
        Node* parent = NULL;
        while (cursor->isLeaf == false) {
            parent = cursor;
            int index = upper_bound(cursor->keys.begin(), cursor->keys.end(), key) - cursor->keys.begin();
            cursor = cursor->ptr2TreeOrData.ptr2Tree[index];
        }

        if (cursor->keys.size() < maxLeafNodeLimit) {
            int i = upper_bound(cursor->keys.begin(), cursor->keys.end(), key) - cursor->keys.begin();
            cursor->keys.push_back(key);
            cursor->ptr2TreeOrData.dataPtr.push_back(filePtr);

            if (i != cursor->keys.size() - 1) {
                for (int j = cursor->keys.size() - 1; j > i; j--) {
                    cursor->keys[j] = cursor->keys[j - 1];
                    cursor->ptr2TreeOrData.dataPtr[j] = cursor->ptr2TreeOrData.dataPtr[j - 1];
                }
                cursor->keys[i] = key;
                cursor->ptr2TreeOrData.dataPtr[i] = filePtr;
            }
            cout << "Insercion completada: " << key << endl;
        }
        else {
            vector<int> virtualNode(cursor->keys);
            vector<FILE*> virtualDataNode(cursor->ptr2TreeOrData.dataPtr);

            int i = upper_bound(cursor->keys.begin(), cursor->keys.end(), key) - cursor->keys.begin();

            virtualNode.push_back(key);
            virtualDataNode.push_back(filePtr);

            if (i != virtualNode.size() - 1) {
                for (int j = virtualNode.size() - 1; j > i; j--) {
                    virtualNode[j] = virtualNode[j - 1];
                    virtualDataNode[j] = virtualDataNode[j - 1];
                }

                virtualNode[i] = key;
                virtualDataNode[i] = filePtr;
            }

            Node* newLeaf = new Node;
            newLeaf->isLeaf = true;
            new (&newLeaf->ptr2TreeOrData.dataPtr) vector<FILE*>;

            Node* temp = cursor->ptr2next;;
            cursor->ptr2next = newLeaf;
            newLeaf->ptr2next = temp;

            cursor->keys.resize((maxLeafNodeLimit) / 2 + 1);
            cursor->ptr2TreeOrData.dataPtr.resize((maxLeafNodeLimit) / 2 + 1);
            for (int i = 0; i <= (maxLeafNodeLimit) / 2; i++) {
                cursor->keys[i] = virtualNode[i];
                cursor->ptr2TreeOrData.dataPtr[i] = virtualDataNode[i];
            }
            for (int i = (maxLeafNodeLimit) / 2 + 1; i < virtualNode.size(); i++) {
                newLeaf->keys.push_back(virtualNode[i]);
                newLeaf->ptr2TreeOrData.dataPtr.push_back(virtualDataNode[i]);
            }

            if (cursor == root) {
                Node* newRoot = new Node;
                newRoot->keys.push_back(newLeaf->keys[0]);
                new (&newRoot->ptr2TreeOrData.ptr2Tree) vector<Node*>;
                newRoot->ptr2TreeOrData.ptr2Tree.push_back(cursor);
                newRoot->ptr2TreeOrData.ptr2Tree.push_back(newLeaf);
                root = newRoot;
                cout << "Creando nueva Raiz." << endl;
            }
            else {
                insertInternal(newLeaf->keys[0], &parent, &newLeaf);
            }
        }
    }
}

void BPlusTree::insertInternal(int x, Node** cursor, Node** child) {
    if ((*cursor)->keys.size() < maxIntChildLimit - 1) {
        int i = upper_bound((*cursor)->keys.begin(), (*cursor)->keys.end(), x) - (*cursor)->keys.begin();
        (*cursor)->keys.push_back(x);
        (*cursor)->ptr2TreeOrData.ptr2Tree.push_back(*child);

        if (i != (*cursor)->keys.size() - 1) {
            for (int j = (*cursor)->keys.size() - 1; j > i; j--) {
                (*cursor)->keys[j] = (*cursor)->keys[j - 1];
            }
            for (int j = (*cursor)->ptr2TreeOrData.ptr2Tree.size(); j > (i + 1); j--) {
                (*cursor)->ptr2TreeOrData.ptr2Tree[j] = (*cursor)->ptr2TreeOrData.ptr2Tree[j - 1];
            }

            (*cursor)->keys[i] = x;
            (*cursor)->ptr2TreeOrData.ptr2Tree[i + 1] = *child;
        }
        cout << "Clave insertada en el nodo interno." << endl;
    }
    else {
        cout << "Insertando nodo en el nodo interno." << endl;
        cout << "Overflow en el internal." << endl;

        vector<int> virtualKeyNode((*cursor)->keys);
        vector<Node*> virtualTreePtrNode((*cursor)->ptr2TreeOrData.ptr2Tree);

        int i = upper_bound((*cursor)->keys.begin(), (*cursor)->keys.end(), x) - (*cursor)->keys.begin();
        virtualKeyNode.push_back(x);
        virtualTreePtrNode.push_back(*child);

        if (i != virtualKeyNode.size() - 1) {
            for (int j = virtualKeyNode.size() - 1; j > i; j--) {
               virtualKeyNode[j] = virtualKeyNode[j - 1]; 
            }
            for (int j = virtualTreePtrNode.size() - 1; j > (i + 1); j--) {
                virtualTreePtrNode[j] = virtualTreePtrNode[j - 1];
            }

            virtualKeyNode[i] = x;
            virtualTreePtrNode[i + 1] = *child;
        }

        int partitionKey;
        partitionKey = virtualKeyNode[(virtualKeyNode.size() / 2)];
        int partitionIndex = (virtualKeyNode.size() / 2);

        (*cursor)->keys.resize(partitionIndex);
        (*cursor)->ptr2TreeOrData.ptr2Tree.resize(partitionIndex + 1);
        (*cursor)->ptr2TreeOrData.ptr2Tree.resize(partitionIndex + 1);

        for (int i = 0; i < partitionIndex; i++) {
            (*cursor)->keys[i] = virtualKeyNode[i];
        }
        for (int i = 0; i < partitionIndex; i++) {
            (*cursor)->ptr2TreeOrData.ptr2Tree[i] = virtualTreePtrNode[i];
        }

        Node* newInternalNode = new Node;
        new (&newInternalNode->ptr2TreeOrData.ptr2Tree) vector<Node*>;

        for (int i = partitionIndex + 1; i < virtualKeyNode.size(); i++) {
            newInternalNode->keys.push_back(virtualKeyNode[i]);
        }
        for (int i = partitionIndex + 1; i < virtualTreePtrNode.size(); i++) {
            newInternalNode->ptr2TreeOrData.ptr2Tree.push_back(virtualTreePtrNode[i]);
        }

        if ((*cursor) == root) {
            Node* newRoot = new Node;
            newRoot->keys.push_back(partitionKey);
            new (&newRoot->ptr2TreeOrData.ptr2Tree) vector<Node*>;
            newRoot->ptr2TreeOrData.ptr2Tree.push_back(*cursor);
            newRoot->ptr2TreeOrData.ptr2Tree.push_back(newInternalNode);

            root = newRoot;
            cout << "Raiz nueva creada." << endl;
        }
        else {
            insertInternal(partitionKey, findParent(root, *cursor), &newInternalNode);
        }
    }
}


void BPlusTree::removeKey(int x) {
    Node* root = getRoot();

    // Si el árbol está vacío
    if (root == NULL) {
        cout << "El Árbol B+ está vacío" << endl;
        return;
    }

    Node* cursor = root;
    Node* parent;
    int leftSibling, rightSibling;

    // Ir al nodo hoja, que puede contener la *clave*
    // TO-DO: Utilizar búsqueda binaria para encontrar el valor
    while (cursor->isLeaf != true) {
        for (int i = 0; i < cursor->keys.size(); i++) {
            parent = cursor;
            leftSibling = i - 1; // lado izquierdo del nodo padre
            rightSibling = i + 1; // lado derecho del nodo padre

            if (x < cursor->keys[i]) {
                cursor = cursor->ptr2TreeOrData.ptr2Tree[i];
                break;
            }
            if (i == cursor->keys.size() - 1) {
                leftSibling = i;
                rightSibling = i + 2; // VERIFICAR aquí, podría necesitar hacerlo negativo
                cursor = cursor->ptr2TreeOrData.ptr2Tree[i+1];
                break;
            }
        }
    }

    // Comprobar si el valor existe en este nodo hoja
    int pos = 0;
    bool found = false;
    for (pos = 0; pos < cursor->keys.size(); pos++) {
        if (cursor->keys[pos] == x) {
            found = true;
            break;
        }
    }

    auto itr = lower_bound(cursor->keys.begin(), cursor->keys.end(), x);

    if (found == false) {
        cout << "Clave no encontrada en el árbol" << endl;
        return;
    }
    
    // Eliminar el archivo correspondiente y FILE*
    string fileName = "../Archivos/" + to_string(x) + ".txt";
    char filePtr[256];
    strcpy(filePtr, fileName.c_str());

    // delete cursor->ptr2TreeOrData.dataPtr[pos]; // evitar fugas de memoria
    if (remove(filePtr) == 0)
        cout << "Archivo eliminado con éxito: " << fileName << endl;
    else
        cout << "No se puede eliminar el archivo: " << fileName << endl;

    // Desplazar las claves y dataPtr para el nodo hoja
    for (int i = pos; i < cursor->keys.size()-1; i++) {
        cursor->keys[i] = cursor->keys[i+1];
        cursor->ptr2TreeOrData.dataPtr[i] = cursor->ptr2TreeOrData.dataPtr[i + 1];
    }
    int prev_size = cursor->keys.size();
    cursor->keys.resize(prev_size - 1);
    cursor->ptr2TreeOrData.dataPtr.resize(prev_size - 1);

    // Si es hoja y también el nodo raíz
    if (cursor == root) {
        if (cursor->keys.size() == 0) {
            // El árbol se vuelve vacío
            setRoot(NULL);
            cout << "¡Ohh! ¡Nuestro árbol está vacío ahora! :(" << endl;
        }
    }
    
    cout << "Eliminado " << x << " del nodo hoja con éxito" << endl;
    if ((cursor->keys.size() >= (getMaxLeafNodeLimit() + 1) / 2) || (cursor == root)) {
        // Nodo suficiente disponible para que la invariante se mantenga
        return;
    }

    cout << "¡Se produjo un desbordamiento en el nodo hoja!" << endl;
    cout << "Iniciando redistribución..." << endl;

    // 1. Intentar tomar prestada una clave del hermano izquierdo
    if (leftSibling >= 0) {
        Node* leftNode = parent->ptr2TreeOrData.ptr2Tree[leftSibling];

        // Comprobar si el hermano izquierdo tiene una clave extra para transferir
        if (leftNode->keys.size() >= (getMaxLeafNodeLimit()+1) / 2 +1) {

            // Transferir la clave máxima del hermano izquierdo
            int maxIdx = leftNode->keys.size()-1;
            cursor->keys.insert(cursor->keys.begin(), leftNode->keys[maxIdx]);
            cursor->ptr2TreeOrData.dataPtr.insert(cursor->ptr2TreeOrData.dataPtr.begin(), leftNode->ptr2TreeOrData.dataPtr[maxIdx]);

            // Redimensionar el nodo hermano izquierdo después de la transferencia
            leftNode->keys.resize(maxIdx);
            leftNode->ptr2TreeOrData.dataPtr.resize(maxIdx);

            // Actualizar el padre
            parent->keys[leftSibling] = cursor->keys[0];
            printf("Transferido del hermano izquierdo del nodo hoja\n");
            return;
        }
    }

    // 2. Intentar tomar prestada una clave del hermano derecho
    if (rightSibling < parent->ptr2TreeOrData.ptr2Tree.size()) {
        Node* rightNode = parent->ptr2TreeOrData.ptr2Tree[rightSibling];

        // Comprobar si el hermano derecho tiene una clave extra para transferir
        if (rightNode->keys.size() >= (getMaxLeafNodeLimit() + 1) / 2 + 1) {

            // Transferir la clave mínima del hermano derecho
            int minIdx = 0;
            cursor->keys.push_back(rightNode->keys[minIdx]);
            cursor->ptr2TreeOrData.dataPtr.push_back(rightNode->ptr2TreeOrData.dataPtr[minIdx]);

            // Redimensionar el nodo hermano derecho después de la transferencia
            rightNode->keys.erase(rightNode->keys.begin());
            rightNode->ptr2TreeOrData.dataPtr.erase(rightNode->ptr2TreeOrData.dataPtr.begin());

            // Actualizar el padre
            parent->keys[rightSibling-1] = rightNode->keys[0];
            printf("Transferido del hermano derecho del nodo hoja\n");
            return;
        }
    }

    // Fusionar y eliminar el nodo
    if (leftSibling >= 0) { // Si existe el hermano izquierdo
        Node* leftNode = parent->ptr2TreeOrData.ptr2Tree[leftSibling];
        // Transferir clave y dataPtr al hermano izquierdo y conectar ptr2next
        for (int i = 0; i < cursor->keys.size(); i++) {
            leftNode->keys.push_back(cursor->keys[i]);
            leftNode->ptr2TreeOrData.dataPtr.push_back(cursor->ptr2TreeOrData.dataPtr[i]);
        }
        leftNode->ptr2next = cursor->ptr2next;
        cout << "Fusionando dos nodos hoja" << endl;
        removeInternal(parent->keys[leftSibling], parent, cursor); // eliminar la clave del nodo padre
        // delete cursor;
    }
    else if (rightSibling <= parent->keys.size()) {
        Node* rightNode = parent->ptr2TreeOrData.ptr2Tree[rightSibling];
        // Transferir clave y dataPtr al hermano derecho y conectar ptr2next
        for (int i = 0; i < rightNode->keys.size(); i++) {
            cursor->keys.push_back(rightNode->keys[i]);
            cursor->ptr2TreeOrData.dataPtr.push_back(rightNode->ptr2TreeOrData.dataPtr[i]);
        }
        cursor->ptr2next = rightNode->ptr2next;
        cout << "Fusionando dos nodos hoja" << endl;
        removeInternal(parent->keys[rightSibling-1], parent, rightNode); // eliminar la clave del nodo padre
        // delete rightNode;
    }
}

void BPlusTree::removeInternal(int x, Node* cursor, Node* child) {
    Node* root = getRoot();

    // Comprobar si se debe eliminar la clave desde la raíz
    if (cursor == root) {
        if (cursor->keys.size() == 1) {
            // Si solo queda una clave y coincide con uno de los punteros de hijo
            if (cursor->ptr2TreeOrData.ptr2Tree[1] == child) {
                setRoot(cursor->ptr2TreeOrData.ptr2Tree[0]);
                // delete cursor;
                cout << "¡Guau! Nueva raíz cambiada" << endl;
                return;
            }
            else if (cursor->ptr2TreeOrData.ptr2Tree[0] == child) {
                setRoot(cursor->ptr2TreeOrData.ptr2Tree[1]);
                // delete cursor;
                cout << "¡Guau! Nueva raíz cambiada" << endl;
                return;
            }
        }
    }

    // Eliminar la clave x del padre
    int pos;
    for (pos = 0; pos < cursor->keys.size(); pos++) {
        if (cursor->keys[pos] == x) {
            break;
        }
    }
    for (int i = pos; i < cursor->keys.size()-1; i++) {
        cursor->keys[i] = cursor->keys[i + 1];
    }
    cursor->keys.resize(cursor->keys.size() - 1);

    // Ahora eliminar el ptr2tree
    for (pos = 0; pos < cursor->ptr2TreeOrData.ptr2Tree.size(); pos++) {
        if (cursor->ptr2TreeOrData.ptr2Tree[pos] == child) {
            break;
        }
    }

    for (int i = pos; i < cursor->ptr2TreeOrData.ptr2Tree.size() - 1; i++) {
        cursor->ptr2TreeOrData.ptr2Tree[i] = cursor->ptr2TreeOrData.ptr2Tree[i + 1];
    }
    cursor->ptr2TreeOrData.ptr2Tree.resize(cursor->ptr2TreeOrData.ptr2Tree.size()-1);

    // Si no hay desbordamiento. ¡Uf!
    if (cursor->keys.size() >= (getMaxIntChildLimit() + 1) / 2 - 1) {
        cout << "Eliminado " << x << " del nodo interno con éxito\n";
        return;
    }

    cout << "¡Desbordamiento en el nodo interno! ¿Qué has hecho? :/" << endl;

    if (cursor == root) {
        return;
    }

    Node** p1 = findParent(root, cursor);
    Node* parent = *p1;

    int leftSibling, rightSibling;

    // Encontrar hermanos izquierdo y derecho como hicimos antes
    for (pos = 0; pos < parent->ptr2TreeOrData.ptr2Tree.size(); pos++) {
        if (parent->ptr2TreeOrData.ptr2Tree[pos] == cursor) {
            leftSibling = pos - 1;
            rightSibling = pos + 1;
            break;
        }
    }

    // Si es posible transferir al hermano izquierdo
    if (leftSibling >= 0) {
        Node* leftNode = parent->ptr2TreeOrData.ptr2Tree[leftSibling];

        // Comprobar si el hermano izquierdo tiene una clave extra para transferir
        if (leftNode->keys.size() >= (getMaxIntChildLimit() + 1) / 2) {

            // Transferir clave del hermano izquierdo a través del padre
            int maxIdxKey = leftNode->keys.size() - 1;
            cursor->keys.insert(cursor->keys.begin(), parent->keys[leftSibling]);
            parent->keys[leftSibling] = leftNode->keys[maxIdxKey];

            int maxIdxPtr = leftNode->ptr2TreeOrData.ptr2Tree.size()-1;
            cursor->ptr2TreeOrData.ptr2Tree.insert(cursor->ptr2TreeOrData.ptr2Tree.begin(), leftNode->ptr2TreeOrData.ptr2Tree[maxIdxPtr]);

            // Redimensionar el nodo hermano izquierdo después de la transferencia
            leftNode->keys.resize(maxIdxKey);
            leftNode->ptr2TreeOrData.dataPtr.resize(maxIdxPtr);

            return;
        }
    }

    // Si es posible transferir al hermano derecho
    if (rightSibling < parent->ptr2TreeOrData.ptr2Tree.size()) {
        Node* rightNode = parent->ptr2TreeOrData.ptr2Tree[rightSibling];

        // Comprobar si el hermano izquierdo tiene una clave extra para transferir
        if (rightNode->keys.size() >= (getMaxIntChildLimit() + 1) / 2) {

            // Transferir clave del hermano derecho a través del padre
            int maxIdxKey = rightNode->keys.size() - 1;
            cursor->keys.push_back(parent->keys[pos]);
            parent->keys[pos] = rightNode->keys[0];
            rightNode->keys.erase(rightNode->keys.begin());

            // Transferir el puntero del hermano derecho al cursor
            cursor->ptr2TreeOrData.ptr2Tree.push_back(rightNode->ptr2TreeOrData.ptr2Tree[0]);
            cursor->ptr2TreeOrData.ptr2Tree.erase(cursor->ptr2TreeOrData.ptr2Tree.begin());
             
            return;
        }
    }

    // Iniciar la fusión ahora, si ninguno de los casos anteriores se aplica
    if (leftSibling >= 0) {
        // leftNode + clave del padre + cursor
        Node* leftNode = parent->ptr2TreeOrData.ptr2Tree[leftSibling];
        leftNode->keys.push_back(parent->keys[leftSibling]);

        for (int val : cursor->keys) {
            leftNode->keys.push_back(val);
        }

        for (int i = 0; i < cursor->ptr2TreeOrData.ptr2Tree.size(); i++) {
            leftNode->ptr2TreeOrData.ptr2Tree.push_back(cursor->ptr2TreeOrData.ptr2Tree[i]);
            cursor->ptr2TreeOrData.ptr2Tree[i] = NULL;
        }

        cursor->ptr2TreeOrData.ptr2Tree.resize(0);
        cursor->keys.resize(0);

        removeInternal(parent->keys[leftSibling], parent, cursor);
        cout << "Fusionado con el hermano izquierdo" << endl;
    }
    else if (rightSibling < parent->ptr2TreeOrData.ptr2Tree.size()) {
        // cursor + clave del padre + rightNode
        Node* rightNode = parent->ptr2TreeOrData.ptr2Tree[rightSibling];
        cursor->keys.push_back(parent->keys[rightSibling - 1]);

        for (int val : rightNode->keys) {
            cursor->keys.push_back(val);
        }

        for (int i = 0; i < rightNode->ptr2TreeOrData.ptr2Tree.size(); i++) {
            cursor->ptr2TreeOrData.ptr2Tree.push_back(rightNode->ptr2TreeOrData.ptr2Tree[i]);
            rightNode->ptr2TreeOrData.ptr2Tree[i] = NULL;
        }

        rightNode->ptr2TreeOrData.ptr2Tree.resize(0);
        rightNode->keys.resize(0);

        removeInternal(parent->keys[rightSibling - 1], parent, rightNode);
        cout << "Fusionado con el hermano derecho\n";
    }
}

void BPlusTree::generateDOT(Node* cursor, ofstream &file) {
    if (cursor == NULL) {
        return;
    }

    queue<Node*> q;
    q.push(cursor);

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node* u = q.front();
            q.pop();
            file << "\"" << u << "\" [label=\"";
            for (int val : u->keys) {
                file << val << " ";
            }
            file << "\"];\n";

            if (!u->isLeaf) {
                for (Node* v : u->ptr2TreeOrData.ptr2Tree) {
                    if (v != NULL) {
                        file << "\"" << u << "\" -> \"" << v << "\";\n";
                        q.push(v);
                    }
                }
            }
        }
    }
}

void BPlusTree::generateDOTFile(string filename) {
    ofstream file;
    file.open(filename);

    file << "digraph BPlusTree {\n";
    file << "node [shape=record];\n";
    generateDOT(root, file);
    file << "}\n";

    file.close();
}