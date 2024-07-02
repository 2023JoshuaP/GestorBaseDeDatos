#include "./Frame.h"

Frame::Frame() {}

Frame::~Frame() {}

void Frame::leerDatosEnPaginaDeFrame(int numPagina) {
    this->paginaEnFrame.recogerRegistros(numPagina);
}