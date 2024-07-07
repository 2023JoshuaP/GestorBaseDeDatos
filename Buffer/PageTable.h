#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

class PageTable {
    public:
        string nameColumnaFrameId = "Frame Id";
        int sizeColumnaFrameId;

        string nameColumnaPageId = "Page Id";
        int columnPageIdSize;

        string nameColumnaDirttyId = "Dirty Bit";
        int columnaDirtyIdSize;

        string nameColumnaPinCount = "Pin Count";
        int columnaPinCountSize;

        //string nameColumnaLastUsed = "Last Used";
        //int columnaLastUsedSize;

        string nameColumnaRefBit = "Ref Bit";
        int columnaRefBitSize;

        string nameColumnaPinned = "Pinned";
        int columnaPinnedSize;
        
        int columnasPageTable = 5;
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
        void cambiarDirtyBitDePagina(int numPagina);
        void renovarLastUsedDePagina(int numPagina);
        void aumentarLastUsedDePagina(int numPagina);
        void actualizarPageTableSolicitandoPaginaNueva(int numPaginaActualizar, int numFilaFrameId);
        void aumentarLastUsedDeTodasLasPaginas(int numFrameIgnorar);
        bool verificarSiHayFrameParaIgnorar(vector<int>& vectorFramesIgnorar, int FrameIdParaEncontrar);
        //void aplicarAlgoritmoLRU(int numPagina, vector<int> &vectorFramesAignorar, int &numPaginaReemplazar, bool &eliminarPageSinEscrituraEnDisco, bool &eliminarPageConEscrituraEnDisco);
        string analizarPageTableParaAgregarPagina(int numPagina);
        bool verificarFramesLlenos();
        bool verificarDirtyDePagina(int numPagina);
        void actualizarDetallesDePaginaEliminada(int numPaginaActualizar, int nuevaPaginaActualizar);
        void activarReferentBit(int numPagina);
        void aplicarAlgoritmoClock(int numPagina, int numFrameAignorar, bool &eliminarPageSinEscrituraEnDisco, bool &eliminarPageConEscrituraEnDisco, int &numPaginaReemplazar);
        void aplicarAlgoritmoClockConCondicionPinned(int numPagina, int numFrameAignorar, bool &eliminarPageSinEscrituraEnDisco, bool &eliminarPageConEscrituraEnDisco, int &numPaginaEliminada);
};

#endif