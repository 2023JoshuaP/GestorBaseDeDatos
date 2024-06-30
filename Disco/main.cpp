#include "Disco.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

string ajustarCampo(const string& campo, int longitud) {
    if (campo.length() < longitud) {
        return campo + string(longitud - campo.length(), ' ');
    }
    else if (campo.length() > longitud) {
        return campo.substr(0, longitud);
    }
    return campo;
}

void ajustarRegistros(const string& fileRegistrosNormal, const string& esquema) {
    string fileLonFija;
    cout << "Archivo para Registros de Longitud Fija: ";
    cin >> fileLonFija;
    string pathLonfija = "../Archivos/" + fileLonFija;
    ifstream fileRegistros(fileRegistrosNormal);
    ifstream fileEsquema(esquema);
    ofstream fileLongitudFija(pathLonfija);

    vector<string> columnasEsquema;
    vector<int> longitudes;

    if (fileEsquema.is_open()) {
        string line;
        getline(fileEsquema, line);
        while (getline(fileEsquema, line)) {
            istringstream ss(line);
            string nombreColumna, tipoDato, longitud;
            ss >> nombreColumna >> tipoDato >> longitud;
            columnasEsquema.push_back(nombreColumna);
            longitudes.push_back(stoi(longitud));
        }
        fileEsquema.close();
    }
    else {
        cerr << "No se pudo abrir el archivo del Esquema." << endl;
        return;
    }

    if (fileRegistros.is_open()) {
        string line;
        while (getline(fileRegistros, line)) {
            istringstream ss(line);
            string campo;
            bool firstField = true;
            int colIndex = 0;

            while (getline(ss, campo, ',')) {
                if (campo.front() == '"' && campo.back() != '"') {
                    string campoCadena = campo;
                    while (getline(ss, campo, ',') && campo.back() != '"') {
                        campoCadena += "," + campo;
                    }
                    campoCadena += "," + campo;
                    campo = campoCadena;
                }
                
                campo = ajustarCampo(campo, longitudes[colIndex]);
                fileLongitudFija << campo;
                firstField = false;
                colIndex++;
            }
            fileLongitudFija << endl;
        }
        fileRegistros.close();
        fileLongitudFija.close();
    }
    else {
        cerr << "Error en el archivo de Registros." << endl;
    }
}

void esquema() {
    string fileCSV;
    string pathCSV = "../Archivos/";
    cout << "File csv para convertir: ";
    cin >> fileCSV;
    string path = pathCSV + fileCSV;
    ifstream file(path);
    
    if (file.is_open()) {
        string csvTXT;
        string esquemaTXT;
        cout << "Nombre del Archivo para registros convertidos a TXT: ";
        cin >> csvTXT;
        cout << "Nombre del Archivo para creacion de esquema en TXT: ";
        cin >> esquemaTXT;

        string pathRegistros = pathCSV + csvTXT;
        string pathEsquema = pathCSV + esquemaTXT;
        ofstream fileRegistros(pathRegistros, ios::app);
        ofstream fileEsquema(pathEsquema, ios::app);
        string line;
        vector<string> columnas;

        if (getline(file, line)) {
            istringstream ss(line);
            string campo;

            while (getline(ss, campo, ',')) {
                columnas.push_back(campo);
            }

            string nameEsquema;
            cout << "Nombre del Esquema: ";
            cin >> nameEsquema;
            fileEsquema << nameEsquema << endl;

            for (const string& nombreColumna : columnas) {
                string tipoDato;
                string tamanio = "4";
                bool tipoValido = false;

                while (!tipoValido) {
                    cout << "Ingrese el tipo de dato para la Columna: " << nombreColumna << " (int, float, str): ";
                    cin >> tipoDato;

                    if (tipoDato == "int" || tipoDato == "float" || tipoDato == "str") {
                        tipoValido = true;
                        if (tipoDato == "str") {
                            cout << "Ingrese el espacio para la columna " << nombreColumna << ": ";
                            cin >> tamanio;
                        }
                    }
                    else {
                        cout << "Tipo de Dato incorrecto." << endl;
                    }
                }
                fileEsquema << left << setw(20) << nombreColumna << setw(10) << tipoDato << setw(5) << tamanio << endl;
            }
        }
        while (getline(file, line)) {
            istringstream ss(line);
            string campo;
            bool firstLine = true;

            while (getline(ss, campo, ',')) {
                if (campo.front() == '"' && campo.back() != '"') {
                    string campoCadena = campo;
                    while (getline(ss, campo, ',') && campo.back() != '"') {
                        campoCadena += ',' + campo;
                    }
                    campoCadena += ',' + campo;
                    campo = campoCadena;
                }

                if (!firstLine) {
                    fileRegistros << ",";
                }
                fileRegistros << campo;
                firstLine = false;
            }
            fileRegistros << endl;
        }
        fileRegistros.close();
        fileEsquema.close();
        file.close();
        cout << "Esquema y Registros creados." << endl;
    }
    else {
        cout << "Error en el archivo CSV." << endl;
    }
}

int main() {
    Disco disco;
    bool creacionDisco = false;
    string fileTXT, fileEsquema;
    string recordsFixed;
    string schema;
    int capacidadBloques;
    int opcion;
    do {
        cout << "-----------------------------------------------------" << endl;
        cout << "\t\t   Menu del Disco\t\t" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "1. Generar esquema y conversion de CSV a archivo de texto." << endl;
        cout << "2. Convertir los registros a longitud fija." << endl;
        cout << "3. Creacion del disco con los bloques y llenado de Sectores." << endl;
        cout << "4. Mostrar capacidad del disco." << endl;
        cout << "5. Eliminacion del disco." << endl;
        cout << "6. Salir del programa del disco." << endl;
        cout << "Ingrese su opcion a ejecutar: " << endl;
        cin >> opcion;
        cout << "-----------------------------------------------------" << endl;
        switch (opcion) {
            case 1: {
                esquema();
                break;
            }
            case 2: {
                cout << "Archivo de Registros en formato de TXT: ";
                cin >> fileTXT;
                cout << "Archivo de Esquema en formato de TXT: ";
                cin >> fileEsquema;
                ajustarRegistros("../Archivos/" + fileTXT, "../Archivos/" + fileEsquema);
                break;
            }
            case 3: {
                if (!creacionDisco) {
                    int platos;
                    int pistas;
                    int sectores;
                    int capacidadSectores;

                    cout << "\t\t   Creacion de Disco\t\t" << endl;
                    cout << "-----------------------------------------------------" << endl;
                    cout << "Platos: ";
                    cin >> platos;
                    cout << "Pistas: ";
                    cin >> pistas;
                    cout << "Sectores: ";
                    cin >> sectores;
                    cout << "Capacidad de Sectores: ";
                    cin >> capacidadSectores;

                    disco.setNumPlatos(platos);
                    disco.setPistasPorSuperficie(pistas);
                    disco.setSectoresPorPista(sectores);
                    disco.setCapacidadPorSector(capacidadSectores);

                    disco.crearDisco();

                    cout << "Capacidad de los Bloques: ";
                    cin >> capacidadBloques;

                    cout << "Archivo con Registros de Longitud Fija en TXT: ";
                    cin >> recordsFixed;
                    cout << "Archivo con el Esquema en TXT: ";
                    cin >> schema;

                    disco.llenarRegistrosSector("../Archivos/" + recordsFixed, "../Archivos/" + schema);
                    disco.crearBloques(capacidadBloques, capacidadSectores, sectores);
                    disco.calcularEspacioLibreEnTodosLosBloques(capacidadBloques);
                }
                else {
                    cout << "Ya existe un Disco existente." << endl;
                }
                break;
            }
            case 4: {
                cout << "-----------------------------------------------------" << endl;
                cout << "\t\t   Capacidad de Disco\t\t" << endl;
                disco.capacidadDisco();
                cout << "-----------------------------------------------------" << endl;
                break;
            }
            case 5: {
                disco.eliminarDisco();
                cout << "Disco eliminado correctamente." << endl;
                break;
            }
            case 6: {
                cout << "Terminando el programa del Disco. " << endl;
                break;
            }
            default: {
                cout << "Opcion incorrecta, elija de nuevo." << endl;
            }
        }
    } while (opcion != 6);
    return 0;
}
