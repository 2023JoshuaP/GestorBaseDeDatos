#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include "Pagina.cpp"
using namespace std;

int main() {
    Pagina pagina;
    int opcion, numPagina;

    do {
        cout << "-----------------------------------------------------" << endl;
        cout << "\t\t   Menu Principal\t\t" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "(1) Recoger registros." << endl;
        cout << "(2) Mostrar contenido de la pagina." << endl;
        cout << "(3) Leer o escribir pagina." << endl;
        cout << "(4) Verificar si la pagina esta vacia." << endl;
        cout << "(5) Agregar contenido." << endl;
        cout << "(6) Salir." << endl;
        cout << "Opcion a elegir: ";
        cin >> opcion;
        cout << "-----------------------------------------------------" << endl;

        switch (opcion) {
            case 1:
                cout << "Ingrese el numero de pagina: ";
                cin >> numPagina;
                pagina.recogerRegistros(numPagina);
                break;
            case 2:
                pagina.mostrarContenidoDePagina();
                break;
            case 3:
                pagina.leerOescribirPagina();
                break;
            case 4:
                if (pagina.verificarPaginaVacia()) {
                    cout << "La pagina esta vacia." << endl;
                } else {
                    cout << "La pagina contiene registros." << endl;
                }
                break;
            case 5:
                cout << "Ingrese el numero de pagina: ";
                cin >> numPagina;
                pagina.agregarContenido(numPagina);
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion incorrecta." << endl;
        }
    } while (opcion != 6);

    return 0;
}
