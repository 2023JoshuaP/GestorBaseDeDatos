#include "PageTable.h"

PageTable::PageTable() {}

PageTable::~PageTable() {}

void PageTable::mostrarPageTable() {
    int numRows = this->matrizPageTable.size();
    int numColumns = this->columnasPageTable;

    cout << "Frame Id \t Page Id \t Dirty Bit \t Pin Count \t Last Used \t Ref Bit \t Pinned";

    for (int i = 0; i < numRows; i++) {
        cout << i << "\t\t";
        for (int j = 0; i < numColumns; j++) {
            cout << this->matrizPageTable[i][j] << "\t\t";
        }
        cout << endl;
    }
}

bool PageTable::verificarExistenciaDeLaPagina(int numPagina) {
    int j = 0;
    for (int i = 0; i < this->sizeColumnaFrameId; i++) {
        if (this->matrizPageTable[i][j] == numPagina) {
            cout << "Pagina " << numPagina << " si existe." << endl;
            return true;
        }
    }
    cout << "Pagina " << numPagina << " no existe." << endl;
    return false;
}

int PageTable::getNumFrameDeLaPagina(int numPagina) {
    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (matrizPageTable[i][j] == numPagina) {
                    cout << "Pagina hallada en el Frame: " << i << endl;;
            }
        }
    }
    else {
        cout << "No existe la Pagina " << numPagina << " para obtener el Frame." << endl;
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j]) {
                cout << this->matrizPageTable[i][j] << ": Pagina si tiene valor." << endl;
            }
            else {
                cout << "Espacion vacio, Page Id confirmado, fila numero " << i << endl;
                return i;
            }
        }
        return INT16_MAX;
    }
}

void PageTable::descontarPinCountDePagina(int numPagina) {
    int numFilaElegida;

    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }

        int columnPinCount = 2;
        this->matrizPageTable[numFilaElegida][columnPinCount] = this->matrizPageTable[numFilaElegida][columnPinCount] - 1;
        cout << "Descuento del Pin Count." << endl;
    }
}

void PageTable::aumentarPinCountDePagina(int numPagina) {
    int numFilaElegida;

    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }

        int columnPinCount = 2;
        this->matrizPageTable[numFilaElegida][columnPinCount] = this->matrizPageTable[numFilaElegida][columnPinCount] + 1;
        cout << "Aumento del Pin Count." << endl;
    }
}

void PageTable::pinnedAPagina(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int columnPinned = 5;
        if (this->matrizPageTable[numFilaElegida][columnPinned] == 1) {
            cout << "La Pagina " << numPagina << " ya esta Pinneada." << endl;
        }
        else {
            cout << "La Pagina " << numPagina << " no esta Pinneada." << endl;
            this->matrizPageTable[numFilaElegida][columnPinned] = 1;
            cout << "Se cambio el Pinned a: " << this->matrizPageTable[numFilaElegida][columnPinned] << endl;
        }
    }
}

void PageTable::unpinnedAPagina(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int columnPinned = 5;
        if (this->matrizPageTable[numFilaElegida][columnPinned] == 1) {
            cout << "La Pagina " << numPagina << " ya esta Pinneada." << endl;
            this->matrizPageTable[numFilaElegida][columnPinned] = 0;
            cout << "Se cambio el Pinned a: " << this->matrizPageTable[numFilaElegida][columnPinned] << endl;
        }
        else {
            cout << "La Pagina " << numPagina << " no esta Pinneada." << endl;
        }
    }
}

void PageTable::cambiarDirtyBitDePaginaA1(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int columnDirty = 1;

        if (this->matrizPageTable[numFilaElegida][columnDirty] == 1) {
            cout << "Dirty Bit de la Pagina " << numPagina << " esta en 1." << endl;
        }
        else {
            cout << "Dirty Bit de la Pagina " << numPagina << " esta en 0." << endl;
            this->matrizPageTable[numFilaElegida][columnDirty] = 0;
            cout << "Se cambia el Dirty Bit: " << this->matrizPageTable[numFilaElegida][columnDirty] << endl;
        }
    }
}

void PageTable::cambiarDirtyBitDePaginaA0(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int columnDirty = 1;

        if (this->matrizPageTable[numFilaElegida][columnDirty] == 1) {
            cout << "Dirty Bit de la Pagina " << numPagina << " esta en 1." << endl;
            this->matrizPageTable[numFilaElegida][columnDirty] = 0;
            cout << "Se cambia el Dirty Bit: " << this->matrizPageTable[numFilaElegida][columnDirty] << endl;
        }
        else {
            cout << "Dirty Bit de la Pagina " << numPagina << " esta en 0." << endl;
        }
    }
}

void PageTable::renovarLastUsedDePagina(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDeLaPagina(numPagina)) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int columnLastUsed = 3;
        this->matrizPageTable[numFilaElegida][columnLastUsed] = 0;
    }
}

void PageTable::aumentarLastUsedDePagina(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int columnLastUsed = 3;
        this->matrizPageTable[numFilaElegida][columnLastUsed] = this->matrizPageTable[numFilaElegida][columnLastUsed] + 1;
    }
}

void PageTable::aumentarLastUsedDeTodasLasPaginas(int numFrameIgnorar) {
    cout << "Actualizando la Page Table." << endl;
    int numPaginaAuxiliar;
    for (int i = 0; i < this->sizeColumnaFrameId; i++) {
        for (int j = 0; j < this->columnasPageTable; j++) {
            if (i == numFrameIgnorar) {
                continue;
            }
            else {
                if (j == 3 && (this->matrizPageTable[i][0]) != 0) {
                    numPaginaAuxiliar = this->matrizPageTable[i][0];
                    this->aumentarLastUsedDePagina(numPaginaAuxiliar);
                    cout << "Frame Id: " << i << " - Aumentando en Last Used." << endl;
                    cout << "Se suma 1 en el Last Used de las demas Paginas." << endl;
                }
            }
        }
    }
    cout << "Last Used aumentado en todas las Paginas." << endl;
}

void PageTable::actualizarPageTableSolicitandoPaginaNueva(int numPaginaActualizar, int numFilaFrameId) {
    cout << "Se esta actualizando la Page Table." << endl;
    for (int j = 0; j < this->columnasPageTable; j++) {
        if (j == 0) {
            this->matrizPageTable[numFilaFrameId][j] = numPaginaActualizar;
            cout << "Frame Id: " << numFilaFrameId;
            cout << "Page Id establecido: " << numPaginaActualizar;
        }
        else if (j == 1) {
            if (this->matrizPageTable[numFilaFrameId][j] == 1) {
                cout << "Frame Id: " << numFilaFrameId << endl;
                cout << "No se cambio el Dirty Bit en 1." << endl;
            }
            else {
                this->matrizPageTable[numFilaFrameId][j] == 0;
                cout << "Frame Id: " << numFilaFrameId << endl;
                cout << "El Dirty Bit es 0." << endl;
            }
        }
        else if (j == 2) {
            this->aumentarPinCountDePagina(numPaginaActualizar);
            cout << "Frame Id: " << numFilaFrameId << endl;
            cout << "Pin Count se establecio." << endl;
        }
        else if (j == 3) {
            this->renovarLastUsedDePagina(numPaginaActualizar);
            cout << "Frame Id: " << numFilaFrameId << endl;
            cout << "Agregando +1 al Last Used de las demas Paginas." << endl;
            int numFrameIgnorar = this->getNumFrameDeLaPagina(numPaginaActualizar);
            this->aumentarLastUsedDePagina(numFrameIgnorar);
        }
        else if (j == 4) {
            this->activarReferentBit(numPaginaActualizar);
            cout << "Frame Id: " << numFilaFrameId << endl;
            cout << "Se estable en 1 el Referent Bit." << endl;
        }
    }
    cout << "Los datos de la Page Table se han actualizado." << endl;
}

bool PageTable::verificarSiHayFrameParaIgnorar(vector<int> &vectorFramesAignorar, int frameIdAencontrar) {
    vector<int>::iterator ptrIt = find(vectorFramesAignorar.begin(), vectorFramesAignorar.end(), frameIdAencontrar);
    if (ptrIt != vectorFramesAignorar.end()) {
        cout << "Elemento Frame a Ignorar encontrado: " << *ptrIt << endl;
        cout << "En la posición: " << distance(vectorFramesAignorar.begin(), ptrIt) << endl;
        return true;
    } 
    else {
        cout << "Elemento no encontrado" << endl;
        return false;
    }
}


void PageTable::aplicarAlgoritmoLRU(int numPagina, vector<int> &vectorFramesAignorar, int &numPaginaReemplazar, bool &eliminarPageSinEscrituraEnDisco, bool &eliminarPageConEscrituraEnDisco) {
    int columnLastUsed = 3;
    int columnPinCount = 2;
    int columnDirtyBit = 1;
    int columnPageId = 0;
    int columnPinned = 5;

    int acumuladorDeMayorLastUsed = 0;
    int frameConMayorLastUsed = 0;
    int numPaginaConMayorLastUsed = 0;

    for (int i = 0; i < this->columnasPageTable; i++) {
        if (verificarSiHayFrameParaIgnorar(vectorFramesAignorar,i)==true) {
            cout<<"Frame a ignorar detectado en el Algoritmo de LRU." << i << endl;
        }
        else {
            if (acumuladorDeMayorLastUsed <= this->matrizPageTable[i][columnLastUsed]) {
                acumuladorDeMayorLastUsed = this->matrizPageTable[i][columnLastUsed];
                frameConMayorLastUsed = i;
                numPaginaConMayorLastUsed = this->matrizPageTable[i][columnPageId];
            }
        }
    }

    cout << "Revisando el Pinned: " << this->matrizPageTable[frameConMayorLastUsed][columnPinned] << endl;
    if (this->matrizPageTable[frameConMayorLastUsed][columnPinned] == 1) {
        cout << "La Pagina " << numPagina << " esta Pinned." << endl;
        cout << "Como la Pagina esta Pinned, no se puede eliminar." << endl;
        cout << "Frame Id: " << frameConMayorLastUsed << " agregado al vector de Frames Ignorados." << endl;
        vectorFramesAignorar.push_back(frameConMayorLastUsed);
        bool paginasPinned = this->verificarSiExistePaginasUnpinned();
        if (paginasPinned == true) {
            aplicarAlgoritmoLRU(numPagina, vectorFramesAignorar, numPaginaConMayorLastUsed, eliminarPageSinEscrituraEnDisco, eliminarPageConEscrituraEnDisco);
        }
        else {
            cout << "No hay Paginas que este Unpinned." << endl;
            eliminarPageSinEscrituraEnDisco = false;
            eliminarPageConEscrituraEnDisco = false;
        }
    }
    else {
        cout << "La Pagina " << numPagina << " no esta Pinned" << endl;
        cout << "Se revisará el Pin Count." << endl;
        if (this->matrizPageTable[frameConMayorLastUsed][columnPinCount] == 0) {
            cout << "Pin Count se encuentra libre." << endl;
            cout << "Verificar el Dirty Bit." << endl;
            if (this->matrizPageTable[frameConMayorLastUsed][columnDirtyBit] == 0) {
                cout << "El Dirty Bit si esta en 0." << endl;
                cout << "Se elimina la Pagina sin escribir en el Disco." << endl;
                actualizarDetallesDePaginaEliminada(numPaginaConMayorLastUsed, numPagina);
                eliminarPageSinEscrituraEnDisco = true;
                eliminarPageConEscrituraEnDisco = false;
            }
            else {
                int option;
                cout << "El Dirty Bit esta en 1." << endl;
                cout << "Como el Dirty esta en 1, desea guardar los cambios en el Disco (1. Si/ 2. No)? ";
                cin >> option;
                if (option == 1) {
                    cout << "Se eliminara la Pagina con escritura en el Disco." << endl;
                    actualizarDetallesDePaginaEliminada(numPaginaConMayorLastUsed, numPagina);
                    eliminarPageConEscrituraEnDisco = true;
                    eliminarPageSinEscrituraEnDisco = false;
                }
                else {
                    cout << "Se elimina la Pagina sin escritura en el Disco." << endl;
                    actualizarDetallesDePaginaEliminada(numPaginaConMayorLastUsed, numPagina);
                    eliminarPageSinEscrituraEnDisco = true;
                    eliminarPageConEscrituraEnDisco = false;
                }
            }
        }
        else {
            cout << "Frame Id: " << frameConMayorLastUsed << " agregado al vector de Frames ignorados." << endl;
            vectorFramesAignorar.push_back(frameConMayorLastUsed);
            cout << "Pin Count no esta libre." << endl;
            bool pinCountsDePaginas=this->verificarSiPinCountDePaginasEnCero();
            bool unppinedPaginas=this->verificarSiExistePaginasUnpinned();
            if (pinCountsDePaginas == true && unppinedPaginas == true) {
                aplicarAlgoritmoLRU(numPagina, vectorFramesAignorar, numPaginaConMayorLastUsed, eliminarPageSinEscrituraEnDisco, eliminarPageConEscrituraEnDisco);
            }
            else {
                cout << "No hay Paginas con Pin Count en 0." << endl;
                eliminarPageSinEscrituraEnDisco = false;
                eliminarPageConEscrituraEnDisco = false;
            }
        }
    }
}

bool PageTable::verificarSiPinCountDePaginasEnCero() {
    int pagina = 0;
    int columnPinCount = 2;
    bool paginaPinCountCero;

    for (int i = 0; i < this->sizeColumnaFrameId; i++) {
        if (this->matrizPageTable[i][columnPinCount] == 0 && this->matrizPageTable[i][pagina]) {
            cout << "Se encontro un Pin Count en 0." << endl;
            return true;
        }
    }

    cout << "No se encontro un Pin Count 0 en las Paginas." << endl;
    return false;
}

bool PageTable::verificarSiPaginaTienePinCountEnCero(int numPagina) {
    int pagina = 0;
    int columnPinCount = 2;

    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][pagina] == numPagina) {
                if (this->matrizPageTable[i][columnPinCount] == 0) {
                    cout << "Pagina " << numPagina << " con el Pin Count 0." << endl;
                    return true;
                }
                else {
                    cout << "Pagina " << numPagina << " con el Pin Count 1." << endl;
                    return false;
                }
            }
        }
    }
    else {
        cout << "No existe la Pagina." << endl;
    }
}

bool PageTable::verificarSiExistePaginasUnpinned() {
    int pagina = 0;
    int columnPinned = 5;
    for (int i = 0; i < this->sizeColumnaFrameId; i++) {
        if (this->matrizPageTable[i][columnPinned] == 0 && this->matrizPageTable[i][pagina]) {
            cout << "Pinned con 0 encontrado." << endl;
            return true;
        }
    }
    cout << "Pinned con 0 no encontrado." << endl;
    return false;
}

bool PageTable::verificarSiPaginaEstaPinned(int numPagina) {
    int pagina = 0;
    int columnPinned = 5;
    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][pagina] == numPagina) {
                if (this->matrizPageTable[i][columnPinned] == 0) {
                    cout << "Pagina " << numPagina << " esta con Pinned en 0." << endl;
                    return false;
                }
                else {
                    cout << "Pagina " << numPagina << " esta con Pinned en 1." << endl;
                    return true;
                }
            }
        }
    }
    else {
        cout << "No existe la Pagina." << endl;
    }
}

string PageTable::analizarPageTableParaAgregarPagina(int numPagina) {
    int numPaginaEliminar;
    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        cout << "Pagina ya encontrada." << endl;
        int numFrame = this->getNumFrameDeLaPagina(numPagina);
        this->actualizarPageTableSolicitandoPaginaNueva(numPagina, numFrame);
        string normal = "Ya encontrado, " + to_string(numPaginaEliminar);
        return normal;
    }
    else {
        bool eliminarPageSinEscrituraEnDisco = false;
        bool eliminarPageConEscrituraEnDisco = false;
        cout << "Pagina no se encuentra en la Page Table." << endl;
        if (this->verificarFramesLlenos() == true) {
            vector<int> vectorFramesPinCount0;
            cout << "Aplicando el algoritmo de Clock." << endl;
            aplicarAlgoritmoClock(numPagina, vectorFramesPinCount0, numPaginaEliminar, eliminarPageSinEscrituraEnDisco, eliminarPageConEscrituraEnDisco);
            if (eliminarPageSinEscrituraEnDisco == true && eliminarPageConEscrituraEnDisco == false) {
                vectorFramesPinCount0.clear();
                string firstBool = "eliminarPageSinEscrituraEnDisco, " + to_string(numPaginaEliminar) + ",";
                return firstBool;
            }
            else if (eliminarPageConEscrituraEnDisco == true && eliminarPageSinEscrituraEnDisco == false) {
                vectorFramesPinCount0.clear();
                string secondBool = "eliminarPageConEscrituraEnDisco, " + to_string(numPaginaEliminar) + ",";
                return secondBool;
            }
            else if (eliminarPageConEscrituraEnDisco == false && eliminarPageSinEscrituraEnDisco == false) {
                vectorFramesPinCount0.clear();
                string thirdBool = "yaEncontrado, " + to_string(numPaginaEliminar) + ",";
                return thirdBool;
            }
        }
        else {
            cout << "Frames no estan llenos, a un  hay espacio." << endl;
            int numFrame = this->getNumFrameDeLaPagina(numPagina);
            this->actualizarPageTableSolicitandoPaginaNueva(numPagina, numFrame);
            string normal = "noEncontradoFramesDisponibles, " + to_string(numPaginaEliminar);
            return normal;
        }
    }
}

bool PageTable::verificarFramesLlenos() {
    int acumulador = 0;
    int j = 0;
    for (int i = 0; i < this->sizeColumnaFrameId; i++) {
        if (this->matrizPageTable[i][j]) {
            continue;
        }
        else {
            acumulador++;
        }
    }
    if (acumulador != 0) {
        return false;
    }
    return true;
}

void PageTable::actualizarDetallesDePaginaEliminada(int numPaginaEliminar, int nuevaPaginaIngresar) {
    int numFilaElegida;
    int numFilaFrame = this->getNumFrameDeLaPagina(numPaginaEliminar);
    if (this->verificarExistenciaDeLaPagina(numPaginaEliminar) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPaginaEliminar) {
                cout << "Pagina a eliminar: " << numPaginaEliminar;
                numFilaElegida = i;
            }
        }
        for (int j = 0; j < this->columnasPageTable; j++) {
            this->matrizPageTable[numFilaElegida][j] = 0;
        }
    }

    cout << "Agregando datos de Nuevo Registro." << endl;
    cout << "Actualizando la Page Table." << endl;

    for (int j = 0; j < this->columnasPageTable; j++) {
        if (j == 0) {
            this->matrizPageTable[numFilaElegida][j] = nuevaPaginaIngresar;
            cout << "Frame Id: " << numFilaElegida << endl;
            cout << "Page Id establecido: " << nuevaPaginaIngresar << endl;
        }
        else if (j == 1) {
            this->matrizPageTable[numFilaElegida][j] = 0;
            cout << "Frame Id: " << numFilaElegida << endl;
            cout << "Dirty Bit esta en 0." << endl;
        }
        else if (j == 2) {
            this->aumentarPinCountDePagina(nuevaPaginaIngresar);
            cout << "Frame Id: " << numFilaFrame << endl;
            cout << "Pin Count establecido." << endl;
        }
        else if (j == 3) {
            this->renovarLastUsedDePagina(nuevaPaginaIngresar);
            cout << "Frame Id: " << numFilaElegida << endl;
            cout << "Agregando +1 a Last Used de todos los demás Pages" << endl;
            int numFilaElegida = this->getNumFrameDeLaPagina(nuevaPaginaIngresar);
            this->aumentarLastUsedDeTodasLasPaginas(numFilaElegida);
        }
        else if (j == 4) {
            this->matrizPageTable[numFilaElegida][j] = 1;
            cout << "Frame Id: " << numFilaElegida << endl;
            cout << "Se establecio 1 en el Ref Bit." << endl;
        }
    }
    cout << "Datos actualizados en la Page Table." << endl;
}

void PageTable::activarReferentBit(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int numColumnaPinCount = 4;

        if (this->matrizPageTable[numFilaElegida][numColumnaPinCount] == 1) {
            cout << "Ref Bit ya se encuentra activado" << endl;
        }
        else {
            this->matrizPageTable[numFilaElegida][numColumnaPinCount] = 1;
            cout << "Se activo Ref Bit a página: " << numPagina << endl;
        }
    }
}

void PageTable::desactivarReferentBit(int numPagina) {
    int numFilaElegida;
    if (this->verificarExistenciaDeLaPagina(numPagina) == true) {
        int j = 0;
        for (int i = 0; i < this->sizeColumnaFrameId; i++) {
            if (this->matrizPageTable[i][j] == numPagina) {
                numFilaElegida = i;
            }
        }
        int numColumnaPinCount = 4;

        if (this->matrizPageTable[numFilaElegida][numColumnaPinCount] == 0) {
            cout << "Ref Bit ya se encuentra desactivado" << endl;
        }
        else {
            this->matrizPageTable[numFilaElegida][numColumnaPinCount] = 0;
            cout << "Se desactiva Ref Bit a página: " << numPagina << endl;
        }
    }
}

void PageTable::aplicarAlgoritmoClock(int numPagina, vector<int> &vectorFramesConPinCount0, int &numPaginaReemplazar, bool &eliminarPageSinEscrituraEnDisco, bool &eliminarPageConEscrituraEnDisco) {
    if (this->verificarSiExistePaginasUnpinned() == true && this->verificarSiPinCountDePaginasEnCero() == true) {
        vectorFramesConPinCount0.clear();
        this->recolectarFramesPinCountEnCeroYUnpinned(vectorFramesConPinCount0);
        if (vectorFramesConPinCount0.empty()) {
            cout << "No se encontro un Frame unpinned y ni un Pin Count 0." << endl;
            eliminarPageSinEscrituraEnDisco = false;
            eliminarPageConEscrituraEnDisco = false;
        }
        else {
            cout << "Si existe uno o mas Frames unpinned y Pin Count 0." << endl;
            int clockHand;
            
        }
    }
}