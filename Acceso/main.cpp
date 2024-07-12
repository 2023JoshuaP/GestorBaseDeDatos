#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "./BPlusTree.cpp"
#define _CRT_SECURE_NO_DEPRECATE
using namespace std;

void insertion(BPlusTree** Btree) {
    int rolNo;
    int age, marks;
    string name;

    cout << "Numero de Registro." << endl;
    cin >> rolNo;

    cout << "Ingresar datos (nombre, edad y marca): ";
    cin >> name >> age >> marks;

    string fileName = "../Archivos/";
    fileName += to_string(rolNo) + ".txt";
    FILE* filePtr = fopen(fileName.c_str(), "w");
    string userTuple = name + " " + to_string(age) + " " + to_string(marks) + "\n";
    fprintf(filePtr, userTuple.c_str());

    (*Btree)->insert(rolNo, filePtr);
    fclose(filePtr);
    cout << "Insercion del rol: " << rolNo << " existoso." << endl;
}

void searching(BPlusTree* Btree) {
    int rolNo;
    cout << "Rol a buscar? ";
    cin >> rolNo;

    Btree->search(rolNo);
}

void printing(BPlusTree* BTree) {
    int option;
    cout << "1. Display Secuencial." << endl;
    cout << "2. Display Iterativo." << endl;
    cin >> option;

    if (option == 1) {
        BTree->seqDisplay(BTree->getRoot());
    }
    else if (option == 2) {
        BTree->display(BTree->getRoot());
    }
}

void deletion(BPlusTree* BTree) {
    cout << "Showing you the Tree, Choose a key from here: " << endl;
    BTree->display(BTree->getRoot());
 
    int tmp;
    cout << "Enter a key to delete: " << endl;
    cin >> tmp;
    BTree->removeKey(tmp);

    //Displaying
    BTree->display(BTree->getRoot());
}

int main() {
    cout << "Arbol B+ como SGBD basico." << endl;

    bool flag = true;
    int option;

    int maxChildInt = 4;
    int maxNodeLeaf = 3;
    cout << "Limite maximo de Nodos Internos Hijos que pueden haber: ";
    cin >> maxChildInt;
    cout << "Limite maximo de claves que pueden haber en un Nodo Hoja: ";
    cin >> maxNodeLeaf;

    BPlusTree* BTree = new BPlusTree(maxChildInt, maxNodeLeaf);

    do {
        cout << "1. Insercion." << endl;
        cout << "2. Busqueda." << endl;
        cout << "3. Imprimir." << endl;
        cout << "4. Eliminar." << endl;
        cout << "5. Salir." << endl;
        cout << "Opcion? ";
        cin >> option;

        switch (option) {
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
                deletion(BTree);
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                flag = false;
                break;
        }
    } while (option != 5);
}