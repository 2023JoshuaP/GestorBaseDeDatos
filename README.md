# Implementación de un Sistema de Gestión de Bases de Datos (SGBD)

Este proyecto implementa un Sistema de Gestión de Bases de Datos (SGBD) en C++. El SGBD permite la creación de un disco virtual con platos, pistas, sectores y bloques, así como la conversión de archivos CSV a registros de longitud fija y la generación de esquemas de datos.

## Características

- Generación de esquemas y conversión de archivos CSV a texto.
- Conversión de registros a longitud fija.
- Creación de un disco virtual con bloques y sectores.
- Llenado de sectores y bloques con registros de longitud fija.
- Mostrar la capacidad del disco.
- Eliminación del disco.

## Requisitos

- Compilador de C++ compatible con C++11 o superior.
- Sistema operativo Windows, macOS o Linux.

## Estructura del Proyecto

```plaintext
.
├── Archivos
│   ├── directorio.txt
│   ├── esquemaTitanic.txt
│   ├── registros.txt
│   ├── registrosTitanic.txt
│   └── Titanic.csv
├── Buffer
│   ├── main.cpp
│   ├── main.exe
│   ├── Pagina.cpp
│   ├── Pagina.h
├── Disco
│   ├── Disco.cpp
│   └── Disco.h
├── README.md
└── .vscode
    └── settings.json

- **Archivos**: Contiene los archivos de datos y esquemas utilizados en el proyecto.
- **Buffer**: Contiene el archivo principal (`main.cpp`) y los archivos de manejo de páginas (`Pagina.cpp`, `Pagina.h`).
- **Disco**: Contiene la implementación del disco virtual (`Disco.cpp`, `Disco.h`).

## Compilación y Ejecución

Para compilar y ejecutar el proyecto, sigue los siguientes pasos:

1. Navega a la carpeta `Buffer`:
    ```sh
    cd Buffer
    ```

2. Compila el archivo `main.cpp`:
    ```sh
    g++ main.cpp Pagina.cpp ../Disco/Disco.cpp -o main
    ```

3. Ejecuta el archivo compilado:
    ```sh
    ./main
    ```

## Ejemplos de Uso

### Generación de Esquema y Conversión de CSV

1. Coloca tu archivo CSV en la carpeta `Archivos`.
2. Ejecuta el programa y selecciona la opción para generar el esquema y convertir el archivo CSV.
3. El esquema y los registros convertidos se guardarán en la carpeta `Archivos`.

### Creación y Manejo del Disco Virtual

1. Ejecuta el programa y selecciona la opción para crear un disco virtual.
2. Ingresa los detalles necesarios (número de platos, pistas, sectores, bloques, etc.).
3. Utiliza las opciones del menú para agregar registros, mostrar la capacidad del disco o eliminar el disco.

### Agregar Contenido a un Bloque

1. Ejecuta el programa y selecciona la opción para agregar contenido a un bloque.
2. Ingresa el número de la página que deseas agregar.
3. El contenido se guardará en el bloque correspondiente en el disco virtual.

## Contribuciones

Las contribuciones son bienvenidas. Si deseas contribuir, por favor sigue los siguientes pasos:

1. Haz un fork del repositorio.
2. Crea una rama con tu nueva característica (`git checkout -b feature/nueva-caracteristica`).
3. Realiza un commit de tus cambios (`git commit -am 'Agregar nueva característica'`).
4. Haz push de la rama (`git push origin feature/nueva-caracteristica`).
5. Abre un Pull Request.