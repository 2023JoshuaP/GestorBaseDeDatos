#include "Pagina.h"

/* Funciones adicionales */

bool isNumber(const std::string &s) {
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0 && ch != '.')
            return false;
    }
    return true;
}

int tamanioString = 0;
string rutaCompleta = "";

/* Implementacion de la clase Pagina */

Pagina::Pagina() {}

Pagina::~Pagina() {}

/* D:\BaseDeDatos2\GestorBaseDeDatos\Archivos\directorio.txt */

void Pagina::recogerRegistros(int numPagina) {
    /* Recogemos las rutas del Disco para mejor búsqueda */
    string directorio = "../Archivos/directorio.txt";
    ifstream fileDirectorio(directorio);
    string pathBlockWrite;
    string line;

    if (!fileDirectorio.is_open()) {
        cout << "No se pudo abrir el archivo del directorio: " << directorio << endl;
        return;
    }

    cout << "Leyendo el archivo del directorio: " << directorio << endl;

    while (getline(fileDirectorio, line)) {
        cout << "Leyendo linea del directorio: " << line << endl;
        size_t pos = line.rfind('/');
        if (pos != string::npos) {
            string value = line.substr(pos + 1);
            cout << "Comparando " << value << " con " << numPagina << endl;
            if (stoi(value) == numPagina) {
                pathBlockWrite = line;
                cout << "Ruta encontrada: " << pathBlockWrite << endl;
                cout << "El valor a considerar es " << value << "." << endl;
                break;
            }
        }
    }

    cout << "La ruta del Bloque es: " << pathBlockWrite << endl;
    stringstream ss(pathBlockWrite);
    vector<string> components;
    string value2;

    while (getline(ss, value2, '/')) {
        components.push_back(value2);
    }

    cout << "Componentes obtenidos: " << endl;
    if (components.size() >= 4) {
        pathBlockWrite = "../Disco/Disco/Plato " + components[0] + "/Superficie " + components[1] + "/Pista " + components[2] + "/Bloque " + components[3] + ".txt";
        cout << "Ruta completa del Bloque: " << pathBlockWrite << endl;
    }
    else {
        cout << "Ruta de Bloque no encontrado." << endl;
        return;
    }

    ifstream pathBlock(pathBlockWrite);

    if (!pathBlock.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    
    int lineNumber = 0;
    while (getline(pathBlock, line)) {
        lineNumber++;
        if (lineNumber > 3) {
            this->vectorRegistrosEnPagina.push_back(line);
        }
    }
    pathBlock.close();
    cout << "Contenido de la Pagina en memoria mandado al Bloque correctamente." << endl;
}

void Pagina::mostrarContenidoDePagina() {
    cout << "Mostrando el contenido de la Pagina." << endl;
    cout << "----------------------------------------------------------" << endl;
    for (size_t i = 0; i < this->vectorRegistrosEnPagina.size(); i++) {
        cout << this->vectorRegistrosEnPagina[i] << endl;
    }
    cout << "----------------------------------------------------------" << endl;
}

void Pagina::leerOescribirPagina() {
    /* Para la lectura y escritura de las Paginas */
    int option;

    do {
        int rowAFind = 0;
        string recordNew;
        string  chainEnd = "";
        cout << "-----------------------------------------------------" << endl;
        cout << "\t\t   Edicion de Pagina\t\t" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "(1) Editar Contenido de una Pagina." << endl;
        cout << "(2) Eliminar Contenido de una Paginia." << endl;
        cout << "(3) Agregar Registro nuevo a Pagina." << endl;
        cout << "(4) No realizar ninguna accion." << endl;
        cout << "Opcion a elegir: ";
        cin >> option;
        cout << "-----------------------------------------------------" << endl;

        switch (option) {
            case 1: {
                cout << "\t\t   Edicion de Registros\t\t" << endl;
                cout << "-----------------------------------------------------" << endl;
                cout << "Fila a editar: ";
                cin >> rowAFind;
                cin.ignore();

                string record = this->vectorRegistrosEnPagina[rowAFind];
                cout << "El registro actual es: " << record << endl;

                vector<string> valuesRecordNew;
                stringstream ss(record);
                string value;

                cout << "Registro nuevo: ";
                getline(cin, recordNew);

                stringstream ss2(recordNew);

                while (getline(ss2, value, ',')) {
                    valuesRecordNew.push_back(value);
                }

                for (size_t i = 0; i < valuesRecordNew.size(); i++) {
                    if (isNumber(valuesRecordNew[i])) {
                        chainEnd += valuesRecordNew[i] + ',';
                    }
                    else {
                        chainEnd += valuesRecordNew[i];
                        int weightValue = valuesRecordNew[i].size();

                        do {
                            chainEnd += " ";
                            weightValue += 1;
                        } while (weightValue < tamanioString);

                        if (i < valuesRecordNew.size() - 1) {
                            chainEnd += ',';
                        }
                    }
                }
                this->vectorRegistrosEnPagina[rowAFind] = chainEnd;
                cout << "Se procede al Guardado del nuevo Registro." << endl;
                break;
            }
            case 2: {
                cout << "\t\t   Borrado de Registro\t\t" << endl;
                cout << "-----------------------------------------------------" << endl;
                cout << "Fila a borrar: ";
                cin >> rowAFind;
                cin.ignore();
                this->vectorRegistrosEnPagina[rowAFind] = " ";
                break;
            }
            case 3: {
                int optionRecord;
                cout << "\t\t   Agregar un Registro\t\t" << endl;
                cout << "(1) Como Longitud Fija." << endl;
                cout << "(2) Como Longitud Variable." << endl;      /* Si elige la opcion 2 con Longitud Variable, le saldrá un mensaje de que no esta funcionando (Proximamente estara la Longitud Variable.)*/
                cout << "Opcion? ";
                cin >> optionRecord;
                cout << "-----------------------------------------------------" << endl;

                string fileName = "../Archivos/esquemaTitanic.txt";
                ifstream file(fileName);

                if (!file.is_open()) {
                    cerr << "No se pudo abrir el archivo." << endl;
                    return;
                }

                string line;
                vector<int> lastValues;

                while (getline(file, line)) {
                    stringstream ss(line);
                    string word;
                    vector<string> words;

                    while (ss >> word) {
                        words.push_back(word);
                    }

                    if (!words.empty()) {
                        try {
                            int lastValue = stoi(words.back());
                            lastValues.push_back(lastValue);
                        } catch (const invalid_argument &e) {
                            /* Manejo del Error, no necesario poner algo */
                        }
                    }
                }

                file.close();

                if (optionRecord == 1) {
                    string nameFileRelation;
                    string pathFileRelation = "../Archivos/";
                    string newRecord;
                    cout << "Archivo Relacion: ";
                    cin >> nameFileRelation;

                    string pathComplete = pathFileRelation + nameFileRelation;
                    ifstream fileRelation(pathComplete);
                    ifstream fileSchema("../Archivos/esquemaTitanic.txt");
                    string lineRelation;
                    string dataInsertRelation;
                    string lineSchema;
                    bool firstValue;
                    int weightChain = 0;
                    int weightString;
                    size_t i = 0;

                    while (getline(fileRelation, lineRelation)) {
                        firstValue = false;
                        stringstream ss(lineRelation);
                        string valueRelation;
                        bool acceptedDataType = true;

                        do {
                            cout << lineRelation << endl;
                            cout << "Inserta Dato: ";
                            cin >> dataInsertRelation;

                            while (getline(ss, valueRelation, ',')) {
                                if (firstValue) {
                                    for (i; i < lastValues.size(); i) {
                                        cout << "Valor considerado a sido " << lastValues[i] << endl;
                                        if (valueRelation == "string" || valueRelation == "int" || valueRelation == "float") {
                                            cout << "Tipo de Dato aceptado." << endl;
                                            int weightChain = dataInsertRelation.length();
                                            weightString = lastValues[i];
                                            while (weightChain < weightString) {
                                                dataInsertRelation += " ";
                                                weightChain++;
                                            }
                                            newRecord += dataInsertRelation + ' ';
                                        }
                                        else {
                                            cout << "Tipo de Dato no aceptado." << endl;
                                            acceptedDataType = false;
                                        }
                                        i++;
                                        break;
                                    }
                                }
                                else {
                                    firstValue = true;
                                }
                            }
                            if (acceptedDataType) {
                                break;
                            }
                        } while(true);
                    }
                    this->vectorRegistrosEnPagina.push_back(newRecord);
                    cout << "Registro agregado correctamente." << endl;
                }
                else if (optionRecord == 2) {
                    cout << "Proximamente Longiud Variable, de momento trabaje con Longitud Fija." << endl;
                }
                break;
            }
            case 4: {
                cout << "Regresando al menu principal...." << endl;
                break;
            }
            default: {
                cout << "Opcion incorrecta." << endl;
            }
        }
    } while (option != 4);
}

bool Pagina::verificarPaginaVacia() {
    if (this->vectorRegistrosEnPagina.empty()) {
        return true;
    }
    return false;
}

void Pagina::agregarContenido(int numPagina) {
    // Leer las rutas del Disco desde un directorio para mejor búsqueda
    string pathDirectory = "../Archivos/directorio.txt";
    ifstream fileDirectory(pathDirectory);
    string pathBlockWrite;
    string line;

    if (!fileDirectory.is_open()) {
        cout << "No se pudo abrir el archivo del directorio: " << pathDirectory << endl;
        return;
    }

    while (getline(fileDirectory, line)) {
        size_t pos = line.rfind('/');
        if (pos != string::npos) {
            string value = line.substr(pos + 1);
            if (stoi(value) == numPagina) {
                pathBlockWrite = line;
                cout << "El valor a considerar es " << value << endl;
                break;
            }
        }
    }

    cout << "Ruta de Bloque: " << pathBlockWrite << endl;
    stringstream ss(pathBlockWrite);
    vector<string> components;
    string value2;

    while (getline(ss, value2, '/')) {
        components.push_back(value2);
    }

    if (components.size() >= 4) {
        pathBlockWrite = "../Disco/Disco/Plato " + components[0] + "/Superficie " + components[1] + "/Pista " + components[2] + "/Bloque " + components[3] + ".txt";
    }
    else {
        cout << "No se encontró la ruta del Bloque." << endl;
        return;
    }

    ofstream pathBlock(pathBlockWrite, ios::trunc);

    if (!pathBlock.is_open()) {
        cout << "No se pudo abrir el archivo del Bloque." << endl;
        return;
    }
    else {
        for (int_least32_t i = 0; i < this->vectorRegistrosEnPagina.size(); ++i) {
            pathBlock << this->vectorRegistrosEnPagina[i] << endl;
        }
        pathBlock.close();
        cout << "Contenido de Pagina en memoria mandado al Bloque." << endl;
    }

    char answer;
    cout << "Desea guardar en el Disco? (S-s/N-n): ";
    cin >> answer;

    if (answer == 's' || answer == 'S') {
        string pathBlockWriteDisk = "../Disco/Disco/Plato " + components[0] + "/Superficie " + components[1] + "/Pista " + components[2] + "/" + components[3] + ".txt";
        ofstream pathBlockDisk(pathBlockWriteDisk, ios::trunc);

        if (!pathBlockDisk.is_open()) {
            cout << "No se pudo abrir el archivo del Disco." << endl;
        }
        else {
            for (int_least32_t i = 0; i < this->vectorRegistrosEnPagina.size(); ++i) {
                pathBlockDisk << this->vectorRegistrosEnPagina[i] << endl;
            }
            pathBlockDisk.close();
            cout << "Contenido guardado en el Disco." << endl;
        }
    }
}