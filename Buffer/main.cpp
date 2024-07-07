#include <iostream>
#include <queue>
#include "./BufferManager.cpp"
using namespace std;

struct Requerimiento {
    int numPagina;
    char accion;
};

queue<Requerimiento> colaDeRequerimientos;

void visualizarCola() {
    queue<Requerimiento> colaTemp = colaDeRequerimientos;
    if (colaTemp.empty()) {
        cout << "La cola esta vacia." << endl;
        return;
    }
    while (!colaTemp.empty()) {
        Requerimiento req = colaTemp.front();
        colaTemp.pop();
        cout << "Pagina: " << req.numPagina << ", Accion: " << (req.accion == 'L' || req.accion == 'l' ? "Leer" : "Escribir") << endl;
    }
}

void procesarColaEscritura(int paginaLiberar) {
    queue<Requerimiento> colaTemp;
    bool escrituraEncontrada = false;
    bool lecturaEncontrada = false;

    while (!colaDeRequerimientos.empty()) {
        Requerimiento req = colaDeRequerimientos.front();
        colaDeRequerimientos.pop();

        if (req.numPagina == paginaLiberar && (req.accion == 'W' || req.accion == 'w')) {
            cout << "Procesando la Escritura en la Pagina: " << req.numPagina << endl;
            escrituraEncontrada = true;
            break;
        }
        else {
            colaTemp.push(req);
        }
    }

    if (escrituraEncontrada) {
        while (!colaTemp.empty()) {
            colaDeRequerimientos.push(colaTemp.front());
            colaTemp.pop();
        }

        cout << "Cola actualizada despues de liberar la Escritura" << endl;
        visualizarCola();
        return;
    }

    colaTemp = queue<Requerimiento>();
    while (!colaDeRequerimientos.empty()) {
        Requerimiento req = colaDeRequerimientos.front();
        colaDeRequerimientos.pop();

        if (req.numPagina == paginaLiberar && (req.accion == 'L' || req.accion == 'l')) {
            cout << "Procesando la Lectura de la Pagina: " << req.numPagina << endl;
            lecturaEncontrada = true;
            break;
        }
        else {
            colaTemp.push(req);
        }
    }

    if (!escrituraEncontrada && lecturaEncontrada) {
        cout << "Cola actualizada despues de liberar la Pagina en modo Lectura" << endl;
        while (!colaTemp.empty()) {
            colaDeRequerimientos.push(colaTemp.front());
            colaTemp.pop();
        }
        visualizarCola();
    }

    if (!escrituraEncontrada && !lecturaEncontrada) {
        cout << "La cola se mantiene sin liberaciones." << endl;
        visualizarCola();
    }
}

bool noEscrituraEnCola(int pagina) {
    queue<Requerimiento> colaTemp = colaDeRequerimientos;
    while (!colaTemp.empty()) {
        Requerimiento req = colaTemp.front();
        colaTemp.pop();
        if (req.numPagina == pagina && (req.accion == 'W' || req.accion == 'w')) {
            return false;
        }
    }
    return true;
}

void procesarColaLectura(int paginaLiberar) {
    queue<Requerimiento> colaTemp;
    bool escrituraEncontrada = false;
    bool lecturaEncontrada = false;

    while (!colaDeRequerimientos.empty()) {
        Requerimiento req = colaDeRequerimientos.front();
        colaDeRequerimientos.pop();

        if (req.numPagina == paginaLiberar && (req.accion == 'L' || req.accion == 'l')) {
            cout << "Procesando la Escritura en la Pagina: " << req.numPagina << endl;
            escrituraEncontrada = true;
            break;
        }
        else {
            colaTemp.push(req);
        }
    }

    if (escrituraEncontrada) {
        while (!colaTemp.empty()) {
            colaDeRequerimientos.push(colaTemp.front());
            colaTemp.pop();
        }

        cout << "Cola actualizada despues de liberar la Escritura" << endl;
        visualizarCola();
        return;
    }

    colaTemp = queue<Requerimiento>();
    while (!colaDeRequerimientos.empty()) {
        Requerimiento req = colaDeRequerimientos.front();
        colaDeRequerimientos.pop();

        if (req.numPagina == paginaLiberar && (req.accion == 'L' || req.accion == 'l')) {
            cout << "Procesando la Lectura de la Pagina: " << req.numPagina << endl;
            lecturaEncontrada = true;
            break;
        }
        else {
            colaTemp.push(req);
        }
    }

    if (!escrituraEncontrada && lecturaEncontrada) {
        cout << "Cola actualizada despues de liberar la Pagina en modo Lectura" << endl;
        while (!colaTemp.empty()) {
            colaDeRequerimientos.push(colaTemp.front());
            colaTemp.pop();
        }
        visualizarCola();
    }

    if (!escrituraEncontrada && !lecturaEncontrada) {
        cout << "La cola se mantiene sin liberaciones." << endl;
        visualizarCola();
    }
}

int main() {
    BufferManager Buffermanager;
    int opcion;
    int numPagina;
    int numFrame;
    int opcionPaginaGuardado;

    while (opcion != 8) {
        cout << "-----------------------------------------------------" << endl;
        cout << "\t\t   Menu del Buffer\t\t" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "1. Crear Buffer Pool." << endl;
        cout << "2. Obtener una Pagina." << endl;
        cout << "3. Mostrar la Page Table." << endl;
        cout << "4. Liberar uso de Pagina." << endl;
        cout << "5. Despinear una Pagina." << endl;
        cout << "6. Visualizar Cola de Requerimientos." << endl;
        cout << "7. Mostrar contenido de una Pagina." << endl;
        cout << "8. Salir del Buffer." << endl;
        cout << "Ingrese su opcion a ejecutar: ";
        cin >> opcion;
        cout << "-----------------------------------------------------" << endl;

        switch (opcion) {
            case 1: {
                int pesoBytesBloques;
                int numFrames;

                cout << "Ingrese la capacidad del Bloque del Disco: ";
                cin >> pesoBytesBloques;
                cout << "Ingrese la cantidad de Frames a tener: ";
                cin >> numFrames;

                Buffermanager.crearBufferPool(numFrames);
                Buffermanager.establerLimiteDeFrames(pesoBytesBloques);

                cout << "Se creo el Buffer Pool." << endl;
                break;
            }
            case 2: {
                char accionPagina;

                cout << "Pagina que desea obtener: ";
                cin >> numPagina;
                Buffermanager.obtenerUnaPagina(numPagina);

                cout << "Leer (L/l) o Escribir (W/w) en la Pagina? ";
                cin >> accionPagina;

                numFrame = Buffermanager.Pagetable.getNumFrameDeLaPagina(numPagina);

                if (accionPagina == 'L' || accionPagina == 'l') {
                    cout << "Proceso de Lectura de la Pagina." << endl;
                    if (Buffermanager.Pagetable.verificarDirtyDePagina(numPagina) == false) {
                        Buffermanager.Bufferpool.mostrarFrameDePagina(numFrame);
                        Buffermanager.Pagetable.aumentarPinCountDePagina(numPagina);

                        if (noEscrituraEnCola(numPagina) == true) {
                            Requerimiento req = {numPagina, accionPagina};
                            colaDeRequerimientos.push(req);
                            break;
                        }
                        else {
                            cout << "No se puede agregar el proceso de Lectura, hay un proceso de Escritura en la cola." << endl;
                            break;
                        }
                    }
                    else {
                        cout << "Dirty de la Pagina " << numPagina << " esta en 1." << endl;
                        cout << "No se podra procesar el requerimiento hasta que el Dirty Bit sea 0." << endl;
                        cout << "Si desea procesar el requerimiento, se debe guardar el archivo." << endl;
                        cout << "Desea guardar el contenido? Si(1)/No(0): ";
                        cin >> opcionPaginaGuardado;

                        if (opcionPaginaGuardado == 0) {
                            cout << "No se guarda el archivo." << endl;
                        }
                        else if (opcionPaginaGuardado == 1) {
                            Buffermanager.Pagetable.cambiarDirtyBitDePagina(numPagina);
                            Buffermanager.Bufferpool.agregarContenidoDePaginaBloque(numFrame, numPagina);
                            Buffermanager.Pagetable.aumentarPinCountDePagina(numPagina);
                            Requerimiento req = {numPagina, accionPagina};
                            colaDeRequerimientos.push(req);
                        }
                    }
                    break;
                }
                else if (accionPagina == 'W' || accionPagina == 'w') {
                    Buffermanager.Bufferpool.lecturaOescrituraPagina(numFrame);
                    Buffermanager.Pagetable.aumentarPinCountDePagina(numFrame);

                    if (noEscrituraEnCola(numPagina) == true) {
                        Buffermanager.Pagetable.cambiarDirtyBitDePagina(numPagina);
                        Requerimiento req = {numPagina, accionPagina};
                        colaDeRequerimientos.push(req);
                        break;
                    }
                    else {
                        cout << "No se puede agregar el requerimiento debido a la espera de uno." << endl;
                        break;
                    }
                    break;
                }

                break;
            }
            case 3: {
                Buffermanager.mostrarPageTable();
                cout << endl;
                break;
            }
            case 4: {
                int opcionGuardado;
                cout << "Pagina que va a ser Liberada: ";
                cin >> numPagina;

                if (Buffermanager.Pagetable.verificarDirtyDePagina(numPagina) == true) {
                    cout << "El Dirty Bit esta en 1." << endl;
                    cout << "Debe guardar el contenido. Lo desea guardar? Si(1)/No(0): ";
                    cin >> opcionGuardado;

                    if (opcionGuardado == 0) {
                        cout << "La Pagina no se guardo, no puede descontar el Pin Count." << endl;
                    }
                    else if (opcionGuardado == 1) {
                        Buffermanager.Pagetable.cambiarDirtyBitDePagina(numPagina);
                        Buffermanager.Bufferpool.agregarContenidoDePaginaBloque(numFrame, numPagina);
                        Buffermanager.Pagetable.descontarPinCountDePagina(numPagina);
                        procesarColaEscritura(numPagina);
                    }
                    else {
                        cout << "Opcion invalida." << endl;
                    }
                }
                else if (Buffermanager.Pagetable.verificarDirtyDePagina(numPagina) == false) {
                    cout << "El Dirty Bit esta en 0." << endl;
                    Buffermanager.Pagetable.descontarPinCountDePagina(numPagina);
                    procesarColaLectura(numPagina);
                }

                break;
            }
            case 5: {
                cout << "Ingrese la Pagina para despinear: ";
                cin >> numPagina;
                Buffermanager.Pagetable.unpinnedAPagina(numPagina);
                break;
            }
            case 6: {
                visualizarCola();
                break;
            }
            case 7: {
                cout << "Ingrese la Pagina a mostrar: ";
                cin >> numPagina;
                Buffermanager.mostrarPagina(numPagina);
                break;
            }
            case 8: {
                cout << "Saliendo del Buffer..." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida, intente de nuevo." << endl;
                break;
            }
        }
    }
    return 0;
}