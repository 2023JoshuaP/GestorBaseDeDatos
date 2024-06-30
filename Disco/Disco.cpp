#include "Disco.h"
#include <filesystem>
namespace fs = std::filesystem;

/* Calcular el tamaño de los registros de Longitud Fija */

vector<FieldInfo> loadSchema(const string& schemaFile) {
    vector<FieldInfo> schema;
    ifstream file(schemaFile);

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo del Esquema." << endl;
        return schema;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        FieldInfo field;
        if (!(iss >> field.fieldName >> field.fieldType >> field.fieldSize)) {
            break;
        }
        schema.push_back(field);
    }

    file.close();
    return schema;
}

int calculateRecordSize(const vector<FieldInfo>& schema) {
    int totalSize = 0;
    for (const auto& field : schema) {
        totalSize += field.fieldSize;
    }
    return totalSize;
}

/* Implementacion de los Componentes Del Disco (estructura del Disco) */

Disco::Disco() {}

void Disco::setNumPlatos(int platos) {
    this->numPlatos = platos;
    return;
}

void Disco::setPistasPorSuperficie(int pistas) {
    this->pistaPorSuperficie = pistas;
    return;
}

void Disco::setSectoresPorPista(int sectores) {
    this->sectoresPorPista = sectores;
    return;
}

void Disco::setCapacidadPorSector(int bytes) {
    this->capacidadPorSector = bytes;
    return;
}

/* Implementación para la creación del Disco */

void Disco::crearCarpetaDisco(const string& rutaCarpeta) {
    fs::create_directories(rutaCarpeta);
}

void Disco::crearArchivoDisco(const string& rutaArchivo) {
    ofstream file(rutaArchivo);
    file.close();
}

void Disco::crearDisco() {
    string carpeta = "Disco";
    crearCarpetaDisco(carpeta);

    for (int plato = 1; plato <= numPlatos; plato++) {
        string carpetaPlato = carpeta + "/Plato " + to_string(plato);
        crearCarpetaDisco(carpetaPlato);
        for (int superficie = 1; superficie <= 2; superficie++) {
            string carpetaSuperficie = carpetaPlato + "/Superficie " + to_string(superficie);
            crearCarpetaDisco(carpetaSuperficie);
            for (int pista = 1; pista <= pistaPorSuperficie; pista++) {
                string carpetaPista = carpetaSuperficie + "/Pista " + to_string(pista);
                crearCarpetaDisco(carpetaPista);
                for (int sector = 1; sector <= sectoresPorPista; sector++) {
                    string archivoSector = carpetaPista + "/" + to_string(sector) + ".txt";
                    crearArchivoDisco(archivoSector);
                }
            }
        }
    }
}

void Disco::capacidadDisco() {
    cout << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Capacidad Total del Disco: " << this->sectoresPorPista * this->capacidadPorSector * this->pistaPorSuperficie * 2 * this->numPlatos << " bytes en total" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;
}

/* Implementacion de la eliminación del Disco */

void Disco::eliminarDisco() {
    string carpeta = "Disco";
    if (fs::exists(carpeta)) {
        fs::remove_all(carpeta);
        cout << "Disco eliminado correctamente." << endl;
    }
    cout << "No existe un Disco creado con anticipación." << endl;
}

/* Implementación de la creación de Bloques con operaciones necesarias */

void Disco::insertarRegistrosSector(ofstream& archivoSector, ifstream& archivoTXT, int registrosPorSector) {
    for (int i = 0; i < registrosPorSector; i++) {
        string line;
        if (getline(archivoTXT, line)) {
            archivoSector << line << endl;
        }
    }
    cout << endl;
}

void Disco::llenarRegistrosSector(const string& archivo, const string& schemaFile) {
    schema = loadSchema(schemaFile);

    if (schema.empty()) {
        cout << "Error al cargar el esquema." << endl;
        return;
    }

    ifstream file(archivo);
    
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    int longitudRegistro = calculateRecordSize(schema);

    string linea;
    int bytes = this->capacidadPorSector;
    int registrosPorSector = bytes / longitudRegistro;

    for (int plato = 1; plato <= this->numPlatos; plato++) {
        for (int superficie = 1; superficie <= 2; superficie++) {
            for (int pista = 1; pista <= this->pistaPorSuperficie; pista++) {
                for (int sector = 1; sector <= this->sectoresPorPista; sector++) {
                    string carpetaPista = "Disco/Plato " + to_string(plato) + "/Superficie " + to_string(superficie) + "/Pista " + to_string(pista);
                    string archivoSector = carpetaPista + "/" + to_string(sector) + ".txt";
                    ofstream archivoSectorEscritura(archivoSector, ios::app);
                    insertarRegistrosSector(archivoSectorEscritura, file, registrosPorSector);
                    archivoSectorEscritura.close();
                }
            }
        }
    }
    file.close();
}

bool Disco::leerSector(const string& sector, string& contenido ) {
    ifstream file(sector);
    if (file.is_open()) {
        stringstream ss;
        ss << file.rdbuf();
        contenido = ss.str();
        file.close();
        return true;
    }
    return false;
}

void Disco::crearBloques(int capacidadBloque, int capacidadSector, int cantidadSectores) {
    int sectoresPorBloque = capacidadBloque / capacidadSector;
    cout << "Cantidad de Sectores por Bloque: " << sectoresPorBloque << endl;
    int cantidadBloques = (cantidadSectores + sectoresPorBloque - 1) / sectoresPorBloque;
    cout << "Cantidad de Bloques a crear: " << cantidadBloques << endl;

    vector<Bloque> bloques(cantidadBloques);
    int contadorBloques = 1;

    for (int plato = 1; plato <= numPlatos; plato++) {
        for (int superficie = 1; superficie <= 2; superficie++) {
            for (int pista = 1; pista <= pistaPorSuperficie; pista++) {
                string carpetaPista = "Disco/Plato " + to_string(plato) + "/Superficie " + to_string(superficie) + "/Pista " + to_string(pista);
                for (int sector = 1; sector <= sectoresPorPista; sector += sectoresPorBloque) {
                    string rutaDirectorio = "../Archivos/directorio.txt";
                    ofstream archivoDirectorio(rutaDirectorio, ios::app);
                    archivoDirectorio << plato << "/" << superficie <<"/" << pista << "/" << contadorBloques << endl;
                    string archivoBloque = carpetaPista + "/Bloque " + to_string(contadorBloques) + ".txt";
                    ofstream archivo(archivoBloque, ios::app);
                    if (archivo.is_open()) {
                        archivo << "Plato: " << plato << " Superficie: " << superficie << " Pista: " << pista << "Bloque: " << contadorBloques << endl;
                        archivo << "=============================================" << endl;
                        for (int i = 0; i < sectoresPorBloque; i++) {
                            int sectorActual = sector + i;
                            if (sectorActual <= sectoresPorPista) {
                                string archivoSector = carpetaPista + "/" + to_string(sectorActual) + ".txt";
                                string contenido;
                                if (leerSector(archivoSector, contenido)) {
                                    archivo << "Plato: " << plato << " Superficie: " << superficie << " Pista: " << pista << "Sector: " << sectorActual << endl;
                                    archivo << contenido;
                                }
                                else {
                                    archivo << "Plato: " << plato << " Superficie: " << superficie << " Pista: " << pista << "Bloque: " << contadorBloques << endl;
                                }
                            }
                        }
                        archivo.close();
                        cout << "Bloque creado." << endl;
                        contadorBloques++; 
                    }
                    else {
                        cerr << "No se pudo crear el Bloque: " << archivoBloque << endl;
                    }
                }
            }
        }
    }
}

int Disco::calcularEspacioLibreEnBloque(const string& archivoBloque, int capacidadBloque) {
    ifstream archivo(archivoBloque);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo del Bloque: " << archivoBloque << endl;
        return -1;
    }

    int espacioOcupado = 0;
    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.find("Plato") == string::npos && linea.find("=============================================") == string::npos) {
            espacioOcupado += linea.size();
        }
    }
    archivo.close();

    int espacioLibre = capacidadBloque - espacioOcupado;
    return espacioLibre;
}

void Disco::calcularEspacioLibreEnTodosLosBloques(int capacidadBloque) {
    int contadorBloques = 1;
    int sectoresPorBloque = capacidadBloque / this->capacidadPorSector;

    for (int plato = 1; plato <= numPlatos; plato++) {
        for (int superficie = 1; superficie <= 2; superficie++) {
            for (int pista = 1; pista <= pistaPorSuperficie; pista++) {
                for (int sector = 1; sector <= sectoresPorPista; sector += sectoresPorBloque) {
                    string archivoBloque = "Disco/Plato " + to_string(plato) + "/Superficie " + to_string(superficie) + "/Pista " + to_string(pista) + "/Bloque " + to_string(contadorBloques) + ".txt";
                    int espacioLibre = calcularEspacioLibreEnBloque(archivoBloque, capacidadBloque);
                    if (espacioLibre != -1) {
                        cout << "Espacio libre en " << archivoBloque << ": " << espacioLibre << " bytes" << endl;
                    }
                    contadorBloques++;
                }
            }
        }
    }
}