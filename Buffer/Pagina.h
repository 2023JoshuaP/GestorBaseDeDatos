#ifndef PAGINA_H
#define PAGINA_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdint>
using namespace std;

class Pagina {
    public:
        int capacidadTotalDePagina;
        int capacidadUsadaDePagina;
        int capacidadRestanteDePagina;
        vector<string> vectorRegistrosEnPagina;
    public:
        Pagina();
        ~Pagina();
        void recogerRegistros(int numPagina);
        void mostrarContenidoDePagina();
        bool verificarPaginaVacia();
        void leerOescribirPagina();
        void agregarContenido(int numPagina);
        void mostrarDetallesDeCapacidad();
        void actualizarDetallesDeCapacidadDePagina(int capacidadDePagina);
};

#endif