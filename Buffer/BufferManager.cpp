#include "./BufferManager.h"

BufferManager::BufferManager() {}

BufferManager::~BufferManager() {}

void BufferManager::crearBufferPool(int numFrames) {
    this->Bufferpool.vectorFramesBufferPool.resize(numFrames);

    this->Pagetable.sizeColumnaFrameId = numFrames;
    this->Pagetable.columnPageIdSize = 0;
    this->Pagetable.columnaDirtyIdSize = 0;
    this->Pagetable.columnaPinCountSize = 0;
    //this->Pagetable.columnaLastUsedSize = 0;
    this->Pagetable.columnaRefBitSize = 0;
    this->Pagetable.columnaPinnedSize = 0;

    cout << "Inicializando la Page Table." << endl;
    this->Pagetable.matrizPageTable.resize(numFrames);

    for (int i = 0; i < numFrames; i++) {
        for (int j = 0; j < this->Pagetable.columnasPageTable; j++) {
            this->Pagetable.matrizPageTable[i].resize(this->Pagetable.columnasPageTable);
        }
    }
}

void BufferManager::establerLimiteDeFrames(int pesoBytesDeBloques) {
    this->Bufferpool.capacidadDeFrame = pesoBytesDeBloques;
    for (size_t i = 0; i < this->Bufferpool.vectorFramesBufferPool.size(); i++) {
        this->Bufferpool.vectorFramesBufferPool[i].capacidadDeBytesDelFrame = pesoBytesDeBloques;
    }
}

void BufferManager::obtenerUnaPagina(int numPagina) {
    string resultadoEliminacionCambio = this->Pagetable.analizarPageTableParaAgregarPagina(numPagina);
    cout << "Resultado: " << resultadoEliminacionCambio << endl;
    istringstream iss(resultadoEliminacionCambio);
    string resultado;
    string paginaElimada;

    getline(iss, resultado, ',');
    getline(iss, paginaElimada, ',');

    if (resultado == "eliminarPageSinEscrituraEnDisco") {
        cout << "Eliminar la Pagina sin Escritura." << endl;
        this->Pagetable.mostrarPageTable();

        cout << "Aplicando los cambios al Buffer Pool segun la Page Table." << endl;
        cout << "Mandando a agregar la nueva Pagina." << endl;

        int numFramePagina = this->Pagetable.getNumFrameDeLaPagina(numPagina);

        cout << "Ingresando Pagina al Buffer Pool dentro del vector de Frames (Sin Escritura)." << endl;
        this->Bufferpool.agregarNuevaPagina(numFramePagina, numPagina);
        this->Bufferpool.mostrarFrameDePagina(numFramePagina);
    }
    else if (resultado == "eliminarPageConEscrituraEnDisco") {
        cout << "Eliminar la Pagina Con Escritura." << endl;
        this->Pagetable.mostrarPageTable();

        cout << "Aplicando los cambios al Buffer Pool segun la Page Table." << endl;
        cout << "Mandando a agregar la nueva Pagina." << endl;

        int numFramePagina = this->Pagetable.getNumFrameDeLaPagina(numPagina);
        int numFramePaginaEliminada = this->Pagetable.getNumFrameDeLaPagina(numPagina);
        int numPaginaEliminar = stoi(paginaElimada);

        cout << "Ingresando Pagina al Buffer Pool dentro del vector de Frames (Con Escritura)." << endl;
        this->Bufferpool.agregarContenidoDePaginaBloque(numFramePaginaEliminada, numPaginaEliminar);
        this->Bufferpool.agregarNuevaPagina(numFramePagina, numPagina);
        this->Bufferpool.mostrarFrameDePagina(numFramePagina);
    }
    else {
        cout << "No hay eliminacion." << endl;
        this->Pagetable.mostrarPageTable();

        cout << "Aplicando los cambios al Buffer Pool segun la Page Table." << endl;
        cout << "Mandando a agregar la nueva Pagina." << endl;

        int numFramePagina = this->Pagetable.getNumFrameDeLaPagina(numPagina);

        cout << "Ingresando Pagina al Buffer Pool dentro del vector de Frames." << endl;
        this->Bufferpool.agregarNuevaPagina(numFramePagina, numPagina);
        this->Bufferpool.mostrarFrameDePagina(numFramePagina);
    }

    char opcionPinned;
    cout << "Desea Pinnear la Pagina (S/N)? ";
    cin >> opcionPinned;

    if (opcionPinned == 'S' || opcionPinned == 's') {
        this->Pagetable.pinnedAPagina(numPagina);
    }
    else if (opcionPinned == 'N' || opcionPinned == 'n') {
        cout << "No se va a Pinnear la Pagina." << endl;
    }
}

void BufferManager::mostrarPageTable() {
    cout << endl;
    this->Pagetable.mostrarPageTable();
    cout << endl;
}

void BufferManager::mostrarPagina(int numPagina) {
    if (this->Pagetable.verificarExistenciaDeLaPagina(numPagina) == true) {
        cout << "Existe la Pagina " << numPagina << endl;
        cout << "Se muestra el contenido de la Pagina." << endl;

        int numFramePagina = this->Pagetable.getNumFrameDeLaPagina(numPagina);
        this->Bufferpool.vectorFramesBufferPool[numFramePagina].paginaEnFrame.mostrarContenidoDePagina();
    }
    else {
        cout << "No existe la Pagina " << numPagina << endl;
        cout << "Se procede la solicitud de la nueva Pagina." << endl;      
    }
}

void BufferManager::dejarDeUsarUnaPagina(int numPagina) {
    this->Pagetable.descontarPinCountDePagina(numPagina);
}

void BufferManager::liberarPinnedPagina(int numPagina) {
    this->Pagetable.unpinnedAPagina(numPagina);
}

void BufferManager::verificarDirtyPagina(int numPagina) {
    this->Pagetable.verificarDirtyDePagina(numPagina);  
}