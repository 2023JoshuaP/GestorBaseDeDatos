#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "./BPlusTree.cpp"
using namespace std;

void insertion(BPlusTree** Btree) {
    //int cont = 1;
    int rolNo;
    string ID;
    string content;
    string date;
    string directorio = "Registros.csv";
    ifstream fileDirectorio(directorio);
    string linea;

    while (getline(fileDirectorio, linea)) {
        stringstream ss(linea);
        string valor;

        // Leer rolNo (primer valor de la línea)
        getline(ss, valor, ',');
        rolNo = stoi(valor);

        // Leer ID (segundo valor de la línea)
        getline(ss, valor, ',');
        ID = valor;

        // Leer date (tercer valor de la línea)
        getline(ss, valor, ',');
        date = valor;

        // Leer date (tercer valor de la línea)
        getline(ss, valor, ',');
        content = valor;

        string fileName = "../Archivos/" + to_string(rolNo) + ".txt";
        FILE* filePtr = fopen(fileName.c_str(), "w");
        string userTuple = to_string(rolNo) + " " + ID + " " + date + " " + content + "\n";
        fprintf(filePtr, "%s", userTuple.c_str());
        fclose(filePtr);

        (*Btree)->insert(rolNo, filePtr);
        //cont ++;
        cout << "Inserción del rol: " << rolNo << " exitosa." << endl;
    }
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
        cout << "5. Generar .dot." << endl;
        cout << "6. Salir." << endl;
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
                BTree->generateDOTFile("BPlusTree.dot");
                break;
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                flag = false;
                break;
        }
    } while (option != 6);
}