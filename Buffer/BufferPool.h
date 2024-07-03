#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <iostream>
#include <vector>
#include "./Frame.cpp"
using namespace std;

class BufferPool {
    public:
        int capacidadDeFrame;
        vector<Frame> vectorFramesBufferPool;
    public:
        BufferPool();
        ~BufferPool();

        void agregarNuevaPagina(int numFrame, int num´Pagina);
        void mostrarFrameDePagina(int numFrame);
        void lecturaOescrituraPagina(int numFrame);
        void agregarContenidoDePaginaBloque(int numFrame, int numPaginaEliminada);
};

#endif