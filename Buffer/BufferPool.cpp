#include "./BufferPool.h"

BufferPool::BufferPool() {}

BufferPool::~BufferPool() {}

void BufferPool::agregarNuevaPagina(int numFrame, int numPagina) {
    if (this->vectorFramesBufferPool[numFrame].paginaEnFrame.vectorRegistrosEnPagina.empty()) {
        this->vectorFramesBufferPool[numFrame].leerDatosEnPaginaDeFrame(numPagina);
    }
    else {
        this->vectorFramesBufferPool[numFrame].paginaEnFrame.vectorRegistrosEnPagina.clear();
        this->vectorFramesBufferPool[numFrame].leerDatosEnPaginaDeFrame(numPagina);
    }
}

void BufferPool::mostrarFrameDePagina(int numFrame) {
    this->vectorFramesBufferPool[numFrame].paginaEnFrame.mostrarContenidoDePagina();
}

void BufferPool::lecturaOescrituraPagina(int numFrame) {
    this->vectorFramesBufferPool[numFrame].paginaEnFrame.leerOescribirPagina();
}

void BufferPool::agregarContenidoDePaginaBloque(int numFrame, int numPaginaEliminada) {
    this->vectorFramesBufferPool[numFrame].paginaEnFrame.agregarContenido(numPaginaEliminada);
}