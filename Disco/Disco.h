#ifndef DISCO_H
#define DISCO_H

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

struct Bloque {
    int tamanio;
    string direccion;
};

struct FieldInfo {
    string fieldName;
    string fieldType;
    int fieldSize;
};

class Disco{
    private:
        int numPlatos;
        int pistaPorSuperficie;
        int sectoresPorPista;
        int capacidadPorSector;
        vector<FieldInfo> schema;
    public:
        /* Constructor del Disco */

        Disco();
        Disco(int platos, int pistas, int sectores, int bytes) : numPlatos(platos), pistaPorSuperficie(pistas), sectoresPorPista(sectores), capacidadPorSector(bytes) {}

        /* Inicializacion del Disco */

        void setNumPlatos(int platos);
        void setPistasPorSuperficie(int pistas);
        void setSectoresPorPista(int sectores);
        void setCapacidadPorSector(int bytes);

        /* Creacion del Disco */

        void crearCarpetaDisco(const string& rutaCarpeta);
        void crearArchivoDisco(const string& rutaArchivo);
        void crearDisco();
        void capacidadDisco();

        /* Eliminar el Disco creado */

        void eliminarDisco();

        /* Funciones para la creacion de Bloques para el Buffer Manager */

        void insertarRegistrosSector(ofstream& archivoSector, ifstream& archivoTexto, int registrosPorSector);
        void llenarRegistrosSector(const string& archivo, const string& schemaFile);
        bool leerSector(const string& sector, string& contenido);
        void crearBloques(int capacidadBloque, int capacidadSector, int cantidadSectores);
        int calcularEspacioLibreEnBloque(const string& archivoBloque, int capacidadBloque);
        void calcularEspacioLibreEnTodosLosBloques(int capacidadBloque);
};

#endif