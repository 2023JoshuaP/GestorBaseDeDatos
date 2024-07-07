#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include "./PageTable.cpp"
#include "./BufferPool.cpp"
using namespace std;

class BufferManager {
    public:
        BufferPool Bufferpool;
        PageTable Pagetable;
    public:
        BufferManager();
        ~BufferManager();
        void crearBufferPool(int numFrames);
        void establerLimiteDeFrames(int pesoBytesDeBloques);
        void obtenerUnaPagina(int numPagina);
        void mostrarPageTable();
        void mostrarPagina(int numPagina);
        void dejarDeUsarUnaPagina(int numPagina);
        void liberarPinnedPagina(int numPagina);
        void verificarDirtyPagina(int numPagina);
};

#endif