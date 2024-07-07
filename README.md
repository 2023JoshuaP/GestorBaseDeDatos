# Implementación de un Gestor de Base de Datos para el curso de Base de Datos 2 (Universidad Nacional de San Agustín de Arequiá - UNSA)

## Descripción del Proyecto

Este repositorio contiene la implementación de un Sistema de Gestión de Bases de Datos (SGBD) escrito en C++. El proyecto permite la creación y manipulación de un disco virtual simulado, incluyendo la gestión de archivos y la conversión de datos CSV en registros de longitud fija. Es ideal para aquellos interesados en comprender los fundamentos de cómo funcionan los sistemas de gestión de bases de datos a nivel interno.

## Características Principales

1. **Generación de Esquemas**:
   - Transforma archivos CSV en un formato de texto estructurado basado en esquemas definidos. Esto es crucial para manejar y organizar datos de manera eficiente.

2. **Conversión de Registros**:
   - Convierte registros de datos en una longitud fija, facilitando el manejo y almacenamiento uniforme de la información en el disco virtual.

3. **Creación de un Disco Virtual**:
   - Simula un disco con una estructura detallada que incluye platos, pistas, sectores y bloques. Este modelo de disco permite experimentar con conceptos de almacenamiento físico en sistemas de bases de datos.

4. **Gestión de Datos en el Disco Virtual**:
   - Permite llenar los sectores y bloques del disco con registros, mostrar la capacidad del disco, y realizar operaciones de eliminación en el disco.

5. **Gestión de la Memoria en el Buffer Manager**:
   - Permite una mejor gestión para los bloques/páginas del disco, manejo de registros en la inserción, modificación y eliminación de dichos registros y guardarlos en memoria y también en el disco.

## Estructura del Proyecto

El proyecto está organizado en varias carpetas y archivos, cada uno con su propósito específico:

```plaintext
.
├── Acceso
│   └── NotasTerceraUnidad.md
├── Archivos
│   ├── directorio.txt
│   ├── esquemaTitanic.txt
│   ├── registros.txt
│   ├── registrosTitanic.txt
│   └── Titanic.csv
├── Buffer
|   ├── BufferManager.cpp
|   ├── BufferManager.h
|   ├── BufferPool.cpp
|   ├── BufferPool.h
|   ├── Frame.cpp
|   ├── Frame.h
│   ├── main.cpp
│   ├── main.exe
│   ├── PageTable.cpp
│   ├── PageTable.h
│   ├── Pagina.cpp
│   └── Pagina.h
├── Disco
│   ├── Disco.cpp
│   └── Disco.h
├── README.md
└── .vscode
    └── settings.json
```

- **Archivos**: Contiene los archivos de datos y los esquemas utilizados en el proyecto. Estos archivos son fundamentales para los procesos de conversión y almacenamiento. Algunos ejemplos incluyen:
  - `Titanic.csv`: Un archivo CSV de ejemplo utilizado para demostrar la conversión de datos.
  - `esquemaTitanic.txt`: El esquema generado a partir del archivo CSV, que define la estructura de los datos.
  - `registrosTitanic.txt`: Los registros convertidos a partir del CSV, ahora en formato de longitud fija.

- **Buffer**: Incluye los archivos fuente en C++ que manejan las operaciones de buffer y gestión de páginas dentro del disco virtual:
  - `main.cpp`: El archivo principal del proyecto que coordina la ejecución de diferentes operaciones.
  - `Pagina.cpp` y `Pagina.h`: Implementan la lógica para manejar las páginas de datos dentro del disco virtual.
  - `Frame.cpp` y `Frame.h`: Implementan los Frames que almacenan las páginas del disco.
  - `PageTable.cpp` y `PageTable.h`: Implementan una Tabla para los procesos que se realiza en la gestión.
  - `BufferPool.cpp` y `BufferPool.h`: Implementan la creación del Buffer Pool con los datos necesarios, mediador entre el Disco y Buffer Manager.
  - `BufferManager.cpp` y `BufferManager.h`: Implementan la parte mas importante de la gestión de memoria creando el Buffer Pool y la Page Table.

- **Disco**: Contiene la implementación del disco virtual:
  - `Disco.cpp` y `Disco.h`: Estos archivos definen cómo se crea y manipula el disco virtual, incluyendo la configuración de su estructura (platos, pistas, sectores y bloques).

- **.vscode**: Contiene configuraciones específicas para el entorno de desarrollo Visual Studio Code, facilitando la configuración y depuración del proyecto.

- **megatron2**: Contiene la informacion de los archivos que servirán para una mejor gestión de las rutas: información de la estructura del Disco y rutas del Disco.

## Contribuciones

Las contribuciones son bienvenidas. Si estás interesado en mejorar o expandir este proyecto, por favor sigue estos pasos:

1. Haz un fork del repositorio.
2. Crea una nueva rama para tu característica (`git checkout -b feature/nueva-caracteristica`).
3. Realiza un commit de tus cambios (`git commit -am 'Agregar nueva característica'`).
4. Haz push de la rama (`git push origin feature/nueva-caracteristica`).
5. Abre un Pull Request para revisión.