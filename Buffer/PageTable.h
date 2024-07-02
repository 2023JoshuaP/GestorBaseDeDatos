#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

class PageTable {
    public:
        int sizeColumnaFrameId;
        int columnasPageTable = 6;
        vector<vector<int>> matrizPageTable;
    public:
        PageTable();
        ~PageTable();
        void mostrarPageTable();
        bool verificarExistenciaDeLaPagina(int numPagina);
        int getNumFrameDeLaPagina(int numPagina);
        void descontarPinCountDePagina(int numPagina);
        void aumentarPinCountDePagina(int numPagina);
        void pinnedAPagina(int numPagina);
        void unpinnedAPagina(int numPagina);
        void cambiarDirtyBitDePaginaA1(int numPagina);
        void cambiarDirtyBitDePaginaA0(int numPagina);
        void renovarLastUsedDePagina(int numPagina);
        void aumentarLastUsedDePagina(int numPagina);
        void actualizarPageTableSolicitandoPaginaNueva(int numPaginaActualizar, int numFilaFrameId);
        void aumentarLastUsedDeTodasLasPaginas(int numFrameIgnorar);
        bool verificarSiPinCountDePaginasEnCero();
        bool verificarSiPaginaTienePinCountEnCero(int numPagina);
        bool verificarSiExistePaginasUnpinned();
        bool verificarSiPaginaEstaPinned(int numPagina);
        bool verificarSiHayFrameParaIgnorar(vector<int>& vectorFramesIgnorar, int FrameIdParaEncontrar);
        void aplicarAlgoritmoLRU(int numPagina, vector<int> &vectorFramesAignorar, int &numPaginaReemplazar, bool &eliminarPageSinEscrituraEnDisco, bool &eliminarPageConEscrituraEnDisco);
        string analizarPageTableParaAgregarPagina(int numPagina);
        bool verificarFramesLlenos();
        void actualizarDetallesDePaginaEliminada(int numPaginaActualizar, int nuevaPaginaActualizar);
        void activarReferentBit(int numPagina);
        void desactivarReferentBit(int numPagina);
        void aplicarAlgoritmoClock(int numPagina, vector<int> &vectorFramesConPinCount0, int &numPaginaReemplazar, bool &eliminarPageSinEscrituraEnDisco, bool &eliminarPageConEscrituraEnDisco);
        void recolectarFramesPinCountEnCeroYUnpinned(vector<int>& vectorFramesPinCountEn0);
        bool verificarSiDirtyBitEstaSucio(int numPagina);
};

#endif