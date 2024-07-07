#include <iostream>
#include <cstdlib>
using namespace std;

void ejecutarBufferManager() {
    cout << "Ejecutando programa del BufferManager..." << endl;
    int resultado = system("cd Buffer && main.exe");
    if (resultado != 0) {
        cout << "Error al ejecutar BufferManager." << endl;
    }
}

void ejecutarDisco() {
    cout << "Ejecutando programa del Disco..." << endl;
    int resultado = system("cd Disco && main.exe");
    if (resultado != 0) {
        cout << "Error al ejecutar Disco." << endl;
    }
}

int main() {
    int opcion;

    do {
        cout << "-----------------------------------------------------" << endl;
        cout << "\t  Menu del Gestor de Base de Datos\t\t" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "1. Ejecutar programa del BufferManager" << endl;
        cout << "2. Ejecutar programa del Disco" << endl;
        cout << "3. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cout << "-----------------------------------------------------" << endl;

        switch (opcion) {
            case 1:
                ejecutarBufferManager();
                break;
            case 2:
                ejecutarDisco();
                break;
            case 3:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida. Por favor, seleccione una opción valida." << endl;
                break;
        }
    } while (opcion != 3);

    return 0;
}